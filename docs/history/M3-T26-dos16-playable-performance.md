# M3 T26: DOS16 playability repair

The owner reported unusable DOSBox gameplay speed. [the admitted diagnosis](M3-T25-dos16-performance-diagnosis.md)
measures the frame rate and stage costs before implementation. Admit this
candidate only after reviewing that diagnostic result. It has zero ROM-node
scope and zero expected matches unless the admitted repair explicitly changes
that contract.

A future S may optimize only the measured dominant DOS16 path. A later S
checks old/new indexed frames, VGA bytes, game state, audio commands,
snapshots, pause and three-target builds, then repeats the same DOSBox workload
under default and explicit accelerated CPU settings. Do not reduce game ticks,
image content or input semantics to meet a frame target. Emulator results do
not establish real 25 MHz 486SX qualification, which remains M4.

## S1 admitted repair chain

Owner goal authorizes completion of the DOS performance repair after reviewed
T25 diagnosis. One S owns the continuous indexed-background ->VGA-scale
chain and its delivery. Scope:shared game/ppu_frame.c read-only compositor,
platform/vga/vga_frame.c generic scaler,original OpenNT16 build flags,focused
project-owned regression harnesses. No gameplay decisions move to platform.
Estimate20-100source/build lines plus50-150test/evidence lines.

First test bounded speed optimization of these two16-bit translation units,
then only measured pixel-loop cost if necessary. Keep C90,no assembly or
CPU-specific instructions,no dropped frames/ticks/content,no new processes
in the product. Native widths must use the same compositor semantics.

Acceptance:2048retained random/boundary full-frame comparisons and native
resource routes with unchanged game state,audio/snapshot/pause checks,
VGA scale equality and actual DOSBox input/presentation/snapshot/exit.
Repeat old/new same-input stage/count controls at default and accelerated
settings,report timing and limits;actual product must improve throughput
without introducing pacing regression. Original DOS16 and x86/x64 builds
refresh all three local EXEs. No physical486SX qualification claim.
ROM scope/expected new labels[],new0,historical1992/1992,local1991/1992
nodes,4260/4261feasible controls(raw4342,infeasible81),unchanged.

## S1 closure and T26 review

The production change is shared,read-only row staging in game/ppu_frame.c.
A272-byte stack palette/row workspace replaces per-dot far-buffer stores,
reads immutable CHR/control values once per row,decodes full eight-dot spans
without the pixel loop,and copies each completed256-byte row once. Partial
scroll spans,transparent palette-zero aliases,CHR bounds,mirroring,status
split,left masks and sprite priority retain the prior semantics. No cache
outlives a call;palette/nametable/resource changes need no invalidation.
No platform gameplay owner,ABI,frame skipping,tick/input/audio or pacing change.
VGA scale remains unchanged because this repair meets the measured target
without altering a second owner. Source/test actual2files,+70/-6lines;
governance/ledger is separate. Original /AL /Gs flags remain:local /Ox and
/Ot attempts failed with the legacy compiler internal-buffer error,so no
unsupported optimizer switch enters the product.

| Measurement | Before | Final | Meaning |
| --- | ---: | ---: | --- |
| auto/auto background mean |1599.1ms|1007.3ms|37.0percent less guest PIT time|
| dynamic/max background mean |16.117ms|10.417ms|35.4percent less guest PIT time|
| auto/auto minimal-counter steps |11/26.69s|16/27.34s|same script,measured wall times|
| dynamic/max minimal-counter steps |1145/26.49s|1745/26.32s|same script,measured wall times|
| dynamic/max profiled steps/running steps |1303/1093|1543/1315|same workload with stage taps|

These are root-step counts,including startup and exit,not a guarantee of
wall-clock60Hz gameplay or physical486 performance. DOSBox cycles=max varies
with host load;the stable conclusion is lower measured background cost with
unchanged output,also supported by independent counter-only runs. Default
core=auto/cycles=auto remains too slow to play;the program cannot manufacture
CPU cycles withheld by the emulator. Operational playability passed with
core=dynamic/cycles=max. Those settings are verification configuration,not
product logic or qualification of a25MHz486SX. Hardware/version/heap/stack
qualification remains M4. The row workspace increases bounded stack use by
272bytes plus small scalars,no persistent allocation or heap increase.

