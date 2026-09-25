param(
    [string]$AsmPath = 'build/reference-source/SMBDIS.ASM',
    [string]$OutputPath = 'docs/etc/architecture/smb1-rom-migration-inventory.md'
)
$ErrorActionPreference = 'Stop'
$asm = Get-Content -LiteralPath $AsmPath
$hash = (Get-FileHash -Algorithm SHA256 -LiteralPath $AsmPath).Hash.ToLowerInvariant()
$labels = for ($i = 0; $i -lt $asm.Count; $i++) {
    if ($asm[$i] -match '^([A-Za-z_][A-Za-z0-9_]*):') {
        [PSCustomObject]@{ Line = $i + 1; Label = $Matches[1] }
    }
}
$modules = @(
    @('Boot, reset, NMI, timing and input', @('Start','ColdBoot','NonMaskableInterrupt','PauseRoutine','OperModeExecutionTree')),
    @('Title, demo, selection and victory modes', @('TitleScreenMode','GameMenuRoutine','DemoEngine','VictoryMode','PlayerEndWorld')),
    @('Screen sequencing, text, status and PPU buffers', @('ScreenRoutines','InitScreen','WriteTopStatusLine','WriteBottomStatusLine','AreaParserTaskControl','WriteGameText')),
    @('Area parser, metatile/attribute rendering and scrolling', @('RenderAreaGraphics','RenderAttributeTables','AreaParserTaskHandler','AreaParserCore','AreaParserTasks','ScrollScreen')),
    @('Game engine, mode transitions and timers', @('GameCoreRoutine','GameEngine','GameRoutines','GameTimerExpired','PlayerEndLevel')),
    @('Player movement, physics, collision and size state', @('PlayerCtrlRoutine','MovePlayerHorizontally','PlayerBGCollision','PlayerHeadCollision','PlayerChangeSize')),
    @('Enemy stream, object initialization and enemy behavior', @('ProcessEnemyData','PositionEnemyObj','CheckpointEnemyID','EnemiesAndLoopsCore','RunNormalEnemies')),
    @('Blocks, coins, power-ups, vines and miscellaneous objects', @('BlockObjMT_Updater','BumpBlock','CoinBlock','SetupPowerUp','PowerUpObjHandler','VineObjectHandler')),
    @('Fireballs, projectile collision and special hazards', @('FireballObjCore','FireballBGCollision','FireballEnemyCollision','ProcFireball_Bubble')),
    @('Object graphics, OAM construction and offscreen bits', @('PlayerGfxHandler','EnemyGraphicsEngine','MiscObjOffset','GetEnemyOffscreenBits','GetFireballOffscreenBits')),
    @('Audio engine, music and sound effects', @('SoundEngine','Square1SfxHandler','Square2SfxHandler','NoiseSfxHandler','MusicHandler')),
    @('Shared arithmetic, RNG, VRAM and utility primitives', @('InitializeMemory','GetPlayerOffscreenBits','RelativePlayerPosition','MoveObjectHorizontally','ImposeGravity'))
)
$out = New-Object System.Collections.Generic.List[string]
$out.Add('# SMB1 ROM migration inventory and conformance checklist')
$out.Add('')
$out.Add('Generated from `build/reference-source/SMBDIS.ASM`; SHA-256: `' + $hash + '`. This file is the mandatory work index for the native C port. It intentionally records no inferred equivalence: an item is conformant only when its original branch semantics, writes, and frame-trace evidence are recorded.')
$out.Add('')
$out.Add('## Rules')
$out.Add('')
$out.Add('- ROM assembly is the authority for all game behavior. The C source must name the original routine(s) it ports.')
$out.Add('- `src/game` owns every game decision, PPU-state construction, OAM construction, and input decoding. `src/platform` may only collect host input, schedule frames, and submit the already constructed frame.')
$out.Add('- A green unit test alone does not close an item. Each behavioral item needs a ROM-reference frame script and comparison of the affected CPU RAM, CIRAM, palette, OAM, PPU state, and audio state.')
$out.Add('- No ad-hoc behavior change is permitted. A repair first names the checklist entry, original labels, exact source branch path, and regression route.')
$out.Add('- The control graph is authoritative for executable structure. Data labels are separately tracked because tables and constants are part of ROM fidelity, but they do not become synthetic C functions.')
$out.Add('')
$out.Add('## Inventory size')
$out.Add('')
$out.Add('- Assembly labels: `' + $labels.Count + '`')
$out.Add('')
$out.Add('## Authoritative top-level execution tree')
$out.Add('')
$out.Add('```text')
$out.Add('Start / ColdBoot')
$out.Add('├─ InitializeMemory, InitializeNameTables, title bootstrap')
$out.Add('└─ NonMaskableInterrupt — once per frame')
$out.Add('   ├─ InitScroll(0,0) → OAM DMA → UpdateScreen')
$out.Add('   ├─ SoundEngine → ReadJoypads → PauseRoutine → UpdateTopScore')
$out.Add('   ├─ timer bank / FrameCounter / LFSR')
$out.Add('   ├─ sprite-0 split: MoveSpritesOffscreen + SpriteShuffler → scene scroll')
$out.Add('   └─ OperModeExecutionTree')
$out.Add('      ├─ TitleScreenMode')
$out.Add('      ├─ GameMode')
$out.Add('      │  ├─ InitializeArea')
$out.Add('      │  ├─ ScreenRoutines')
$out.Add('      │  ├─ SecondaryGameSetup')
$out.Add('      │  └─ GameCoreRoutine')
$out.Add('      │     ├─ GameRoutines[GameEngineSubroutine]')
$out.Add('      │     └─ GameEngine')
$out.Add('      │        ├─ ProcFireball_Bubble')
$out.Add('      │        ├─ six × (EnemiesAndLoopsCore → FloateyNumbersRoutine)')
$out.Add('      │        ├─ player relative position / PlayerGfxHandler')
$out.Add('      │        ├─ block objects → misc objects → cannon/whirlpool/flagpole')
$out.Add('      │        └─ timer/palette/parser/save-input tail')
$out.Add('      ├─ VictoryMode')
$out.Add('      └─ GameOverMode')
$out.Add('```')
$out.Add('')
$out.Add('The labels and branches behind every line remain open until individually bound below. Source anchors: `NonMaskableInterrupt` line 764, `OperModeExecutionTree` line 954, `GameMode` line 5310, `GameCoreRoutine` line 5318, `GameEngine` line 5336, and `GameRoutines` line 5583.')
$out.Add('')
$out.Add('## Logical tree and module gates')
$out.Add('')
foreach ($m in $modules) {
    $out.Add('- [ ] **' + $m[0] + '**')
    foreach ($entry in $m[1]) {
        $found = $labels | Where-Object Label -eq $entry | Select-Object -First 1
        if ($null -eq $found) { $out.Add('  - [ ] `' + $entry + '` — label lookup pending') }
        else { $out.Add('  - [ ] `' + $entry + '` — ROM line ' + $found.Line + '; C owner/evidence pending') }
    }
}
$out.Add('')
$out.Add('## Mandatory conformance gates')
$out.Add('')
$out.Add('- [ ] Every label below is assigned to exactly one logical owner or explicitly classified as a local branch of an assigned owner.')
$out.Add('- [ ] Every `src/game` entry point has its ROM label set, state-write map, and trace route recorded.')
$out.Add('- [ ] Every visible OAM family, status-bar split, palette/CIRAM path, and audio queue has a matching reference route.')
$out.Add('- [ ] W1-1 title/start, movement/jump, coin/block, mushroom/fire-flower, damage/death/restart, pipe, flag/castle, warp and two-player routes pass frame comparison on x86 and x64.')
$out.Add('- [ ] x86 and x64 native traces are byte-identical for every approved route.')
$out.Add('- [ ] DOS backend consumes the same game frame contract; its adapter has no game-state write.')
$out.Add('')
$out.Add('## Complete ROM label index — unclassified items remain open')
$out.Add('')
$out.Add('| ROM source line | label | owner | status | evidence |')
$out.Add('|---:|---|---|---|---|')
foreach ($l in $labels) { $out.Add('| ' + $l.Line + ' | `' + $l.Label + '` | unassigned | open | none |') }
$dir = Split-Path -Parent $OutputPath
if (!(Test-Path -LiteralPath $dir)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
$dot = New-Object System.Collections.Generic.List[string]
$dot.Add('digraph smb1_rom {')
$dot.Add('  rankdir=LR;')
$dot.Add('  node [shape=box,fontname="Consolas",fontsize=9];')
$current = $null
$edges = New-Object System.Collections.Generic.HashSet[string]
for ($i = 0; $i -lt $asm.Count; $i++) {
    if ($asm[$i] -match '^([A-Za-z_][A-Za-z0-9_]*):') { $current = $Matches[1] }
    if ($null -ne $current -and $asm[$i] -match '^\s*(jsr|jmp|bcc|bcs|beq|bmi|bne|bpl|bvc|bvs)\s+([A-Za-z_][A-Za-z0-9_]*)\b') {
        $kind = $Matches[1].ToUpperInvariant(); $target = $Matches[2]
        if (($labels.Label -contains $target) -and $target -ne $current) {
            [void]$edges.Add('  "' + $current + '" -> "' + $target + '" [label="' + $kind + '"];')
        }
    }
}
foreach ($edge in ($edges | Sort-Object)) { $dot.Add($edge) }
$dot.Add('}')
$controlNodes = @(($edges | ForEach-Object { @($_.Split('"')[1], $_.Split('"')[3]) }) | Sort-Object -Unique)
$out.Add('')
$out.Add('## Control-graph size')
$out.Add('')
$out.Add('- Executable control nodes with an explicit edge: `' + $controlNodes.Count + '`')
$out.Add('- Static/data-only or unconnected labels requiring separate classification: `' + ($labels.Count - $controlNodes.Count) + '`')
$dotPath = Join-Path (Split-Path -Parent $AsmPath) 'smb1-rom-controlgraph.dot'
$gameFiles = Get-ChildItem -LiteralPath 'src/game' -Recurse -File -Include '*.c','*.h'
$gameText = ($gameFiles | ForEach-Object { Get-Content -LiteralPath $_.FullName -Raw }) -join "`n"
$covered = New-Object System.Collections.Generic.HashSet[string]
foreach ($l in $labels) {
    if ($gameText -match ('(?<![A-Za-z0-9_])' + [regex]::Escape($l.Label) + '(?![A-Za-z0-9_])')) { [void]$covered.Add($l.Label) }
}
$audit = New-Object System.Collections.Generic.List[string]
$audit.Add('# ROM migration baseline audit')
$audit.Add('')
$audit.Add('- ROM symbols: ' + $labels.Count)
$audit.Add('- Symbols mentioned anywhere in `src/game`: ' + $covered.Count)
$audit.Add('- A mention is not migration proof. All items remain open until the inventory records a C owner, state-write map, and frame-reference evidence.')
$audit.Add('')
$audit.Add('## Mentioned ROM symbols')
$audit.Add('')
foreach ($name in ($covered | Sort-Object)) { $audit.Add('- `' + $name + '`') }
$audit.Add('')
$audit.Add('## Unmentioned ROM symbols — mandatory classification backlog')
$audit.Add('')
foreach ($l in $labels) { if (!$covered.Contains($l.Label)) { $audit.Add('- ROM line ' + $l.Line + ': `' + $l.Label + '`') } }
$auditPath = Join-Path (Split-Path -Parent $AsmPath) 'smb1-rom-migration-baseline-audit.md'
[IO.File]::WriteAllLines($auditPath, $audit, [Text.UTF8Encoding]::new($false))
[IO.File]::WriteAllLines($dotPath, $dot, [Text.UTF8Encoding]::new($false))
[IO.File]::WriteAllLines($OutputPath, $out, [Text.UTF8Encoding]::new($false))
Write-Output ('mentioned=' + $covered.Count)
Write-Output ('baselineAudit=' + (Resolve-Path -LiteralPath $auditPath))
Write-Output ('edges=' + $edges.Count)
Write-Output ('controlgraph=' + (Resolve-Path -LiteralPath $dotPath))
Write-Output ('labels=' + $labels.Count)
Write-Output ('output=' + (Resolve-Path -LiteralPath $OutputPath))
