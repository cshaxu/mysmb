# M3 T27: separate the ROM core, PPU, and non-ROM projections

## Owner request and timing

Make the original-ROM game implementation `src/core/` and the original PPU
support implementation `src/ppu/`. Review other components currently mixed
into `src/game/` and split those with a real ownership boundary. Owner admits
this candidate as M3 T27 after closing T26 with remaining
performance work transferred to the queued optimization proposal. S1 starts
with the post-T26 source and product baseline.
This is an architecture and code migration, not a gameplay redesign or a
performance claim by directory move.

## Current ownership census and proposed destinations

The current `src/game/` has 185 files: 14 under `presentation/text/`, two
`ppu_frame` files, four `render`/`frame_snapshot` files and 165 remaining
files. This is a planning snapshot, not a frozen file manifest. The admitted
S1 records every actual file, symbol, build owner, state producer/consumer,
ROM-label provenance and final destination before any move.

### Proposed component structure

This is the target layout for this queue candidate, not the current tree:

```text
src/
  core/                 translated ROM CPU program and canonical game state
    area/ enemy/ player/ world/ blocks/ fireball/ oam/
    boot, frame/NMI, modes, source sound engine, RAM and observation receipts
  ppu/                  PPU storage, registers, visible latch and CHR binding
    state               addressed nametables/palette/OAM and read-only frame view
    frame               shared 256x240 background/sprite pixel compositor
  text/                 authored 80x50 scene, glyph roles and observer consumer
  io/                   neutral input, video, audio, text and snapshot contracts
  app/                  core-to-IO and snapshot composition glue
  platform/
    dos16/ win32/ vga/ file/   devices, mode/scale, timing and file services
  validate/             recorder/reference helpers; absent from product runtime
  assets/               owner-local generated declarations, never tracked
test/                   project-owned tests and validation harnesses
tools/                  build, generator and governance scripts
```

The `state` and `frame` names under `ppu/` describe responsibilities, not
preapproved filenames. S1 decides their exact headers and storage layout.
`src/core/oam/` remains translated ROM sprite-writing code; it is not the
pixel compositor. `src/core/audio.c` remains translated APU command production;
host synthesis stays below `platform/`. `src/validate/` receives the current
test-only `render` and `frame_snapshot` helpers only after S7 confirms no
product consumer. The existing `src/io`, `src/app`, `src/platform`, tests and
tools keep their current roles; this task updates their includes/build lists
as needed, not their behavior.

Allowed dependency direction is `core -> ppu/state` for ROM-defined writes,
`ppu/frame -> ppu/state` for read-only pixels, and
`text -> core` through an immutable observation/state view.
`core` never calls the text implementation, `ppu` never reads core internals,
and `io` imports none of them. Composition roots in `app`/`platform` join the
outputs; `validate` is linked only by tests/recorders. The S1 dependency map
must resolve current observer calls and snapshot ownership before any move so
this structure does not hide a reverse dependency.

| Destination | Current content and boundary |
| --- | --- |
| `src/core/` | Translated 6502 program: boot/NMI/frame-root, title/modes, area, player, enemy, world, objects, OAM writers, source sound engine and CPU RAM. OAM sprite drawing and `audio.c` are ROM routines that produce canonical OAM/APU state; their names do not make them host renderers or synthesizers. |
| `src/ppu/` | Emulated PPU memory/register/visible-frame state and read-only 256x240 background/sprite rasterization, currently represented by fields in `game.h` and `ppu_frame.c/.h`. Own CHR binding and screen pixel production, but no VGA mode, DOS video memory or Win32 window. |
| `src/text/` | The 14 authored text scene, element and observation files. Their scene output is not original-ROM gameplay. Preserve source-decision receipts at the core boundary without a core-to-text implementation dependency or a second mutable owner. |
| `src/validate/` or test support | `render.c/.h` and `frame_snapshot.c/.h`: current call search finds test/recorder consumers, no production root consumer. Keep any required validation API, but do not retain test-only projection in the runtime library merely because it used to sit under `game/`. Confirm link reachability before deciding exact placement. |
| Existing `src/io/`, `src/app/`, `src/platform/` | Retain neutral I/O contracts, composition/snapshot glue and DOS/Windows devices. Do not move the translated sound engine into host audio, or PPU rasterization into a platform adapter. |

The boundary between `core` and `ppu` is important: ROM routines that decide
*when and what* to write to `$2000`/`$2001`, VRAM, palette and OAM remain
translated control flow in `core`; `ppu` owns the addressed storage, visible
latch and pixel interpretation. Core writes through a narrow declared PPU
state/API, while PPU never includes core internals. Preserve exact NMI,
producer/visible-frame, scroll/sprite-0 and DMA timing. Avoid a full-state
copy per frame or host-sized layouts on DOS16. Snapshot bytes and resource
fingerprints keep their current format and meaning.

## Planned S sequence

