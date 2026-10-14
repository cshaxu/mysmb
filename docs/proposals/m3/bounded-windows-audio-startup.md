# Audio Device Lifetime Across Win32, Win16 And DOS16

## Current task status

Owner expands retained M3 T19 to design and repair all three host families.
The final section, "Approved three-platform design amendment", is the current
scope and execution authority at efd9015a. Earlier sections preserve their
audit-time facts and rejected options; their Windows-only restrictions and
single-S T closure plan are superseded. S1-S2 are closed; S3-S4 remain planned.
S1 P3 implements the Win32 repair below. S2 is closed by P1 below; S3-S4 remain planned and unadmitted.

## Historical suspension

M3 T19 S1 is suspended by explicit owner instruction,not closed or accepted.
Research and the single-process assessment below are retained;remaining
prototype,implementation and verification work returns to the queue. The
owner prohibits additional production processes. Re-admission resumes this
same task and subtask with its outstanding obligations;no identifier recycling
or repair credit. No product code or executable changed in this research.
Independent character-presentation work proceeds under M3 T20.

Unnumbered candidate found during T15 S2 host regression. A transient private
desktop product startup created and painted its GUI,then blocked inside the
unchanged Win32 audio open call before entering the message loop. Both product
widths exceeded the existing8-second host budget. A diagnostic baseline using
the retained T14 compositor stalled at the same before-audio marker;there was
no after-audio marker. Both Windows audio services report Running;the cause
inside the device/driver/session route is not established. Subsequent unchanged
products passed all six launch/close routes on each width. No audio repair is
claimed. No service restart,
global input or user-window operation was attempted.

Proposed bounded S:inspect WinMM device acquisition under current local/remote
conditions;keep root startup,close and input responsive if acquisition stalls.
Give device acquisition/cancellation/lifetime one platform owner. Preserve
audio renderer and game semantics,normal sound,snapshot/focus/exit cleanup.
Test both normal device and deliberately stalled acquisition routes;repeat
actual product private-desktop launch/close checks after repair. Neither a
longer test timeout nor silently disabling all audio is an accepted repair.

T14's historical accepted startup receipts remain within their original host
conditions. Final current host routes passed;they do not prove acquisition is
always bounded. Receipts remain beneath build/m3-t15-s2. No node
credit,external import,original game change or DOS audio requirement.

## M3 T19 Admission And S Plan

Owner admits the queue head after closed T18. Allocate M3 T19 with one active
S1 P1,covering the complete device-acquisition/lifetime chain. This avoids
separate mapping,repair,test and delivery subtasks for the same capability.
Estimated6-9code/build/test files,500-800lines;scope changes are reported.

S1 responsibilities,in execution order:

1. Bind the existing synchronous open/prepare/close/reset call sites,renderer
   ownership,snapshot dependencies and previous stall receipts. The original
   driver/session cause remains unknown until reproduced and identified.
2. Give pending/ready/failed/abandoned acquisition and late completion one
   platform owner. Keep the composition root message loop responsive while
   acquiring a device. The acquisition activity receives no game state.
3. Define a bounded acquisition policy and visible device status;preserve
   ordinary sound and renderer/snapshot semantics. A late result cannot write
   released root storage or resurrect a closing application. Audit preparation
   failure and blocked cleanup as the same lifetime problem. Do not forcibly
   terminate a thread or free storage still borrowed by a driver.
4. Exercise normal open,device failure,partial preparation failure,deliberately
   stalled open,timeout,late completion and exit during pending acquisition.
   Project-owned event-controlled seams model stalls;no service restart,
   global keyboard injection or manipulation of the owner's desktop.
5. Run both native product widths on owned private desktops. Check input,
   close/ESC,graphics/text Tab,pause,normal audio and snapshot restore. Recheck
   T18 pacing and platform purity. Product changes rebuild/package all three
   local EXEs with the existing DOS16 toolchain and appropriate operational
   receipts. Update ledger,evidence and actual scope before closing S1/T19.

The responsiveness target is an owned close request serviced within1second
while acquisition is deliberately held;child supervision remains8seconds.
Acquisition budget starts at2seconds and must be bound to deterministic tests;
normal initialization is separately verified. These are application-path
budgets,not a promise to cancel an arbitrary blocked kernel/driver call. Choose
the concrete ownership/isolation design only after proving its abandonment and
late-cleanup behavior. Increasing probe budgets is not an accepted repair.

Boundaries:no shared game,DOS audio,ROM-node,resource or snapshot-wire change.
Reuse existing owner-local embedded resources for native operational checks
only;no new source/ROM/translation import. Probe binaries/logs stay below
ignored build/m3-t19-s1. Retain unrelated workspace changes and protected local
products. No M2 claims:empty scope/expected/actual,new0;historical1992/1992,
retained local1991/1992nodes and4260/4261feasible controls remain unchanged.

Exit requires reproduced deterministic stall coverage,correct late-result and
partial-failure lifetime handling,bounded responsive exit,normal sound and
cross-mode/snapshot regression,three local artifacts for product changes,
similar-issue sweep and both ledger/documentation gates. A passing ordinary
launch alone cannot close this task. S1 is admitted,not implemented or closed.

## S1 Research And Revised Constraint

Research/prototypes are retained locally below build/m3-t19-s1;product code and
EXEs unchanged. Microsoft public API contracts were consulted as references;
no external code imported. Sixteen real acquisition/cleanup cycles succeed on
the current private desktop. Open median is436/394ms,max580/466ms by width;
the original8second stall was not reproduced. Driver/session cause stays unknown.

The root currently blocks before entering its message loop and synchronously
cleans up inside WM_DESTROY. Notifications do not give open a timeout contract;
[waveOutOpen](https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutopen).
Thread-only acquisition is insufficient for reliable abandonment:buffer
lifetimes and DLL-detach locks remain shared with the parent;
[ExitProcess](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-exitprocess).

