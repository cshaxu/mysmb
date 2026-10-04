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
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /D MYSMB_LOCAL_TITLE /c /Foprobe.obj /I (Join-Path $repository 'src') /I $runtimeInclude /I (Join-Path $ProductDirectory 'local-rom') (Join-Path $repository 'test/dos16_input_progress_probe.c')
    if($LASTEXITCODE -ne 0){throw 'Input probe compilation failed.'}
    $libraries=@()
    foreach($library in (Get-ChildItem -LiteralPath $ProductDirectory -Filter 'smbgrp*.lib' | Sort-Object Name)) {
        Copy-Item -LiteralPath $library.FullName -Destination $library.Name -Force
        $libraries+=$library.Name
    }
    if($libraries.Count -eq 0){throw 'No product libraries found.'}
    Copy-Item -LiteralPath (Join-Path $RuntimeDirectory 'LVARSTCK.OBJ') -Destination 'stack.obj' -Force
    $objects=(@('probe.obj','stack.obj')+$libraries)-join "+`n"
    @($objects,'input.exe','input.map',(Join-Path $RuntimeDirectory 'LLIBCE.LIB')) | Set-Content -Encoding ascii input.rsp
    $command='"'+$Linker+'" /nologo /NOE /SEGMENTS:2048 @input.rsp < NUL'
    & cmd.exe /d /c $command
    if($LASTEXITCODE -ne 0){throw 'Input probe link failed.'}
} finally {$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp;Pop-Location}
