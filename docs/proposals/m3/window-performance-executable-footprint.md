# Window Performance And Executable Footprint

Owner-requested first queue candidate. One future M3 T with sequential S1/S2;
allocate the next ascending T at admission. This planning record does not
admit work,change the current S,or claim a measured cause. Owner observes
graphical Windows mode stuttering while text mode feels smoother.

## S1: Graphical Frame Pacing And Presentation

Measure the actual x86/x64 product path,including game update,indexed frame
generation,DIB conversion,window scaling/blit,message handling,audio service,
and pacing waits. Record elapsed frame intervals,median/p95/p99 times,long
frames and logical-tick backlog. Use comparable deterministic gameplay and
window sizes for graphical/text modes;report hardware/session conditions.
Prior compositor-only speedups do not prove actual window smoothness.

Separate sustained rendering cost from scheduling/presentation jitter and
device stalls. Inspect redundant conversion/repaint,per-pixel API calls,
stretch cost,buffer lifetime and message-loop starvation;repair measured
bottlenecks within their existing shared-renderer or platform owners. Keep
original tick rate,input responsiveness,pixels,audio and snapshot semantics.
Do not hide slow rendering by slowing gameplay or silently dropping logical
ticks. Keep platform code free of game decisions. Startup audio acquisition
remains the separate queued candidate;link overlapping evidence rather than
claiming this task repaired an unobserved driver/device fault.

Exit:record the root cause and before/after frame-time distribution on the
same workloads;resolve reproduced stutter with explicit bounded frame/tick
budgets chosen from the baseline. Verify both widths,graphics/text Tab round
trips,input/focus/exit,audio and snapshot behavior,unchanged indexed pixels
and game state. Any shared change also requires original DOS16 build and
appropriate DOSBox checks. Live RDP and real486 claims require actual evidence.

## S2: Executable Disk Footprint,With DOS16 Priority

Inventory all three products by executable headers,code,immutable resources,
initialized data,zero-initialized storage,alignment,padding,debug/symbol data
and runtime-library contribution. Use local linker maps only as diagnostic
outputs. Distinguish file bytes,DOS filesystem cluster allocation,distribution
files and runtime conventional-memory/heap/stack requirements.

Prefer removing unnecessary file/debug payload,unused linked code,duplicate
immutable data and avoidable file padding. Check whether zero-initialized
buffers unnecessarily occupy disk rather than loader/runtime storage. Keep
the existing historical DOS16 compiler/linker,large-model requirements and
standalone embedded-resource product contract. Do not delete required states,
text artwork,game logic or validation-dependent resources to shrink a file.
Changes to compiler optimization,segment layout or resources need their own
measured compatibility/equivalence checks within this S.

Consider executable packing only after structural savings are measured;report
DOS loader compatibility,unpacking startup time,peak conventional memory and
486SX cost before choosing it. No new packer or external dependency is admitted
by this proposal. Moving embedded content to required companion files does
not count as reduced total footprint or preserve the existing product shape.

Exit:report before/after file sizes and allocated disk space for a declared
DOS filesystem cluster size,each retained/rejected optimization and measured
memory/startup tradeoffs. Implement safe proven savings;where no safe reduction
is established,record the evidence rather than claiming optimization. Verify
all three builds,loader/startup,graphics/text,input/exit,snapshot/resource
binding and focused equivalence. Recheck S1 frame pacing to prevent a size
optimization from reintroducing stutter. Real486/DOS-version qualification
remains explicit when not observed.

## Delivery And Boundaries

At each S admission,announce components,scope,estimated change size and
measurable acceptance budgets. At closure,record actual changes,tests and
remaining limits. Product changes refresh all three local EXEs;pure analysis
does not require rebuilding unchanged products. Temporary profiles,maps,logs
and build outputs stay beneath ignored build. No protected assets or products
are committed. Research/import follows the source policy at admission.

These are presentation/build tasks with no new ROM-node credit. Preserve
existing node/edge dispositions and incomplete M2 certification;register the
explicit node scope and ledger on admission. S2 follows closed S1 under the
same T. Current text-object work and unrelated workspace edits remain intact.

## M3 T18 S1 Admission

Owner admits this queue head after closed T17. S1 is active;S2 stays planned.
Estimated4-7code/test files,200-350lines. Use existing project-owned native
root/adapters and owner-local embedded resources only for controlled comparison.
Resources are nonredistributable local inputs;no external code/import/packer.
Profiles/probe binaries and raw timings remain below ignored build/m3-t18-s1.
Private desktop windows and owned console records avoid the owner's desktop.
Record actual measured frame budgets before selecting a repair. No invented
cause or RDP/486claim. Empty scope/expected/actual,new0;historical1992/1992,
retained local1991/1992nodes and4260/4261feasible controls unchanged.

## S1 P1 Review And Closure

S1 resolves the reproduced host wait/presentation discrepancy. S2 remains a
separate sequential footprint check;this is not whole-T or whole-game closure.
The native root and its real adapters ran on a private Windows11 build26200
desktop,x86/x64,512x480 blit,same title-to-idle-game workload,8seconds per mode,
with waveOut off and on. A private desktop does not expose physical scanout or
live RDP delivery. Graphics paint is explicitly invoked once per built frame
because occluded desktop windows may defer ordinary WM_PAINT. Both comparison
versions use that same GDI route. Timings include game,compositor,conversion,
paint,text composition/output,messages,audio and wait;raw records stay in build.

