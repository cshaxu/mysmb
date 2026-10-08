# Project Status

**Active: M3 T36 S1, whole-pipeline performance assessment.**

## M3 T36 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New owner-approved zero-ROM audit after closed T35. |
| Admission And Approval | Owner directs a comprehensive measurement of shared core, PPU, DOS presentation and Win32 presentation to locate worthwhile optimization opportunities. |
| Objective | Attribute current frame cost to input/control, game tick, PPU preparation/composition, palette/device publication, audio handoff and pacing; produce a finite, evidence-backed optimization register. |
| Non-goals | No translated-game behavior change, no DOS-specific core path, no platform presentation policy change, no cache-policy change, no frameskip, no persistent DOSBox setting change and no unmeasured performance claim. |
| Reference Baseline | T34 direct VGA removes a measured duplicate copy; T35 rejects a slower scanline-OAM schedule. Existing DOSBox PIT receipts are descriptive only and are not 486SX qualification. |
| Candidate Proposal | [M3 T36 whole-pipeline profile](../history/M3-T36-whole-pipeline-profile.md). |
| Files And ABI Surface | Expected 200--350 lines of profile/test support or no tracked source if existing diagnostics suffice. Any product code remains unchanged; profile artifacts stay below ignored `build/`. |
| Applicable Rules | Execution,Documentation,Architecture,Coding and source policy; System Architecture and Source Layout. Core remains one portable C90 owner; platforms expose only timing/presentation adapters. |
| Verification | Validate stage boundaries against existing root order; use PIT for DOS16 where available; retain host measurements only as host evidence; repeat bounded samples; audit every candidate for output/state equivalence and memory cost. |
| Expected Markers | ROM scope[],expectedMatches[],actualMatches[],new0;historical1992/1992,local1991/1992nodes,4260/4261feasible controls unchanged(raw4342,infeasible81). |
| Asset Needs | None. Project-owned instrumentation and ignored receipts only. |
| Reporting Requirements | Report stage definitions, route limits, measured cost, uncertainty and each candidate's owner/memory/semantic disposition; include total/local node and edge counters. |
| Stop Conditions | Reject any route that conflates host scheduling with target timing, mutates product behavior, depends on untracked owner assets, or cannot isolate a stage. |
| Exit Criteria | A finite stage-cost report and candidate register exist, with each accepted opportunity assigned to a bounded successor implementation task or explicitly rejected/deferred. |
| Original Owner Request | The owner asks for a comprehensive assessment of core, drawing and display efficiency to identify real optimization opportunities without allowing core divergence. |
| Similar-Issue Sweep | Trace all frame-root phases and both graphical platforms; distinguish shared computation from DOS physical output, Win32 presentation, audio and intentional pacing. |

## Current Technical Baseline

- T34 S3 P47 closes the five-state controlled cache-topology matrix with
  current-root test fixtures below `build/`: none, A-only, B-only, A+B and
  A+B+C each reach their asserted pointer state after normal root steps. A
  stable sixteen-frame native-VGA measurement separates publication from
  composition: the fixed palette-plus-15-band submission costs 24,240--24,441
  PIT ticks (about 20.32--20.48ms) in all five states. Therefore A/B/C reduce
  composition work but do not reduce the fixed 61,440-byte VGA submission;
  this descriptor is DOSBox-only and is not a 486SX cadence claim. The
  restored owner NESticle binary starts at 256x240/no-sound under the same
  unmodified persistent DOSBox configuration, but its noninteractive title
  route has no game-frame accounting and Enter terminates it, so no fair
  reference ratio is claimed.

- T34 S3 P48 implements the DOS16-only synchronous direct-band path while
  preserving the PPU slot-row producer, palette, band order and 256x240
  pixels. The original-toolchain native device probe writes a patterned full
  frame through both buffered and direct paths: each has zero mismatches over
  61,440 pixels, the direct path covers exactly 61,440 bytes in fifteen bands,
  and two text/graphics round trips restore the original display mode. The
  same current root passes the bounded 384KiB title/input/Tab/Escape route;
  x86 and x64 focused host suites pass. The sixteen-frame A+B+C publication
  median is 18,368 PIT ticks (about 15.394ms), versus P47's buffered 24,441
  ticks (about 20.484ms): 5.090ms or 24.85% lower. This is DOSBox-only
  descriptive timing, not a physical 486SX cadence claim. No core/PPU/game,
  cache, frameskip, DOSBox-setting or Windows behavior changed.

