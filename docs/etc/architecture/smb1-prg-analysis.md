# SMB1 PRG Static Architecture Record

## Scope And Containment

This record describes the owner-local SMB1 NROM image admitted by M2 T1. It is
an architecture and provenance record, not a ROM dump, disassembly, or
translation. The raw ROM, local listing, control-flow graphs, byte maps, and
generated reports remain ignored. The ROM SHA-256 is
`f61548fdf1670cffefcc4f0b7bdcdd9eaba0c226e3b74f8666071496988248de`.

The image contains a 32 KiB PRG mapped at CPU `$8000-$ffff`; its vectors are
NMI `$8082`, reset `$8000`, and IRQ `$fff0`. Every address below is a CPU PRG
address for this ROM revision.

## Method And Coverage

`smb_static_analysis.py` decodes official 2A03 instruction metadata directly
from the PRG. It starts at all three vectors, follows direct branches, calls,
and jumps, and separately resolves the ROM's `JumpEngine` dispatch idiom. The
analysis found 18 static dispatch tables with 177 candidate target entries,
one indirect jump site, 10,713 decoded instructions, and 12,729 CFG edges.

The optional local listing is never treated as the ROM. Its 10,691 instruction
layout entries are independently reconciled with direct-ROM opcode signatures:
1,428 unique anchors establish two address mappings. Listing addresses through
the anchored `$8000-$9ca3` region map unchanged. From the source-side
`$aeb8` insertion point through the anchored `$f8db` region, the corresponding
ROM address is source address plus `$24`. This explains the previously observed
listing divergence at ROM `$aeb8`; all M2 implementation provenance must name
the ROM address, with the source-side address only as a local research note.

The complete local ledger has these non-overlapping dispositions:

| Disposition | Bytes | Evidence |
| --- | ---: | --- |
| Direct CFG code | 22,821 | Vector-seeded control flow plus static dispatch resolution |
| Reconciled code addition | 12 | Instruction opcode and width match under the measured `$24` relocation |
| Same-address structured data | 6,422 | Listing structure before divergence, checked against ROM alignment |
| Relocated structured data | 3,358 | Listing data structure after the measured relocation |
| ROM-only revision data | 149 | Three explicit ranges outside the reconciled listing structure |
| Vectors | 6 | Fixed NROM vector bytes |
| Unresolved | 0 | No byte is left without a disposition |

The ROM-only data ranges are `$aeb8-$aedb` (revision-specific area-data
extension), `$ff86-$ffef` (revision-specific audio data), and `$fff3-$fff9`
(tail data). They are data dispositions, not executable fall-through.

## Runtime Control Architecture

### Boot, Interrupt, And Frame Ownership

- `$8000` begins reset and cold/warm boot setup. `$8082` is the NMI entry.
- The NMI-owned frame path handles display synchronization, controller
  sampling, timers, pseudo-random state, pause handling, sprite sequencing,
  and the major operating-mode dispatch.
- Controller serialization is rooted at `$8e5c`; title and gameplay code read
  the sampled state rather than a host input API. This is the source boundary
  for MySMB's future neutral input latch.
- `$8212` is the operating-mode execution tree. Its top-level routes include
  title/menu, gameplay, victory, and game-over paths.
- `$8e04` is the reusable stack-return-address dispatch helper. It receives a
  selector and transfers to a following word table. It must become an explicit
  bounded C dispatch table, never a generic indirect-CPU abstraction.

### Title, Menu, Screen, And Mode Transitions

- `$8231` starts title-screen mode; `$8245` owns menu input; `$8255` is the
  start selection path. Demo, continue, world selection, and reset-title
  branches are in this same early mode region.
- `$838b` starts victory mode; `$9218` starts game-over mode. The screen task,
  text, score, timer, palette, and transition support routines are between
  these mode roots and the PPU/area setup region.
- PPU command ownership begins at `$8e19` for name-table initialization.
  `$8eed` writes mirrored PPU control state. This confirms that M1's title
  command transfer is only one part of a larger command and mode pipeline.
