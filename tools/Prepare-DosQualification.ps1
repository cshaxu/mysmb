param(
    [Parameter(Mandatory = $true)][string]$Executable,
    [Parameter(Mandatory = $true)][string]$Map,
    [Parameter(Mandatory = $true)][string]$OutputDirectory
)

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
    'Arrow keys move; Enter starts; Z and X are action buttons.',
    'F1 switches between VGA graphics and 80x25 colored text.',
    'Record results using docs/history/M4-T1-486sx-qualification-protocol.md.',
    'This package contains no ROM, CHR, or generated ROM-derived data.',
    "MYSMB.EXE SHA-256: $executableHash",
    "MYSMB.MAP SHA-256: $mapHash"
) | Set-Content -Encoding Ascii (Join-Path $OutputDirectory 'README.TXT')
