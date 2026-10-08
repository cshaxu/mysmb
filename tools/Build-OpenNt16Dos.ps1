param(
    [Parameter(Mandatory = $true)][string]$Compiler,
    [Parameter(Mandatory = $true)][string]$Linker,
    [Parameter(Mandatory = $true)][string]$IncludeDirectory,
    [Parameter(Mandatory = $true)][string]$OutputDirectory,
    [Parameter(Mandatory = $true)][string]$RuntimeDirectory,
    [Parameter(Mandatory = $true)][string]$SourceRoot,
    [string]$RomPath = '',
    [switch]$CompileOnly,
    [ValidateSet('None','Safe')][string]$RenderOptimization = 'Safe',
    [ValidateRange(0,65536)][int]$NearHeapReserveBytes = 4096
)

$toolDirectory = Split-Path -Parent $Compiler
$librarian = Join-Path $toolDirectory 'lib16.exe'
$runtimeLibrary = Join-Path $RuntimeDirectory 'LLIBCE.LIB'
$stackObject = Join-Path $RuntimeDirectory 'LVARSTCK.OBJ'
$runtimeIncludeDirectory = Join-Path (Split-Path -Parent $RuntimeDirectory) 'INC'
$pythonExecutable = (Get-Command python -ErrorAction Stop).Source
$originalBuildPath = $env:PATH
$safeRenderSources = @('ppu/frame.c','io/planar_frame.c','io/palette_pairs.c','io/palette_expand.c',
    'platform/dos16/palette_expand.c','platform/dos16/nibble_expand.c','platform/dos16/slot_copy.c','platform/dos16/planar_row.c')