| S slot | Bounded deliverable | Node forecast |
| --- | --- | --- |
| S1 | Re-census after T26, classify all current files/symbols and 6502 labels, map all call/data edges and test/build consumers, measure existing output/state/ABI baseline and fix the target interface. | Exact scope `[]`, expected new matches `[]` (0). |
| S2 | Extract PPU state ownership and a borrowed, read-only visible-frame view. Migrate core writes/NMI handoff through explicit APIs without changing their translated order or bytes. Recheck state, snapshots and controlled original-ROM route where moved writes touch source semantics. | List exact affected labels and receiving S at admission; expected new matches 0. |
| S3 | Move the shared pixel compositor to `src/ppu/` and consume only the PPU view. Verify full 256x240 indexed pixels, palette, scroll, mirroring, masks, sprite priority and DOS16 far-memory behavior against the pre-move build. | Exact affected-label list at admission; expected new matches 0. |
| S4 | Move core entry/state, frame/NMI, area and mode translation into `src/core/` with source provenance, include/build scripts and tests updated. Do not alter logic while moving it. | Exact moved-label list at admission; expected new matches 0. |
| S5 | Move remaining translated player/enemy/world/object/OAM/sound files in bounded ownership cohorts. Keep original OAM and sound writers with core; test each cohort before the next. | Exact moved-label list per admitted cohort; expected new matches 0. |
| S6 | Extract authored text presentation and its observation contract. Preserve snapshot presentation receipts, text-mode pixel independence and DOS/Win32 console behavior. | Exact scope at admission; expected new matches 0. |
| S7 | Relocate test-only render/frame-snapshot helpers after a link-reachability audit; remove runtime linkage only if no product consumer remains. | Exact scope at admission; expected new matches 0. |
| S8 | Cross-module dependency and integration review: no cycles or direct platform access, complete build/source manifests, DOS16 link, Win32 x86/x64 builds, deterministic state and output equality, sound commands, snapshots, graphical/text switching and actual DOSBox route. Record file/symbol dispositions and remaining limits. | Exact scope at admission; expected new matches 0. |

S4/S5 may be subdivided into smaller S slots if the S1 manifest shows separate
state or ownership chains; no source-order chain crosses an unadmitted edge.
The node ledger retains every existing receiving S and conformance status.
Before each S admission, register its exact moved-label set, incoming count,
zero-credit forecast and tests; no node is silently reclassified by a move.

## Acceptance and non-goals

- The same core tick produces identical CPU RAM, PPU-visible state, OAM,
  ordered APU writes and snapshot bytes for controlled routes before/after.
  The same visible state produces byte-identical indexed pixels and, where
  applicable, VGA output and text cells. A path rename is not ROM proof.
- All product and test targets use one declared owner for mutable state.
  `core` has no dependency on authored text, devices or renderer internals;
  `ppu` does not include core internals; only composition roots wire them.
- The DOS16 large-model build and x86/x64 products, relevant focused tests,
  platform-purity check and actual DOSBox route pass. Repeat T26 performance
  measurement to catch regressions; this task promises no speed gain.
- Do not change gameplay, ROM mapping, pixel content, audio semantics, save
  format, platform behavior or DOSBox settings as part of a structural move.
  Any discovered semantic defect receives a separate admitted repair.
- Owner-local ROM/resource material and generated executables remain ignored
  and uncommitted under the source policy. This candidate imports no new
  third-party implementation.

## T27 S1 P1 admission

Owner approves component separation with original-ROM and PPU semantics
unchanged. S1 is a bounded dependency/storage/interface census,not a source
move or performance implementation. Scope/expected node labels[],new0,
baseline/max1992/1992historical;local1991/1992nodes and4260/4261feasible
controls(raw4342,infeasible81) remain unchanged. Register as audit;existing
ROM receivers remain intact. Estimate0product lines,120-250neutral planning
and inventory lines;generated symbol/include/site manifests stay under build.

S1 enumerates every current file and symbol,PPU/text producer and consumer,
build/test dependency and target destination;then fixes storage and borrowed
views without another mutable owner or full-state copy each frame. Name RAM,
VRAM/palette/OAM,DMA and producer/visible-latch owners,CHR binding,observer
receipts and snapshot offsets/lifetimes explicitly before S2 starts.
No source move,logic rewrite,cache optimization or new runtime emulator is
part of S1. Source and research policy applies to existing local inputs;
no third-party source or new ROM/disassembly import is authorized.

Baseline identity records committed source plus every pre-existing working
change. In particular terrain.c has an unrelated dirty change:preserve it,
record its source identity and do not imply the existing EXEs include it.
Unrelated UI/roadmap/certification changes remain untouched. Before migration,
bind fresh reference tests/products to the chosen working-source manifest.
Existing local P2 binaries alone cannot establish that dirty-source baseline.

Acceptance has two tracks:preserve mapped ROM control/write order and all PPU
contracts;separately demonstrate native build/runtime behavior. Preserve NMI
register/scroll handoff,sprite-0 split,nametable mirrors,palette aliases,
OAM DMA,mask/clipping/priority and resource bounds. Keep snapshot numeric bytes
and observation producer/visible phases unchanged. Compare scoped original-ROM
routes where moved writes touch semantics;pre/post pixel equality alone is
not ROM certification. Record exact affected labels before each migration S.

S1 exit requires complete file/symbol/build dispositions,a reviewed dependency
and state-ownership map,explicit view/lifetime/far-memory contracts,and source-
bound reference verification plans. Later S product changes require original
DOS16 compilation,Win32 x86/x64 tests and all three refreshed local EXEs.
No unexplained state,pixel,audio or snapshot difference may pass to the next S.

## S1 initial census checkpoint

The post-admission file manifest contains185files:165proposed core,2PPU,
14text and4validation files,with447include directives. These are file-level
classifications,not completed symbol or call/data-edge acceptance. The ignored
source-census manifest records source hashes and proposed destinations.

Three boundaries require explicit resolution before migration:game.h currently
includes the authored text observation header;boot/OAM DMA commits producer
and visible observation phases;render/frame_snapshot helpers currently share
the runtime library despite no identified platform/app caller. Direct PPU
state fields in game.h also require a single owner and stable snapshot binding.
S1 remains active until its full symbol/state/interface and baseline obligations
are complete. This checkpoint changes no product source and earns zero nodes.
