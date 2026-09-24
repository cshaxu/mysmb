param(
    [Parameter(Mandatory = $true)][string]$Compiler,
    [Parameter(Mandatory = $true)][string]$Linker,
    [Parameter(Mandatory = $true)][string]$IncludeDirectory,
    [Parameter(Mandatory = $true)][string]$OutputDirectory,
    [Parameter(Mandatory = $true)][string]$RuntimeDirectory,
    [Parameter(Mandatory = $true)][string]$SourceRoot
)

$toolDirectory = Split-Path -Parent $Compiler
$runtimeLibrary = Join-Path $RuntimeDirectory 'LLIBCE.LIB'
$stackObject = Join-Path $RuntimeDirectory 'LVARSTCK.OBJ'
$runtimeIncludeDirectory = Join-Path (Split-Path -Parent $RuntimeDirectory) 'INC'
$sources = @(
    'game/game.c', 'game/audio.c', 'game/area.c', 'game/player.c',
    'game/objects.c', 'game/render.c', 'platform/text/text_frame.c',
    'platform/vga/vga_frame.c', 'platform/dos16/dos16_root.c',
    'platform/dos16/main_dos16.c'
)
if (!(Test-Path -LiteralPath $runtimeLibrary) -or !(Test-Path -LiteralPath $stackObject) -or
    !(Test-Path -LiteralPath $runtimeIncludeDirectory)) {
    throw 'The configured DOS runtime lacks LLIBCE.LIB, LVARSTCK.OBJ, or its INC directory.'
}
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
Push-Location $OutputDirectory
try {
    $env:PATH = $toolDirectory + ';' + $env:PATH
    $objects = @()
    foreach ($relativeSource in $sources) {
        $source = Join-Path $SourceRoot $relativeSource
        & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /I $IncludeDirectory /I $runtimeIncludeDirectory $source
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
        $objects += [System.IO.Path]::GetFileNameWithoutExtension($source) + '.obj'
    }
    $objectLine = ($objects -join '+') + '+' + $stackObject
    @($objectLine, 'mysmb-dos16.exe', 'nul.map', $runtimeLibrary) |
        Set-Content -Encoding Ascii mysmb-dos16.rsp
    & $Linker /nologo '@mysmb-dos16.rsp'
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
finally {
    Pop-Location
}
