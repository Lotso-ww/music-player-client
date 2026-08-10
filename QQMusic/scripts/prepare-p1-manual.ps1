$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $PSScriptRoot
$sourceRoot = Join-Path $projectRoot 'musics'
$fixtureRoot = Join-Path $projectRoot 'test-fixtures\p1-manual'

if (-not (Test-Path $sourceRoot)) { throw "Music sample directory not found: $sourceRoot" }

Remove-Item -LiteralPath $fixtureRoot -Recurse -Force -ErrorAction SilentlyContinue
New-Item -ItemType Directory -Path $fixtureRoot -Force | Out-Null
New-Item -ItemType Directory -Path (Join-Path $fixtureRoot 'nested\level-1') -Force | Out-Null
New-Item -ItemType Directory -Path (Join-Path $fixtureRoot 'duplicates') -Force | Out-Null
New-Item -ItemType Directory -Path (Join-Path $fixtureRoot 'invalid') -Force | Out-Null

$samples = @(Get-ChildItem -LiteralPath $sourceRoot -Filter '*.mp3' -File | Select-Object -First 3)
if ($samples.Count -lt 3) { throw 'At least three MP3 samples are required in musics.' }
foreach ($sample in $samples) {
    Copy-Item -LiteralPath $sample.FullName -Destination (Join-Path $fixtureRoot $sample.Name)
    $lrc = [System.IO.Path]::ChangeExtension($sample.Name, '.lrc')
    $lrcPath = Join-Path $sourceRoot $lrc
    if (Test-Path $lrcPath) { Copy-Item -LiteralPath $lrcPath -Destination (Join-Path $fixtureRoot $lrc) }
}

Copy-Item -LiteralPath ((Get-ChildItem -LiteralPath $sourceRoot -Filter '*.mp3' -File | Select-Object -Skip 3 -First 1).FullName) `
    -Destination (Join-Path $fixtureRoot 'nested\level-1\nested-song.mp3')
Copy-Item -LiteralPath $samples[0].FullName `
    -Destination (Join-Path $fixtureRoot 'duplicates\same-content-copy.mp3')

Set-Content -LiteralPath (Join-Path $fixtureRoot 'invalid\not-audio.mp3') -Value 'invalid audio fixture' -Encoding ASCII
Set-Content -LiteralPath (Join-Path $fixtureRoot 'ignore-me.txt') -Value 'unsupported file fixture' -Encoding UTF8
 $manualCases = @(
    "P1 manual acceptance fixtures",
    "",
    "1. Scan this directory: discover root songs and nested/level-1, ignore ignore-me.txt.",
    "2. duplicates/same-content-copy.mp3 has the same content as the root 2002 song: duplicate count should increase.",
    "3. invalid/not-audio.mp3 is a failure fixture: no crash or infinite wait.",
    ("4. After the first scan, close the app; move {0} to nested/level-1/relocated-song.mp3 and scan again. Check re-association instead of a duplicate." -f $samples[1].Name),
    "5. Delete nested/level-1/nested-song.mp3 and wait about 10 seconds. The record remains but becomes unavailable; favorites/history remain.",
    ("6. Play {0} and test lyrics minimize, tray, topmost, lock, opacity and position restore." -f $samples[0].Name)
 ) -join [Environment]::NewLine
Set-Content -LiteralPath (Join-Path $fixtureRoot 'MANUAL-CASES.txt') -Value $manualCases -Encoding UTF8

Write-Output "P1 manual fixtures prepared: $fixtureRoot"
