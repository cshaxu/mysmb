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
$probe = Join-Path $PSScriptRoot 'reference_bump_probe.c'
if (-not (Test-Path -LiteralPath (Join-Path $sourceRoot 'CMakeLists.txt')) -or
    -not (Test-Path -LiteralPath $probe)) {
    throw 'The local nnes source root or project-owned bump probe is unavailable.'
}
New-Item -ItemType Directory -Path $outputRoot -Force | Out-Null
$escapedNnes = $sourceRoot.Replace('\', '/')
$escapedProbe = $probe.Replace('\', '/')
@'
cmake_minimum_required(VERSION 3.20)
project(mysmb_reference_bump_probe C)
function(mynes_enable_strict_warnings target)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    elseif(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    endif()
endfunction()
add_subdirectory("@NNES@/src/lib" nxvm-lib EXCLUDE_FROM_ALL)
add_subdirectory("@NNES@/src/common" nxvm-common EXCLUDE_FROM_ALL)
add_subdirectory("@NNES@/src/app-mynes/core" mynes-core EXCLUDE_FROM_ALL)
add_executable(mysmb_reference_bump_probe "@PROBE@")
target_include_directories(mysmb_reference_bump_probe PRIVATE
    "@NNES@/src/app-mynes" "@NNES@/src/lib")
target_link_libraries(mysmb_reference_bump_probe PRIVATE mynes-core-driver)
'@.Replace('@NNES@', $escapedNnes).Replace('@PROBE@', $escapedProbe) |
    Set-Content -LiteralPath (Join-Path $outputRoot 'CMakeLists.txt') -Encoding ascii
cmake -S $outputRoot -B (Join-Path $outputRoot 'build')
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build (Join-Path $outputRoot 'build') --target mysmb_reference_bump_probe --parallel
exit $LASTEXITCODE
