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
