$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $PSScriptRoot
$backendRoot = Join-Path $projectRoot 'backend'
$envFile = Join-Path $backendRoot '.env'

if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
    throw 'Docker Engine with Docker Compose is required for P2A validation. See backend/README.md.'
}
if (-not (Test-Path $envFile)) {
    throw 'Create backend/.env from backend/.env.example and set non-default local passwords before validation.'
}

Push-Location $backendRoot
try {
    & docker compose --env-file .env -f docker-compose.yml config -q
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    & docker compose --env-file .env -f docker-compose.yml up --build --wait
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    $health = Invoke-WebRequest -UseBasicParsing -Uri 'http://localhost:8080/api/v1/health'
    if ($health.StatusCode -ne 200) { throw "Health endpoint returned $($health.StatusCode)." }
    $body = $health.Content | ConvertFrom-Json
    if ($body.data.status -ne 'ok' -or $body.data.database -ne 'available') {
        throw 'Health response does not confirm MySQL availability.'
    }
    if (-not $health.Headers['X-Request-Id'] -or $body.request_id -ne $health.Headers['X-Request-Id']) {
        throw 'Health response request ID is missing or inconsistent.'
    }

    try {
        Invoke-WebRequest -UseBasicParsing -Uri 'http://localhost:8080/api/v1/not-found' | Out-Null
        throw 'Unknown API route unexpectedly succeeded.'
    } catch [System.Net.WebException] {
        $response = $_.Exception.Response
        if ($response.StatusCode.value__ -ne 404) { throw }
        $reader = New-Object System.IO.StreamReader($response.GetResponseStream())
        $error = ($reader.ReadToEnd() | ConvertFrom-Json)
        if ($error.error.code -ne 'route_not_found' -or -not $error.error.request_id) {
            throw '404 response does not use the standard error contract.'
        }
    }
    Write-Output 'P2A Docker, MySQL, HTTP, JSON, and error-contract validation passed.'
} finally {
    Pop-Location
}
