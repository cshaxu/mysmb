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
$recorder = Join-Path $PSScriptRoot 'reference_frame_recorder.c'
$sourceCmake = Join-Path $sourceRoot 'CMakeLists.txt'
if (-not (Test-Path -LiteralPath $sourceCmake) -or
    -not (Test-Path -LiteralPath $recorder)) {
    throw 'The local nnes source root or project-owned recorder source is unavailable.'
}
New-Item -ItemType Directory -Path $outputRoot -Force | Out-Null
$cmakeLists = Join-Path $outputRoot 'CMakeLists.txt'
$escapedNnes = $sourceRoot.Replace('\', '/')
$escapedRecorder = $recorder.Replace('\', '/')
@'
cmake_minimum_required(VERSION 3.20)
project(mysmb_reference_frame_recorder C)

# The NXVM root configures every product and its governance assertions.  The
# recorder only needs the immutable MyNES core dependency graph, so assemble
# that graph explicitly in this isolated build instead of treating the full
# NXVM product as a subproject.
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
add_executable(mysmb_reference_frame_recorder "@RECORDER@")
target_include_directories(mysmb_reference_frame_recorder PRIVATE
    "@NNES@/src/app-mynes" "@NNES@/src/lib")
target_link_libraries(mysmb_reference_frame_recorder PRIVATE mynes-core-driver)
'@.Replace('@NNES@', $escapedNnes).Replace('@RECORDER@', $escapedRecorder) |
    Set-Content -LiteralPath $cmakeLists -Encoding ascii
cmake -S $outputRoot -B (Join-Path $outputRoot 'build')
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build (Join-Path $outputRoot 'build') --target mysmb_reference_frame_recorder --parallel
exit $LASTEXITCODE
