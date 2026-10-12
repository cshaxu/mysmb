param(
    [Parameter(Mandatory = $true)][string]$Compiler,
    [Parameter(Mandatory = $true)][string]$IncludeDirectory,
    [Parameter(Mandatory = $true)][string]$Source,
    [Parameter(Mandatory = $true)][string]$OutputDirectory
)

$toolDirectory = Split-Path -Parent $Compiler
$kvmIncludeDirectory = Join-Path (Split-Path -Parent (Split-Path -Parent $IncludeDirectory)) 'lib/kvm/include'
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
Push-Location $OutputDirectory
try {
    $env:PATH = $toolDirectory + ';' + $env:PATH
    & $Compiler /nologo /AL /D MYGAMES_DOS16_TARGET /c /I $IncludeDirectory /I $kvmIncludeDirectory $Source
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }
}
finally {
    Pop-Location
}
