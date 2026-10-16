param(
    [Parameter(Mandatory=$true)][string]$ProbeDirectory,
    [Parameter(Mandatory=$true)][string]$DosBoxExecutable,
    [Parameter(Mandatory=$true)][string]$DosBoxConfiguration,
    [ValidateSet(0,64)][int]$ConventionalPressureKiB=0
)
$ErrorActionPreference='Stop'
function Get-ConfigurationHash([string]$path) {
    $hash=[Security.Cryptography.SHA256]::Create()
    try {return [BitConverter]::ToString($hash.ComputeHash([IO.File]::ReadAllBytes($path))).Replace('-','')}
    finally {$hash.Dispose()}
}
$repository=Split-Path -Parent $PSScriptRoot
$build=[IO.Path]::GetFullPath((Join-Path $repository 'build'))+'\'
$output=(Resolve-Path $ProbeDirectory).Path
if(!$output.StartsWith($build,[StringComparison]::OrdinalIgnoreCase)){throw 'Runtime must remain below build.'}
$configuration=(Resolve-Path $DosBoxConfiguration).Path
$configurationHash=Get-ConfigurationHash $configuration
if($ConventionalPressureKiB) {
    $source=Join-Path $output 'mysmb-dos16.exe'
    $output=Join-Path $output 'pressure64'
    New-Item -ItemType Directory -Force $output | Out-Null
    Copy-Item -LiteralPath $source -Destination (Join-Path $output 'mysmb-dos16.exe') -Force
    # Own DOS COM helper: free its copied environment (PSP:2Ch, AH49h),
    # then MOV DX,1000h; MOV AX,3100h; INT21h. Retain64KiB including
    # PSP, plus DOS's MCB, independently of the DOSBox configuration.
    [IO.File]::WriteAllBytes((Join-Path $output 'MEMHOLD.COM'),[byte[]](0xa1,0x2c,0x00,0x8e,0xc0,0xb4,0x49,0xcd,0x21,0xba,0x00,0x10,0xb8,0x00,0x31,0xcd,0x21))
}
Copy-Item -LiteralPath (Join-Path $output 'mysmb-dos16.exe') -Destination (Join-Path $output 'CACHE.EXE') -Force
$batch=@('@echo off','if exist CACHE.LOG del CACHE.LOG','if exist FAILED del FAILED','if exist DONE del DONE')
$modes=0..6
if($ConventionalPressureKiB){$batch+='MEMHOLD.COM';$modes=@(0)}
foreach($mode in $modes){$batch+="CACHE.EXE $mode";$batch+='if errorlevel 1 goto failed'}
$batch+=@('echo done>DONE','goto end',':failed','echo failed>FAILED',':end','exit')
$batch | Set-Content -LiteralPath (Join-Path $output 'RUN.BAT') -Encoding ascii
# Only mounting/commands are supplied. CPU, memory, video and audio settings
# come from the unmodified owner's DOSBox configuration.
@('[autoexec]',('mount c "'+$output+'"'),'c:','RUN.BAT','exit') |
    Set-Content -LiteralPath (Join-Path $output 'probe.conf') -Encoding ascii
$savedVideo=$env:SDL_VIDEODRIVER;$savedAudio=$env:SDL_AUDIODRIVER
try {
    $env:SDL_VIDEODRIVER='dummy';$env:SDL_AUDIODRIVER='dummy'
    $arguments='-conf "'+$configuration+'" -conf probe.conf -noconsole'
    $process=Start-Process -FilePath $DosBoxExecutable -ArgumentList $arguments -WorkingDirectory $output -WindowStyle Hidden -PassThru
    if(!$process.WaitForExit(180000)) {
        Stop-Process -Id $process.Id -Force
        throw 'Bounded cache probe exceeded180seconds.'
    }
    if($process.ExitCode -ne 0 -or !(Test-Path (Join-Path $output 'DONE')) -or
        (Test-Path (Join-Path $output 'FAILED'))){throw 'Cache matrix did not complete successfully.'}
    if((Get-ConfigurationHash $configuration) -ne $configurationHash){throw 'DOSBox configuration changed during probe.'}
    $configurationHash | Set-Content -LiteralPath (Join-Path $output 'configuration.sha256') -Encoding ascii
} finally {$env:SDL_VIDEODRIVER=$savedVideo;$env:SDL_AUDIODRIVER=$savedAudio}
