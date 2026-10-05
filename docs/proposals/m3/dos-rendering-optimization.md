# Candidate: DOS rendering optimization without ROM logic changes

## Owner request and queue position

Place the six discussed optimization opportunities second in the queue,after
the core/PPU module split and before the text object/state visual audit.
This candidate is unnumbered and not admitted. M3 T27 is active after the owner-directed T26 closure;the unresolved
T26 performance obligation is explicitly received below.
At admission,reconcile the completed T26 work and module migration so this
candidate implements only remaining opportunities,without repeating accepted
work or retaining obsolete source paths.

## Objective and ownership

Reduce the cost of producing and presenting the same frame. Preserve original
ROM control flow,state transitions,collision,movement,timers,ordered audio
writes and tick/input ordering. Retain the full256x240 indexed source and
borderless640x400 DOS stretch,no dropped frames/ticks or reduced detail.

CHR/background/sprite optimizations belong to the shared PPU compositor,
now src/ppu/frame after the completed component migration.
They must use the same semantics on DOS16,Win32 and x64. Platform VGA work
consumes only the neutral indexed frame;it cannot read Mario,enemy,level or
other gameplay state. Neutral IO and snapshot contracts remain unchanged.

## Opportunities and suggested order

| Priority | Opportunity | Bounded implementation and correctness obligations |
| --- | --- | --- |
| 1 | CHR decode cache | Decode bound immutable CHR into palette-independent pixel indices once;share the cache between background and sprites. Preserve bounds/absent-resource behavior,flips and transparency. Rebinding resources invalidates the cache;palette animation uses current palette values,never cached final colors. Evaluate full versus bounded cache using actual DOS memory headroom. |
| 2 | Background calculation reuse | Prepare the palette once per frame and reuse tile-row/attribute/address calculations where their inputs are identical. Preserve status-bar split,scroll,mirroring,pattern-bank selection and left-edge masks. Do not cache across a changed visible-state input without an explicit invalidation rule. |
| 3 | Sprite background-occlusion reuse | Retain background opacity information while composing the background;behind-background sprites query that information instead of re-decoding background pixels. Preserve sprite order,transparent pixels,clipping and mask semantics. Select a bounded bit representation after measuring its memory and access cost. |
| 4 | Repeated stretch-row reuse | In the240-to400-row enlargement,convert each unique source row once per plane and copy duplicate output rows. Preserve the exact current coordinate mapping,all pixels and four32000-byte planes. This reduces repeated conversion,not the required complete output or its video-memory writes. |
| 5 | VGA bulk-transfer optimization | Inspect original OpenNT16 generated copy code;optimize contiguous transfers and unnecessary segment setup within the device owner. Retain four correct plane selections,A000 offsets,far-pointer limits and complete submissions. Any specialized helper remains beneath the platform boundary and is admitted explicitly. |
| 6 | Unchanged-region reuse | Consider bounded dirty regions or unchanged-frame reuse only after earlier measurements. Account for every relevant PPU input,resource identity and presentation lifetime event. Scrolling,VRAM/palette/OAM/mask changes,mode switches and snapshot restore must rebuild the affected output. Continue every game tick,input and audio operation;reuse pixels only when equality is established. |

These opportunities can be combined,but their gains overlap. Record both
incremental and cumulative costs;do not multiply isolated speedup ratios or
promise60Hz on a25MHz486SX before qualification. Prefer priorities1-4 first;
use measurements to decide whether5/6 justify their complexity. A cache that
consumes excessive DOS memory or adds more checking cost than it saves is
rejected with a recorded disposition,not silently counted as implemented.

## Planned S breakdown

These are proposal-local S slots,not allocated active identifiers.

| Slot | Scope and exit |
| --- | --- |
| S1 | Reconcile T26/migration receipts;freeze a representative workload,baseline stage costs and DOS storage budget. Name actual owners,cache keys/lifetimes and all six opportunity dispositions. No speed gain claimed from planning. |
| S2 | Shared CHR cache and background calculation reuse as one composition chain. Compare all scoped frame/state outputs,resource/bounds cases and cache lifecycle;measure incremental and combined costs. |
| S3 | Shared background opacity and sprite-priority chain. Prove foreground/behind-background,mask,flip,clipping and overlap output equality;measure memory and time. |
| S4 | DOS stretch-row reuse and contiguous VGA submission chain. Keep the same full-screen mapping;verify all packed bytes,segment guards,plane readback and mode lifecycle. Retain transfer specialization only when measured beneficial. |
| S5 | Decide unchanged-region reuse using S1-S4 measurements. If worthwhile,implement the bounded invalidation contract and compare cache-hit/miss paths;otherwise record rejection and retain the complete redraw path. |
| S6 | Integrated cumulative regression and performance report,including startup,gameplay,transitions,pause,snapshot,graphics/text switching and exit. Report implemented/rejected/deferred opportunities and remaining performance deficit. |

Before each S,report owners,scope,expected size and exact node accounting.
Keep a reference implementation for the admitted comparison contract;each
optimization must pass on its own and combined with accepted predecessors.
An output/state difference is repaired and rechecked in that S before moving
on. If measurements change the proposed grouping,amend it before admission.

## Verification and acceptance

- Compare complete256x240 indexed frames and original game state,visible PPU
  state,OAM,ordered audio and snapshot semantics under identical inputs.
  Palette cycling,scroll/page boundaries,status-bar split,disabled layers,
  sprite priority,partial clipping and resource-rebind cases are explicit.
- Independently compare every packed VGA byte to the current stretch oracle;
  check far-buffer guards,all source-coordinate coverage and plane readback.
  Verify populated actual DOS graphics,Tab round trips,snapshot redraw and
  restored original video mode on Escape. Text output remains unchanged.
- Use the original DOS16 toolchain and Win32 x86/x64 builds,focused tests and
  platform-purity checks. Every product-code P refreshes all three local EXEs;
  documentation/audit-only work does not require a rebuild.
- Measure stage and complete-frame costs with the same workload and unchanged
  installed DOSBox configuration,including sound. Verify config identity;
  no CPU/cycle/frameskip/machine/render overrides or runtime speed shortcuts.
  Isolated dummy-host device checks earn no performance qualification.
- Report baseline,each retained optimization and cumulative results with
  timing overhead,input latency,DOS memory/stack headroom and remaining deficit.
  A faster compositor alone is not a claim that the complete product sustains
  nominal cadence. Physical486SX qualification remains a separate M4 obligation.

Closure requires all six opportunities explicitly disposed,accepted changes
passing both their scoped equality checks and integrated regression,and a
measured cumulative performance result with unresolved limits visible.
Any unmet performance obligation has a named receiver before closure;no new
ROM certification follows from presentation equivalence alone. Exact affected
labels and zero-credit expectations are registered at admission. Retain the
historical/local node and control counts separately from performance results.

All generated probes,profiles,traces,captures and build intermediates remain
under ignored build. This candidate imports no third-party implementation.
Owner-local resources and derived executables remain uncommitted under the
source policy;only neutral evidence summaries enter the proposal/history.

## Accepted T26 remaining-work transfer

Owner closes T26 and admits component separation as T27. This candidate
receives the unproven fixed-config nominal gameplay cadence and remaining
performance optimization obligation. It stays unnumbered after active T27;
reconcile completed T26 work and measure the actual post-split source before
implementation. Neither the transfer nor T26 closure proves playability or
25MHz486SX qualification. No ROM-node responsibility transfers with this
presentation-only obligation.
