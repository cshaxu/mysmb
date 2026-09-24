param(
    [Parameter(Mandatory = $true)]
    [string]$ReferenceTrace,
    [Parameter(Mandatory = $true)]
    [string]$NativeTrace,
    [ValidateSet('vertical')]
    [string]$Mirroring = 'vertical',
    [int]$StartSample = 0,
    [int]$EndSample = -1
)

$ErrorActionPreference = 'Stop'
$recordSize = 4395
$headerSize = 12

function Read-M2Trace([string]$Path, [byte[]]$Magic) {
    $bytes = [System.IO.File]::ReadAllBytes($Path)
    if ($bytes.Length -lt $headerSize) { throw 'Trace is shorter than its header.' }
    for ($index = 0; $index -lt 8; ++$index) {
        if ($bytes[$index] -ne $Magic[$index]) { throw 'Trace kind or version is unsupported.' }
    }
    $count = [System.BitConverter]::ToUInt32($bytes, 8)
    if ($count -gt 600) { throw 'Trace exceeds the 600-sample containment limit.' }
    if ($bytes.Length -ne $headerSize + [int64]$count * $recordSize) {
        throw 'Trace length does not match its declared record count.'
    }
    return @{ Bytes = $bytes; Count = $count }
}

function Compare-M2Range($Reference, $Native, [int]$ReferenceOffset,
                         [int]$NativeOffset, [int]$Count, [int]$Sample,
                         $Result) {
    $different = $false
    for ($index = 0; $index -lt $Count; ++$index) {
        if ($Reference[$ReferenceOffset + $index] -ne $Native[$NativeOffset + $index]) {
            ++$Result.DifferentBytes
            if ($Result.FirstOffset -lt 0) { $Result.FirstOffset = $index }
            $different = $true
        }
    }
    if ($different) {
        ++$Result.DifferentSamples
        if ($Result.FirstSample -lt 0) { $Result.FirstSample = $Sample }
    }
}

function New-M2Result([string]$Field) {
    return [pscustomobject]@{
        Field = $Field
        DifferentSamples = 0
        DifferentBytes = 0
        FirstSample = -1
        FirstOffset = -1
    }
}

$reference = Read-M2Trace $ReferenceTrace ([byte[]](77,83,70,82,1,0,0,0))
$native = Read-M2Trace $NativeTrace ([byte[]](77,83,70,78,1,0,0,0))
if ($reference.Count -ne $native.Count) { throw 'Trace sample counts differ.' }
if ($EndSample -lt 0) { $EndSample = [int]$reference.Count - 1 }
if ($StartSample -lt 0 -or $EndSample -lt $StartSample -or
    $EndSample -ge $reference.Count) { throw 'Sample range is outside the trace.' }

$ram = New-M2Result 'cpu-ram'
$nameTable0 = New-M2Result 'ciram-page-0'
$nameTable1 = New-M2Result 'ciram-page-1'
$palette = New-M2Result 'palette'
$oam = New-M2Result 'oam'
$ppu = @(
    (New-M2Result 'ppu-control'),
    (New-M2Result 'ppu-mask'),
    (New-M2Result 'ppu-name-table'),
    (New-M2Result 'ppu-scroll-x'),
    (New-M2Result 'ppu-scroll-y'),
    (New-M2Result 'ppu-address-low'),
    (New-M2Result 'ppu-address-high')
)
for ($sample = $StartSample; $sample -le $EndSample; ++$sample) {
    $record = $headerSize + $sample * $recordSize
    # Both traces reserve four leading ordinal bytes.  They are timing labels,
    # not comparable output because a native tick has no physical PPU revision.
    Compare-M2Range $reference.Bytes $native.Bytes ($record + 4) ($record + 4) 2048 $sample $ram
    # SMB1 mapper 0 is vertically mirrored: the two physical CIRAM pages map
    # directly to MySMB's two canonical name tables.
    Compare-M2Range $reference.Bytes $native.Bytes ($record + 2052) ($record + 2052) 1024 $sample $nameTable0
    Compare-M2Range $reference.Bytes $native.Bytes ($record + 3076) ($record + 3076) 1024 $sample $nameTable1
    Compare-M2Range $reference.Bytes $native.Bytes ($record + 4100) ($record + 4100) 32 $sample $palette
    Compare-M2Range $reference.Bytes $native.Bytes ($record + 4132) ($record + 4132) 256 $sample $oam
    for ($scalar = 0; $scalar -lt 7; ++$scalar) {
        Compare-M2Range $reference.Bytes $native.Bytes ($record + 4388 + $scalar) ($record + 4388 + $scalar) 1 $sample $ppu[$scalar]
    }
}

[pscustomobject]@{
    Samples = $reference.Count
    StartSample = $StartSample
    EndSample = $EndSample
    Mirroring = $Mirroring
    Results = @($ram, $nameTable0, $nameTable1, $palette, $oam) + $ppu
} | ConvertTo-Json -Depth 3
