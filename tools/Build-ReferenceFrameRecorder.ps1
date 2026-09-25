[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$NnesSourceDirectory,
    [Parameter(Mandatory = $true)]
    [string]$OutputDirectory
)

$ErrorActionPreference = 'Stop'
$sourceRoot = (Resolve-Path -LiteralPath $NnesSourceDirectory).Path
$outputRoot = [System.IO.Path]::GetFullPath($OutputDirectory)
$profileAssets = Join-Path (Split-Path -Parent $sourceRoot) 'nxvm-assets/profiles-nxvm'
$recorder = Join-Path $PSScriptRoot 'reference_frame_recorder.c'
$sourceCmake = Join-Path $sourceRoot 'CMakeLists.txt'
 $template = Join-Path $sourceRoot 'assets/binary-mynes/mynes.ini'
if (-not (Test-Path -LiteralPath $template)) {
    $template = Join-Path $sourceRoot 'assets/mynes/mynes.ini'
}
if (-not (Test-Path -LiteralPath $sourceCmake) -or -not (Test-Path -LiteralPath $recorder) -or
    -not (Test-Path -LiteralPath $template)) {
    throw 'The local nnes source root or project-owned recorder source is unavailable.'
}
New-Item -ItemType Directory -Path $outputRoot -Force | Out-Null
$outputAssets = Join-Path $outputRoot 'assets/binary-mynes'
New-Item -ItemType Directory -Path $outputAssets -Force | Out-Null
Copy-Item -LiteralPath $template -Destination (Join-Path $outputAssets 'mynes.ini') -Force
$cmakeLists = Join-Path $outputRoot 'CMakeLists.txt'
$escapedNnes = $sourceRoot.Replace('\', '/')
$escapedRecorder = $recorder.Replace('\', '/')
@"
cmake_minimum_required(VERSION 3.20)
project(mysmb_reference_frame_recorder C)
add_subdirectory("$escapedNnes" nnes EXCLUDE_FROM_ALL)
add_executable(mysmb_reference_frame_recorder "$escapedRecorder")
target_include_directories(mysmb_reference_frame_recorder PRIVATE
    "$escapedNnes/src/app-mynes" "$escapedNnes/src/lib")
target_link_libraries(mysmb_reference_frame_recorder PRIVATE mynes-core-driver)
"@ | Set-Content -LiteralPath $cmakeLists -Encoding ascii
cmake -S $outputRoot -B (Join-Path $outputRoot 'build') "-DNXVM_PROFILE_ASSETS_ROOT=$profileAssets"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build (Join-Path $outputRoot 'build') --target mysmb_reference_frame_recorder --parallel
exit $LASTEXITCODE
