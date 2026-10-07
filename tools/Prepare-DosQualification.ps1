param(
    [Parameter(Mandatory = $true)][string]$Executable,
    [Parameter(Mandatory = $true)][string]$Map,
    [Parameter(Mandatory = $true)][string]$OutputDirectory
)

$ErrorActionPreference = 'Stop'
$repository = Split-Path -Parent $PSScriptRoot
$build = [IO.Path]::GetFullPath((Join-Path $repository 'build')) + [IO.Path]::DirectorySeparatorChar
$output = [IO.Path]::GetFullPath($OutputDirectory)
if (!$output.StartsWith($build, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'Owner-local qualification outputs must remain below the ignored build directory.'
}
$OutputDirectory = $output
if (!(Test-Path -LiteralPath $Executable) -or !(Test-Path -LiteralPath $Map)) {
    throw 'The linked DOS executable and map must exist before preparing a qualification package.'
}
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
Copy-Item -LiteralPath $Executable -Destination (Join-Path $OutputDirectory 'MYSMB.EXE') -Force
Copy-Item -LiteralPath $Map -Destination (Join-Path $OutputDirectory 'MYSMB.MAP') -Force
$executableHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $Executable).Hash
$mapHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $Map).Hash
@(
    'Run MYSMB.EXE on the physical MS-DOS host.',
    'W/S/A/D move; J runs/fires; K jumps; Enter starts; either Shift selects.',
    'Tab switches native VGA graphics and 80x25 colored text; Escape exits.',
    'P saves and O loads mysmb.sav beside the executable.',
    'Graphics preserves 256x240 source pixels with VGA scan repetition.',
    'Record host CPU/clock, DOS version, free conventional memory, VGA and monitor.',
    'Record startup, play, scroll, input, P/O, Tab both ways and exit outcomes.',
    'LCD filling, physical cadence and memory samples require actual host observations.',
    'Current acceptance scope: docs/history/M3-T34-native-vga-performance-proposal.md.',
    'The EXE embeds owner-local ROM-derived resources; this package remains local.',
    "MYSMB.EXE SHA-256: $executableHash",
    "MYSMB.MAP SHA-256: $mapHash"
) | Set-Content -Encoding Ascii (Join-Path $OutputDirectory 'README.TXT')
