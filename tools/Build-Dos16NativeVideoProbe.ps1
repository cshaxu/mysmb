param(
    [Parameter(Mandatory=$true)][string]$Compiler,
    [Parameter(Mandatory=$true)][string]$Linker,
    [Parameter(Mandatory=$true)][string]$DosBoxDirectory,
    [Parameter(Mandatory=$true)][string]$ProductDirectory,
    [Parameter(Mandatory=$true)][string]$RuntimeDirectory,
    [Parameter(Mandatory=$true)][string]$OutputDirectory
)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$output=[IO.Path]::GetFullPath($OutputDirectory)
$build=[IO.Path]::GetFullPath((Join-Path $repository 'build'))+[IO.Path]::DirectorySeparatorChar
if(!$output.StartsWith($build,[StringComparison]::OrdinalIgnoreCase)){throw 'Probe must remain below build.'}
New-Item -ItemType Directory -Force -Path $output | Out-Null
$runtimeInclude=Join-Path (Split-Path -Parent $RuntimeDirectory) 'INC'
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP
$env:PATH=(Split-Path -Parent $Compiler)+';'+$env:PATH
$compileTemp=Join-Path (Join-Path $repository 'build') 'tmp16'
New-Item -ItemType Directory -Force -Path $compileTemp | Out-Null
$env:TEMP=$compileTemp;$env:TMP=$compileTemp
Push-Location $output
try {
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fonative.obj /I (Join-Path $repository 'src') /I $runtimeInclude (Join-Path $repository 'test/dos16_native_video_probe.c')
    if($LASTEXITCODE -ne 0){throw 'Native video probe compilation failed.'}
    $members=@('platform_dos16_devices.c','platform_dos16_keyboard.c',
        'platform_dos16_pit_clock.c','io_color.c','io_pacing.c','io_control.c',
        'text_elements.c','io_text_glyph.c','text_layout.c')
    $dependencies=@()
    for($i=0;$i -lt $members.Count;++$i) {
        $name='dep'+$i+'.obj'
        Copy-Item -LiteralPath (Join-Path $ProductDirectory $members[$i]) -Destination $name -Force
        $dependencies+=$name
    }
    Copy-Item -LiteralPath (Join-Path $RuntimeDirectory 'LVARSTCK.OBJ') -Destination 'stack.obj' -Force
    Copy-Item -LiteralPath (Join-Path $RuntimeDirectory 'LLIBCE.LIB') -Destination 'RT.LIB' -Force
    $objects=(@('native.obj','stack.obj')+$dependencies)-join "+`n"
    @($objects,'native.exe','native.map','RT.LIB') | Set-Content -Encoding ascii native.rsp
    Copy-Item -LiteralPath $Linker -Destination 'LINK.EXE' -Force
    @'
@echo off
LINK /NOE @NATIVE.RSP > LINK.LOG
if errorlevel 1 echo 1 > LINK.DON
if not errorlevel 1 echo 0 > LINK.DON
exit
'@ | Set-Content -Encoding ascii LINK.BAT
    @"
[sdl]
fullscreen=false
output=surface
waitonerror=false
mapperfile=mapper-native-link.map
usescancodes=false
[dosbox]
machine=vgaonly
captures=.
memsize=16
[cpu]
core=auto
cycles=auto
[mixer]
nosound=true
[midi]
mpu401=none
mididevice=none
[autoexec]
mount c "$output"
c:
LINK.BAT
exit
"@ | Set-Content -Encoding ascii LINK.CONF
    $savedVideo=$env:SDL_VIDEODRIVER;$savedAudio=$env:SDL_AUDIODRIVER
    try {
        $env:SDL_VIDEODRIVER='dummy';$env:SDL_AUDIODRIVER='dummy'
        $process=Start-Process -FilePath (Join-Path $DosBoxDirectory 'DOSBox.exe') -WorkingDirectory $output -ArgumentList '-noconsole','-conf','LINK.CONF' -WindowStyle Hidden -PassThru
        if(!$process.WaitForExit(60000)){Stop-Process -Id $process.Id -Force;throw 'Native video probe link exceeded 60 seconds.'}
    } finally {$env:SDL_VIDEODRIVER=$savedVideo;$env:SDL_AUDIODRIVER=$savedAudio}
    $probeExecutable=Join-Path $output 'native.exe'
    $linkDone=Join-Path $output 'LINK.DON'
    if(!(Test-Path $probeExecutable) -or !(Test-Path $linkDone) -or [IO.File]::ReadAllText($linkDone).Trim() -ne '0'){throw 'Native video probe link failed.'}
} finally {$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp;Pop-Location}
