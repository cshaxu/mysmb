# Win32 Startup Presenter And Console Exit

Owner approves new M3 T13 with one bounded S1:launch classification,enabled
console close,host regression and three product builds. Estimated5-8files,
150-250lines. Direct cmd.exe,powershell.exe,pwsh.exe parents with a console
select text;Explorer and other parents select graphics. Detection failure
falls back to graphics. Use an owned console without altering the shell.
Tab remains bidirectional;DOS keeps default graphics. No game/neutral ABI changes.

A bounded console handler posts WM_CLOSE to the root and waits for cleanup.
Root uses the existing shared exit latch;handler performs no device/game work.
Verify shell/non-shell process routes,menu/close/Tab,snapshot/focus/audio,
x86/x64 tests,original DOS16 compile/link and all three refreshed products.
Microsoft Windows API documentation is reference-only;no third-party import.
Existing owner-local ROM used solely for builds;derivatives/products remain
local. Evidence/logs beneath ignored build/m3-t13-s1.

Sweep all SC_CLOSE/handler/open/close paths,root destruction,initial presenter
selection and DOS text_mode initialization. Stop for unowned host effects,
game changes or unresolved scoped tests. Closure requires launch/cleanup
proof,three builds,ledger/documentation review. Empty ROM scope/expected/actual,
new0;historical1992/1992,local1991/1992nodes,4260/4261controls unchanged.
Deferred M2 certification remains queued separately.

## S1 P1 review and T closure

Closed. Shell identity is checked against the direct parent in one process
snapshot;only CMD/Windows PowerShell/PowerShell7 with an attachable console
select text. Detection failures,Explorer and arbitrary launchers select
Windows graphics. An attachment probe never changes the shell's font,buffer,
input,palette or menu. Actual text uses a separately allocated owned console.
DOS root/device initialization remains graphics;its regression now asserts it.

Console close is enabled and posts WM_CLOSE to the existing neutral root exit.
The root closes audio before its console. A host-close pending flag preserves
the registered handler/attachment until normal CRT process exit;unregistering
or detaching during that event previously reproduced STATUS_CONTROL_C_EXIT.
The callback performs no game/device mutation and waits at most4000ms for
process exit. A hung process is still subject to Windows termination. Ordinary
Tab/recovery unregisters and detaches immediately;no event handle is leaked.

Both x86/x64 pass7focused CTests including policy,IO,root,snapshot,focus,purity
and real product self-test. Isolated-desktop tests per width pass six actual
launch routes:ordinary CreateProcess,console-bearing arbitrary launch,
CMD without a console,CMD with a console,Windows PowerShell and PowerShell7.
The first three are graphical,the latter three text. Each actual product
closes through its proper GUI/console menu and exits0. The existing controlled
host route passes Tab/Unicode/input,save/load,focus pause,audio continuation,
allocation failure,clipped output and lost-console recovery. No global input
or user-window activation. Explorer itself is not launched by the probe;
its graphics disposition is the tested non-shell policy.

Original OpenNT16 compilation/link succeeds with existing legacy warnings.
Refreshed local products16/32/64 are360987/442635/458788bytes. DOS hash remains
identical to the T12 product;Windows hashes and source/test receipts are local
beneath build/m3-t13-s1. No physical486speed or new ROM equality claim.

Actual code/build/test changes:10files,+306/-14lines. The larger-than-estimated
addition is the isolated-desktop real-process acceptance harness;production
remains limited to the Windows root,console adapter and launch classifier.
Architecture and task/ledger records are separate governance updates.
Sweep:one production SC_CLOSE setting now enables close;one handler remains
console-owned;all root destroy/Tab/recovery branches reviewed. DOS's two
initialization owners retain text_mode0. No parallel exit policy or game
changes. Existing unrelated UI/Roadmap/terrain changes are preserved.

Empty scope/expected/actual,new0;historical1992/1992,local1991/1992nodes,
4260/4261feasible controls(raw4342,infeasible81) unchanged. M2 certificate
remains incomplete. Ledger/custody prefix retained;documentation gate passes.
All owner-requested T13 clauses close. Products/ROM/generated data are not
staged;this is a local P commit with no remote push. Remaining M2 candidate
stays in Queue;no successor T is automatically admitted.

Windows API reference:[AttachConsole](https://learn.microsoft.com/en-us/windows/console/attachconsole)
and [control handlers](https://learn.microsoft.com/en-us/windows/console/registering-a-control-handler-function).
References informed host lifetime semantics;no external code was imported.
