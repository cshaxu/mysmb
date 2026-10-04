param(
    [Parameter(Mandatory=$true)][string]$Compiler,
    [Parameter(Mandatory=$true)][string]$DosBoxDirectory,
    [Parameter(Mandatory=$true)][string]$ProductPath,
    [Parameter(Mandatory=$true)][string]$OutputDirectory,
    [string]$SeedPath=''
)
$ErrorActionPreference='Stop'
& (Join-Path $PSScriptRoot 'Build-DosBoxIoProbe.ps1') -Compiler $Compiler -DosBoxDirectory $DosBoxDirectory -OutputDirectory $OutputDirectory
if($LASTEXITCODE -ne 0){throw 'Probe build failed.'}
$output=[IO.Path]::GetFullPath($OutputDirectory)
$game=Join-Path $output 'GAME'
New-Item -ItemType Directory -Force -Path $game | Out-Null
Copy-Item -LiteralPath $ProductPath -Destination (Join-Path $game 'MYSMB.EXE') -Force
foreach($name in @('mysmb.sav','mysmb.tmp','mysmb.log')){
    foreach($folder in @($output,$game)){
        $path=Join-Path $folder $name
        if(Test-Path -LiteralPath $path){Remove-Item -LiteralPath $path -Force}
    }
}
if($SeedPath){Copy-Item -LiteralPath $SeedPath -Destination (Join-Path $game 'mysmb.sav')}
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
C:\GAME\MYSMB.EXE
echo MYSMB_EXIT_OK>exit.ok
"@ | Set-Content (Join-Path $output 'probe.conf') -Encoding ascii
(@('pause')*32)+@('exit') | Add-Content (Join-Path $output 'probe.conf') -Encoding ascii
if($SeedPath){$start=@('6000 key 111 1','6300 key 111 0')}
else{$start=@('7000 key 13 1','7500 key 13 0')}
$start+@(
    '26000 capture saved.bmp 0',
    '27000 key 112 1','27400 key 112 0',
    '28500 key 100 1','31500 key 100 0',
    '33000 capture moved.bmp 0',
    '34000 key 111 1','34500 key 111 0',
    '35000 capture loaded.bmp 0',
    '37000 key 27 1','37500 key 27 0',
    '39000 capture exit.bmp 0','41000 quit 0 0'
) | Set-Content (Join-Path $output 'input.script') -Encoding ascii
foreach($name in @('saved.bmp','moved.bmp','loaded.bmp','exit.bmp','exit.ok','probe.log')){
    $path=Join-Path $output $name
    if(Test-Path -LiteralPath $path){Remove-Item -LiteralPath $path -Force}
}
$oldVideo=$env:SDL_VIDEODRIVER;$oldAudio=$env:SDL_AUDIODRIVER
try{
    $env:SDL_VIDEODRIVER='dummy';$env:SDL_AUDIODRIVER='dummy'
    $process=Start-Process -FilePath (Join-Path $output 'DOSBox.exe') -WorkingDirectory $output -ArgumentList '-noconsole -conf probe.conf' -WindowStyle Hidden -PassThru
    if(!$process.WaitForExit(50000)){Stop-Process -Id $process.Id -Force;throw 'Snapshot route exceeded 50 seconds.'}
    & python (Join-Path $PSScriptRoot 'VerifyDosBoxSnapshotReceipt.py') $output
    if($LASTEXITCODE -ne 0){throw 'Snapshot receipt failed.'}
}finally{$env:SDL_VIDEODRIVER=$oldVideo;$env:SDL_AUDIODRIVER=$oldAudio}
