param(
    [Parameter(Mandatory=$true)][string]$Compiler,
    [Parameter(Mandatory=$true)][string]$DosBoxDirectory,
    [Parameter(Mandatory=$true)][string]$ProductPath,
    [Parameter(Mandatory=$true)][string]$OutputDirectory
)
$ErrorActionPreference='Stop'
& (Join-Path $PSScriptRoot 'Build-DosBoxIoProbe.ps1') -Compiler $Compiler -DosBoxDirectory $DosBoxDirectory -OutputDirectory $OutputDirectory
if ($LASTEXITCODE -ne 0) {throw 'Probe build failed.'}
$output=[IO.Path]::GetFullPath($OutputDirectory)
Copy-Item -LiteralPath $ProductPath -Destination (Join-Path $output 'MYSMB.EXE') -Force
@"
[sdl]
fullscreen=false
output=surface
waitonerror=false
mapperfile=mapper.map
usescancodes=false
[dosbox]
machine=vgaonly
captures=.
memsize=16
[cpu]
core=dynamic
cycles=max
[mixer]
nosound=true
[midi]
mpu401=none
mididevice=none
[autoexec]
mount c "$output"
c:
MYSMB.EXE
echo MYSMB_EXIT_OK>exit.ok
"@ | Set-Content -LiteralPath (Join-Path $output 'probe.conf') -Encoding ascii
# Keep the restored DOS screen alive despite any buffered Escape repeat.
(@('pause')*32)+@('exit') | Add-Content -LiteralPath (Join-Path $output 'probe.conf') -Encoding ascii
@'
6000 capture title.bmp 0
7000 key 13 1
7500 key 13 0
26000 capture start.bmp 0
27000 key 100 1
27000 key 106 1
29000 capture right-run.bmp 0
29100 key 107 1
29800 capture jump.bmp 0
30200 key 107 0
31000 key 106 0
31000 key 100 0
33000 capture before-left.bmp 0
33100 key 97 1
37100 key 97 0
47000 capture release.bmp 0
50000 capture stopped.bmp 0
52000 key 27 1
52500 key 27 0
54000 capture exit.bmp 0
56000 quit 0 0
'@ | Set-Content -LiteralPath (Join-Path $output 'input.script') -Encoding ascii
# Remove only this probe's declared receipts so a failed run cannot reuse them.
foreach ($name in @('title.bmp','start.bmp','right-run.bmp','jump.bmp','before-left.bmp','release.bmp','stopped.bmp','exit.bmp','exit.ok','probe.log')) {
    $path=Join-Path $output $name
    if (Test-Path -LiteralPath $path) {Remove-Item -LiteralPath $path -Force}
}
$oldVideo=$env:SDL_VIDEODRIVER
$oldAudio=$env:SDL_AUDIODRIVER
try {
    $env:SDL_VIDEODRIVER='dummy'
    $env:SDL_AUDIODRIVER='dummy'
    $process=Start-Process -FilePath (Join-Path $output 'DOSBox.exe') -WorkingDirectory $output -ArgumentList '-noconsole -conf probe.conf' -WindowStyle Hidden -PassThru
    if (!$process.WaitForExit(60000)) {
        Stop-Process -Id $process.Id -Force
        throw 'DOSBox route exceeded its 60-second budget.'
    }
    if (!(Test-Path -LiteralPath (Join-Path $output 'exit.ok'))) {throw 'Actual EXE did not return to DOS.'}
    Get-Content -LiteralPath (Join-Path $output 'probe.log')
    $env:PYTHONDONTWRITEBYTECODE='1'
    & python (Join-Path $PSScriptRoot 'VerifyDosBoxIoReceipt.py') $output
    if ($LASTEXITCODE -ne 0) {throw 'Captured route failed its I/O receipt checks.'}
} finally {
    $env:SDL_VIDEODRIVER=$oldVideo
    $env:SDL_AUDIODRIVER=$oldAudio
}