Both-width focused builds and14focused tests passed. Dependent game snapshot,
window snapshot/focus,frame snapshot and snapshot continuation targets were
explicitly relinked and their5tests passed again. The presentation harness
compares2048random/boundary full indexed frames without game mutation and
1198resource-bound native frames,with VGA equality and snapshot capture;
audio snapshot,pause,clock/root and platform-purity checks remain separate.
The real OpenNT16 ABI also passes128neutral full-frame/state comparisons in
[test/ppu_frame_dos16.c](../../test/ppu_frame_dos16.c),linked with the current
compositor and retained project-owned reference,using two61440-byte far
buffers. Compile both owners with /AL /Gs /D MYSMB_DOS16_TARGET;rename the
reference build/bind symbols and link with the same large-model DOS runtime.
Run the harness under the bounded local DOSBox dynamic/max configuration;
its receipt is `PASS 128 full frames state unchanged`.

Actual DOS product input route passes movement,jump,release and exit. Its
text route passes4000cells,held Tab,no state loss,paused graphics round-trip,
snapshot save/load,text-mode retention and exit. These operational receipts
are byte-bound to the final DOS product. Scripts,raw captures,instrumented
mirrors and neutral summaries remain below ignored build/m3-t26-s1;the neutral
final-review.json binds timing/counter results,source and product identities.
No ROM/assets/derived EXE is committed. The exploratory all-target x86 build
hit a pre-existing unrelated cannon-children harness missing its observer
link;this T claims the explicitly built/passing focused targets,not the whole
test inventory. No unrelated game/queue/UX work was changed or staged.

| Local product | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe |365723|DB046C9FD0FFB8D3D0EE44F731B9D10369EE4C494477928A15869B4855CEE88B|
| mysmb32.exe |319115|FD4BACDC12CB8D6F1278254262DF2A8E342A80A7D4795BB8F18FD7875DE1677B|
| mysmb64.exe |327275|E4287BF0389721C0403982E47EE330132CA3FA2D1D69FC0DBA8DFF86C0F5CB87|

All three local packages equal their current builds. Original DOS16 links with
the retained OLDNAMES warning;no toolchain substitution. Scope/expected/actual
new nodes and edges0;historical1992/1992,local nodes1991/1992 and feasible
controls4260/4261(raw4342,infeasible81) remain unchanged. No M2 certification
credit. Similar-issue review covers far accesses in background,CHR/sprite
reads,VGA writes and disabled-background fill. Only the dominant background
path changed;the other owners remain measured/validated and no new mismatch
was found in this bounded contract. T26 S1 and T26 close after gates and P
commit;physical486 and unreviewed M2 obligations are not closed by this result.

## S2 corrective admission: fixed DOSBox settings

Owner rejects changing DOSBox settings as cheating. This correction supersedes
S1's T-level performance acceptance:the measured program improvement and
pixel/state equality remain scoped evidence,but accelerated-configuration
operation does not establish the requested playability. T26 is reopened.
S1 implementation remains historical;S2 owns the unresolved performance claim.

Use the installed DOSBox configuration read-only,without an alternate config,
CPU/renderer/sound/machine/frameskip overrides or runtime speed shortcuts.
Only mounting and launching the local program may be scripted. Baseline config
SHA-256 is `0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917`;core=auto,cycles=auto,frameskip=0,
machine=svga_s3,nosound=false. Before/after runs must verify this same complete
configuration identity. Even earlier auto/auto profiles disabled sound and
therefore are stage-diagnosis evidence,not fixed-environment acceptance.
No new accelerated-setting trials are authorized. Prior accelerated receipts
remain historical measurements only,excluded from performance completion.

S2 first captures an actual-product baseline in this fixed environment,then
optimizes the measured program chain,retaining all ticks,pixels,input/audio,
pause and snapshots. Scope:shared indexed compositor/generic VGA scale and
original DOS compiler path;no gameplay in platform. Initial estimate50-200
source/test lines,amend before ownership expansion. Code changes refresh all
three local EXEs and repeat scoped equality plus DOS operation. A percentage
speedup alone does not close S2:the unchanged environment must sustain the
original nominal game-frame cadence through the declared gameplay workload,
with stage/root timing,input latency and output/state equality reported.
If that cannot be demonstrated,the task remains incomplete;do not substitute
an emulator-speed increase or another platform for acceptance.

Scope/expected new ROM labels[],new0,historical1992/1992,local1991/1992nodes,
4260/4261feasible controls(raw4342,infeasible81),unchanged. This admission P
changes governance only,no product change or EXE refresh. Physical486SX
qualification remains separately pending,not proof supplied by DOSBox.
