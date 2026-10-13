param(
    [Parameter(Mandatory=$true)][string]$SdkIncludeDirectory,
    [Parameter(Mandatory=$true)][string]$WindowsLibrary,
    [Parameter(Mandatory=$true)][string]$RuntimeLibrary,
    [Parameter(Mandatory=$true)][string]$OutputDirectory,
    [switch]$LinkOnly
)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$output=[IO.Path]::GetFullPath($OutputDirectory)
if(!$output.StartsWith((Join-Path $repository 'build')+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Mine intermediates must remain below build.'}
$compiler=Join-Path $repository 'tools/dos16/cl16.exe'
$linker=Join-Path $repository 'tools/dos16/link16.exe'
$python=(Get-Command python).Source
$SdkIncludeDirectory=(Resolve-Path $SdkIncludeDirectory).Path
$WindowsLibrary=(Resolve-Path $WindowsLibrary).Path
$RuntimeLibrary=(Resolve-Path $RuntimeLibrary).Path
$common=@('src/app-mine/core/mine.c','src/app-mine/kvm/app/app.c','src/app-mine/kvm/app/session.c','src/app-mine/kvm/text/scene.c','src/app-mine/kvm/graphics/scene.c','src/app-mine/kvm/io/number.c','src/lib/kvm/color.c','src/lib/kvm/video.c','src/lib/kvm/pointer.c')
$dos=@('src/app-mine/kvm/platform/dos16/main.c')+$common+@('src/lib/dos16/host.c','src/lib/dos16/video_mode.c','src/lib/dos16/pit_clock.c','src/lib/dos16/raw_keyboard.c','src/lib/dos16/mouse.c','src/lib/dos16/mouse_dos.c','src/lib/dos16/text_cells.c')
$windows=@('src/app-mine/kvm/platform/win16/main.c')+$common+@('src/lib/kvm/windows_key.c','src/lib/win16/host.c','src/lib/win16/dib.c','src/lib/win16/text.c')
New-Item -ItemType Directory -Force $output | Out-Null
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP
$env:PATH=(Split-Path $compiler)+';'+(Join-Path $env:SystemRoot 'System32');$env:TEMP=$output;$env:TMP=$output
try {
    foreach($target in @('dos','windows')){
        $dir=Join-Path $output $target
        New-Item -ItemType Directory -Force $dir | Out-Null
        Push-Location $dir
        try {
            if(!$LinkOnly){
                $sources=$dos;$flags=@('/D','MYGAMES_DOS16_TARGET');$include=Join-Path $repository 'tools/dos16/runtime/INC'
                if($target -eq 'windows'){$sources=$windows;$flags=@('/G2sw','/D','MYGAMES_WIN16_TARGET');$include=$SdkIncludeDirectory}
                $objects=@()
                for($i=0;$i -lt $sources.Count;++$i){
                    $object="unit$i.obj";$objects+=$object
                    & $compiler /nologo /AS /Gs /W3 /Oas @flags /c "/Fo$object" /I $include /I (Join-Path $repository 'src/lib') /I (Join-Path $repository 'src/app-mine') (Join-Path $repository $sources[$i])
                    if($LASTEXITCODE){throw "Mine $target compile failed: $($sources[$i])"}
                }
                if($target -eq 'dos'){
                    @(($objects-join "+`n"),'mine-dos.exe','mine-dos.map',(Join-Path $repository 'tools/dos16/runtime/LIB/SLIBCE.LIB'),';') | Set-Content -Encoding ascii mine.rsp
                } else {
                    @('NAME MINE','EXETYPE WINDOWS',"STUB 'mine-dos.exe'",'CODE PRELOAD MOVEABLE DISCARDABLE','DATA PRELOAD MOVEABLE MULTIPLE','HEAPSIZE 4096','STACKSIZE 8192','EXPORTS',' MygamesWin16WndProc @1') | Set-Content -Encoding ascii mine.def
                    @(($objects-join "+`n"),'mine16.exe','mine16.map',"$WindowsLibrary+`n$RuntimeLibrary",'mine.def;') | Set-Content -Encoding ascii mine.rsp
                }
            } else {
                if($target -eq 'dos'){
                    & $linker /nologo /NOE /NOD /STACK:8192 '@mine.rsp'
                } else {
                    Copy-Item (Join-Path $output 'dos/mine-dos.exe') mine-dos.exe -Force
                    & $linker /nologo /NOE /NOD /ALIGN:16 '@mine.rsp'
                }
                if($LASTEXITCODE){throw "Mine $target link failed."}
                if($target -eq 'windows'){
                    & $python (Join-Path $PSScriptRoot 'bind_win16_mz.py') --stub mine-dos.exe --hybrid mine16.exe --repair
                    if($LASTEXITCODE){throw 'Mine NE/MZ verification failed.'}
                }
            }
        } finally {Pop-Location}
    }
} finally {$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp}
