param(
    [Parameter(Mandatory=$true)][string]$Compiler,
    [Parameter(Mandatory=$true)][string]$Linker,
    [Parameter(Mandatory=$true)][string]$SdkIncludeDirectory,
    [Parameter(Mandatory=$true)][string]$WindowsLibrary,
    [Parameter(Mandatory=$true)][string]$RuntimeLibrary,
    [Parameter(Mandatory=$true)][string]$DosStub,
    [Parameter(Mandatory=$true)][string]$RomPath,
    [Parameter(Mandatory=$true)][string]$OutputDirectory,
    [switch]$CompileOnly,
    [switch]$LinkOnly
)
$ErrorActionPreference='Stop'
$repository=Split-Path -Parent $PSScriptRoot
$sourceRoot=Join-Path $repository 'app-mario/src'
$output=[IO.Path]::GetFullPath($OutputDirectory)
$buildRoot=[IO.Path]::GetFullPath((Join-Path $repository 'build'))+'\'
if(!$output.StartsWith($buildRoot,[StringComparison]::OrdinalIgnoreCase)) {
    throw 'Win16 intermediates must be below build.'
}
foreach($path in @($Compiler,$Linker,$SdkIncludeDirectory,$WindowsLibrary,$RuntimeLibrary,$DosStub,$RomPath)) {
    if(!(Test-Path -LiteralPath $path)){throw "Missing configured input: $path"}
}
$Compiler=(Resolve-Path -LiteralPath $Compiler).Path
$Linker=(Resolve-Path -LiteralPath $Linker).Path
$SdkIncludeDirectory=(Resolve-Path -LiteralPath $SdkIncludeDirectory).Path
$WindowsLibrary=(Resolve-Path -LiteralPath $WindowsLibrary).Path
$RuntimeLibrary=(Resolve-Path -LiteralPath $RuntimeLibrary).Path
$DosStub=(Resolve-Path -LiteralPath $DosStub).Path
$RomPath=(Resolve-Path -LiteralPath $RomPath).Path
New-Item -ItemType Directory -Force -Path $output | Out-Null
$oldPath=$env:PATH;$oldTemp=$env:TEMP;$oldTmp=$env:TMP
$python=(Get-Command python -ErrorAction Stop).Source
Push-Location $output
try {
    $env:PATH=(Split-Path -Parent $Compiler)+';'+(Join-Path $env:SystemRoot 'System32')
    $env:TEMP=$output;$env:TMP=$output
    if(!$LinkOnly) {
        $generated=Join-Path $output 'local-rom'
        & $python (Join-Path $PSScriptRoot 'smb_rom_codegen.py') --rom $RomPath --output $generated
        if($LASTEXITCODE){throw 'ROM generator failed'}
        & $python (Join-Path $PSScriptRoot 'smb_title_codegen.py') --rom $RomPath --output $generated
        if($LASTEXITCODE){throw 'Title generator failed'}
        $sources=@(Get-ChildItem -LiteralPath (Join-Path $sourceRoot 'core') -Recurse -Filter *.c | Sort-Object FullName | ForEach-Object {$_.FullName})
        $sources+=@('ppu/state.c','ppu/frame.c','io/palette_expand.c','io/palette_pairs.c','io/input_latch.c','io/control.c','app/input_mapping.c','platform/win16/main_win16.c') | ForEach-Object {Join-Path $sourceRoot $_}
        $sources+=@((Join-Path $repository 'lib/kvm/src/color.c'),(Join-Path $repository 'lib/kvm/src/windows_key.c'),(Join-Path $repository 'lib/win16/src/host.c'),(Join-Path $generated 'smb1_local_rom.c'),(Join-Path $generated 'smb1_local_title.c'))
        $sources+=Join-Path $repository 'lib/win16/src/dib.c'
        $sources+=Join-Path $repository 'lib/win16/src/clock.c'
        $objects=@()
        foreach($source in $sources) {
            $relative=$source.Substring($repository.Length+1)
            $object=($relative -replace '[\\/-]', '_' -replace '\.c$', '.obj')
            $renderFlags=@()
            if($relative.Replace('\','/') -in @('app-mario/src/ppu/frame.c','app-mario/src/io/palette_expand.c','app-mario/src/io/palette_pairs.c','lib/win16/src/dib.c')) {
                # Match the reviewed DOS render-only optimization flags while
                # retaining the Win16 Windows ABI and unchanged core compiler.
                $renderFlags=@('/Ox','/On','/Ow')
            }
            & $Compiler /nologo /AL /G2sw /Gs /W3 @renderFlags /c "/Fo$object" /I $SdkIncludeDirectory /I $sourceRoot /I (Join-Path $repository 'lib/kvm/include') /I (Join-Path $repository 'lib/win16/include') /I $generated $source
            if($LASTEXITCODE){throw "Win16 compile failed: $relative"}
            $objects+=$object
        }
        # Historical LINK's file-descriptor table cannot hold the split core
        # as direct objects. Group OMF members, as in the existing DOS build.
        $entry='app_mario_src_platform_win16_main_win16.obj'
        $members=@($objects | Where-Object {$_ -ne $entry})
        $groups=@()
        $librarian=Join-Path (Split-Path -Parent $Compiler) 'lib16.exe'
        for($first=0;$first -lt $members.Count;$first+=16) {
            $library='w16grp{0:D2}.lib' -f ($first/16)
            if(Test-Path -LiteralPath $library){Remove-Item -LiteralPath $library -Force}
            $last=[Math]::Min($first+15,$members.Count-1)
            $arguments=@('/NOLOGO',$library)+@($members[$first..$last] | ForEach-Object {'+'+$_})+@(';')
            & $librarian @arguments
            if($LASTEXITCODE){throw 'Win16 OMF grouping failed'}
            $groups+=$library
        }
        @('NAME MYSMB','EXETYPE WINDOWS',"STUB 'dos-stub.exe'",'CODE PRELOAD MOVEABLE DISCARDABLE','DATA PRELOAD MOVEABLE MULTIPLE','HEAPSIZE 4096','STACKSIZE 16384','EXPORTS',' MygamesWin16WndProc @1') | Set-Content -Encoding Ascii mysmb-win16.def
        @(((@($entry)+$groups)-join "+`n"),'mysmb16.exe','mysmb16.map',"$WindowsLibrary+`n$RuntimeLibrary",'mysmb-win16.def;') | Set-Content -Encoding Ascii mysmb-win16.rsp
    }
    # LinkOnly must bind the caller's current DOS product, not a stale staged
    # executable left by an earlier compile. Relative inputs were resolved
    # before changing working directory.
    if($DosStub -ne (Join-Path $output 'dos-stub.exe')) {
        Copy-Item -LiteralPath $DosStub -Destination 'dos-stub.exe' -Force
    }
    if(!$CompileOnly) {
        & $Linker /nologo /NOE /NOD /ALIGN:16 /SEGMENTS:2048 '@mysmb-win16.rsp'
        if($LASTEXITCODE){throw 'Win16 link failed'}
        & $python (Join-Path $PSScriptRoot 'bind_win16_mz.py') --stub dos-stub.exe --hybrid mysmb16.exe --repair
        if($LASTEXITCODE){throw 'Win16 MZ preservation failed'}
    }
} finally {
    Pop-Location;$env:PATH=$oldPath;$env:TEMP=$oldTemp;$env:TMP=$oldTmp
}
