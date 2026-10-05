# Win32 Event Keyboard For Local And Remote Sessions

Owner requests investigation and repair of keyboard failure over RDP,with
read-only reference to sibling SoftPC Lib. New M3 T14 S1 owns one bounded
host-input repair;estimated8-12files,300-450lines. Window messages and console
key records must maintain held/released keys without global async polling.
Preserve WASD/JK(J=B,K=A),Enter,either Shift,Tab,P/O,Escape,focus auto-pause,
startup selection and console close. DOS behavior/game semantics unchanged.

Reference admission:owner-selected sibling SoftPC Lib is read-only research
for Windows event/focus patterns;inspect licensing/provenance before copying.
No sibling source is imported or translated. Implement MySMB-owned adapter
against Windows API documentation. Existing owner-local ROM solely builds
three local products and runs existing tests;derivatives stay uncommitted.
Temporary research/logs/probes remain beneath build/m3-t14-s1.

Verification:deliver window messages and real console input records while
asynchronous key service returns zero;check every mapping,short presses,
multiple keys,aliases/modifiers,repeats,release/focus/presenter/restore lifetime.
Both widths run root/input/Tab/snapshot/focus/close/startup regressions and
purity;original DOS16 compile/link and three refreshed local products.
Actual remote client routing requires a live RDP session;isolated probes
prove the event-driven path without claiming an unobserved remote session.

Sweep:all GetAsyncKeyState/GetKeyState,window/system key handlers,console
KEY_EVENT/FOCUS_EVENT consumers,focus changes,shortcut and restore reset paths.
Stop for game changes,unowned desktop input or unresolved scoped differences.
Empty node scope/expected/actual,new0;historical1992/1992,local1991/1992nodes,
4260/4261controls unchanged. M2 final certification stays separate.

## S1 P1 review and T closure

Closed bounded host-input repair. Previously game keys were consumed only by
GetAsyncKeyState;window messages and console records handled shortcuts only.
Tab's shared latch was also released by the async service each loop. These
dependencies explain why delivered Escape could work while game keys failed
when asynchronous state was unavailable. Actual RDP client delivery was not
observed;the repair removes that dependency rather than claiming live RDP proof.

The Win32 event adapter now owns independent physical held keys and one-tick
short presses. Window/system-key messages and actual console records feed the
same adapter. J=B,K=A,WASD,arrows,Enter and either Shift retain their mappings.
Repeated downs cannot reissue Tab/P/O. Focus loss clears keys and shortcuts;
presenter changes and restore clear game keys but preserve held shortcut edges.
No game,neutral IO or DOS input code changes. Snapshot test now explicitly
releases P before O;all existing save/load/error/audio assertions remain.

Console devices use owned CONIN$/CONOUT$ handles rather than inherited stdio.
Raw input disables virtual-terminal,processed,line,echo and quick-edit modes.
Focus records clear stale input. An isolated320-pixel-high desktop exposed a
separate existing failure:fixed8-pixel font could not fit50rows. Device font
now shrinks when necessary;shared cells,buffer and visible grid remain80x50.
If none of the bounded font choices fit,existing graphics fallback remains.

Both x86/x64 pass7focused CTests:keyboard,launch policy,snapshot binding,
focus pause,DOS root,purity and actual product self-test. Per-width isolated
host routes pass13GUI and13console mappings,repeat/release,chords,aliases,
either Shift,short pulses,focus clearing,P/O requests and bidirectional Tab.
The async stub always returns0 and receives zero product calls. Existing
Unicode,color,save/load,audio continuation,allocation/clipping/lost-console
recovery checks pass. Console buffer/view remain80x50;raw mode is asserted.
Six actual launch/close routes also pass per width:ordinary and console-bearing
non-shell launch,CMD without a console select graphics;CMD,Windows PowerShell
and PowerShell7 with consoles select text. All owned product exits return0.
Probes use private desktops,not global input or user-window activation.

Original OpenNT16 compilation/link succeeds with existing legacy warnings.
Three local products16/32/64 are360987/444880/461571bytes. DOS is byte-identical
to the prior product. Build,test,host-route,product hash and review receipts
remain beneath ignored build/m3-t14-s1. No physical486qualification or live
RDP session is claimed;owner can test the refreshed Windows products remotely.

Actual code/build/test changes:9files,+302/-63lines. Architecture and task/ledger
records are separate governance updates. Similar-issue sweep finds zero
remaining production GetAsyncKeyState/GetKeyState calls;all window/system key,
console key/focus,presenter,restore and release paths use the declared owner.
Held shortcut retention and real release tests prevent restore/repeat regressions.
Unrelated UI/Roadmap/terrain edits are preserved. No sibling code was imported.

Empty scope/expected/actual,new0;historical mapping1992/1992,local scoped
nodes1991/1992,feasible controls4260/4261(raw4342,infeasible81) unchanged.
These are retained local dispositions,not full-game verification. M2 certificate
remains incomplete and its continuation stays queued. Ledger custody and prior
runs are preserved;documentation gate passes. T14 has no remaining admitted S.
Products/ROM/generated data are not staged. Local P commit,no remote push.

Read-only SoftPC Lib inspection identified window key/system-key handling,
console key/focus records and disabling terminal input. No sibling license was
located;reference-only inspection did not copy or transliterate source.
Original adapter implementation uses primary Windows API contracts:
[keyboard input](https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input),
[asynchronous state limits](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate)
and [console input mode](https://learn.microsoft.com/en-us/windows/console/setconsolemode).
