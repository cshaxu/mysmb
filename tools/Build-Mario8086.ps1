param(
    [Parameter(Mandatory=$true)][string]$SdkIncludeDirectory,
    [Parameter(Mandatory=$true)][string]$WindowsLibrary,
    [Parameter(Mandatory=$true)][string]$RuntimeLibrary,
    [Parameter(Mandatory=$true)][string]$RomPath
)
# Additional local products, with no change to the accelerated16c/16w targets.
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$compiler=Join-Path $PSScriptRoot 'dos16/cl16.exe'
$linker=Join-Path $PSScriptRoot 'dos16/link16.exe'
$dos=Join-Path $repository 'build/86c'
$windows=Join-Path $repository 'build/86w'
& (Join-Path $PSScriptRoot 'Build-OpenNt16Dos.ps1') -Compiler $compiler -Linker $linker -IncludeDirectory (Join-Path $repository 'src/app-mario') -SourceRoot (Join-Path $repository 'src/app-mario') -RuntimeDirectory (Join-Path $PSScriptRoot 'dos16/runtime/LIB') -OutputDirectory $dos -RomPath $RomPath -InstructionSet 8086
if($LASTEXITCODE){throw '8086 DOS build failed'}
& (Join-Path $PSScriptRoot 'Build-OpenNt16Windows.ps1') -Compiler $compiler -Linker $linker -SdkIncludeDirectory $SdkIncludeDirectory -WindowsLibrary $WindowsLibrary -RuntimeLibrary $RuntimeLibrary -DosStub (Join-Path $dos 'mysmb-dos16.exe') -RomPath $RomPath -OutputDirectory $windows -InstructionSet 8086
if($LASTEXITCODE){throw '8086 Win16 build failed'}
& python (Join-Path $PSScriptRoot 'Audit-Dos16Isa.py') --directory $dos --output (Join-Path $dos 'isa.json')
if($LASTEXITCODE){throw '8086 DOS inventory failed'}
& python (Join-Path $PSScriptRoot 'Audit-Dos16Isa.py') --ne (Join-Path $windows 'mysmb16.exe') --output (Join-Path $windows 'isa.json')
if($LASTEXITCODE){throw '8086 Win16 inventory failed'}
foreach($receipt in @((Join-Path $dos 'isa.json'),(Join-Path $windows 'isa.json'))) {
    if((Get-Content -Raw -LiteralPath $receipt | ConvertFrom-Json).candidateCount -ne 0) {
        throw 'Unresolved post8086 executable-code candidates; publication blocked'
    }
}
Write-Output '8086 DOS and Win16 products validated; publish through Package-MySMB.ps1 with both ISA receipts.'