The original Sleep(1) actually waited about12-16ms,allowing work plus coarse
wakeups to miss the16.667ms deadline. Graphics drawing itself had submillisecond
median stages. An intermediate timeBeginPeriod-only fix improved text but
retained graphics p99 about31ms. This is consistent with the documented
Windows11 occluded-window resolution limitation;it is not proof of the exact
scheduler decision on every machine. [Microsoft timer-resolution contract](https://learn.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod).

The shared Win32 root now uses an owned high-resolution waitable timer with
message wakeups and deadline-derived waits. Runtime API resolution/failure
falls back to matched timeBeginPeriod/timeEndPeriod and message-aware timeouts;
no new static dependency on modern Windows exports. Supported flag semantics:
[Microsoft waitable timer contract](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createwaitabletimerexw).
Timer handles are closed after normal exit. Clock baseline resets after device
startup rather than treating device acquisition time as game tick debt.

Message batches and logical update batches are bounded at64messages/four ticks;
remaining logical debt is retained rather than reset to now. Ordinary cadence
stays60Hz,there is no forced synchronization to a lower game rate,no busy spin
and no game decision in frame_wait. A64-entry RGB lookup replaces61440color
function calls per frame;all256possible byte indices retain identical RGB.

| Mode/audio | Width | Before median/p95/p99 ms | After median/p95/p99 ms | Frames over25ms before/after |
| --- | --- | --- | --- | --- |
| Graphics/off | x86 | 16.643/26.272/29.105 | 16.654/17.360/18.133 | 39/0 |
| Graphics/off | x64 | 16.475/20.671/23.759 | 16.649/17.345/18.885 | 4/0 |
| Text/off | x86 | 16.604/20.270/24.341 | 16.638/18.474/20.430 | 3/0 |
| Text/off | x64 | 16.577/24.847/28.178 | 16.671/18.247/19.550 | 21/0 |
| Graphics/on | x86 | 15.869/23.731/31.925 | 16.662/17.335/17.754 | 22/0 |
| Graphics/on | x64 | 15.860/24.948/32.030 | 16.666/17.322/18.589 | 24/1 |
| Text/on | x86 | 16.131/26.722/28.579 | 16.649/18.717/20.402 | 29/0 |
| Text/on | x64 | 16.024/25.391/29.363 | 16.630/18.040/19.236 | 25/0 |

After measurements meet the selected p95<=20ms,p99<=25ms local budgets for
every route. Long-frame rate is under1percent,not a zero-jitter promise.
The one x64 audio-on outlier reached31.103ms with11.707ms audio service;this
task does not claim the separately queued transient device-startup issue fixed.
All final routes advance477logical ticks in8seconds after startup,with477built
frames;an injected twelve-frame debt leaves eight after the first four-tick
batch. No logical update is discarded by overload handling. RGB conversion
median drops from0.33-0.35ms to0.10-0.12ms. Other rendering stages are retained.

Both widths pass10focused CTests:wait,actors,elements,observations,background,
captions,snapshot,PPU,purity and product self-test. Both owned host probes pass
Tab/snapshot/focus/audio/Unicode/recovery plus six actual launcher/close routes.
Indexed equality remains2048boundary cases and1198native frames with unchanged
game state. Original DOS16 compilation/link and DOSBox graphics/text/held-Tab,
snapshot,round-trip and exit pass. No DOS or original game source changed.
An initial make invocation regenerated target lists then missed the newly
added target;the subsequent explicit build and final test passes are retained.

All three local products refreshed:364127/451327/468010bytes. Package hashes
match final build outputs;no executable,ROM,generated data or raw trace is
committed. S1 product/test/tool scope is7files,+350/-10lines,including a repeatable
private-desktop profiler at the initial estimate's upper bound. Reports are observations on this
host,not physical486,DOS-version,live-RDP or all-input qualification.

Reproduce current native paths from a configured owner-local build:

```text
python tools/Profile-Win32Presentation.py --build-directory build/m2-focus-make-x86 --output build/pacing-x86 --audio 1
python tools/Profile-Win32Presentation.py --build-directory build/m2-focus-make-x64 --output build/pacing-x64 --audio 0
```

For a before comparison,retain the pre-S1 composition root beneath build and
pass --source with --legacy-wait. The tool instruments project-owned source,
links existing owner-local build objects and binds source/probe hashes and host
metadata locally. Each child has a20second timeout and20KB receipt budget.
No focus switch,global key injection or default-desktop window is used.

Similar-issue sweep:only one production Win32 unconditional Sleep loop and one
four-frame debt-discard branch existed;both are replaced. Paint already uses
one StretchDIBits per frame,so no invented per-pixel GDI repair or renderer
rewrite. RGB conversion is equivalent;message pumping remains responsive.
Audio queue/device startup is unchanged and retained in its own candidate.
DOS pacing and hardware qualification remain their existing owners;there is
no transfer of gameplay state/rules to the platform adapter.

Empty node scope/expected/actual,new0. Historical1992/1992,retained local
nodes1991/1992 and feasible controls4260/4261(raw4342,infeasible81) unchanged.
M2 certification is still incomplete;S1 performance evidence earns no ROM
node/edge certification. Prior ledger custody and evidence are preserved.
