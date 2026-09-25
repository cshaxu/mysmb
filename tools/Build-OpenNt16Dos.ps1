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
    'game/boot.c', 'game/frame_root.c', 'game/title_modes.c', 'game/terminal_modes.c', 'game/game.c', 'game/audio.c', 'game/area.c', 'game/player.c',
    'game/objects.c', 'game/bridge.c', 'game/bullet_bill_gfx.c', 'game/hammer_gfx.c', 'game/firebar_gfx.c', 'game/vine_gfx.c', 'game/enemy_bounds.c',
    'game/power_up_gfx.c', 'game/block_gfx.c', 'game/goomba_gfx.c',
    'game/bubble_gfx.c', 'game/piranha_gfx.c', 'game/cheep_gfx.c',
    'game/bloober_gfx.c', 'game/podoboo_gfx.c', 'game/normal_enemy_gfx.c',
    'game/spiny_gfx.c', 'game/hammer_bro_gfx.c', 'game/bowser_gfx.c', 'game/bowser_flame_gfx.c', 'game/endgame_objects.c', 'game/flagpole_gfx.c',
    'game/small_platform_gfx.c',
    'game/render.c', 'game/ppu_frame.c', 'game/frame_snapshot.c', 'platform/text/text_frame.c',
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
    # LINK 5.60 has a short physical-line limit even inside response files.
    # Keep every continuation line short and stage the stack object locally.
    Copy-Item -LiteralPath $stackObject -Destination 'mysmb-stack.obj' -Force
    $objectLine = (($objects + 'mysmb-stack.obj') -join "+`n")
    @($objectLine, 'mysmb-dos16.exe', 'mysmb-dos16.map', $runtimeLibrary) |
        Set-Content -Encoding Ascii mysmb-dos16.rsp
    & $Linker /nologo /NOE '@mysmb-dos16.rsp'
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
finally {
    Pop-Location
}