Owner explicitly prohibits additional processes. Withdraw the proposed
same-EXE private audio child and its uncommitted channel/device implementation;
no product build or executable was generated from it. Retain the process
containment measurements as rejected-design research only,not acceptance.

Continue S1 with single-process acquisition/lifetime research. A platform-owned
thread can keep the UI responsive,but a timeout alone does not cancel WinMM
or establish safe buffer release and DLL-detach behavior. Prove ownership,
late completion,partial preparation,reset and exit before selecting that
implementation. Do not forcibly terminate a thread,free driver-borrowed
storage,disable ordinary audio permanently or claim a hard arbitrary-driver
shutdown guarantee. Any remaining unproven shutdown condition stays explicit.
The implementation estimate is pending that design;the rejected process
estimate is no longer an execution plan. S1 remains open,with no product repair
or closure credit from the research probes.

## Single-Process Assessment

Recommended candidate:one platform-owned device thread,with all WinMM calls
serialized there. The production runtime creates no additional process. Keep
WinMM rather than adding a new WASAPI/DirectSound dependency without evidence
that it repairs the observed failure. The earlier cause remains unknown.

Current call-site sweep finds open/prepare before the root message loop,
write during logical ticks,reset during snapshot load,and reset/unprepare/close
inside WM_DESTROY. Moving open alone is insufficient. The current close also
discards reset/unprepare/close error results and clears ownership regardless;
the new lifetime owner must retain borrowed storage after a failed cleanup.

Ownership and protocol:

1. Main owns the unchanged synthesizer and snapshot state. Device thread owns
   device handle,headers,completion event,preparation count and every driver
   call. It receives PCM/control requests only,no game state or window pointers.
2. Use one persistent lifetime object and eight total PCM slots,not an extra
   eight-slot staging backlog. Interlocked publication transfers each slot
   through free,producer-ready,driver-queued and completed states. The producer
   never touches a driver-owned slot or waits for a driver-held mutex. Event
   notification wakes the device thread without polling every game frame.
3. Start the message loop immediately. Opening/ready/stalled/failed/stopping
   are explicit states. A two-second observation deadline marks stalled;it
   never pretends to cancel open or authorizes releasing its object. Continue
   the synthesizer's ordered writes/phase while sound is unavailable,without
   replaying accumulated startup PCM when the device becomes ready. Verify
   this intentional unavailable-device policy against renderer snapshots.
4. A late successful open may recover on the same thread if still running;
   after stop it must clean up without publishing ready. Retry only after the
   prior operation and cleanup have returned. Never spawn accumulating threads
   to replace a stalled owner. No persistent silent-disable fallback.
5. Snapshot load validates and retains the candidate on main,requests a queue
   epoch reset,and waits asynchronously while still pumping messages. Commit
   game and renderer together only after successful reset acknowledgement;
   failure/timeout leaves both candidates uncommitted. Do not release old slots
   until the device actually returns them. Late acknowledgements cannot commit
   an abandoned transaction. No snapshot format changes.

Exit is a separate,explicit decision. Normal close posts stop and lets the
thread reset,unprepare and close,then joins before freeing its lifetime object.
The proposed graceful wait budget is250ms,with message dispatch still enabled;
WM_DESTROY must not run any driver call. If the device thread remains blocked,
ordinary return from WinMain can deadlock in DLL detach;
[ExitProcess contract](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-exitprocess).
The single-process emergency candidate is termination of this application
itself after owned file transactions are complete,without further manual
audio-buffer release or TerminateThread. It bypasses DLL detach and normal
cleanup,so it must remain an exceptional,recorded path and requires prototype
acceptance before product use. It does not create another process or kill any
other application. Pending kernel I/O can still delay final process teardown;
[TerminateProcess contract](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminateprocess).
Do not promise arbitrary broken-driver process disappearance within1second.

Prototype acceptance before implementation:hold open/write/reset/close in
project-owned seams;prove message response,one-thread limit,late recovery,
partial-prepare ownership,error cleanup,PCM equality/capacity,reset transaction
atomicity,and graceful versus emergency exit on both widths. Real normal
device checks remain separate from simulated stalls. Repeat Tab/focus/snapshot,
T18 pacing and platform purity,then rebuild/package three targets if product
code changes. Existing sixteen successful real opens do not prove this design.
Estimated6-9code/build/test files,500-900lines;no game or DOS code changes.
This is an evaluated candidate,not implemented or accepted closure evidence.

## 2026-10-13 current-source audit and revised design

This section is the current design authority for resumed T19 S1 at453ae52d.
Earlier sections are historical research. This turn authorizes audit/design,
not production implementation. The old driver/session cause remains unknown;
normal successful opens do not discharge the stalled-call obligation.

### Current call chain and findings

| ID | Current owner/site | Finding and disposition |
| --- | --- | --- |
| A1 | app-mario/kvm/platform/win32/main_win32.c, WinMain around588 | Synchronous audio open/prepare still precedes the message loop. A slow device delays window and Console input alike. Outstanding. |
| A2 | main_win32.c, step around498; audio_output.c submit | Each logical tick can call waveOutWrite on main. Moving only open is insufficient. Outstanding. |
| A3 | main_win32.c, snapshot_request around348 | Reset is synchronous, but game and renderer are correctly committed only after validation/reset succeeds. Preserve this transaction when asynchronous; do not move game state to the worker. |
| A4 | main_win32.c WM_DESTROY around538; audio_output.c close | Root teardown calls the driver synchronously and the void app wrapper discards close failure. This can block Console restoration/PostQuitMessage and cannot acknowledge safe device teardown. Outstanding. |
| A5 | lib/win32/pcm.c close and open failure unwind | Contrary to the old proposal, failed reset/unprepare/close now retains the device and remaining prepared count. Keep this improvement. Partial preparation can still return open failure with a live device if cleanup fails; callers must retain its lifetime. |
| A6 | audio_output.c submit device-null return | Queue-full render advances oscillator phase, but device-absent render does not. Startup/late recovery needs explicit app policy: advance the synthesizer every logical tick even without a writable slot, discard PCM, and never replay old startup samples. This is an adapter change, not core/APU logic. |
| A7 | main_win32.c update_title around193; g_audio_available | Availability is initialized once and title caching keys only on pause. Async status changes require app-owned status/title invalidation; the library must not choose user strings. |
| A8 | test/lib/win32/pcm_smoke.c and app audio tests | Current mocks cover open/prepare/write/reset errors, queue reuse and reset-failed close retention. They do not inject unprepare/close failures, combined prepare+cleanup failure, blocked calls, late results or concurrent publication. Add those focused obligations; retain existing snapshot/render/host tests. |