- The gameplay operating-mode root is ROM `$aedc`; its dispatch helper call is
  followed by state targets. The main game-core wrapper begins `$aeea` and the
  per-frame gameplay engine begins `$aefe`.

### Area, World, And Object Streams

- `$92b0` owns the area-parser task handler and `$93fc` its core task route.
  `$9508` begins area-data processing, with decode and scroll/warp helpers in
  the following region.
- `$9c03` loads area pointers. The related area/enemy pointer tables and area
  object setup occupy the late `$9cxx` region and feed the parser rather than
  a host-level map format.
- The revision-only range ending immediately before gameplay mode is area data.
  It explains why a different listing revision moves gameplay roots by `$24`
  without changing the earlier boot/title code.

### Player, Physics, Blocks, And Timers

- ROM `$b04a` begins the game-routine dispatcher; `$b0e9` is the player control
  route. Player entrance, automatic control, movement, state changes, death,
  power state, animation, and fireball/bubble work form the `$b0xx-$b7xx`
  region.
- `$b74f` owns the game-timer route. Flagpole and warp behavior are adjacent
  game-mode services, not presentation-only effects.
- Block, coin, mushroom, vine, star, and bouncing-block logic occupy the
  `$b8xx-$befx` region. `$be70` is the block-object core. Horizontal/vertical
  movement and gravity helpers follow it and serve both player and objects.

### Enemy, Collision, Graphics, And Audio

- `$c047` begins the enemy loop core. Enemy stream processing, initialization,
  per-type movement, platforms, and frenzy control extend through `$cxxx`.
- Collision and spatial rules span `$dxxx-$e3xx`: player/enemy,
  fireball/enemy, background, block-buffer, flagpole, and platform relations
  are separate state routes. They must remain separate C units or documented
  shared helpers; a renderer cannot replace their semantics.
- Enemy graphics tables and draw routes follow in `$e7xx-$edxx`. Player
  graphics handling begins `$eee9`; player action selection, offscreen
  calculation, and drawing follow through `$f12a` and nearby routines.
- `$f2d0` begins the sound engine and `$f694` begins the music handler. The
  original writes NES audio registers through game-owned queues, length
  counters, channel state, and event/area music selection. MySMB translates
  this as neutral audio commands and state; host playback is a later adapter.
- Audio and music tables occupy late PRG data, including `$ff86-$ffef`; their
  contents remain local.

## Memory And Hardware Boundary

The direct-CFG access inventory finds 460 distinct direct RAM operand bases,
seven PPU register bases, and 16 APU/I/O bases. It observes 10 direct PPU
reads, 26 direct PPU writes, one direct APU/I/O read, and 50 direct APU/I/O
writes. Indexed and indirect accesses are recorded as access forms rather than
guessed concrete addresses.

The RAM model is organized as follows: `$0000-$00ff` contains scratch,
dispatch, arithmetic, and per-frame temporaries; `$0100-$01ff` contains stack
and temporary use; `$0200-$02ff` is sprite/OAM-equivalent data; `$0300-$03ff`
holds VRAM command buffers and related state; `$0400-$06ff` holds movement,
object, collision, and block-buffer state; `$0700-$07ff` holds persistent mode,
scroll, timer, input, and player/session state. Future C structures may group
fields only when original addresses, aliases, and reset semantics stay
traceable.

## Implementation Consequences

The next task translates ROM `$8231` title mode through the `$aedc` gameplay-
mode transfer, including sampled input and original dispatch tables. The area
bootstrap task starts from `$92b0`, `$9508`, and `$9c03`. Player work starts at
`$b04a/$b0e9`; object and collision work starts at `$be70/$c047`; audio starts
at `$f2d0`. These are implementation-order anchors, not permission to merge
subsystems or replace their state semantics.

## Reproduction

Run the project-owned static analyzer, listing-layout parser, reconciliation
tool, and complete-ledger tool against an owner-local ROM and optional local
review listing. Outputs belong below an ignored build directory. The resulting
ledger must report the vector values, the two measured address mappings, all
disposition counts above, and zero unresolved bytes. The tracked tests exercise
parser, decoder, dispatch, reconciliation, and ledger contracts using
synthetic data only.
