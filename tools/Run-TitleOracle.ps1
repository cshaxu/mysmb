[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$NnesOracle,
    [Parameter(Mandatory = $true)]
    [string]$OwnerRom,
    [Parameter(Mandatory = $true)]
    [string]$NativeOracle,
    [ValidateRange(1, 100000)]
    [int]$Slices = 1200
)

$ErrorActionPreference = 'Stop'

foreach ($path in @($NnesOracle, $OwnerRom, $NativeOracle)) {
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
        throw "Missing local oracle input: $path"
    }
}

$savedRom = $env:MYNES_OWNER_NROM_ROM
$savedSlices = $env:MYNES_OWNER_SLICES
try {
    $env:MYNES_OWNER_NROM_ROM = (Resolve-Path -LiteralPath $OwnerRom).Path
    $env:MYNES_OWNER_SLICES = [string]$Slices
    $reference = & (Resolve-Path -LiteralPath $NnesOracle).Path
    if ($LASTEXITCODE -ne 0) { throw "nnes oracle failed with exit code $LASTEXITCODE" }
}
finally {
    $env:MYNES_OWNER_NROM_ROM = $savedRom
    $env:MYNES_OWNER_SLICES = $savedSlices
}

 $native = & (Resolve-Path -LiteralPath $NativeOracle).Path
if ($LASTEXITCODE -ne 0) { throw "Native title oracle failed with exit code $LASTEXITCODE" }
Write-Output "checkpoint=title-after-$Slices-slices $native"
Write-Output "reference=$reference"
Write-Output 'disposition=The native side is the M1 title-command transfer only; the reference checkpoint also includes subsequent ROM title-route updates. Hash equality is deferred to M2 state-route translation.'
