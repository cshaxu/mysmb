# Shared Presentation And DOS Output Performance

Owner approves measurement-led performance work for the native DOS16 target,
especially25MHz486SX. New M3 T15 has two sequential bounded subtasks.

S1 measures shared game tick,graphics,text,scaling and snapshot stages;retains
the current project-owned pixel compositor as a test reference,then replaces
per-pixel background lookup with scanline/tile-row decode. Estimated5-8files,
300-500lines. Entry is committed visible game state;exit is identical256x240
indexed pixels. No original game control,collision,state or timing changes.

S2 optimizes DOS fixed320x200 scaling and full-frame VGA transfer,with snapshot
cost reviewed against the measured stages. Estimated4-7files,150-300lines.
Keep original OpenNT16 toolchain and64-color/frame contracts. Compiler options
change only with supported-option and behavior evidence;no speculative flags.
Preserve snapshot last-running-boundary,Tab,palette and text semantics.

Acceptance per implementation S:both-width focused tests,old/new whole-frame
equality,unchanged game state,repeatable stage timing,original DOS16 compile/link,
three refreshed local products,purity and governance checks. DOSBox operation
is operational evidence only. Modern-host timings and emulated speeds do not
qualify physical486SX;real-machine deadline/memory measurements remain M4.
No game-rate reduction,game-tick dropping or fidelity tradeoff is authorized.

No third-party import or new ROM research. Existing owner-local ROM solely
builds products and supplies existing native gameplay routes;all derivatives,
logs,reference build intermediates and raw receipts stay beneath build.
Tracked reference compositor is existing project-owned C,not ROM bytes/data.
Empty ROM node scope/expected/actual,new0;historical1992/1992,local1991/1992nodes,
4260/4261feasible controls remain unchanged;M2 certificate remains incomplete.

Sweep graphics background lookup,opacity/sprite priority,scroll split,scaling,
far-memory transfer,snapshot cache and inactive presenter work. Stop on unequal
output,state mutation,unsupported16-bit ABI or unresolved scoped regressions.
S1 closes before S2 admission;P commits report actual scope and measurements.

## S1 P1 closure

Closed. Shared background composition now decodes one visible tile row at a
time,including partial edges,CHR bounds,mirroring and palette lookup. Original
sprite/opacity/priority path remains unchanged. No new cache lifetime or ABI.
Both widths compare2048controlled boundary frames and1198native frames against
the retained project-owned T14 compositor;all pixels match and source game
state is unchanged. These are regression proofs,not new original-ROM credit.

Dense old/new graphics timings on the current unoptimized modern host:
x86=3177/911microseconds(3.49x),x64=3095/893microseconds(3.47x).
Native per-frame stages x86/x64:tick16/15,graphics524/562,text194/209,
VGA scale275/305,snapshot11/12microseconds. Stage sampling excludes host display
submission and DOS far-pointer/runtime costs. Timing is descriptive,no flaky
speed assertion. The route exercises native program state rather than a CPU
emulator;finite routes are not whole-game certification or486qualification.

Both widths5focused CTests pass;original OpenNT16 compile/link succeeds.
Actual DOSBox product graphics/start/move/jump/release/Escape-return receipt
passes with its existing operational verifier. Three local products16/32/64
are361675/445454/462144bytes. Receipts remain beneath build/m3-t15-s1.
Code/build/tests4files,+330/-10lines;smaller file count than estimate because
the owner and ABI were retained. All prior ledger custody/runs preserved.
Empty scope/expected/actual,new0;node/edge totals unchanged. No game-rate change.

S2 priority is now fixed VGA scaling and batch transfer. Snapshot cost is low
in this host profile;do not change last-running-boundary semantics for speculative
gain. Compiler optimization and hardware-specific memory/timing remain measured
qualification work;this task retains the existing supported toolchain flags.

## S2 P1 and T closure

Closed bounded performance task. Fixed256x240-to320x200 nearest-neighbor
scaling expands four source columns into five output columns and advances six
source rows per five output rows. No division or32-bit accumulator remains
in its pixel loop. The generic IO scaler remains unchanged and independent.
Both widths compare all64000output bytes against that prior route on dense
and1198native frames;the formula/sentinel VGA test also passes. No game state
or snapshot/clock/input semantics change. Shared graphics continues to match
the prior compositor for2048boundary and1198native frames per width.

DOS uses four bounded16000-byte large-model memcpy transfers into its64000-byte
VGA aperture. The historical runtime lacks _fmemcpy;that initial link failure
was repaired using its declared ordinary memcpy with far default pointers under
/AL. Final original-toolchain compile/link passes. No new library,assembly,
compiler optimization flag or unsupported instruction requirement was added.
Text80x50 output remains unchanged. Architecture records fixed VGA scaling
ownership explicitly;no platform code acquires game logic.

Current host scale timings x86=295/71microseconds(4.18x),
x64=290/66microseconds(4.41x). Dense shared graphics remains3.67x/3.34x faster.
Native graphics/scale averages x86=522/64,x64=553/67microseconds;unoptimized
modern-host evidence only. DOS memory-copy speed and real486frame deadlines
are not measured here. Snapshot cost remains11-12microseconds in this host
route;its last-running-boundary behavior remains intact. No tick dropping.

Both widths8focused CTests pass. Final isolated Windows routes pass the existing
Tab/Unicode/snapshot/focus/audio/recovery route and six actual launch/close
routes per width. Actual DOSBox graphics input/return and text/Tab/paused
round-trip/held-Tab/save-load/return receipts pass. DOSBox uses dynamic/max
cycles;these are operational proofs,not25MHz486qualification.

An earlier Windows host run stalled after first paint inside unchanged audio
acquisition,before its message loop. Diagnostic old-compositor and current
baselines stopped at the same before-audio marker. Both audio services were
Running;cause unknown. Later unchanged products passed all host routes. No
audio fix or service restart occurred. The probe now waits for its owned root
message owner,prints route identity and retains completed routes on failure;
its8-second budget and exit assertions are retained. A named unnumbered
[follow-up](../proposals/m3/bounded-windows-audio-startup.md) retains this incident.

S2 code/tests/tool4files,+66/-8lines;architecture and governance are separate.
Three local products16/32/64=361803/445454/462144bytes. Windows products remain
byte-identical to S1 because VGA scaling is only used by DOS. Local receipts,
hashes,baseline diagnostics and logs remain beneath build/m3-t15-s2. DOS graphics
copies cover offsets0-63999 with four individually segment-safe transfers.
Sweep dispositions:shared background lookup optimized;priority child retained;
fixed VGA scaler optimized;generic scaler retained;pixel/text presenters mutually
exclusive;snapshot capture retained;compiler flags retained;hardware timings M4.

Empty scope/expected/actual,new0;historical1992/1992,local1991/1992nodes,
4260/4261feasible controls unchanged. No new ROM equality or whole-game claim.
S1/S2 are closed;M2 certificate and physical486qualification remain incomplete.
Preserve unrelated UI/Roadmap/terrain changes;do not stage local products.
Ledger custody/prior runs retained;documentation gate passes. Local P commits,
no remote push. The new audio candidate and deferred M2 work remain queued;
no successor T automatically admitted.
