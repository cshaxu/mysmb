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
    'game/whirlpool.c',
    'game/cannon.c',
    'game/timer.c',
    'game/jumpspring.c',
    'game/vine.c',
    'game/hammer.c',
    'game/coin.c',
    'game/misc.c', 'game/score.c', 'game/power_up_init.c', 'game/power_up.c',
    'game/blocks/head.c', 'game/blocks/bump.c', 'game/blocks/chunks.c', 'game/blocks/lifetime.c', 'game/blocks/replacement.c',
    'game/enemy/lifecycle.c',
    'game/enemy/normal.c',
    'game/enemy/special_callers.c',
    'game/enemy/platform_callers.c',
    'game/enemy/podoboo.c',
    'game/enemy/hammer_bro.c',
    'game/enemy/paratroopa.c',
    'game/enemy/x_counter.c',
    'game/enemy/green_paratroopa.c',
    'game/enemy/bloober.c',
    'game/enemy/bullet_bill.c',
    'game/enemy/swimming_cheep.c',
    'game/enemy/firebar.c',
    'game/enemy/flying_cheep.c',
    'game/enemy/lakitu.c',
    'game/enemy/bowser.c',
    'game/enemy/bowser_flame.c',
    'game/enemy/fireworks.c',
    'game/enemy/star_flag.c',
    'game/enemy/piranha.c',
    'game/enemy/balance_platform.c',
    'game/enemy/platform.c',
    'game/enemy/actor_slots.c',
    'game/world/fireball_enemy.c',
    'game/world/fireball_hit.c',
    'game/world/hammer_collision.c',
    'game/world/powerup_collision.c',
    'game/world/player_enemy_collision.c',
    'game/oam/fireworks_gfx.c',
    'game/enemy/firebar_children.c',
    'game/enemy/distance.c',
    'game/enemy/background.c',
    'game/enemy/side_collision.c',
    'game/area/block_buffer.c',
    'game/area/area_data.c',
    'game/boot.c', 'game/dispatcher.c', 'game/engine.c', 'game/engine_slots.c', 'game/engine_tail.c', 'game/frame_root.c', 'game/title_modes.c', 'game/terminal_modes.c', 'game/game.c', 'game/audio.c', 'game/area.c', 'game/area/block_metatile.c', 'game/enemy/stream.c', 'game/enemy/group.c', 'game/enemy/init.c', 'game/enemy/init_targets.c', 'game/enemy/loop.c', 'game/enemy/core.c', 'game/enemy/dispatch_targets.c', 'game/enemy/movement.c', 'game/enemy/frenzy.c', 'game/player.c', 'game/player_control.c', 'game/player_transition.c', 'game/player_modes.c', 'game/player_end_level.c', 'game/player_movement.c', 'game/scroll.c', 'game/entry.c',
    'game/objects.c', 'game/fireball/fireball_spawn.c', 'game/fireball/fireball_core.c', 'game/world/movement.c', 'game/world/gravity.c', 'game/world/collision.c', 'game/bridge.c', 'game/oam/bullet_bill_gfx.c', 'game/oam/hammer_gfx.c', 'game/oam/firebar_gfx.c', 'game/oam/vine_gfx.c', 'game/enemy_bounds.c',
    'game/oam/power_up_gfx.c', 'game/oam/object_position.c', 'game/oam/player_gfx.c', 'game/oam/fireball_gfx.c', 'game/oam/block_gfx.c', 'game/oam/goomba_gfx.c',
    'game/fireball/bubble.c', 'game/oam/piranha_gfx.c', 'game/oam/cheep_gfx.c',
    'game/oam/bloober_gfx.c', 'game/oam/podoboo_gfx.c', 'game/oam/normal_enemy_gfx.c',
    'game/oam/spiny_gfx.c', 'game/oam/hammer_bro_gfx.c', 'game/oam/bowser_gfx.c', 'game/oam/bowser_flame_gfx.c', 'game/endgame_objects.c', 'game/oam/flagpole_gfx.c',
    'game/oam/small_platform_gfx.c',
    'game/render.c', 'game/ppu_frame.c', 'game/frame_snapshot.c', 'game/status.c', 'platform/text/text_frame.c',
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
        # OpenNT writes /c output into the current directory.  Preserve the
        # source-relative stem so game/enemy/movement.c and
        # game/world/movement.c cannot overwrite one another.
        $object = ($relativeSource -replace '[\\/]', '_' -replace '\.c`$', '.obj')
        & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fo$object /I $IncludeDirectory /I $runtimeIncludeDirectory $source
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
        $objects += $object
    }
    # LINK 5.60 has a short physical-line limit even inside response files.
    # Keep every continuation line short and stage the stack object locally.
    Copy-Item -LiteralPath $stackObject -Destination 'mysmb-stack.obj' -Force
    $objectLine = (($objects + 'mysmb-stack.obj') -join "+`n")
    @($objectLine, 'mysmb-dos16.exe', 'mysmb-dos16.map', $runtimeLibrary) |
        Set-Content -Encoding Ascii mysmb-dos16.rsp
    # The default LINK 5.60 segment table overflows as shared translation
    # units are split. Increase linker capacity; keep /AL and DOS layout.
    & $Linker /nologo /NOE /SEGMENTS:1024 '@mysmb-dos16.rsp'
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
finally {
    Pop-Location
}