The sole production Win32 WinMM API table is in lib/win32/pcm.c. Its production
consumer is Mario's audio_output adapter; Mine currently has no audio calls.
DOS16 and Win16 have separate host mechanisms and are outside this repair.
The neutral PCM implementation is synchronous by contract and not thread-safe;
placing calls on different threads without an ownership layer would add races.

### Fresh bounded normal-device measurements

Project-owned build-only probe directly links the current pcm.c, injects
API-timing wrappers through its existing API table, and uses silence rather
than game/ROM data. Each width performs8sequential cycles: open44,100Hz mono
16-bit, prepare8blocks of735samples, write all8, reset, close. Close itself
performs a second reset. QPC measures only each API call, excluding logging.
The supervisor allows12seconds per probe and can stop only its own test
process. Neither probe timed out; every API result was success. No service,
endpoint, driver, desktop input or DOSBox settings were modified.

| API | Calls per width | x86 median/max ms | x64 median/max ms |
| --- | --- | --- | --- |
| Open | 8 | 358.678/785.255 | 386.79/454.046 |
| PrepareHeader | 64 | 0.196/0.303 | 0.182/1.172 |
| Write | 64 | 0.218/10.815 | 0.211/7.359 |
| Reset | 16 | 1.923/7.886 | 2.365/11.168 |
| UnprepareHeader | 64 | 0.193/0.973 | 0.185/0.289 |
| Close | 8 | 15.608/16.972 | 16.384/17.25 |

The historical8-second failure did not recur. These measurements describe the
current tool session, not separate proven local/RDP configurations, audible
music quality, a permanent upper bound, or a before/after speedup. Write/reset
outliers can consume a substantial part of a16.67msmain-thread tick budget,
but this small sample does not quantify gameplay slowdown.
Current sample storage is11760bytes; headers256/384bytes, queue flags8bytes
and PCM descriptors28/48bytes for x86/x64. The proposed queue keeps eight total
sample blocks, not two eight-block queues. Worker stack/events/state are new
Windows-only overhead to measure; there is no DOS memory increase.

Reproduction: compile the neutral wrappers with GCC32/64 and current pcm.c,
C90/O2/Wall/Wextra, linking WinMM; run the above fixed format/count sequence
with a12second external deadline. Both existing pcm_smoke owner tests also
compile with Werror and pass on both widths. The timing harness and raw CSVs
remain below build/t19-s1-audit. No full product suite or EXE rebuild is needed
for this documentation-only P; the T45 receipts are retained, not relabeled
as new T19 operational proof.

### Recommended single-process architecture

Keep the current PCM driver-call owner and add a neutral asynchronous lifetime
owner under lib/win32 (proposed pcm_session.c/.h). One session has at most one
device thread. Only that thread calls pcm_open/acquire/submit/reset/close or
reads driver completion flags. Extend the existing open mechanism with an
optional completion-event handle, defaulting to NULL for synchronous clients;
do not create a second set of WinMM call implementations.

The session owns stable heap storage for headers, eight sample slots, flags,
command/status records, events and the thread handle. The app borrows a free
slot, renders, and publishes it with an interlocked transition. States are
FREE -> PRODUCER -> READY -> DRIVER -> FREE; failed writes return ownership
only after the call returns. Main never waits on a driver-held lock. Worker
uses completion/command events and checks all queued headers after a wake;
event coalescing must not lose completions. A slot borrowed by either producer
or driver cannot be reset, freed or reused by another owner.

Public operations are nonblocking begin, status, acquire/publish, reset-request,
stop-request and terminal-result/release. Requests carry monotonically changing
IDs/epochs; status carries current operation, start time and last result.
OPENING -> READY/FAILED; READY -> RESETTING -> READY/FAILED; stop is monotonic
from every state to STOPPING -> CLOSED or CLEANUP_FAILED. STALLED is a deadline
observation of an outstanding operation, not cancellation or ownership release.
Main never retries an in-flight call or spawns a replacement thread. A failed
cleanup retains the object and supports serialized retry after the prior call
returns. Ready is published only after all headers are prepared. Late open
after stop goes straight to cleanup without publishing ready.

The Mario adapter owns renderer advancement and overflow/unavailable policy.
It renders to a free slot or its existing discard workspace every logical
tick. It produces no startup backlog while OPENING. When a stalled operation
returns, any unsubmitted old backlog must be invalidated before normal output
resumes; if driver blocks remain queued, the app requests reset and waits for
its acknowledgement while rendering/discarding. Generic epochs implement the
mechanism; no60Hz, NES, frame-count or gameplay rules belong in lib.
Normal ready-path PCM must match the current synthesizer sample-for-sample.

The app polls published status during its existing message/tick loop; no new
frame-wait architecture is required initially. It updates its own audio title
state and retains Tab/focus/exit behavior in either presenter. A2second device
operation observation deadline is an initial policy to qualify, not a driver
cancellation guarantee. Closed/failed status must remain distinct from stalled.

### Snapshot and shutdown transactions

