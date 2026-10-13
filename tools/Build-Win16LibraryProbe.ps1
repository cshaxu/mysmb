param([Parameter(Mandatory=$true)][string]$SdkIncludeDirectory,
[Parameter(Mandatory=$true)][string]$WindowsLibrary,
[Parameter(Mandatory=$true)][string]$RuntimeLibrary,
[Parameter(Mandatory=$true)][string]$OutputDirectory,
[ValidateSet("S","L")][string]$MemoryModel="L",
[switch]$LinkOnly)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$output=[IO.Path]::GetFullPath($OutputDirectory)
if(!$output.StartsWith((Join-Path $repository 'build')+'\',[StringComparison]::OrdinalIgnoreCase)){throw 'Probe must remain below build.'}
$compiler=Join-Path $repository 'tools/dos16/cl16.exe'
$linker=Join-Path $repository 'tools/dos16/link16.exe'
$WindowsLibrary=(Resolve-Path $WindowsLibrary).Path
$RuntimeLibrary=(Resolve-Path $RuntimeLibrary).Path
$sources=@('test/lib/win16/host_native_probe.c','src/lib/win16/host.c','src/lib/win16/dib.c','src/lib/win16/text.c','src/lib/win16/audio.c','src/lib/win16/file.c','src/lib/win16/file_replace.c','src/lib/kvm/video.c','src/lib/kvm/color.c','src/lib/kvm/pointer.c','src/lib/kvm/windows_key.c')
New-Item -ItemType Directory -Force $output | Out-Null
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP
$env:PATH=(Split-Path $compiler)+';'+(Join-Path $env:SystemRoot 'System32');$env:TEMP=$output;$env:TMP=$output
Push-Location $output
try {
 if(!$LinkOnly){
  $objects=@()
  for($i=0;$i -lt $sources.Count;++$i){
   $object="unit$i.obj";$objects+=$object
   & $compiler /nologo "/A$MemoryModel" /G2sw /Gs /D MYGAMES_WIN16_TARGET /W3 /c "/Fo$object" /I $SdkIncludeDirectory /I (Join-Path $repository 'src/lib') (Join-Path $repository $sources[$i])
   if($LASTEXITCODE){throw 'Neutral Win16 probe compile failed.'}
  }
  @('NAME NEUTRAL','EXETYPE WINDOWS','CODE PRELOAD MOVEABLE DISCARDABLE','DATA PRELOAD MOVEABLE MULTIPLE','HEAPSIZE 4096','STACKSIZE 8192','EXPORTS',' MygamesWin16WndProc @1') | Set-Content -Encoding ascii neutral.def
  @(($objects -join "+`n"),'neutral.exe','neutral.map',"$WindowsLibrary+`n$RuntimeLibrary",'neutral.def;') | Set-Content -Encoding ascii neutral.rsp
 }
 if($LinkOnly){& $linker /nologo /NOE /NOD /ALIGN:16 '@neutral.rsp';if($LASTEXITCODE){throw 'Neutral Win16 probe link failed.'}}
} finally {Pop-Location;$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp}