- T34 S3 P44 restores the product DOSBox receipt chain and binds the current
  cache boundary to the P43 product. At 384KiB, the full route reaches title,
  input, graphics/text switch, synchronous P/O and Escape return. The product
  MCB trace at 501KiB retains root plus B (compact background) and A, but has
  no C allocation; at 502KiB it additionally retains C. C is requested only
  after both A and B exist, therefore 502KiB is the current observed A+B+C
  threshold and 501KiB the adjacent observed A+B-only route. P45's current
  root probe at 384KiB records A-only directly (`decoded=1,packed=0,
  byteCache=0,near=1`). The remaining low-memory matrix needs zero-cache and
  a controlled B-only allocation-failure receipt; neither is inferred from
  the adjacent thresholds. The owner-suggested 20ms "do not build while
  publishing" candidate is rejected for the current architecture: publication
  is synchronous before the next root step, the existing period is about
  16.67ms, and skipping game ticks would change ROM-frame/input/timer
  semantics. No DOSBox setting changed.

- T34 S3 P43 consolidates the DOS16 text/row store and the single on-demand
  snapshot store into one root-owned far allocation. A same-runtime,
  separate-process DOS allocator probe measures 32,784B for split 15,532B
  plus 10,048B requests and 25,616B for the combined 25,580B request: a
  7,168B realized reduction. The graphics row writer remains confined to the
  existing 4,096B prefix;the snapshot suffix,shared PPU/game behavior,
  snapshot format and Win32 code are unchanged. The full current source
  compiles and links through the original16-bit/compiler LINK3.65 route and
  both Windows-width focused suites pass. Product interactive DOS P/O/title/
  exit evidence is supplied by P44.

- T34 S3 P42 extends the same DOS16 largest-block preflight to B, the
  63,488-byte compact background tier. A block that DOS proves cannot fit B
  now goes directly to A, avoiding a futile fragmented far-heap walk while
  retaining the specified B/A/C selection order and fallbacks. The direct
  diagnostic has separate, smaller platform setup and is retained only as an
  allocator probe. Current-product FIT boundary routes prove 508 KiB reaches
  the B allocation but cannot retain C, while 509 KiB reaches a second
  61,472-byte background allocation, captures title and exits normally. Since
  C is requested only after A and B both succeed, 509 KiB is the current
  product's minimum observed A+B+C threshold; 512 KiB is its rounded safe
  tier. Both Windows-width focused suites pass; no shared PPU/game change.

- T34 S3 P41 keeps the owner-directed B/A/C cache policy but makes the DOS16
  root ask DOS for the current largest conventional block before attempting
  C's 61,440-byte far allocation. When that block cannot fit C, the root
  retains the already selected B/A combination without making a guaranteed
  failing far-heap request; a later allocation may still fail normally after
  a positive preflight. This is DOS16 allocation policy only: shared PPU,
  pixels, cache formats, game decisions and Windows allocation stay unchanged.
  OpenNT CL16 compiled the current source, local LINK 3.65 in private DOSBox
  linked the rebuilt objects to a 325,113-byte MZ, and its MAP has fourteen
  nonempty code segments with a largest bucket of 58,312 bytes. A private
  DOSBox smoke route reached title, Enter, D+J, Escape and normal DOS return.
  Windows x86/x64 keyboard, focus-pause and DOS-root smoke tests pass. The
  original fallback-tier matrix remains open; this receipt does not claim an
  intermediate-memory result or physical performance.

- T34 S3 P39 applies the owner-directed DOS16 optional-cache order without
  changing shared PPU or game decisions: request B (the 63,488-byte packed
  background tier), then A (the 8,192-byte decoded-CHR tier); request C (the
  61,440-byte byte-background upgrade) only when both B and A succeeded.
  Thus B failure falls back to A alone when possible; A failure after B
  retains B alone; C failure retains A+B. Three products require rebuilding
  and the memory-route matrix must prove that no fallback skips this order.
  Its actual unchanged-configuration 384KiB FIT receipt now records
  `decoded=1,packed=0,byteCache=0`: B was unavailable and A was retained.
  An allocation-only current-object probe can retain all three tiers with
  unrestricted conventional memory. The 416/448KiB FIT routes have not
  emitted a post-exec result; the prior 500KiB child did return, but its old
  probe opened its report file too late to observe tiers. All three remain
  unresolved rather than evidence for any intermediate tier.
  Because the owner-installed fixed-base OpenNT `link16.exe` is presently
  rejected by the Windows loader before it can link, P39 may perform a
  build-only, ignored-directory feasibility probe with a local historical
  Microsoft DOS segmented linker against the same OpenNT-generated OMF
  objects and runtime library. It is not a product dependency or a toolchain
  replacement unless its output and limits are separately reviewed.