Save remains synchronous on main with the existing renderer/game snapshot;
PCM slots and device handles are not serialized. For load, validate into the
existing staging snapshot and a renderer candidate, request a new reset epoch,
and suspend logical ticks while continuing input/paint/Tab/close dispatch.
The app owns this transaction. Do not pump nested messages inside the old
synchronous reset function. New P/O requests cannot overwrite the staging
candidate while a reset acknowledgement is pending; coalesce or reject them
explicitly until that transaction resolves. Exit takes priority.

Only matching successful reset acknowledgement commits game and renderer
together. Reset failure/timeout abandons the candidate and resumes the old
logical state with a re-anchored clock; no late acknowledgement may commit it.
Outstanding reset still owns driver buffers; output remains gated until it
returns. A device that never opened has no old PCM to reset, but its command
epoch must still acknowledge that fact so a late open cannot publish stale
work. No save-format or game-pause-bit change is required.

Exit first disables production and posts stop while main continues dispatch.
The worker performs reset/unprepare/close; only successful close plus thread
termination permits lifetime release. WM_DESTROY contains no driver calls.
Restore the borrowed Console and finish owned file transactions before any
exceptional termination policy. If graceful cleanup exceeds its proposed
250msbudget, keep memory alive; never TerminateThread or free borrowed buffers.
Self-TerminateProcess after app cleanup remains a prototype candidate from the
old plan, not an implemented or approved-safe guarantee. Measure normal-close
latency before finalizing the budget. If the candidate cannot satisfy lifetime
and host restoration tests, report the explicit remaining shutdown limitation
instead of claiming a bounded arbitrary-driver exit.

The official contracts support these boundaries: [waveOutOpen](https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutopen)
defines notification modes but no timeout argument; [waveOutReset](https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutreset)
returns pending buffers; [unprepare](https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutunprepareheader)
must precede freeing them; [close](https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-waveoutclose)
can fail with buffers outstanding. [ExitProcess](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-exitprocess)
can deadlock through DLL detach locks; [TerminateProcess](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminateprocess)
still cannot promise immediate teardown when kernel I/O remains pending.

### Bounded implementation and acceptance matrix

Retain S1 as the complete device-lifetime chain. Do not split individual API
calls into new S tasks. Design P1 records this audit; subsequent implementation
parts first qualify controlled lifetime seams, then integrate app transactions
and run acceptance. Estimated10-14source/test/build files and600-1000lines,
including mirrored tests; confirm after the prototype, not a delivery promise.

| Owner | Required acceptance before S1/T19 closes |
| --- | --- |
| lib/win32/pcm | Every preparation index failure, combined cleanup failure, reset/unprepare/close failure with exact retained ownership and successful retry; preserve existing positive paths. |
| lib/win32/pcm_session | Event-controlled held open/prepare/write/reset/unprepare/close; one thread, nonblocking producer, no early free/reuse, stop priority, late open/ack, epoch reset, full queue, event coalescing and allocation/thread/event failure. |
| Mario audio adapter | Ready PCM equality; absent/pending/full-queue synth-state continuity; no startup/stale recovery playback; status reporting; no game/snapshot fields in library. |
| Mario root/snapshot | UI close/input serviced within1second while fake acquisition is held; Tab/focus both presenters; load success/failure/timeout/late acknowledgement, repeated P/O and close during load; game+renderer commit atomically. |
| Shutdown host join | Graceful thread join before free; failed/stalled cleanup retains ownership; borrowed Console restored; exceptional self-exit prototype measured separately from normal cleanup. No arbitrary-driver hard-exit claim. |
| Actual products | Both widths with normal real device and capability failure; owned/borrowed Console, window, snapshots and audio regression; all applicable unit/integration suites; three Mario EXEs when production changes. |

Tests assert each owner's decision once; integration fixtures cover joins and
actual timing rather than duplicating renderer rules. Deliberate stalls use
project-owned event seams, not a broken real driver or longer test timeout.
No separate production process, backend switch to WASAPI/DirectSound, Mine
music feature, DOS/Win16 change or core/PPU redesign is admitted by this plan.

### Audit disposition

Audit/research/design is complete for this turn. T19/S1 remains active and
unfinished: lifecycle prototype, production repair and acceptance matrix above
are outstanding. The resumed queue entry is removed; five other candidates
keep their order. T45/S4 still awaits owner play acceptance independently.
No product code, test source or EXE changed. Historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls (4342raw,81infeasible)
are unchanged; scope/expected/actual additions are empty. Single-person review
checked current findings against source and did not count historical claims
or timing samples as an implemented repair.

## Approved three-platform design amendment

Owner approves the audited Win32/64, Win16 and DOS16 lifecycle repair. This
amendment retains T19/S1 and adds planned S2-S4 within T19; it does not create
three active tasks. P2 is the reviewed design delta. Only a subsequent code P
can claim a repair, with all three refreshed local Mario products. No core,
PPU, original sound command, snapshot wire format or Mine sound feature change.

### Fixed additional findings and receiving S

The retained A1-A8 findings above belong to S1. The following source findings
are static evidence, not reproduced real-driver stalls. Existing positive
behaviors are constraints to preserve, not defects to rewrite.