$sources = @(
    'core/whirlpool.c',
    'core/cannon.c',
    'core/timer.c',
    'core/jumpspring.c',
    'core/vine.c',
    'core/hammer.c',
    'core/coin.c',
    'core/misc.c', 'core/score.c', 'core/power_up_init.c', 'core/power_up.c',
    'core/blocks/head.c', 'core/blocks/bump.c', 'core/blocks/chunks.c', 'core/blocks/lifetime.c', 'core/blocks/replacement.c',
    'core/enemy/lifecycle.c',
    'core/enemy/normal.c',
    'core/enemy/special_callers.c',
    'core/enemy/platform_callers.c',
    'core/enemy/podoboo.c',
    'core/enemy/hammer_bro.c',
    'core/enemy/paratroopa.c',
    'core/enemy/x_counter.c',
    'core/enemy/green_paratroopa.c',
    'core/enemy/bloober.c',
    'core/enemy/bullet_bill.c',
    'core/enemy/swimming_cheep.c',
    'core/enemy/firebar.c',
    'core/enemy/flying_cheep.c',
    'core/enemy/lakitu.c',
    'core/enemy/bowser.c',
    'core/enemy/bowser_flame.c',
    'core/enemy/fireworks.c',
    'core/enemy/star_flag.c',
    'core/enemy/piranha.c',
    'core/enemy/balance_platform.c',
    'core/enemy/platform.c',
    'core/enemy/actor_slots.c',
    'core/world/fireball_enemy.c',
    'core/world/fireball_hit.c',
    'core/world/hammer_collision.c',
    'core/world/powerup_collision.c',
    'core/world/player_enemy_collision.c',
    'core/world/enemy_collision.c',
    'core/enemy/platform_collision.c',
    'core/enemy/platform_position.c',
    'core/oam/fireworks_gfx.c',
    'core/enemy/firebar_children.c',
    'core/enemy/distance.c',
    'core/enemy/background.c', 'core/enemy/jump_terrain.c',
    'core/enemy/side_collision.c',
    'core/area/block_buffer.c',
    'core/area/area_data.c',
    'ppu/state.c', 'core/boot.c', 'core/dispatcher.c', 'core/engine.c', 'core/engine_slots.c', 'core/engine_tail.c', 'core/frame_root.c', 'core/title_modes.c', 'core/terminal_modes.c', 'core/game.c', 'core/audio.c', 'core/area.c', 'core/area/block_metatile.c', 'core/enemy/stream.c', 'core/enemy/group.c', 'core/enemy/init.c', 'core/enemy/init_targets.c', 'core/enemy/loop.c', 'core/enemy/core.c', 'core/enemy/dispatch_targets.c', 'core/enemy/movement.c', 'core/enemy/frenzy.c', 'core/player.c', 'core/player/terrain.c', 'core/player/terrain_metatiles.c', 'core/player/climbing.c', 'core/player/pipe_entry.c', 'core/player/impede.c', 'core/world/metatiles.c', 'core/player_control.c', 'core/player_transition.c', 'core/player_modes.c', 'core/player_end_level.c', 'core/player_movement.c', 'core/scroll.c', 'core/entry.c',
    'core/objects.c', 'core/fireball/fireball_spawn.c', 'core/fireball/fireball_core.c', 'core/world/movement.c', 'core/world/gravity.c', 'core/world/collision.c', 'core/world/block_buffer.c', 'core/world/bounding_box.c',
    'core/world/geometry.c', 'core/bridge.c', 'core/oam/bullet_bill_gfx.c', 'core/oam/hammer_gfx.c', 'core/oam/firebar_gfx.c', 'core/oam/vine_gfx.c', 'core/oam/sprite_stacker.c', 'core/oam/sprite_dump.c', 'core/enemy_bounds.c',
    'core/oam/power_up_gfx.c', 'core/oam/object_position.c', 'core/oam/sprite_row.c', 'core/oam/enemy_offscreen.c', 'core/oam/sprite_draw.c', 'core/oam/block_offscreen.c', 'core/oam/player_gfx.c', 'core/oam/fireball_gfx.c', 'core/oam/block_gfx.c', 'core/oam/goomba_gfx.c',
    'core/fireball/bubble.c', 'core/oam/piranha_gfx.c', 'core/oam/cheep_gfx.c',
    'core/oam/bloober_gfx.c', 'core/oam/podoboo_gfx.c', 'core/oam/normal_enemy_gfx.c',
    'core/oam/spiny_gfx.c', 'core/oam/hammer_bro_gfx.c', 'core/oam/bowser_gfx.c', 'core/oam/bowser_flame_gfx.c', 'core/endgame_objects.c', 'core/oam/flagpole_gfx.c',
    'core/oam/small_platform_gfx.c',
    'ppu/frame.c', 'core/status.c',
    'core/observation.c',
    'text/observer_snapshot.c',
    'text/elements.c', 'text/compact_elements.c', 'text/layout.c', 'text/actor_scene.c',
    'text/background_scene.c', 'text/caption_scene.c',
    'text/scene.c',
    'app/game_io.c', 'app/game_snapshot.c', 'io/color.c', 'io/palette_pairs.c', 'io/palette_expand.c', 'io/text_glyph.c', 'io/scale.c', 'io/pacing.c', 'io/control.c', 'io/snapshot.c', 'io/snapshot_store.c', 'io/snapshot_keys.c', 'io/file/snapshot_files.c', 'platform/dos16/snapshot_replace.c', 'platform/dos16/keyboard.c', 'platform/dos16/pit_clock.c', 'platform/dos16/devices.c',
    'io/file/executable_path.c', 'platform/dos16/executable_path.c',
    'io/planar_frame.c', 'platform/dos16/planar_row.c', 'platform/dos16/palette_expand.c', 'platform/dos16/nibble_expand.c', 'platform/dos16/slot_copy.c', 'platform/dos16/retained_background.c', 'platform/dos16/dos16_root.c',
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
    # The historical optimizer driver overflows its command buffer with a long
    # inherited PATH, even for a tiny C function. This is process-local only.
    $env:PATH = $toolDirectory + ';' + (Join-Path $env:SystemRoot 'System32')
    # Compile the neutral contract probe with the real far-pointer ABI too.
    # It is not linked into the product and supplies no ROM or device data.
    $ioContractProbe = Join-Path (Split-Path -Parent $SourceRoot) 'test/io_contract_smoke.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Foio_contract_smoke.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $ioContractProbe
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $ioBridge = Join-Path $SourceRoot 'app/game_io.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Foapp_game_io.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $ioBridge
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    # Isolated text foundation: check the real far-pointer ABI without linking
    # a dormant presentation path into the current graphical product.
    $textElements = Join-Path $SourceRoot 'text/elements.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fotext_elements.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $textElements
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $textScene = Join-Path $SourceRoot 'text/actor_scene.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fotext_actor_scene.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $textScene
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $textBackground = Join-Path $SourceRoot 'text/background_scene.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fotext_background_scene.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $textBackground
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $objects = @()
    $textCaption = Join-Path $SourceRoot 'text/caption_scene.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fotext_caption_scene.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $textCaption
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    $textAssembly = Join-Path $SourceRoot 'text/scene.c'
    & $Compiler /nologo /AL /Gs /D MYSMB_DOS16_TARGET /c /Fotext_scene.obj /I $IncludeDirectory /I $runtimeIncludeDirectory $textAssembly
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    foreach ($relativeSource in $sources) {
        $source = Join-Path $SourceRoot $relativeSource
        # OpenNT writes /c output into the current directory.  Preserve the
        # source-relative stem so core/enemy/movement.c and
        # core/world/movement.c cannot overwrite one another.
        $object = ($relativeSource -replace '[\\/]', '_' -replace '\.c`$', '.obj')
        $renderFlags = @()
        if ($RenderOptimization -eq 'Safe' -and $relativeSource -in $safeRenderSources) {
            # Keep aliasing and machine-width behavior conservative. No core,
            # IRQ, clock, input, root or startup source enters this whitelist.
            $renderFlags = @('/Ox','/On','/Ow','/G0')
        }
        & $Compiler /nologo /AL /Gs @renderFlags /D MYSMB_DOS16_TARGET @resourceDefines /c /Fo$object /I $IncludeDirectory /I $runtimeIncludeDirectory @resourceIncludes $source
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
    # Resolve the private runtime hook explicitly before LLIBCE is searched.
    $entrySource = Get-Content -Raw -Encoding UTF8 (Join-Path $SourceRoot 'platform/dos16/main_dos16.c')
    if ($entrySource -notmatch '(?m)^\s*int\s+main\s*\(\s*void\s*\)') {
        throw 'The DOS startup hook requires main(void); review argument consumers.'
    }
    $startupSource = Join-Path $SourceRoot 'platform/dos16/process_startup.c'
    & $Compiler /nologo /AL /Gs /c /Fomysmb-startup.obj /I $runtimeIncludeDirectory $startupSource
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    # C vectors are omitted; physical DOS environment and cinit are retained.
    $consumerTool = Join-Path $PSScriptRoot 'VerifyDos16StartupConsumers.py'
    & $pythonExecutable $consumerTool @objects 'mysmb-startup.obj'
    if ($LASTEXITCODE -ne 0) { throw 'DOS CRT vector consumer review required.' }
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
    $objectLine = ((@('mysmb-startup.obj', $entryObject, 'mysmb-stack.obj') + $libraries) -join "+`n")
    @($objectLine, 'mysmb-dos16.exe', 'mysmb-dos16.map', $runtimeLibrary) |
        Set-Content -Encoding Ascii mysmb-dos16.rsp
    if ($CompileOnly) {
        return
    }
    # LINK 5.60 reads response-file fields through its interactive input
    # parser.  Redirecting stdin to NUL supplies the required terminal EOF;
    # otherwise the linker waits after the final library name.  Its segment
    # table also needs room for the fully split shared core.
    $linkCommand = '"' + $Linker + '" /nologo /NOE /SEGMENTS:2048 @mysmb-dos16.rsp < NUL'
    & cmd.exe /d /c $linkCommand
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
    # Keep initialized DGROUP/stack and the original runtime heap bounds;
    # optional near allocations may fail and use their existing far fallback.
    $memoryTool = Join-Path $PSScriptRoot 'VerifyDos16Memory.py'
    & $pythonExecutable $memoryTool (Get-Location).Path --limit-loader-allocation "--near-heap-reserve=$NearHeapReserveBytes"
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

}
finally {
    $env:PATH = $originalBuildPath
    Pop-Location
}
