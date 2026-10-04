param(
    [Parameter(Mandatory = $true)][string]$Compiler,
    [Parameter(Mandatory = $true)][string]$Linker,
    [Parameter(Mandatory = $true)][string]$IncludeDirectory,
    [Parameter(Mandatory = $true)][string]$OutputDirectory,
    [Parameter(Mandatory = $true)][string]$RuntimeDirectory,
    [Parameter(Mandatory = $true)][string]$SourceRoot,
    [string]$RomPath = ''
)

$toolDirectory = Split-Path -Parent $Compiler
$librarian = Join-Path $toolDirectory 'lib16.exe'
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
    'game/world/enemy_collision.c',
    'game/enemy/platform_collision.c',
    'game/enemy/platform_position.c',
    'game/oam/fireworks_gfx.c',
    'game/enemy/firebar_children.c',
    'game/enemy/distance.c',
    'game/enemy/background.c', 'game/enemy/jump_terrain.c',
    'game/enemy/side_collision.c',
    'game/area/block_buffer.c',
    'game/area/area_data.c',
    'game/boot.c', 'game/dispatcher.c', 'game/engine.c', 'game/engine_slots.c', 'game/engine_tail.c', 'game/frame_root.c', 'game/title_modes.c', 'game/terminal_modes.c', 'game/game.c', 'game/audio.c', 'game/area.c', 'game/area/block_metatile.c', 'game/enemy/stream.c', 'game/enemy/group.c', 'game/enemy/init.c', 'game/enemy/init_targets.c', 'game/enemy/loop.c', 'game/enemy/core.c', 'game/enemy/dispatch_targets.c', 'game/enemy/movement.c', 'game/enemy/frenzy.c', 'game/player.c', 'game/player/terrain.c', 'game/player/terrain_metatiles.c', 'game/player/climbing.c', 'game/player/pipe_entry.c', 'game/player/impede.c', 'game/world/metatiles.c', 'game/player_control.c', 'game/player_transition.c', 'game/player_modes.c', 'game/player_end_level.c', 'game/player_movement.c', 'game/scroll.c', 'game/entry.c',
    'game/objects.c', 'game/fireball/fireball_spawn.c', 'game/fireball/fireball_core.c', 'game/world/movement.c', 'game/world/gravity.c', 'game/world/collision.c', 'game/world/block_buffer.c', 'game/world/bounding_box.c',
    'game/world/geometry.c', 'game/bridge.c', 'game/oam/bullet_bill_gfx.c', 'game/oam/hammer_gfx.c', 'game/oam/firebar_gfx.c', 'game/oam/vine_gfx.c', 'game/oam/sprite_stacker.c', 'game/oam/sprite_dump.c', 'game/enemy_bounds.c',
    'game/oam/power_up_gfx.c', 'game/oam/object_position.c', 'game/oam/sprite_row.c', 'game/oam/enemy_offscreen.c', 'game/oam/sprite_draw.c', 'game/oam/block_offscreen.c', 'game/oam/player_gfx.c', 'game/oam/fireball_gfx.c', 'game/oam/block_gfx.c', 'game/oam/goomba_gfx.c',
    'game/fireball/bubble.c', 'game/oam/piranha_gfx.c', 'game/oam/cheep_gfx.c',
    'game/oam/bloober_gfx.c', 'game/oam/podoboo_gfx.c', 'game/oam/normal_enemy_gfx.c',
    'game/oam/spiny_gfx.c', 'game/oam/hammer_bro_gfx.c', 'game/oam/bowser_gfx.c', 'game/oam/bowser_flame_gfx.c', 'game/endgame_objects.c', 'game/oam/flagpole_gfx.c',
    'game/oam/small_platform_gfx.c',
    'game/render.c', 'game/ppu_frame.c', 'game/frame_snapshot.c', 'game/status.c',
    'app/game_io.c', 'io/color.c', 'io/scale.c', 'io/pacing.c', 'platform/dos16/keyboard.c', 'platform/dos16/pit_clock.c', 'platform/dos16/devices.c',
    'platform/vga/vga_frame.c', 'platform/dos16/dos16_root.c',
    'platform/dos16/main_dos16.c'
)
if (!(Test-Path -LiteralPath $runtimeLibrary) -or !(Test-Path -LiteralPath $stackObject) -or
    !(Test-Path -LiteralPath $runtimeIncludeDirectory)) {
    throw 'The configured DOS runtime lacks LLIBCE.LIB, LVARSTCK.OBJ, or its INC directory.'
}
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
$resourceIncludes = @()
$resourceDefines = @()
$resourceSources = @()
if ($RomPath -ne '') {
    $generatorRoot = Split-Path -Parent $SourceRoot
    $resourceDirectory = Join-Path ([IO.Path]::GetFullPath($OutputDirectory)) 'local-rom'
    & python (Join-Path $generatorRoot 'tools/smb_rom_codegen.py') --rom $RomPath --output $resourceDirectory
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    & python (Join-Path $generatorRoot 'tools/smb_title_codegen.py') --rom $RomPath --output $resourceDirectory
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $resourceIncludes = @('/I', $resourceDirectory)
    $resourceDefines = @('/D', 'MYSMB_LOCAL_TITLE')
    $resourceSources = @('smb1_local_rom.c', 'smb1_local_title.c')
}
Push-Location $OutputDirectory
try {
    $env:PATH = $toolDirectory + ';' + $env:PATH
    # Compile the neutral contract probe with the real far-pointer ABI too.
    # It is not linked into the product and supplies no ROM or device data.
    $ioContractProbe = Join-Path (Split-Path -Parent $SourceRoot) 'test/io_contract_smoke.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Foio_contract_smoke.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $ioContractProbe
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $ioBridge = Join-Path $SourceRoot 'app/game_io.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Foapp_game_io.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $ioBridge
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $objects = @()
    foreach ($relativeSource in $sources) {
        $source = Join-Path $SourceRoot $relativeSource
        # OpenNT writes /c output into the current directory.  Preserve the
        # source-relative stem so game/enemy/movement.c and
        # game/world/movement.c cannot overwrite one another.
        $object = ($relativeSource -replace '[\\/]', '_' -replace '\.c`$', '.obj')
        & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET @resourceDefines /c /Fo$object /I $IncludeDirectory /I $runtimeIncludeDirectory @resourceIncludes $source
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
        $objects += $object
    }
    foreach ($resourceSource in $resourceSources) {
        $object = [IO.Path]::ChangeExtension($resourceSource, '.obj')
        & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fo$object /I $resourceDirectory (Join-Path $resourceDirectory $resourceSource)
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
        $objects += $object
    }
    # LINK 5.60 has a short physical-line limit even inside response files.
    # Keep every continuation line short and stage the stack object locally.
    Copy-Item -LiteralPath $stackObject -Destination 'mysmb-stack.obj' -Force
    # LINK 5.60 rejects the runtime library once the direct input set grows
    # past the observed object-file threshold. Group compiled objects into
    # small OMF libraries; keep the main object explicit as the entry root.
    if (!(Test-Path -LiteralPath $librarian)) {
        throw 'The configured compiler directory lacks lib16.exe.'
    }
    $entryObject = 'platform_dos16_main_dos16.c'
    $members = @($objects | Where-Object { $_ -ne $entryObject })
    $libraries = @()
    for ($first = 0; $first -lt $members.Count; $first += 16) {
        # LIB treats '-' as a member-removal operator even in a filename.
        $library = 'smbgrp{0:D2}.lib' -f ($first / 16)
        if (Test-Path -LiteralPath $library) {
            Remove-Item -LiteralPath $library -Force
        }
        $last = [Math]::Min($first + 15, $members.Count - 1)
        $libraryArgs = @('/NOLOGO', $library)
        $libraryArgs += @($members[$first..$last] | ForEach-Object { '+' + $_ })
        $libraryArgs += ';'
        & $librarian @libraryArgs
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
        $libraries += $library
    }
    $objectLine = ((@($entryObject, 'mysmb-stack.obj') + $libraries) -join "+`n")
    @($objectLine, 'mysmb-dos16.exe', 'mysmb-dos16.map', $runtimeLibrary) |
        Set-Content -Encoding Ascii mysmb-dos16.rsp
    # LINK 5.60 reads response-file fields through its interactive input
    # parser.  Redirecting stdin to NUL supplies the required terminal EOF;
    # otherwise the linker waits after the final library name.  Its segment
    # table also needs room for the fully split shared core.
    $linkCommand = '"' + $Linker + '" /nologo /NOE /SEGMENTS:2048 @mysmb-dos16.rsp < NUL'
    & cmd.exe /d /c $linkCommand
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
finally {
    Pop-Location
}
