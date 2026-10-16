param(
    [Parameter(Mandatory=$true)][string]$ProductDirectory,
    [Parameter(Mandatory=$true)][string]$OutputDirectory,
    [switch]$LinkOnly
)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$build=[IO.Path]::GetFullPath((Join-Path $repository 'build'))+'\'
$output=[IO.Path]::GetFullPath($OutputDirectory)
$product=(Resolve-Path $ProductDirectory).Path
if(!$output.StartsWith($build,[StringComparison]::OrdinalIgnoreCase) -or
    !$product.StartsWith($build,[StringComparison]::OrdinalIgnoreCase)){throw 'Probe inputs/outputs must stay below build.'}
$compiler=Join-Path $repository 'tools/dos16/cl16.exe'
$linker=Join-Path $repository 'tools/dos16/link16.exe'
$include=Join-Path $repository 'tools/dos16/runtime/INC'
$python=(Get-Command python).Source
New-Item -ItemType Directory -Force $output | Out-Null
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP
$env:PATH=(Split-Path $compiler)+';'+(Join-Path $env:SystemRoot 'System32')
# The original compiler's temporary filename buffer cannot hold a deeply
# nested CMake output path. Use the same short build-only convention as the
# existing DOS probe builders.
$compileTemp=Join-Path $repository 'build/tmp16'
New-Item -ItemType Directory -Force $compileTemp | Out-Null
$env:TEMP=$compileTemp;$env:TMP=$compileTemp
Push-Location $output
try {
    if(!$LinkOnly) {
        foreach($pattern in @('smbgrp*.lib','mysmb-startup.obj','mysmb-stack.obj')) {
            Get-ChildItem -LiteralPath $product -Filter $pattern | Copy-Item -Destination $output -Force
        }
        # LINK consumes these libraries in its object field. Remove the old
        # root module rather than relying on lazy archive extraction.
        $removed=$false
        foreach($group in Get-ChildItem -Filter 'smbgrp*.lib') {
            & (Join-Path $repository 'tools/dos16/lib16.exe') /nologo ($group.Name+',members.txt')
            if($LASTEXITCODE){throw 'Unable to inspect product archive.'}
            if((Get-Content members.txt -Raw) -match 'kvm_platform_dos16_dos16_root') {
                & (Join-Path $repository 'tools/dos16/lib16.exe') /nologo $group.Name -kvm_platform_dos16_dos16_root ';'
                if($LASTEXITCODE){throw 'Unable to remove replaced root module.'}
                $removed=$true
            }
        }
        if(!$removed){throw 'Product root archive member was not found.'}
        $flags=@('/nologo','/AL','/Gs','/W3','/D','MYSMB_DOS16_TARGET','/D','MYGAMES_DOS16_TARGET',
            '/I',$include,'/I',(Join-Path $repository 'src/lib'),'/I',(Join-Path $repository 'src/app-mario'),
            '/I',(Join-Path $repository 'src/app-mario/kvm'))
        & $compiler @flags /c /Foprobe.obj (Join-Path $repository 'test/app-mario/kvm/platform/dos16/cache_allocation_probe.c')
        if($LASTEXITCODE){throw 'Probe compilation failed.'}
        & $compiler @flags /D main=cache_product_main /D mysmb_dos16_root_step=cache_observed_step /D MYSMB_LOCAL_TITLE /I (Join-Path $product 'local-rom') /c /Foentry.obj (Join-Path $repository 'src/app-mario/kvm/platform/dos16/main_dos16.c')
        if($LASTEXITCODE){throw 'Observed product entry compilation failed.'}
        & $compiler @flags /D _fmalloc=cache_fmalloc /D _nmalloc=cache_nmalloc /D _ffree=cache_ffree /D _nfree=cache_nfree /D intdos=cache_intdos /c /Foroot.obj (Join-Path $repository 'src/app-mario/kvm/platform/dos16/dos16_root.c')
        if($LASTEXITCODE){throw 'Observed root compilation failed.'}
        & $python (Join-Path $repository 'tools/VerifyDos16StartupConsumers.py') probe.obj entry.obj root.obj
        if($LASTEXITCODE){throw 'Probe introduced an unsupported startup vector consumer.'}
        $rsp=Get-Content -LiteralPath (Join-Path $product 'mysmb-dos16.rsp') -Raw
        $rsp=$rsp.Replace('kvm_platform_dos16_main_dos16.c+',"probe.obj+`nentry.obj+`nroot.obj+")
        $rsp | Set-Content -Encoding ascii probe.rsp
    } else {
        & $linker /nologo /NOE /NOD /SEGMENTS:2048 '@probe.rsp'
        if($LASTEXITCODE){throw 'Probe link failed.'}
        & $python (Join-Path $repository 'tools/VerifyDos16Memory.py') $output --limit-loader-allocation --near-heap-reserve=4096
        if($LASTEXITCODE){throw 'Probe loader bound failed.'}
    }
} finally {Pop-Location;$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp}