| ID | Current source/contract | Required disposition | S |
| --- | --- | --- | --- |
| W16-1 | lib/win16/audio.c; WinMain calls open before host run | Window must paint and begin dispatch before acquisition; submit must not reopen the device. | S2 |
| W16-2 | audio.c retries MMSYSERR_ALLOCATED after1000ms in submit, without attempt limit | Move retry to explicit service; finite retry episode, no retry on arbitrary errors, no retry after stop. | S2 |
| W16-3 | reset/unprepare/close errors retain memory correctly, but close returns void | Publish cleanup result and retained ownership; partial preparation/cleanup must be retryable without new allocation or premature unload. | S2 |
| W16-4 | Mario snapshot/focus invoke synchronous reset; load commits before ignored reset result | Serialize app load/reset; failed reset cannot report a clean queue or publish a new game state over old queued sound. Close supersedes pending load. | S2 |
| W16-5 | lib/win16/host.c service precedes first UpdateWindow and destroys directly on close | Add only generic optional startup/close lifecycle hooks if required; prevent nested device work and service pending cleanup while unfocused. Preserve Mine default behavior. | S2 |
| D16-1 | pcm_dos.c probe1024polls, write4096polls; IRQ calls start_block | Bound a whole operation as well as individual polls; qualify a separate short IRQ budget. Poll count is not a measured millisecond bound. | S3 |
| D16-2 | failed start_block returns a block but does not invalidate audio.ready | Latch device failure, mask DMA, acknowledge IRQ; defer cleanup to main. No endless resubmission to a failed DSP. | S3 |
| D16-3 | IRQ and main share playing/free/ready; main can call ensure_playing concurrently | Audit and protect compound ownership publication/start decisions with short interrupt-state-preserving sections; volatile alone is insufficient. | S3 |
| D16-4 | reset/release call stop_playback with interrupts disabled; unconditional enable follows; vector/PIC restored | Preserve incoming IF, bound critical work, handle pending IRQ and faulted playback independently of playing; prove DMA is masked before freeing. | S3 |
| D16-5 | no completion-progress watchdog; native hardware file absent from portable PCM unit | Add main-serviced completion timeout and hardware seam coverage for lost IRQ/DSP busy/partial DMA start. Generic parse/probe tests are not hardware proof. | S3 |
| X-1 | Win16 advances synth without device; DOS/Win32 skip when unavailable | Make app-level unavailable/recovery policy explicit and test ordered commands; no stale samples on recovery and no compulsory wasted DOS synthesis for a terminally absent device. | S1-S3 |
| X-2 | host errors currently collapse into booleans; DOS submit may accept a prefix before failure | Distinguish ready/full/failed/pending, consumed sample count and cleanup outcome; no caller retries an already accepted prefix. | S1-S3 |

### Common contract, separate host execution

Use one small C90 declaration owner, proposed lib/kvm/audio.h, for neutral
status/result facts: lifecycle phase, last error domain/code, request ID,
accepted sample count, queue capacity and cleanup completion. Storage and
state transitions stay with the host owner. Capability flags distinguish
asynchronous Win32 control from cooperative Win16/direct DOS control; do not
label every submit or service call nonblocking. Hardware/WinMM handles never
enter this header. Add no generic thread abstraction or second PCM queue.

All hosts enforce: one device owner; no wait for a free sample block; no
overwrite of queued storage; explicit partial acceptance; stop prevents new
production/retry; memory outlives driver/DMA references. RESETTING, STOPPING
and CLEANUP_FAILED are not CLOSED. A timeout is an observation, never proof
that the driver released data. Reopen requires completed old-device cleanup.
Do not serialize handles, queue indices, clocks or pending requests into saves.

Apps own synthesis, cadence, pause/focus behavior, overflow policy, retry
configuration, recovery and user-visible status. Platform libraries receive
PCM only. During transient opening/reset/recovery the app consumes ordered
sound commands and advances/discards synthesis as appropriate. A terminally
unavailable DOS device may stop synthesis to save486CPU; any later explicit
reopen/load must resynchronize from current APU state, never replay missed
PCM. Win16/DOS retain their existing phase-reinitialize save contract; Win32
retains its serialized renderer. No new cross-platform save compatibility is
claimed. Normal ready-path PCM must match each platform's current format and
renderer reference, not falsely compare44.1kHz16-bit with11.025kHz8-bit bytes.

### S1: Win32 device and application transaction

Keep the preceding one-thread/eight-slot design and A1-A8 acceptance matrix.
One worker owns all WinMM calls, completion inspection and cleanup. Main owns
game/renderer and never waits on a worker-held mutex. Publish immutable status
snapshots/interlocked ownership; specify the memory ordering of every slot
transition. Test stop/reset while a producer has borrowed a slot and prohibit
release until that producer has returned it. Generation checks discard stale
unsubmitted blocks and abandoned load acknowledgements.

The existing2second stalled observation and250msgraceful-exit budget remain
prototype candidates. An event-held driver call must not prevent input/close
dispatch within1second on either width. No replacement thread, extra process
or TerminateThread. Successful cleanup precedes release. Emergency self-exit
must pass the separate host-restoration/lifetime prototype before adoption;
otherwise its limitation stays open, not hidden behind a longer test timeout.

Estimated10-16source/test/build files,700-1200changed lines, including shared
declarations and app load/focus/close/title integration. Preserve measured
eight-slot PCM storage; report thread-stack reserve separately from committed
memory. Establish this contract before adapting the two16-bit hosts.

### S2: Win16 cooperative lifecycle

Retain MMSYSTEM and the existing eight184-byte PCM blocks. Introduce explicit
begin/service/status/reset-request/stop-request operations within lib/win16;
service performs at most one driver lifecycle call per host dispatch. Submit
may perform its single waveOutWrite, but never open/retry/reset or pump USER.
An in-service guard prevents reentry from messages dispatched by a driver;
nested requests set intent only. Stop outranks reset and startup retries.

Start acquisition only after initial window paint, not merely after CreateWindow
or in the first pre-paint service call. Optional neutral ready/close-request
hooks belong in lib/win16/host; audio policy stays in Mario. Existing clients
with no hooks keep the current close behavior. Service audio before the app's
focus/tick guard, including pending stop while paused/unfocused. A close request
starts cleanup; release host/app storage only after the declared result permits
it. No game logic or audio-specific branch belongs in the generic window owner.

Initial busy policy: at most three total opens, at least1000msbetween returned
MMSYSERR_ALLOCATED failures; caller supplies this policy. Other errors end that
episode. Stop cancels scheduled retries immediately. Failed cleanup preserves
the module, handle, locked memory and remaining header ownership; subsequent
service retries are bounded and explicit, never an automatic tight loop.
Exhausted cleanup remains visible to the app, not silently classified closed.
For returned cleanup errors, use at most three service-spaced attempts per
episode; on exhaustion the Mario window stays alive with PCM submission
disabled and app-owned Retry/Cancel-close feedback. Retry starts another
explicit episode, Cancel keeps the retained device storage and returns to the
app. Do not return from WinMain over a known live driver reference. This
feedback cannot execute while the driver itself has not returned.

