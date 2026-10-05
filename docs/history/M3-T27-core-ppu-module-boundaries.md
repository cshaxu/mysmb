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

## S1 state and interface decisions

| State or operation | Single owner and migration contract |
| --- | --- |
| CPU RAM,frame/startup/mode state and ordered APU writes | Core retains original routines and source order. CPU RAM OAM at0200 remains the producer backing;do not merge it with visible OAM. |
| Nametables,palette,CHR and physical/visible PPU fields | One embedded PPU state object,never a duplicate shadow. PPU state headers have no core/text/host dependency;core retains decisions about when/what to write. Preserve existing register and scroll producer/visible phases and array byte values. |
| NMI and OAM DMA | Core retains the NMI sequence and oam_dma_primed startup guard. PPU transfer takes a borrowed256-byte source span;no core pointer enters the PPU module. Commit visible OAM at the existing call site only. |
| Read-only compositor | Consume a borrowed const PPU state/view and immutable CHR binding. No CPU RAM,gameplay selector,text template or platform access. Retain current nametable/palette phase semantics;do not add another visible copy or rerun ROM writes. |
| Source-decision observations | Move observation.h/.c to core-owned receipt support,not the text renderer. Existing enable/clear/record/commit/invalidate and visible-entry comparison keep their order,capacity and byte semantics. This changes the file-level forecast to167core,12text,2PPU,4validation. Core includes no text implementation. |
| Authored text | Templates and scene composers move to src/text. Read immutable core receipts/state and PPU output;never choose ROM graphics again or mutate source decisions. Existing observation snapshot codec remains a downstream receipt codec with explicit composition binding. |
| Snapshot binding | app owns numeric marshaling across core/PPU/receipt fields. Preserve serialized offsets,resource fingerprints,validation-before-write,schema1 handling and both receipt phases;struct padding is not serialized. |
| DOS storage and devices | Retain16-bit far buffers and original toolchain. The borrowed PPU state/view lives in the root-owned game container through frame production;device adapters receive neutral pixels/cells only. No per-frame game-state clone or heap transaction is introduced. |
| Validation projections | render/frame_snapshot move to validate only after their full symbol caller/link reachability check. Public compatibility remains test/recorder-only;production build lists exclude their implementations. |

Implement storage extraction before compositor separation. A temporary
compositor-to-core include during S2 is explicitly transitional and must be
removed in S3;it cannot survive T closure. New PPU types are independent C90
byte/word types,not imported from core;retain original numeric widths and
neutral IO compatibility. Register-address/mirroring/palette and DMA helpers
belong to PPU storage;ROM control flow and RAM mirrors remain core-owned.
Keep physical-register write before RAM mirror where the original does so.
Do not replace source semantics with a general hardware emulation engine.

The initial source scan enumerates248C/header files,862named function
definitions,1615direct named call sites and206PPU/observation member-access
sites across14source owners. These are lexical inventories,not ROM control
edge counts;macros,aliases and indirect calls require contextual disposition.
Hash-bound source copies and detailed local manifests are retained below
build/m3-t27-s1 for pre/post comparison. Existing14text-file placement was
provisional;the receipt owner decision above deliberately corrects it.

Baseline checks were rebuilt from the current working-source manifest for
both Windows widths and the original DOS16 toolchain. Both widths pass14
focused tests covering PPU composition,NMI/bootstrap/VRAM,state and observation
snapshots,text scenes,IO and platform purity,including the separately selected
NMI-parent integration test. DOS compilation/link succeeds.
All three rebuilt product hashes equal the currently packaged P2 binaries;
terrain.c's reported dirty state has no normalized content diff. The earlier
dirty-source concern is resolved by actual rebuilding and hash comparison,
not an assumption based on file timestamps.

S1 remains open until
the symbol/build mapping,contextual access classification and source-bound
verification baseline are ready;these decisions alone do not close S1.

## S1 P2 owner-directed working-tree review and submission

Owner explicitly assigns review and submission of all pending files to this
agent. Review accepts the roadmap80x50/shared-presenter update and queued M2
handoff checks;correct stale UI placeholder,320x240 and unimplemented speaker
claims,and update T22's handoff paragraph to its actual closed scoped status.
terrain.c has no normalized source change;stage it to reconcile line endings
without claiming a gameplay repair. Product source changes0.

Under the owner's explicit all-pending-files submission instruction,this P
also includes the three already-tracked local EXEs as a narrow exception to
the repository's default no-derived-binary submission guidance. Their bytes
match fresh original-DOS16/x86/x64 builds and the earlier scoped P2 device
receipt:429963/319115/327275bytes. This is a local Git submission only,no remote
or publication is requested. No ROM,generated source,trace or new capture is
added. The source policy otherwise remains in force;no broader redistribution
permission or new ROM-equivalence conclusion is inferred.

S1 source/graph census and interface review continue. Historical1992/1992,
local nodes1991/1992 and feasible controls4260/4261(raw4342,infeasible81) are
unchanged;new0. The current receipts establish a source-bound migration
baseline within the tested contracts,not complete original-game certification.
