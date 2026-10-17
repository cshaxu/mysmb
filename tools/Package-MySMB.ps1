param(
    [Parameter(Mandatory = $true)][string]$Dos16Executable,
    [Parameter(Mandatory = $true)][string]$Win16Executable,
    [Parameter(Mandatory = $true)][string]$Win32Executable,
    [Parameter(Mandatory = $true)][string]$Win64Executable,
    [Parameter(Mandatory = $true)][string]$Win32BuildDirectory,
    [Parameter(Mandatory = $true)][string]$Win64BuildDirectory,
    [string]$OutputDirectory = ''
)

if ($OutputDirectory -eq '') {
    $OutputDirectory = Join-Path (Split-Path -Parent $PSCommandPath) '..\assets\mario'
}

function Require-File([string]$Path, [string]$Label) {
    if (!(Test-Path -LiteralPath $Path -PathType Leaf)) {
        throw "$Label does not exist: $Path"
    }
}

function Read-UInt16([byte[]]$Bytes, [int]$Offset) {
    return [BitConverter]::ToUInt16($Bytes, $Offset)
}

function Read-UInt32([byte[]]$Bytes, [int]$Offset) {
    return [BitConverter]::ToUInt32($Bytes, $Offset)
}

function Assert-DosMz([string]$Path) {
    $header = [System.IO.File]::ReadAllBytes($Path)
    if ($header.Length -lt 2 -or $header[0] -ne 0x4d -or $header[1] -ne 0x5a) {
        throw "DOS executable is not an MZ image: $Path"
    }
}

function Assert-PeMachine([string]$Path, [UInt16]$ExpectedMachine, [string]$Label) {
    $header = [System.IO.File]::ReadAllBytes($Path)
    if ($header.Length -lt 64 -or $header[0] -ne 0x4d -or $header[1] -ne 0x5a) {
        throw "$Label is not an MZ/PE image: $Path"
    }
    $peOffset = Read-UInt32 $header 60
    if ($peOffset -gt $header.Length - 6 -or
        $header[$peOffset] -ne 0x50 -or $header[$peOffset + 1] -ne 0x45 -or
        $header[$peOffset + 2] -ne 0 -or $header[$peOffset + 3] -ne 0) {
        throw "$Label does not contain a PE signature: $Path"
    }
    if ((Read-UInt16 $header ($peOffset + 4)) -ne $ExpectedMachine) {
        throw "$Label has an unexpected PE machine type: $Path"
    }
}

function Assert-16BitKind([string]$Path, [bool]$Hybrid) {
    Assert-DosMz $Path
    $header = [System.IO.File]::ReadAllBytes($Path)
    if ($header.Length -lt 64) { throw 'Truncated 16-bit executable header' }
    $offset = Read-UInt32 $header 60
    $signature = ''
    if ($offset -ge 64 -and $offset -le $header.Length - 2) {
        $signature = [Text.Encoding]::ASCII.GetString($header, $offset, 2)
    }
    if ($Hybrid) {
        if ($signature -ne 'NE' -or $offset -gt $header.Length - 64) {
            throw 'Win16 executable must contain a native NE header'
        }
    } elseif ($signature -in @('NE','PE','LE','LX')) {
        throw 'DOS executable must be a pure MZ, not a native hybrid'
    }
}

function Assert-LocalResourceBuild([string]$BuildDirectory, [string]$Label) {
    $cache = Join-Path $BuildDirectory 'CMakeCache.txt'
    $ninja = Join-Path $BuildDirectory 'build.ninja'
    Require-File $cache "$Label CMake cache"
    Require-File $ninja "$Label build manifest"
    $cacheText = [System.IO.File]::ReadAllText($cache)
    $ninjaText = [System.IO.File]::ReadAllText($ninja)
    if ($cacheText -notmatch '(?m)^MYSMB_ROM_PATH:FILEPATH=.+') {
        throw "$Label was not configured with owner-local ROM resources"
    }
    if ($ninjaText -notmatch 'MYSMB_LOCAL_TITLE=1') {
        throw "$Label does not bind owner-local title resources"
    }
}

Require-File $Dos16Executable 'DOS executable'
Require-File $Win16Executable 'Win16 executable'
Require-File $Win32Executable 'Win32 executable'
Require-File $Win64Executable 'Win64 executable'
Assert-16BitKind $Dos16Executable $false
Assert-16BitKind $Win16Executable $true
Assert-PeMachine $Win32Executable 0x014c 'Win32 executable'
Assert-PeMachine $Win64Executable 0x8664 'Win64 executable'
Assert-LocalResourceBuild $Win32BuildDirectory 'Win32 build'
Assert-LocalResourceBuild $Win64BuildDirectory 'Win64 build'

# A hybrid must contain this exact DOS program, including resident bounds.
& python (Join-Path $PSScriptRoot 'bind_win16_mz.py') --stub $Dos16Executable --hybrid $Win16Executable
if ($LASTEXITCODE -ne 0) { throw 'Win16 hybrid does not preserve the DOS program' }

New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
Copy-Item -LiteralPath $Dos16Executable -Destination (Join-Path $OutputDirectory 'mysmb16c.exe') -Force
Copy-Item -LiteralPath $Win16Executable -Destination (Join-Path $OutputDirectory 'mysmb16w.exe') -Force
Copy-Item -LiteralPath $Win32Executable -Destination (Join-Path $OutputDirectory 'mysmb32.exe') -Force
Copy-Item -LiteralPath $Win64Executable -Destination (Join-Path $OutputDirectory 'mysmb64.exe') -Force
$legacy = Join-Path $OutputDirectory 'mysmb16.exe'
if (Test-Path -LiteralPath $legacy -PathType Leaf) {
    Remove-Item -LiteralPath $legacy -Force
}
