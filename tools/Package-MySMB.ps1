param(
    [Parameter(Mandatory = $true)][string]$Dos16Executable,
    [Parameter(Mandatory = $true)][string]$Win32Executable,
    [Parameter(Mandatory = $true)][string]$Win64Executable,
    [string]$OutputDirectory = ''
)

if ($OutputDirectory -eq '') {
    $OutputDirectory = Join-Path (Split-Path -Parent $PSCommandPath) '..\assets'
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

Require-File $Dos16Executable 'DOS executable'
Require-File $Win32Executable 'Win32 executable'
Require-File $Win64Executable 'Win64 executable'
Assert-DosMz $Dos16Executable
Assert-PeMachine $Win32Executable 0x014c 'Win32 executable'
Assert-PeMachine $Win64Executable 0x8664 'Win64 executable'

New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
Copy-Item -LiteralPath $Dos16Executable -Destination (Join-Path $OutputDirectory 'mysmb16.exe') -Force
Copy-Item -LiteralPath $Win32Executable -Destination (Join-Path $OutputDirectory 'mysmb32.exe') -Force
Copy-Item -LiteralPath $Win64Executable -Destination (Join-Path $OutputDirectory 'mysmb64.exe') -Force
