param(
    [Parameter(Mandatory = $true)][string]$Compiler,
    [Parameter(Mandatory = $true)][string]$Librarian,
    [Parameter(Mandatory = $true)][string]$DosLinker,
    [Parameter(Mandatory = $true)][string]$DosBoxDirectory,
    [Parameter(Mandatory = $true)][string]$IncludeDirectory,
    [Parameter(Mandatory = $true)][string]$SourceRoot,
    [Parameter(Mandatory = $true)][string]$RuntimeDirectory,
    [Parameter(Mandatory = $true)][string]$OutputDirectory,
    [Parameter(Mandatory = $true)][string]$RomPath,
    [string]$Python = 'python'
)
$ErrorActionPreference = 'Stop'
$output = [IO.Path]::GetFullPath($OutputDirectory)
$stage = Join-Path $output 'link365'
$runtime = Join-Path $RuntimeDirectory 'LLIBCE.LIB'
$stack = Join-Path $RuntimeDirectory 'LVARSTCK.OBJ'
if (!(Test-Path -LiteralPath $runtime) -or !(Test-Path -LiteralPath $stack)) {
    throw 'The DOS runtime is missing LLIBCE.LIB or LVARSTCK.OBJ.'
}
if (!(Test-Path -LiteralPath $DosLinker) -or !(Test-Path -LiteralPath (Join-Path $DosBoxDirectory 'DOSBox.exe'))) {
    throw 'The supplied DOS linker or DOSBox directory is unavailable.'
}
$primaryLinker = Join-Path (Split-Path -Parent $Compiler) 'link16.exe'
$pythonExecutable = (Get-Command $Python -ErrorAction Stop).Source
$originalPath = $env:PATH
$originalTemp = $env:TEMP
$originalTmp = $env:TMP
try {
    # OpenNT's compiler launches sibling optimizer passes by name.  This
    # process-local PATH keeps that legacy lookup deterministic.
    $env:PATH = (Split-Path -Parent $Compiler) + ';' +
        (Join-Path $env:SystemRoot 'System32') + ';' + (Split-Path -Parent $pythonExecutable)
    # The legacy optimizer also has a short temporary-path limit.  Keep its
    # private scratch below the repository build tree rather than nesting it
    # beneath a caller-selected output directory.
    $compileTemp = Join-Path (Join-Path (Split-Path -Parent $PSScriptRoot) 'build') 'tmp16'
    New-Item -ItemType Directory -Force -Path $compileTemp | Out-Null
    $env:TEMP = $compileTemp
    $env:TMP = $compileTemp
    & (Join-Path $PSScriptRoot 'Build-OpenNt16Dos.ps1') `
        -Compiler $Compiler -Linker $primaryLinker -IncludeDirectory $IncludeDirectory `
        -SourceRoot $SourceRoot -OutputDirectory $output -RuntimeDirectory $RuntimeDirectory `
        -RomPath $RomPath -CompileOnly
    if ($LASTEXITCODE -ne 0) { throw 'OpenNT object compilation failed.' }
}
finally {
    $env:PATH = $originalPath
    $env:TEMP = $originalTemp
    $env:TMP = $originalTmp
}
& $Python (Join-Path $PSScriptRoot 'PrepareDosLink365Omf.py') `
    --input $output --output $stage --stack 'mysmb-stack.obj' `
    --direct 'mysmb-startup.obj' --direct 'platform_dos16_main_dos16.c'
if ($LASTEXITCODE -ne 0) { throw 'OMF preparation failed.' }
$manifest = Get-Content -Raw (Join-Path $stage 'manifest.json') | ConvertFrom-Json
Push-Location $stage
try {
    foreach ($group in $manifest.groups) {
        $arguments = @('/NOLOGO', $group.library)
        $arguments += @($group.members | ForEach-Object { '+' + (Join-Path 'obj' $_) })
        $arguments += ';'
        & $Librarian @arguments
        if ($LASTEXITCODE -ne 0) { throw ('Library creation failed: ' + $group.library) }
    }
    Copy-Item -LiteralPath $DosLinker -Destination 'LINK.EXE' -Force
    Copy-Item -LiteralPath $runtime -Destination 'RT.LIB' -Force
    $response = @($manifest.direct | ForEach-Object { Join-Path 'obj' $_ })
    $response += @($manifest.stack)
    $response += @($manifest.groups | ForEach-Object { $_.library })
    (($response -join "+`r`n") + ",`r`nMYSMB.EXE,`r`nMYSMB.MAP,`r`nRT.LIB;") |
        Set-Content -Encoding Ascii 'LINK.RSP'
    @'
@echo off
LINK /NOE @LINK.RSP > LINK.LOG
if errorlevel 1 echo 1 > LINK.DON
if not errorlevel 1 echo 0 > LINK.DON
exit
'@ | Set-Content -Encoding Ascii 'LINK.BAT'
    @"
[sdl]
fullscreen=false
output=surface
waitonerror=false
mapperfile=mapper-link365.map
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
mount c "$stage"
c:
LINK.BAT
exit
"@ | Set-Content -Encoding Ascii 'link365.conf'
    $savedVideo = $env:SDL_VIDEODRIVER
    $savedAudio = $env:SDL_AUDIODRIVER
    try {
        $env:SDL_VIDEODRIVER = 'dummy'
        $env:SDL_AUDIODRIVER = 'dummy'
        $process = Start-Process -FilePath (Join-Path $DosBoxDirectory 'DOSBox.exe') `
            -WorkingDirectory $stage -ArgumentList '-noconsole -conf link365.conf' `
            -WindowStyle Hidden -PassThru
        if (!$process.WaitForExit(60000)) {
            Stop-Process -Id $process.Id -Force
            throw 'DOS LINK route exceeded 60 seconds.'
        }
    }
    finally {
        $env:SDL_VIDEODRIVER = $savedVideo
        $env:SDL_AUDIODRIVER = $savedAudio
    }
    if (!(Test-Path -LiteralPath 'LINK.DON') -or
        [IO.File]::ReadAllText('LINK.DON').Trim() -ne '0' -or
        !(Test-Path -LiteralPath 'MYSMB.EXE')) {
        throw 'DOS LINK did not produce a successful executable.'
    }
    $header = [IO.File]::ReadAllBytes((Join-Path $stage 'MYSMB.EXE'))[0..1]
    if ($header[0] -ne 0x4d -or $header[1] -ne 0x5a) { throw 'DOS LINK output is not MZ.' }
    Copy-Item -LiteralPath 'MYSMB.EXE' -Destination (Join-Path $output 'mysmb-dos16.exe') -Force
    Copy-Item -LiteralPath 'MYSMB.MAP' -Destination (Join-Path $output 'mysmb-dos16.map') -Force
}
finally {
    Pop-Location
}
