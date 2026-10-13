param(
    [Parameter(Mandatory=$true)][string]$Compiler,
    [Parameter(Mandatory=$true)][string]$DosLinker,
    [Parameter(Mandatory=$true)][string]$DosBoxDirectory,
    [Parameter(Mandatory=$true)][string]$RuntimeDirectory,
    [Parameter(Mandatory=$true)][string]$OutputDirectory
)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$output=[IO.Path]::GetFullPath($OutputDirectory)
$build=[IO.Path]::GetFullPath((Join-Path $repository 'build'))+[IO.Path]::DirectorySeparatorChar
if(!$output.StartsWith($build,[StringComparison]::OrdinalIgnoreCase)){throw 'Audio probe must remain below build.'}
$runtimeInclude=Join-Path (Split-Path -Parent $RuntimeDirectory) 'INC'
$runtime=Join-Path $RuntimeDirectory 'LLIBCE.LIB'
$stack=Join-Path $RuntimeDirectory 'LVARSTCK.OBJ'
New-Item -ItemType Directory -Force -Path $output | Out-Null
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP;$oldAudio=$env:SDL_AUDIODRIVER;$oldVideo=$env:SDL_VIDEODRIVER
$compileTemp=Join-Path (Join-Path $repository 'build') 'tmp16'
New-Item -ItemType Directory -Force -Path $compileTemp | Out-Null
$env:PATH=(Split-Path -Parent $Compiler)+';'+(Join-Path $env:SystemRoot 'System32')
$env:TEMP=$compileTemp;$env:TMP=$compileTemp
Push-Location $output
try {
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Foprobe.obj /I (Join-Path $repository 'app-mario/src') /I (Join-Path $repository 'lib/kvm/include') /I $runtimeInclude (Join-Path $repository 'app-mario/test/dos16_audio_device_probe.c')
    if($LASTEXITCODE -ne 0){throw 'DOS audio probe compilation failed.'}
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Foaudio.obj /I (Join-Path $repository 'app-mario/src') /I (Join-Path $repository 'lib/kvm/include') /I $runtimeInclude (Join-Path $repository 'app-mario/src/platform/dos16/dos_audio.c')
    if($LASTEXITCODE -ne 0){throw 'DOS audio renderer compilation failed.'}
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fopcm.obj /I (Join-Path $repository 'app-mario/src') /I (Join-Path $repository 'lib/kvm/include') /I $runtimeInclude (Join-Path $repository 'app-mario/src/io/audio_renderer.c')
    if($LASTEXITCODE -ne 0){throw 'Shared PCM renderer compilation failed.'}
    # Keep this name inside DOS 8.3 limits because LINK 3.65 runs in DOSBox.
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Foaudiodos.obj /I (Join-Path $repository 'app-mario/src') /I (Join-Path $repository 'lib/kvm/include') /I $runtimeInclude (Join-Path $repository 'app-mario/src/platform/dos16/dos_audio_dos.c')
    if($LASTEXITCODE -ne 0){throw 'DOS audio device compilation failed.'}
    Copy-Item -LiteralPath $DosLinker -Destination 'LINK.EXE' -Force
    Copy-Item -LiteralPath $runtime -Destination 'RT.LIB' -Force
    Copy-Item -LiteralPath $stack -Destination 'stack.obj' -Force
    @('probe.obj+','audio.obj+','pcm.obj+','audiodos.obj+','stack.obj,','audio.exe,','audio.map,','RT.LIB;') | Set-Content -Encoding ascii LINK.RSP
    @'
@echo off
LINK /NOE @LINK.RSP > LINK.LOG
if errorlevel 1 echo 1 > LINK.DON
if not errorlevel 1 echo 0 > LINK.DON
exit
'@ | Set-Content -Encoding ascii LINK.BAT
    @"
[sdl]
fullscreen=false
output=surface
waitonerror=false
[dosbox]
machine=vgaonly
memsize=16
[mixer]
nosound=true
[autoexec]
mount c "$output"
c:
LINK.BAT
exit
"@ | Set-Content -Encoding ascii LINK.CONF
    $env:SDL_VIDEODRIVER='dummy';$env:SDL_AUDIODRIVER='dummy'
    $link=Start-Process -FilePath (Join-Path $DosBoxDirectory 'DOSBox.exe') -WorkingDirectory $output -ArgumentList '-noconsole','-conf','LINK.CONF' -WindowStyle Hidden -PassThru
    if(!$link.WaitForExit(60000)){Stop-Process -Id $link.Id -Force;throw 'DOS audio probe linker timed out.'}
    $linkedProbe=Join-Path $output 'AUDIO.EXE';$linkDone=Join-Path $output 'LINK.DON'
    if(!(Test-Path $linkedProbe) -or [IO.File]::ReadAllText($linkDone).Trim() -ne '0'){throw 'DOS audio probe link failed.'}
    @'
@echo off
AUDIO.EXE
if errorlevel 2 goto submit_failed
if errorlevel 1 goto open_failed
echo BLASTER-DSP-DMA-IRQ > AUDIO.OK
goto done
:submit_failed
echo AUDIO-SUBMIT-FAILED > AUDIO.ERR
goto done
:open_failed
echo AUDIO-OPEN-FAILED > AUDIO.ERR
:done
exit
'@ | Set-Content -Encoding ascii AUDIO.BAT
    $probeOk=Join-Path $output 'AUDIO.OK';$probeError=Join-Path $output 'AUDIO.ERR'
    Remove-Item -LiteralPath $probeOk,$probeError -Force -ErrorAction SilentlyContinue
    @"
[autoexec]
mount c "$output"
c:
audio.bat
exit
"@ | Set-Content -Encoding ascii RUN.CONF
    # Use the installed default configuration for its existing SB16 device;
    # dummy SDL prevents the automated device witness from using host audio.
    $run=Start-Process -FilePath (Join-Path $DosBoxDirectory 'DOSBox.exe') -WorkingDirectory $output -ArgumentList '-noconsole','-conf','RUN.CONF' -WindowStyle Hidden -PassThru
    if(!$run.WaitForExit(30000)){Stop-Process -Id $run.Id -Force;throw 'DOS audio probe runtime timed out.'}
    if(!(Test-Path $probeOk)) { $detail=if(Test-Path $probeError){Get-Content -Raw $probeError}else{'no receipt'};throw ('DOS audio device probe failed: '+$detail) }
    Get-Content -Raw $probeOk
}
finally {
    $env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp;$env:SDL_AUDIODRIVER=$oldAudio;$env:SDL_VIDEODRIVER=$oldVideo
    Pop-Location
}
