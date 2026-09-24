# M2 T10 Translated Background Output

## Result

T10 closes the portable background-output route. The native C program now
owns source-shaped name-table, attribute, palette, status, scroll, and
metatile-update state through its NMI-boundary snapshot. This is a background
closure only; it does not establish sprite output, faithful Win32 rendering,
or M2 completion.

## Source Scope

| ROM range | Portable owner | Verified background effect |
| --- | --- | --- |
| `$740-$842`, `$8e19-$8eed` | `game.c` NMI commit and VRAM command transfer | Buffer selection, name tables, palettes, display mask, scroll, and committed PPU state. |
| `$8567-$889c` | `game.c` screen tasks and `area.c` status/message helpers | Static/alternate palettes, title and status streams, intermediate text, Time Up, Game Over, and Warp output. |
| `$88ae-$8acd` | `area.c` parser graphics/attribute and `objects.c` dynamic producers | Incremental columns, attributes, palette rotation, block changes, coin removal, and bridge collapse. |
| `$92b0-$9bff` plus static object handlers | `area.c` persistent parser | Scenery, terrain, parser slots, all static area-object metatile families, and scroll-driven column scheduling. |

The closure sweep found that `render.c` and the platform roots read these
states but do not mutate canonical background state. Win32 begins through
`mysmb_game_begin_title_bootstrap`, which uses the normal screen-task route.
The retained bulk title helper is a test-compatibility API and is not the
product startup path.

## Evidence

ROM-free parser, buffer, palette, mode, area, title-bootstrap, victory,
block, and frame-snapshot tests cover the owners listed above. The bounded
owner-local reference routes in the frame-output ledger cover title, running,
jumping, death/rebuild, opposite-direction movement, coin-block output, and
sprint-hop output. The repaired sprint-hop route has exact two-page CIRAM,
palette, and all seven PPU scalar fields through sample 599. Raw ROM traces
were deleted after their neutral summaries.

The final T10 validation passed the 38-test ROM-enabled suite, Win32 x86 and
x64 builds, the configured OpenNT large-model core compile, documentation
governance, and `git diff --check`.

## Deferred Work

T11 owns all OAM producers and NMI submission: player, enemy, item,
projectile, effect, score, platform, boss, sprite priority, animation, title
sprite work, and offscreen initialization. T12 then replaces the marker
consumer with a native CHR frame consumer. CPU RAM and OAM trace differences
remain unresolved until those owners have direct evidence.