For load, validate the staged save before requesting reset; keep the old game
until reset completes or the device is safely closed with no borrowed buffers.
Then restore/resynchronize together and re-anchor the scheduler. Failed reset
aborts the load without a game commit. Do not add a second10KiBsave allocation;
reuse existing staging while rejecting further P/O until resolved. Saving does
not require a device reset solely because the current function handles both P
and O; preserve app pause and timing semantics explicitly.

Win16 cooperative execution cannot preempt a driver that never returns. A
timer, callback or a second cooperative task is not a cancellation mechanism.
Acceptance covers finite returned errors/delays, no unbounded app retries,
safe buffer retention and ordinary real-driver operations. It does not claim
hard responsiveness/exit during an arbitrary stuck driver. A failed-close
receipt must state the app's actual user-visible outcome; no unsafe freeing or
unconditional task exit may masquerade as a successful close.

Estimated8-12files,400-750lines including mirrored tests and optional host
hooks. Resident PCM capacity stays unchanged; control state target below1KiB.
No new Win16 thread, helper process, full-frame or snapshot buffer.

### S3: DOS16 DSP, DMA and interrupt lifecycle

Retain Sound Blaster8-bit mono, two2048-byte DMA blocks, existing BLASTER and
toolchain. Do not introduce another ring or change DOSBox cycles/hardware to
pass. Keep fixed bounded port access in the hardware owner; test seams must not
add per-sample indirect calls to the production path.

Separate foreground device service from the short IRQ continuation. IRQ only
acknowledges hardware, publishes completion, attempts the next block under a
qualified small total DSP budget, records fault and sends EOI. No allocation,
free, vector replacement, reset/reprobe, synthesis or blocking retry in IRQ.
If continuation fails, mask DMA immediately and publish a latched fault; main
owns stop/recovery/cleanup. Do not just move every next-block start to a slow
game tick: that can create audible gaps and requires its own timing proof.

Use short FLAGS-preserving critical sections for queue claim/publication and
start ownership. Do not disable interrupts across sample copies, allocation,
foreground waits or an entire cleanup retry. Both IRQ and main see each block
as free, filling, ready or playing; failed partial publication reports exact
consumption. Mask DMA on every failure after programming, even if playing was
never set. Teardown must reconcile a pending IRQ and restore the prior vector
and relevant PIC state before memory release; test cleanup at each start stage.

Add service(now) with a monotonic host timestamp for progress observation,
derived from the existing clock rather than another timer interrupt. Its
watchdog depends on programmed samples/rate plus an explicit margin; do not
time out while deliberately stopped. Lost completion transitions to fault,
stops DMA and lets gameplay continue without sound. Retry/reprobe requires a
new explicit episode, not every game tick. Preserve elapsed-wrap behavior.

Measure ordinary and fault-path foreground cost and worst IRQ duration at
unchanged DOSBox settings. Select the poll budget from measured supported DSP
response with margin; do not relabel4096iterations as a fixed time guarantee.
Compare underruns/audio continuity before accepting a shorter IRQ budget.
Estimated7-11files,350-650lines; retain4KiBDMA, control-state target below1KiB.
The DMA64KiBboundary rejection remains an explicit capability failure in this
task; no unrelated allocator redesign is required to claim lifecycle repair.

### S4: integrated acceptance and task closure

| Proof owner | Required evidence |
| --- | --- |
| Shared contract | Single owner per decision; accepted-prefix semantics, phase/error facts, declared capabilities; no host/game dependency in kvm. |
| Win32 session | All held driver call sites, partial prepare/cleanup failure, late return, reset epochs, queue saturation, producer/stop race, one worker and safe terminal release. |
| Win16 lifecycle | Fake SDK covers each open attempt and timing boundary, reentry, one lifecycle call per service, close during prepare/retry, reset failure, partial cleanup and retained GlobalLock/module ownership. |
| DOS hardware | Port/vector/IF seams cover busy DSP, absent reset signature, DMA boundary, partial start, full/prefix queue, interleaved IRQ/publication, lost IRQ, fault cleanup and repeat reset/close. |
| App joins | Graph/text Tab, focus/pause, save/load success/failure, repeated P/O, close during startup/load, unavailable/recovery synthesis policy; Mine unchanged under optional host hooks. |
| Operational | Complete applicable x86/x64 unit and integration suites, independent library build, native host integration, real DOS and Win3.x execution of the combined MZ/NE product, normal audio and absent-device routes. |
| Audio evidence | Neutral known PCM verifies device transport; captured product audio verifies nonempty/nonflat output and reset/recovery continuity. Neither alone proves subjective listening quality; retain an owner listening check separately. |
| Resource/performance | Before/after PCM/control/thread memory, device latency, DOS IRQ duration/underruns and ordinary game timing at unchanged settings. Report measured maxima as samples, not universal bounds. |

Each code-changing P rebuilds local assets/mario/mysmb16.exe (DOS MZ plus
Win16 NE), mysmb32.exe and mysmb64.exe, and reports hashes/build/run results.
Do not commit binaries or protected captures. S4 republishes only when code
changed or hashes/build provenance are stale. Source/test ownership and Mine
regression are mandatory for any generic Win16 host hook.

Close findings individually against their owner tests and actual integration
joins, not a single aggregate pass count. For each S: before-work brief with
owners/size, implementation plus similar-issue sweep, tests/products, reviewed
commit and result report; only then admit the next S. S4 adds no new speculative
optimization. Any unqualified lifetime or host path remains named and open;
unsupported arbitrary-driver cancellation is an explicit platform limit, not
a test that is silently skipped. T19 closes only when A1-A8, W16-1..5,
D16-1..5 and X-1..2 have dispositions backed by the above evidence.

