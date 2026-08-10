$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $PSScriptRoot
$qtRoot = 'D:\QT5\5.14.2\mingw73_64'
$toolRoot = 'D:\QT5\Tools\mingw730_64\bin'
$qmake = Join-Path $qtRoot 'bin\qmake.exe'
$make = Join-Path $toolRoot 'mingw32-make.exe'

if (-not (Test-Path $qmake) -or -not (Test-Path $make)) {
    throw 'Qt 5.14.2 MinGW 7.3 toolchain was not found under D:\QT5.'
}

$env:PATH = "$toolRoot;$qtRoot\bin;$env:PATH"
$env:QT_QPA_PLATFORM = 'offscreen'
Push-Location $projectRoot
try {
    Remove-Item -LiteralPath 'test-build\p1-ui' -Recurse -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath 'test-build\p1-moc' -Recurse -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath 'test-build\p1-obj' -Recurse -Force -ErrorAction SilentlyContinue
    & $qmake p1-tests.pro CONFIG+=debug
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    & $make -f Makefile -j2
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $resultFile = 'test-build\p1-results.txt'
    & '.\test-build\bin\qqmusic_p1_tests.exe' -o "$resultFile,txt"
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    Get-Content -LiteralPath $resultFile | Select-String -Pattern 'Totals:'
    Write-Output 'P1 automated tests passed.'
    exit 0
}
finally {
    Pop-Location
}
