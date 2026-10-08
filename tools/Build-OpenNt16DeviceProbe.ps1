param(
    [Parameter(Mandatory=$true)][string]$Compiler,
    [Parameter(Mandatory=$true)][string]$Linker,
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
$env:TEMP=$output;$env:TMP=$output
Push-Location $output
try {
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fodevice.obj /I (Join-Path $repository 'src') /I $runtimeInclude (Join-Path $repository 'test/dos16_video_lifecycle_probe.c')
    if($LASTEXITCODE -ne 0){throw 'Device probe compilation failed.'}
    $members=@('platform_dos16_devices.c','platform_dos16_keyboard.c',
        'platform_dos16_pit_clock.c','io_color.c','io_pacing.c','io_control.c',
        'text_elements.c','io_text_glyph.c')
    $dependencies=@()
    for($i=0;$i -lt $members.Count;++$i) {
        $name='dep'+$i+'.obj'
        Copy-Item -LiteralPath (Join-Path $ProductDirectory $members[$i]) -Destination $name -Force
        $dependencies+=$name
    }
    Copy-Item -LiteralPath (Join-Path $RuntimeDirectory 'LVARSTCK.OBJ') -Destination 'stack.obj' -Force
    $objects=(@('device.obj','stack.obj')+$dependencies)-join "+`n"
    @($objects,'device.exe','device.map',(Join-Path $RuntimeDirectory 'LLIBCE.LIB')) | Set-Content -Encoding ascii device.rsp
    $command='"'+$Linker+'" /nologo /NOE /SEGMENTS:2048 @device.rsp < NUL'
    & cmd.exe /d /c $command
    if($LASTEXITCODE -ne 0){throw 'Device probe link failed.'}
} finally {$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp;Pop-Location}
