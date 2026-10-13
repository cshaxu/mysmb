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
$kvmInclude=Join-Path $repository 'src/lib'
$dos16Include=Join-Path $repository 'src/lib'
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP
$env:PATH=(Split-Path -Parent $Compiler)+';'+(Join-Path $env:SystemRoot 'System32')
$env:TEMP=$output;$env:TMP=$output
Push-Location $output
try {
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /D MYGAMES_DOS16_TARGET /c /Fodevice.obj /I (Join-Path $repository 'src/app-mario') /I (Join-Path $repository 'src/app-mario/kvm') /I $kvmInclude /I $dos16Include /I $runtimeInclude (Join-Path $repository 'app-mario/test/dos16_video_lifecycle_probe.c')
    if($LASTEXITCODE -ne 0){throw 'Device probe compilation failed.'}
    . (Join-Path $PSScriptRoot 'Get-Dos16DeviceProbeMembers.ps1')
    $members=@(Get-Dos16DeviceProbeMembers)
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
