# Bounded Windows Audio Device Startup

## Retained Task Status

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
