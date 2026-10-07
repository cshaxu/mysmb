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
$executableHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $Executable).Hash
$mapHash = (Get-FileHash -Algorithm SHA256 -LiteralPath $Map).Hash
$exeBytes = [IO.File]::ReadAllBytes($Executable)
if ($exeBytes.Length -lt 28 -or $exeBytes[0] -ne 0x4d -or $exeBytes[1] -ne 0x5a) {
    throw 'The qualification executable must be an MZ image.'
}
Copy-Item -LiteralPath $Executable -Destination (Join-Path $OutputDirectory 'MYSMB.EXE') -Force
Copy-Item -LiteralPath $Map -Destination (Join-Path $OutputDirectory 'MYSMB.MAP') -Force
$relocationCount = [BitConverter]::ToUInt16($exeBytes, 6)
$headerParagraphs = [BitConverter]::ToUInt16($exeBytes, 8)
$mapBytes = (Get-Item -LiteralPath $Map).Length
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
    "MYSMB.EXE bytes: $($exeBytes.Length)",
    "MYSMB.EXE MZ relocations: $relocationCount",
    "MYSMB.EXE MZ header paragraphs: $headerParagraphs",
    "MYSMB.MAP SHA-256: $mapHash",
    "MYSMB.MAP bytes: $mapBytes",
    'Fill RESULT.TXT during the physical run; do not infer its observations from an emulator.'
) | Set-Content -Encoding Ascii (Join-Path $OutputDirectory 'README.TXT')

@(
    'MYSMB physical DOS qualification result',
    '',
    "MYSMB.EXE SHA-256: $executableHash",
    "MYSMB.EXE bytes: $($exeBytes.Length)",
    "MYSMB.EXE MZ relocations: $relocationCount",
    "MYSMB.MAP SHA-256: $mapHash",
    "MYSMB.MAP bytes: $mapBytes",
    '',
    'Git commit:',
    'CPU model and clock:',
    'Conventional memory before launch:',
    'Extended memory configuration:',
    'MS-DOS version and boot configuration:',
    'VGA adapter and monitor:',
    'Boot/executable media:',
    '',
    'Route 1 title/play: PASS | FAIL | notes',
    'Route 2 scrolling/dense sprites: PASS | FAIL | notes',
    'Route 3 death/area transition: PASS | FAIL | notes',
    'W/S/A/D, J, K, Enter, left/right Shift: PASS | FAIL | notes',
    'Tab VGA -> text -> VGA: PASS | FAIL | notes',
    'P save / O load: PASS | FAIL | notes',
    'Escape exit: PASS | FAIL | notes',
    '',
    '600-frame wall-clock sample 1:',
    '600-frame wall-clock sample 2:',
    '600-frame wall-clock sample 3:',
    'Input-latency observations:',
    'Visual corruption/mode-reset observations:',
    'VGA height-fill and scan-repetition observations:',
    'Halt/reset/unexpected behavior:',
    '',
    'This file records physical observations only. Blank fields mean the qualification remains open.'
) | Set-Content -Encoding Ascii (Join-Path $OutputDirectory 'RESULT.TXT')