P2 design review: current Win16 tests already exercise failed reset/unprepare/
close retention; extend rather than duplicate those assertions. Current DOS
pcm_smoke tests parse/probe/reserve/reprobe, not actual pcm_dos port/IRQ code.
No fresh audio capture, product run or repair is claimed in this P. Only S1 is
registered active; subsequent S admission adds its own empty-ROM ledger run.
Historical1992/1992 and retained1991/1992nodes,4260/4261feasible controls
(4342raw,81infeasible) are unchanged; no final ROM certification credit.

P2 review/gates: node responsibility validation regenerated the view without
node/custody changes; the empty-scope admission gate and documentation topology
gate passed. Actual design diff touches three tracked documents (proposal,
CURRENT and ledger JSON); no production build is warranted for this P.


## S1 P3 implementation and coordinator review

Closed Win32 scope: one device thread owns open/prepare/write/reset/unprepare/
close and completion scanning; the producer borrows the same eight PCM slots.
Interlocked slot publication and reset IDs fence stale production and late load
acknowledgements. Device APIs never run on the game/message thread. No second
process or second PCM queue. Close requests retain driver-owned storage;
after250ms the app restores its host and may terminate itself without DLL
detach when cleanup is held. No individual thread termination or early free.
The deterministic held-exit product-root fixture proves this exceptional path.

A1-A8 are resolved for the admitted Win32 contract: all six driver call sites
have event-held responsiveness/lifetime tests, all nine allocation/handle/thread
failures unwind, partial preparation and failed reset/unprepare/close retain
ownership, chronological queue reuse and reset/borrow/stop joins pass. The app
advances synthesis when unavailable/full, commits staged load only after its
matching successful reset, rejects nested P/O while pending, and abandons a
failed/timed-out load. Late completion cannot commit abandoned staging.
One owner assertion per decision is in pcm_smoke or pcm_session_smoke; app
integration covers renderer continuity, load/reset/focus and actual host exit.
ROM game, PPU, save format and Mine behavior are unchanged.

Operational receipts: x86 and x64 each313/313 default tests pass. Independent
library23/23 passes. Named mysmb_win32_host_integration passes15/15 routes on
each width; mine_win32_host_integration passes3/3 on each. A tiny480pixel-wide
RDP desktop exposed two fixture assumptions: initial geometry ignored the
existing monitor clamp, and a clipped ReadConsoleOutput rectangle was compared
as if all requested cells were returned. Only those fixture expectations were
repaired; production geometry and text presentation are unchanged.

Real mysmb_win32_audio_host_integration passes on both widths. First x86 run
exceeded its12second device-open observation budget; the unchanged rerun
passed. A separate matched probe measured main/NULL1094ms, main/EVENT10110ms,
worker/NULL10093ms, worker/EVENT32ms, all successful. This confirms a variable
host endpoint delay, not a thread/callback-specific explanation. Keep this
failed receipt explicit. Neither the12second diagnostic nor the rerun changes
the2second app stall observation or250ms exit policy. Ordinary API acceptance
is not a subjective listening receipt; capture/continuity belongs to S4.

Memory: sample capacity stays11760bytes, eight headers and queue flags remain;
new slot/order arrays add64bytes plus the session/handles. One Windows thread
uses the executable's default stack reservation; reservation is not committed
memory. No DOS/Win16 PCM change in S1. Both original16-bit products compile and
link with the repository toolchain; Mario's combined MZ/NE and Mine's combined
MZ/NE are rebuilt. A sandbox-only link execution failure was resolved by running
the identical linker with authorized execution, not by replacing its toolchain.
Fresh16-bit runtime qualification follows in S2/S3/S4.

Executor/coordinator diff review: changed owners match S1; neutral status enums
have no host/app dependency; APIs expose their own error/request/acceptance
facts without an unnecessary common mutable context. Similar-issue sweep
covers every Win32 driver call, resource acquisition, load/reset, Tab/focus and
root exit path. No unreviewed third-party code or protected artifacts enter Git.
All six local products refreshed; their hashes below bind this P's builds.
Empty ROM scope/expected/actual; historical1992/1992; retained1991/1992nodes,
4260/4261feasible controls(4342raw,81infeasible) unchanged, no new certification.

- mario/mysmb16.exe: `9c00f3daacd1e3c211daf208c6196e9c8a4338eb613c82cfc22518ab31951e78`.

- mario/mysmb32.exe: `0f66ff02c78adc1f86944ca15cb9e9f3a06791944b5c99581973346d6f3559f2`.

- mario/mysmb64.exe: `b2f2a79c40267d6c6bdf133ab72c0ab55b53430e60450594258e5e96c9d39590`.

- mine/mine16.exe: `b30d5f34c0d9b90f850ea0b132ec5f94548fb41b0ee2c255b0ea3ef66388c7e4`.

- mine/mine32.exe: `ff855e856a3346826bc67a6bcdd4cea3c368bcd5a64e77702ef19e1f67e98ee6`.

- mine/mine64.exe: `ea0099b94e70952e5d457e56a7b6db4cced022a536dd10ae679c599b372d87b7`.


## S2 P1 implementation and coordinator review

W16-1..5 resolved within the cooperative-platform contract. begin records
intent; service executes at most one WinMM lifecycle call. The host invokes
started after initial paint and then services it even without focus. Acquisition
retries only ALLOCATED, at most three opens separated by1000ms. Submission
never opens/retries, returns exact accepted count and rejects busy/full/pending
reset/stop. Nested driver callbacks cannot reenter service; stop wins over late
open/prepare/reset returns. Reset acknowledgement is distinct from request.

Cleanup has an explicit phase/error and at most three failed calls per episode,
spaced by the caller's delay. It retains GlobalLock/module/header ownership
on failure. Mario stays open and offers Retry/Cancel-close on exhaustion;
Cancel preserves the device storage and continues without PCM submission.
No task exit over a known live driver reference. A driver that never returns
cannot be preempted under Win16; that platform limit is unchanged and explicit.