- T34 S3 P38 restores the local equal-budget reference inputs: the owner ZIP
  and its embedded x.xx EXE match retained hashes, and DOS4GW1.97 launches
  the reference at 256x240/no sound under unchanged DOSBox settings. This
  supersedes P36's missing-file finding only; a controlled equal-route,
  frameskip/submission-accounted comparison remains required. No product,
  ROM-node or control-edge change. [Reference recovery](../history/M3-T34-native-vga-performance-proposal.md#s3-p38-reference-artifact-recovery-and-launch-probe).

- T34 S3 P37 prepares a current P31 physical-DOS handoff package: a local
  helper rejects non-MZ input, copies matching EXE/MAP identities and emits a
  structured physical-observation form. The M4 protocol now names Tab rather
  than the obsolete F1 switch. No physical host was run and the global memory,
  stack/IRQ/NMI, reference and 25MHz486SX/VGA/LCD gates remain open. [Packet
  receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p37-physical-qualification-packet-readiness).

- T34 S3 P36 confirms the equal-budget NESticle gate remains unavailable to
  this task: no owner-local x.xx reference executable is currently accessible,
  while retained observations use mismatched resolution/frameskip and an
  older MySMB product. Historical 0.2 source is conceptual only. The gate
  needs the owner binary plus an explicit equal route/accounting matrix;
  no performance conclusion follows. [Reference disposition](../history/M3-T34-native-vga-performance-proposal.md#s3-p36-equal-budget-reference-availability-disposition).

- T34 S3 P35 rebinds the P20 project-owned allocation surface to P31: the
  only production source change since P20 is the PPU read-path edit, with no
  allocator or file-service owner change. The 159212B application-request
  bound remains current; CRT, loader, DOS and fragmentation remain external
  and unproved. [Allocation-surface receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p35-current-application-allocation-surface-rebinding).

- T34 S3 P34 rebinds the P31 DOS product to stock-configuration 384/448/500KiB
  memory routes. Each completes load, input, text/graphics, P/O and exit with
  a valid save; observed owned maxima are 373856/437408/498880B. This proves
  current tier fallback and lifecycle behavior only, not a global DOS-memory
  peak or physical performance result. [Tier receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p34-current-memory-tier-route-revalidation).

- T34 S3 P31 removes two dead raw-CHR reads from the already decoded sprite
  compositor branch. The raw reads now occur only in the unchanged fallback;
  all pixel decisions stay shared. Both Windows suites and the stock-config
  384KiB DOS route pass. DOS returns to the P29 324873B size with unchanged
  DGROUP, stack and allocation policy. [Dead-read receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p31-decoded-sprite-dead-read-removal).

- T34 S3 P30 accepts a zero-cache shared PPU hot-path repair: bind each
  decoded sprite CHR row once rather than reconstructing its far offset for
  every sprite pixel. Exact pixel/cache tests and both Windows suites pass;
  the DOS16 product passes the stock-config 384KiB route. DOS code grows 16B,
  while DGROUP, the 2048B stack and runtime allocations are unchanged. Three
  local EXEs refreshed. [Sprite-row receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p30-decoded-sprite-row-binding).

- T34 S3 P29 reruns the actual DOS16 product under the unchanged stock DOSBox
  configuration at 384KiB and 448KiB. Both complete title/load, WSAD/JK,
  Tab text/graphics, P/O and Escape routes with captures and normal exit;
  product/config hashes match the current accepted receipt. This confirms
  functional cache-tier behavior, not 486 performance. No product change.
  [DOS route receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p29-current-dos-cache-tier-route-revalidation).

- T34 S3 P28 reruns the current x86/x64 presentation probe: 2048 pixel-equal
  cases, cache-lifetime/priority guards and 1198 native routes pass on both.
  Current cached graphics are 339.524us (x86) and 282.393us (x64) per dense
  host frame; host timing is descriptive only, not a DOS or 486 claim. No
  product change. [Current presentation receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p28-current-host-presentation-remeasurement).

- T34 S3 P27 combines only current application-owned stack evidence: 734-byte
  foreground path plus the 78-byte IRQ9 path is 812 bytes of the configured
  2048-byte DOS stack, leaving 1236 bytes unallocated by this accounting.
  DOS/BIOS/NMI/firmware bodies and nesting remain excluded, so this is not a
  global-stack certificate or product change.
  [Application budget](../history/M3-T34-native-vga-performance-proposal.md#s3-p27-current-application-stack-budget).

- T34 S3 P26 binds the current IRQ9 keyboard path: its longest local branch is
  72 bytes, plus the six-byte hardware FLAGS/CS/IP entry frame, for a known
  78-byte application-side contribution. It directly acknowledges the PIC and
  never chains BIOS keyboard code. NMI, firmware and other service nesting
  remain outside this contribution; no global-stack closure or product change.
  [IRQ9 receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p26-current-keyboard-irq9-application-contribution).

- T34 S3 P25resolves normal flushall under current FILE ownership:untouched
  standard streams take no-output paths,private files clear active flags on
  close including errors. Conditional own+nested contribution26bytes,no write
  or allocation. Abnormal/fatal exit and external service/interrupt gates remain;
  no product change. [Normal-exit condition](../history/M3-T34-native-vga-performance-proposal.md#s3-p25-normal-exit-stream-ownership-condition).

- T34 S3 P24binds current no-copy startup hooks,disabled early dynamic init,
  empty cinit tables and14-byte retained main-entry frame(known total734).
  Actual exit table selects flushall;unpruned dynamic/text/error paths remain
  unresolved,so its partial84-byte result is not a bound. No product change
  or global certification. [Startup/exit receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p24-current-startup-and-exit-dispatcher-binding).

- T34 S3 P23rebinds all12remaining nested CRT/service wrapper entries to current
  EXE bytes;seven binary-stream/allocator CFGs balance and wrapper depths
  agree. Current project+CRTknown contributions720/704bytes exclude external
  service bodies,startup/exit and IRQ/NMI/firmware. Project/CRTrebinding is
  complete;global stack gate is not. No product change.
  [Runtime integration](../history/M3-T34-native-vga-performance-proposal.md#s3-p23-current-nested-crt-and-service-wrapper-integration).

- T34 S3 P22relinks current objects to loaded-image-identical public MAP and
  rechecks16CRTleaf symbols/15addresses from current EXE bytes. Depths and
  argument pops agree with retained proof;current known main/root_step totals
  720/704bytes exclude12nested/service entries,startup and interrupts. No code
  change or global-stack closure. [CRT binding](../history/M3-T34-native-vga-performance-proposal.md#s3-p22-current-linked-crt-leaf-rebinding).

- T34 S3 P21rebinds all168current project objects:161retained,seven refreshed
  (including file services). Census908functions/32indirect sites;787entry-
  reachable functions have balanced own-stack paths. Source-only contributions
  main708/root_step692bytes exclude runtime/startup/service/interrupt depths;
  no global stack certification. Product unchanged;four original gates open.
  [Current call model](../history/M3-T34-native-vga-performance-proposal.md#s3-p21-current-project-wide-stack-evidence-rebinding).

- T34 S3 P20binds final DOS SHA to384/448/500KiBarena launch,P/O,Tab and exit
  receipts;observed maxima373856/437408/498880bytes. Current requested heap
  upper bound159212bytes excludes loader/CRT/fragmentation/external services;
  no global-peak certification. No code/products changed;four original gates
  remain open. [Current memory receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p20-final-product-low-memory-routes-and-payload-bound).

- T34 S3 P19measures a forced full background rebuild stress route:with8KiB
  CHR1312.501ms/step versus1614.275without,saving301.774diagnostic ms.
  Each of13samples rebuilds1920tiles;paired final state CRC agrees. Rejected
  truncated long windows remain explicit. This is stress cost,not normal FPS;
  CHR cannot be treated as redundant from warm-only results. No product/policy
  change or gate closure. [Stress receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p19-forced-background-rebuild-chr-stress-comparison).

- T34 S3 P18adds paired packed/packed-without-CHR diagnostic runs from AREA
  and EXIT checkpoints. Each61-step pair has equal final state CRC;8KiBCHR
  shows no benefit here(0.344/0.736ms slower medians). Warm windows rebuild
  only4/0tiles,so cold/sustained-scroll and sprite-density coverage remain
  explicit. No product/cache-policy change or gate/node promotion.
  [Conditional costs](../history/M3-T34-native-vga-performance-proposal.md#s3-p18-conditional-chr-cost-on-retained-transition-seeds).

- T34 S3 P17reviews all24indirect sites in the P16bound changed-unit listings:
  23current constructor targets and one inactive legacy presenter. Copied
  file/hook lifetimes and pacing-only clock adapter are reconciled;transitive
  stack/service gates remain open. No code/product/node-credit change.
  [Callback receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p17-current-callback-constructor-review).

- T34 S3 P16rebinds the six P15changed DOS source objects and resolves72local
  own-stack paths with balanced returns;save/load maxima68/74bytes. No large
  snapshot buffer moved to stack. Callee/indirect/service overlays and the four
  original gates remain open;source/products unchanged. Cache policy awaits
  owner decision using conditional marginal costs,with smaller memory preferred
  for similar benefit. [Scoped receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p16-post-consolidation-local-stack-binding).

- T34 S3 P15delivers one10048-byte DOS/x86transaction store(x6410080),no
  frame/pause snapshot cache or spare,and no per-frame capture. P synchronously
  dumps current running/paused state;O validates before restore and preserves
  the saved pause state. Header36streams separately;schema1/2remain compatible.
  Normal diagnostic medians packed77.162/byte57.314ms versus85.999/66.196;
  requested snapshot storage reduces30068bytes and observed full-cache owned
  memory526080to498880. Three final local EXEs refreshed,each Windows width23
  checks and isolated text snapshot route pass. Full host fixture131is explicit
  TODO;all four original global/reference/physical gates remain open.
  [Delivery,large-space census and proposed policies](../history/M3-T34-native-vga-performance-proposal.md#s3-p15-single-workspace-on-demand-io).

- T34 S1/S2deliver native chain4scanout,shared byte-slot cache with packed/no-cache
  fallback,bounded Y folding and transactional snapshot publication. Fixed61step
  diagnostic151.258to66.182ms,2.285xratio;not hardware FPS or fair reference proof.
  S3repairs pending Escape lost during load;both widths23checks pass,original
  DOS tools and confirmed fresh-game/host routes pass. Current products
  DOS323977B,x86331278B,x64347150B;logical loader347248..351344B,DGROUP51472,
  stack2048. Four retained memory arenas observe526048/464576/401056/393216B,
  not global peaks. S3/T34remain active with the
  [fixed remaining gates](../history/M3-T34-native-vga-performance-proposal.md#fixed-s3-remaining-gate-register).
- T34 S3 P2adds six actual DOS lifecycle routes from controller-generated
  checkpoints:death,respawn,vertical entry,new area,side exit and upward exit.
  Snapshot fields/native2x2captures,text round trips and exit pass;no code or
  EXE change,new ROM credit0. Four original gates remain unproved:global memory,
  stack/IRQ/NMI,equal-budget reference and physical486SX/VGA/LCD. No T closure.
  [Receipts](../history/M3-T34-native-vga-performance-proposal.md#s3-p2-six-named-transition-routes).
- T34 S3 P3bounds current application-requested heap payload at169248B:
  required35616,optional persistent133120,one temporary stdio buffer512.
  A mapped relink is loaded-image identical;historical CRT allocation/close
  bindings confirm512-byte buffering. This excludes allocator/loader/CRT/DOS
  reservations and therefore does not certify total memory/global peak.
  Product unchanged;[bound](../history/M3-T34-native-vga-performance-proposal.md#s3-p3-application-payload-bound-and-crt-binding).
- T34 S3 P4binds eight compiler listings to identical product code/data/fixups;
  85local functions have balanced own stack paths. Maxima596initialize/
  312background-row bytes and a78-byte reviewed keyboard/control branch are
  partial bounds,not the full2048-byte stack proof. Thirteen indirect sites,
  whole foreground/core/runtime chains and firmware/NMI remain explicit.
  No product change,[receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p4-current-compiler-stack-listings-and-interrupt-boundary).
- T34 S3 P5binds the13reported indirect sites plus their file-replacement
  callee's existing callback. Fourteen sites reviewed,two current-production
  inactive;all active targets have local receipts. Eleven source units match
  current objects,97local paths balance. Known-component674/598/650-byte
  contributions omit external depths and do not certify global stack.
  [Binding](../history/M3-T34-native-vga-performance-proposal.md#s3-p5-constructor-bound-indirect-calls).
- T34 S3 P6binds all168project source objects and catalogs897Cfunctions,
  2064direct/30indirect call sites. Current constructor-bound subgraph reaches
  784functions;the legacy internal-RET parser limitation is outside it. Two
  symbolic cycle guards are resolved by P7;28runtime symbols remain;
  no global stack/IRQ proof or ROM-node promotion.
  [Census](../history/M3-T34-native-vga-performance-proposal.md#s3-p6-current-product-wide-source-stack-census).
- T34 S3 P7resolves the two symbolic-cycle guards:checkpoint reentry uses
  non-frenzy IDs;page-select/loop-command state prevents immediate repeat.
  Both nesting bounds2are supported by20480frenzy/4096stream Ccases. No core
  edits or ROM classification change. Full runtime/firmware/global stack and
  other original gates remain open;[guards](../history/M3-T34-native-vga-performance-proposal.md#s3-p7-state-guards-resolve-the-two-abstract-cycles).
- T34 S3 P8anchors28runtime entry symbols to current MZ bytes;16symbols at
  15addresses have balanced leaf CFGs and bounded own depths. Arithmetic
  argument-pop8is confirmed. Twelve runtime/service entries and firmware/
  startup/IRQ/NMI overlay remain unproved;no global stack certification.
  No code/EXE change,[leaves](../history/M3-T34-native-vga-performance-proposal.md#s3-p8-linked-runtime-leaf-depths).
- T34 S3 P9bounds five DOS/BIOS wrappers'own contributions(2/4/4/6/22bytes),
  including remove/rename shared tails. INT10gateway contributes28bytes at
  service entry before unknown BIOS depth. Seven nested allocator/file entries
  plus DOS/BIOS/firmware/startup/IRQ/NMI clauses remain,not zero-cost leaves.
  [Wrappers](../history/M3-T34-native-vga-performance-proposal.md#s3-p9-dosbios-service-wrapper-contributions).
- T34 S3 P10models the seven remaining allocator/file internal contributions
  for current binary streams:64/50/64/34/56/122/136bytes,balanced returns.
  The linked descriptor test excludes text conversion only under rb/wb/ab
  caller binding;general text/dynamic-stack/fatal paths are not certified.
  DOS/BIOS bodies,startup,IRQ/NMI and all four fixed gates remain open.
  No source/EXE change;[receipt](../history/M3-T34-native-vga-performance-proposal.md#s3-p10-current-binary-file-runtime-contributions).
- T34 S3 P11combines current source/runtime contributions:720bytes at main,
  734including the retained14-byte CRT main-entry frame;standalone root_step676.
  DOS/BIOS internal depths remain unknown. Linked heap-growth preference8192
  and free-without-DOS-release require retained-segment/reuse accounting,not
  payload-only claims. No product change;all four fixed gates remain open.
  [Boundaries](../history/M3-T34-native-vga-performance-proposal.md#s3-p11-combined-runtime-and-allocator-boundaries).
- T34 S3 P12runs two original-tool/CRT DOS heap/file reuse cohorts,1000loops
  each,zero failures. MCB samples stay249264/249376bytes respectively,including
  after-free retention. These are harness observations,not product memory
  figures or a global bound. No setting/product change;four gates stay open.
  [Reuse](../history/M3-T34-native-vga-performance-proposal.md#s3-p12-repeated-buffer-and-file-reuse-probe).
- T34 S3 P13binds current DOS SHA to actual384/544KiB arena routes:startup,
  P/O,Tab,Escape,save CRC and output dimensions pass;observed393216/526048bytes.
  High sample splits351728primary+160environment+174160auxiliary;low includes
  transient expansion. These are route observations,not global bounds or
  repeated512/448KiB proofs. [Endpoints](../history/M3-T34-native-vga-performance-proposal.md#s3-p13-current-product-memory-arena-endpoints).
- T34 S3 P14prioritizes packed background before CHR:448KiB now retains packed
  output;current448/544routes observe456384/526080bytes and pass P/O/Tab/exit.
  Both widths23checks and512raw-CHR/packed pixel states pass;three local EXEs
  refreshed,DOS323993bytes. Six-cache costs and all large buffers are recorded;
  per-frame snapshot capture still costs8.771diagnostic ms and remains in code.
  [Delivery and next snapshot segment](../history/M3-T34-native-vga-performance-proposal.md#s3-p14-cache-inventory-priority-and-controlled-costs).

- T33 S2 P12delivers default80x25on all three products;50-row code/art and
  interfaces remain. Shared semantic compact art/palette/layout owns output;
  hosts only adapt devices. White HUD,question marks and spring white edges
  are retained. Core/PPU code unchanged;ROM credit0.
  [Delivery](../history/M3-T33-windows-console-fit-proposal.md#s2-p12-implementation-and-local-play-test-delivery).
- Each Windows width20checks passes;53legacy cell cases byte-identical,
  1200native frames read-only,owned and interactiveCMD Tab/input/exit pass.
  DOS original build/link/memory and stock-config startup/text/Enter/exit pass.
  Products:16-bit320681B,32-bit330766B,64-bit346126B. Owner accepts S2and closes T33;unreviewed gallery
  and broader host applicability remain explicit TODO clauses.

- T33closed by owner-directed engineering acceptance. P3entry/Restore share
  bounded rollback/retry;actual classic capture and4000glyph checks pass.
  [Closure](../history/M3-T33-windows-console-fit.md#s1-p3-and-t33-owner-directed-engineering-closure).
- T33 S1 P2 restores the T24one-time80x50geometry sequence independently of
  HWND availability,+31/-10Win32device/header lines. Same-host neutral probe
  and actual x86/x64products report80x50;rollback/borrowed restoration and
  each width18tests pass. Fonts still have separate physical acceptance.
  [Correction](../history/M3-T33-windows-console-fit.md#s1-p2-restore-the-actual-t24-geometry-contract).
- T29classified Terminal and skipped working geometry;P1restored font but
  still gated geometry on a real HWND. P2corrects that unsupported inference.
  No per-frame forced Terminal resize. Terminal physical glyph/live caption applicability
  is retained in TODO;no all-host visual certification or next admission.
- Historical S1 products:DOS307349B,x86318478B,x64331790B. DOS DGROUP49264,
  stack2048,loader331584..335680logical bytes at that closure. Global stack/memory
  proof and physical25MHz486SX playability remain unqualified.
- T32/S9suspended. S8P21counter137.665ms,PPU59.677/mapping44.716/VGA18.062ms
  are diagnostic costs,not hardware FPS/fair reference proof. Remaining native
  VGA/performance/acceptance work is the
  [admitted T34 package](../history/M3-T34-native-vga-performance-proposal.md).
  Its original-tool pattern probe retains61440exact pixels/512x480hardware
  replication;S1 now adopts this native path in the actual game.
- Historical1992/1992,local1991/1992nodes and4260/4261feasible controls
  (raw4342,infeasible81),new0. Full M2certificate remains incomplete:
  10691sites/4171accesses,6/136groups and42/952facets accepted;
  130groups/910facets and four final packages pending in
  [audit ledger](M2_AUDIT_LEDGER.md). Do not infer whole-game correctness.

## Compact closure status

- [T32 retained checkpoints](../history/M3-T32-rendering-performance-continuation.md):
  S8transfer closure stands;T32/S9suspended by owner queue packaging.
- [T29 retained host work](../history/M3-T29-win32-usability-regression.md):
  asynchronous acquisition and native RGB retained;T33fit/Restore repair closes.
- T19Windows audio startup remains separately suspended in the queue.

- T34 S3 P40 establishes a bounded DOS16 linker route while the
  host refuses the fixed-base OpenNT LINK16 image: OpenNT CL16 objects are
  copied only below ignored build, their code-segment names are bucketed into
  the existing 11 libraries, and owner-local Microsoft LINK 3.65 runs inside
  a private DOSBox configuration.  It emits a 324889-byte MZ from the current
  startup/main/stack and passes title/input/Escape plus snapshot save/load
  routes. The adapter reduces 1,068 raw OMF records to 13 bounded code
  buckets without changing data/far-data records; its current 512x480-aware
  receipts pass. This is a candidate DOS artifact producer, pending the P39
  cache fallback matrix and normal three-product packaging.
