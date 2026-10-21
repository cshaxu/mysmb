param(
    [Parameter(Mandatory=$true)][string]$SdkIncludeDirectory,
    [Parameter(Mandatory=$true)][string]$WindowsLibrary,
    [Parameter(Mandatory=$true)][string]$RuntimeLibrary,
    [Parameter(Mandatory=$true)][string]$RomPath
)
# One publication boundary for every supported Mario executable profile.
$ErrorActionPreference='Stop'
foreach($inputName in @('SdkIncludeDirectory','WindowsLibrary','RuntimeLibrary','RomPath')) {
    Set-Variable -Name $inputName -Value (Resolve-Path -LiteralPath (Get-Variable -Name $inputName -ValueOnly)).Path
}
$repository=Split-Path -Parent $PSScriptRoot
$compiler=Join-Path $PSScriptRoot 'dos16/cl16.exe'
$linker=Join-Path $PSScriptRoot 'dos16/link16.exe'
Push-Location $repository
try {
    foreach($width in @('x64','x86')) {
        $tree="build/ninja-ccache-$width-release"
        if(!(Test-Path -LiteralPath "$tree/CMakeCache.txt")) {
            throw "Configure the $width Ninja/ccache preset before publication"
        }
        & cmake -S . -B $tree "-DMYSMB_ROM_PATH:FILEPATH=$RomPath"
        if($LASTEXITCODE){throw "Native $width resource configure failed"}
        & cmake --build --preset "build-$width"
        if($LASTEXITCODE){throw "Native $width build failed"}
        & ctest --preset "test-$width"
        if($LASTEXITCODE){throw "Native $width tests failed"}
    }
    & (Join-Path $PSScriptRoot 'Build-OpenNt16Dos.ps1') -Compiler $compiler -Linker $linker -IncludeDirectory (Join-Path $repository 'src/app-mario') -SourceRoot (Join-Path $repository 'src/app-mario') -RuntimeDirectory (Join-Path $PSScriptRoot 'dos16/runtime/LIB') -OutputDirectory (Join-Path $repository 'build/16c') -RomPath $RomPath
    if($LASTEXITCODE){throw 'Accelerated DOS build failed'}
    & (Join-Path $PSScriptRoot 'Build-OpenNt16Windows.ps1') -Compiler $compiler -Linker $linker -SdkIncludeDirectory $SdkIncludeDirectory -WindowsLibrary $WindowsLibrary -RuntimeLibrary $RuntimeLibrary -DosStub (Join-Path $repository 'build/16c/mysmb-dos16.exe') -RomPath $RomPath -OutputDirectory (Join-Path $repository 'build/16w')
    if($LASTEXITCODE){throw 'Win16 build failed'}
    & (Join-Path $PSScriptRoot 'Build-Mario8086.ps1') -SdkIncludeDirectory $SdkIncludeDirectory -WindowsLibrary $WindowsLibrary -RuntimeLibrary $RuntimeLibrary -RomPath $RomPath
    if($LASTEXITCODE){throw '8086 profile builds failed'}
    & (Join-Path $PSScriptRoot 'Package-MySMB.ps1') -Dos16Executable build/16c/mysmb-dos16.exe -Win16Executable build/16w/mysmb16.exe -Dos86Executable build/86c/mysmb-dos16.exe -Win86Executable build/86w/mysmb16.exe -Dos86IsaReceipt build/86c/isa.json -Win86IsaReceipt build/86w/isa.json -Win32Executable build/ninja-ccache-x86-release/src/app-mario/mysmb-win32-x86.exe -Win64Executable build/ninja-ccache-x64-release/src/app-mario/mysmb-win32-x64.exe -Win32BuildDirectory build/ninja-ccache-x86-release -Win64BuildDirectory build/ninja-ccache-x64-release
    if($LASTEXITCODE){throw 'Six-product publication failed'}
} finally {Pop-Location}