Mario validates load staging before requesting reset; it freezes logical tick
and ignores additional P/O until success/failure. Successful acknowledgement
commits game and resynchronized synthesis together; failure preserves the old
game and logs the load failure. Save no longer resets audio. Focus loss requests
reset; service continues while unfocused. No additional snapshot buffer.
Generic host extension is a separate optional lifecycle argument, preserving
the old application structure and Mine entry. USER callbacks cannot recursively
run app update. Window/system close and app exit share the close hook; default
clients retain direct close. Audio policy stays in Mario, not lib/host.

Owner tests extend existing fake SDK: load/allocation/lock/proc/open/prepare/
write/reset/unprepare/close failures, three busy attempts and timing boundary,
stop during busy/open/prepare, reentry, retained cleanup and reset coalescing.
Host tests prove post-paint start, deferred close, update reentry guard and
unchanged clients. Mario app join tests use its actual root and file codec:
save without reset, load held across P/O, successful commit, failed reset without
commit, Tab/focus/close and allocation unwind. No included production C hack.

Both default width suites313/313 passed; after final review edits each Win16
subset9/9 passed. Independent library23/23 passed. The original toolchain builds
both MZ/NE products; unchanged x86/x64 binaries retain S1 provenance. Real
private Win3.x runs of final Mario and Mine pass: Mario graphical/text Tab,
save/movement/load and Escape; Mine click/level/text/graphics and Q. Captures
and the10035byte Mario save are local only. Audio transport capture remains S4.
PCM capacity remains eight184byte blocks plus headers; added control state is
below1KiB, no thread or new sample/snapshot allocation. Native16bit compiles
confirm both small-model Mine and large-model Mario generic host ABI.

Coordinator review of actual diff and similar-issue sweep: all callers of the
old synchronous Win16 audio entry points migrated, including the neutral native
probe. No app or original semantics in the reusable audio/host owners. Ledger
semantic comparison proves only the new S2 subtask/run was added, despite a
large textual diff from repeated1992label arrays. Empty ROM scope/expected/
actual; historical1992/1992, retained1991/1992nodes and4260/4261feasible controls
unchanged. No new certification. Six local products available; changed hashes:

- mario/mysmb16.exe: `e5c76ed9ff3af88796b5958fb3979023276d1ec8af8a5a988770d2a228d390fc`.

- mine/mine16.exe: `5b87aedf04da4d32af9d4361144551c32fb27662608ca59c63b309eab29fafad`.


## S3 P1 implementation and coordinator review

D16-1..5: the original two2048byte DMA blocks remain. Claim/publication/start
use short FLAGS-preserving sections; sample copies keep caller interrupts.
Submission returns an exact accepted prefix. The app consumes each synthesis
frame once, drops only unaccepted output, and restarts synthesis after load.
DSP start/IRQ share128polls per operation; cleanup shares512; probe retains1024.
Faults mask DMA immediately and latch failure. Main service, using the existing
PIT clock, owns watchdog and cleanup. No added timer, thread or per-tick retry.
The watchdog is block duration plus500ms and handles wrap/midnight reset.

Pending PIC edges drain through the installed suspended ISR before vector,
mask and DMA storage release. A caller with IF clear cannot be forced enabled;
close reports pending and app exit waits through normal service. Only owned
PIC mask bits are restored. The first diagnostic PIC-poll approach was rejected
because ordinary DOSBox does not implement it; no such command remains.

Port/FLAGS owner tests cover six partial DSP starts, queue saturation/prefix,
copy/IRQ interleaving, spurious IRQ, masked/latched cleanup, lost completion,
wrap, missing hardware, DMA boundary, allocation, slave IRQ and reset/close.
The app adapter test owns renderer continuity and partial consumption. Both
width suites315/315 and independent library24/24 pass. Native original-toolchain
PCM probe at unchanged DOSBox settings completes60periods,18IRQs, zero gaps in
its prefilled workload, and restores masks. Observed normal IRQ max672PIT ticks
(0.563ms), baseline611(0.512ms); submit62919(52.73ms) versus62890; service151
(0.127ms). Injected busy IRQ consumes128polls,1815ticks(1.521ms); subsequent
cleanup consumes512additional polls. These are workload measurements, not
universal timing bounds or a normal-path speedup. No production probe hooks.

DOS static minimum388288bytes, bounded maximum392384; DMA remains4096bytes.
Compared with S1 static minimum adds1456bytes and DGROUP adds16. Dynamic game
caches are excluded. Final DOS/Win16 hybrid binds successfully; the other five
products retain reviewed S1/S2 provenance. Actual product DOS capture after a
late Start contains nonflat PCM (52.896s, signed16 range -11848..19933).
The earlier all-zero capture pressed Start before title initialization and
is retained as a failed fixture, not a claimed audio pass.

A separate integrated-product defect is explicitly assigned to S4: at unchanged
DOSBox default cycles, persistent lateness permanently suppresses presentation.
The old retained executable reproduces the same empty graphics/text result;
a build-only forced-publication probe shows valid pixels. S3 audio ownership
scope closes, but T acceptance remains blocked until S4 repairs and tests bounded
presentation progress, then repeats final product/audio/save/load routes.
Coordinator authorizes that narrow app scheduling correction as necessary to
this task's requested usable-product acceptance. Do not alter core/PPU, logical
tick sequence, audio rate, or DOSBox configuration. No performance parity claim.

Executor/coordinator review: all DOS PCM API callers migrated; failure cleanup
cannot free driver-owned storage, no DOS policy enters shared game logic. Empty
ROM scope/expected/actual: historical1992/1992, retained1991/1992nodes and
4260/4261feasible controls(4342raw,81infeasible) unchanged, no certification credit.

- mario/mysmb16.exe: `3086cfdf69e3ca2d2ece2b8e9cf46421821af3f9b3e0d672f049215bd44af18b`.
