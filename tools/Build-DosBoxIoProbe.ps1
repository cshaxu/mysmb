param(
    [Parameter(Mandatory=$true)][string]$Compiler,
    [Parameter(Mandatory=$true)][string]$DosBoxDirectory,
    [Parameter(Mandatory=$true)][string]$OutputDirectory
)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$output=[IO.Path]::GetFullPath($OutputDirectory)
$build=[IO.Path]::GetFullPath((Join-Path $repository 'build'))+[IO.Path]::DirectorySeparatorChar
if (!$output.StartsWith($build,[StringComparison]::OrdinalIgnoreCase)) {
    throw 'Probe outputs must remain below ignored build.'
}
New-Item -ItemType Directory -Force -Path $output | Out-Null
$env:TEMP=$output
$env:TMP=$output
foreach ($name in @('DOSBox.exe','SDL_net.dll')) {
    Copy-Item -LiteralPath (Join-Path $DosBoxDirectory $name) -Destination (Join-Path $output $name) -Force
}
Copy-Item -LiteralPath (Join-Path $DosBoxDirectory 'SDL.dll') -Destination (Join-Path $output 'SDL_real.dll') -Force
$dump=Join-Path (Split-Path $Compiler) 'objdump.exe'
$exports=& $dump -p (Join-Path $output 'SDL_real.dll')
if ($LASTEXITCODE -ne 0) {throw 'Unable to inspect installed SDL exports.'}
$definitions=@('LIBRARY SDL','EXPORTS')
foreach ($line in $exports) {
    if ($line -match '^\s*\[\s*\d+\].*\s(SDL_\w+)\s*$') {
        $name=$Matches[1]
        if ($name -eq 'SDL_PollEvent') {$definitions+='SDL_PollEvent=probe_poll'}
        else {$definitions+="$name=SDL_real.$name"}
    }
}
if ($definitions.Count -lt 100) {throw 'Incomplete SDL export inventory.'}
$def=Join-Path $output 'SDL.def'
$definitions | Set-Content -LiteralPath $def -Encoding ascii
& $Compiler -std=c17 -O2 -Wall -Wextra -shared (Join-Path $repository 'test/dosbox_io_probe.c') $def -o (Join-Path $output 'SDL.dll')
exit $LASTEXITCODE
