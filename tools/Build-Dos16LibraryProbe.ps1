param(
    [Parameter(Mandatory=$true)][string]$ProbeSource,
    [Parameter(Mandatory=$true)][string[]]$Sources,
    [Parameter(Mandatory=$true)][string]$OutputDirectory,
    [ValidateSet('S','L')][string]$MemoryModel='L',
    [switch]$CompileOnly,
    [switch]$LinkOnly
)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$output=[IO.Path]::GetFullPath($OutputDirectory)
$build=[IO.Path]::GetFullPath((Join-Path $repository 'build'))+'\'
if(!$output.StartsWith($build,[StringComparison]::OrdinalIgnoreCase)){throw 'Probe must remain below build.'}
$compiler=Join-Path $repository 'tools/dos16/cl16.exe'
$linker=Join-Path $repository 'tools/dos16/link16.exe'
$runtime=Join-Path $repository 'tools/dos16/runtime'
$inputs=@($ProbeSource)+$Sources
$inputs=@($inputs | ForEach-Object {(Resolve-Path -LiteralPath $_).Path})
New-Item -ItemType Directory -Force $output | Out-Null
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP
$env:PATH=(Split-Path $compiler)+';'+(Join-Path $env:SystemRoot 'System32')
$env:TEMP=$output;$env:TMP=$output
Push-Location $output
try {
    if(!$LinkOnly) {
        $objects=@()
        for($i=0;$i -lt $inputs.Count;++$i) {
            $object="unit$i.obj";$objects+=$object
            & $compiler /nologo "/A$MemoryModel" /Gs /Oas /D MYGAMES_DOS16_TARGET /c "/Fo$object" /I (Join-Path $repository 'src/lib') /I (Join-Path $runtime 'INC') $inputs[$i]
            if($LASTEXITCODE -ne 0){throw "Probe compilation failed: $($inputs[$i])"}
        }
        Copy-Item (Join-Path $runtime "LIB/${MemoryModel}VARSTCK.OBJ") stack.obj -Force
        $objects+='stack.obj'
        @(($objects-join "+`n"),'probe.exe','probe.map',(Join-Path $runtime "LIB/${MemoryModel}LIBCE.LIB")) | Set-Content -Encoding ascii probe.rsp
    }
    if(!$CompileOnly) {
        & cmd /d /c ('"'+$linker+'" /nologo /NOE @probe.rsp < NUL')
        if($LASTEXITCODE -ne 0){throw 'Probe link failed.'}
    }
} finally {Pop-Location;$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp}
