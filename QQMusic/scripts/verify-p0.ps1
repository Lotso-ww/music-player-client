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
Push-Location $projectRoot
try {
    & $qmake QQMusic.pro CONFIG+=debug
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    & $make -f Makefile -j2
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    Remove-Item -LiteralPath 'test-build' -Recurse -Force -ErrorAction SilentlyContinue
    & $qmake p0-tests.pro CONFIG+=debug
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    & $make -f Makefile -j2
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    $env:QT_QPA_PLATFORM = 'offscreen'
    & '.\test-build\bin\qqmusic_tests.exe' -v1
    exit $LASTEXITCODE
}
finally {
    Pop-Location
}
