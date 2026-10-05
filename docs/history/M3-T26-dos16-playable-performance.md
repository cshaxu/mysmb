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

## S2 owner amendment: preserve all240 source rows

Owner explicitly requires repair of DOS picture degradation. Existing VGA
mode13h is320x200;the adapter expands256columns to320 and drops40of240rows.
A640x400host capture doubles that already lossy output;it does not restore
NES detail. The existing VGA-scaled equality check proves the old mapping,
not preservation of every source row. It is insufficient for this requirement.

Extend S2 to VGA mode setup,frame layout,device submission and DOS root buffer
binding,plus associated pixel/readback/lifetime tests. Estimate200-400source
and test lines,subject to measured mode design. Owner requires full640x400 stretch,not original-size centering. Use320x400
Mode X with direct nearest-neighbor enlargement and horizontal double-dot
scanout. Retain all256x240source pixels without downsampling;verify full
source-to-device coordinate coverage,all palette indices and aspect/placement.
NoVESA/higher-resolution dependency is assumed. Keep DOSBox's full installed
configuration unchanged,including CPU and sound. VGA registers programmed by
the application are its device adaptation,not emulator-setting changes.

Preserve graphics/text switching,snapshot redraw,original video-mode restoration,
input and exit. New storage must remain16-bit addressable with bounded far
segments. Standard/native-mode options require documented register/stride
and palette semantics and a neutral synthetic device probe before product
changes. Read-only hardware research references are permitted for these
semantics only;no third-party source import or ROM material redistribution.
The shared ROM game routines remain unchanged;PPU-compatible composition
and device scanout are separate output owners. Any new mode must pass an
updated lossless mapping oracle,not the obsolete320x200reference scaler.
Three product builds/packages are required for each product-code P.

## S2 P2 display delivery: full640x400 stretch

Owner rejected original-size centering with black margins. That local320x240
experiment is not delivered. The device now uses320x400 unchained VGA memory
with BIOS mode13h timing and horizontal double-dot scanout to640x400.
Direct enlargement maps logical x to floor(x*4/5),y to floor(y*3/5).
Every256x240source coordinate is retained;there are no added borders and no
320x200 intermediate. Noninteger enlargement necessarily repeats source dots
unevenly;this is the requested full-screen stretch,not an aspect-fit layout.
Four far buffers each hold32000bytes below the64KB segment boundary;the VGA
sequencer selects each plane at the same A000 offset. DOS binary/storage grows
by64240bytes versus S1;this picture repair is not a claimed performance gain.

Bounded similar-issue sweep:VGA sizing/mapping,all four root far allocations,
plane submission,stride/mode registers,palette,graphics/text transitions and
exit restoration. Root allocations already follow the shared page-size constant.
Only platform adapters changed;shared game/IO contracts,PPU composition and
ROM routines remain unchanged. The independent VGA oracle replaces the old
lossy200-row reference;buffer guards remain checked. Product/test5files,+53/-33.

Operational evidence below ignored build/m3-t26-s2:mode400-run neutral probe
reads all four32000-byte VGA planes and verifies all256000 captured640x400
pixels against a synthetic palette grid. Product-stretch-run launches the
actual new DOS EXE using the unchanged installed configuration and a retained
local snapshot;the populated640x400 picture remains byte-identical while
paused and through graphics->80x50text->graphics. Escape returns to DOS and
the captured original text mode is restored. SDL dummy isolates host display
and audio for device correctness only;it earns no performance acceptance.
Config hash remains the admitted0494236f...41917 value before/after.
The capture scripts' early exit-window issue was corrected by leaving the DOS
prompt open until its bounded capture;it was not a product defect.

Original OpenNT16 compiler/link succeeds;both Windows widths each pass five
focused tests:VGA frame,presentation performance,DOS root,DOS snapshot and
platform purity. Retained compositor oracle runs2048boundary and1198native
cases per width;new full-frame plane mapping compares the actual packed output.
No new ROM certification claim follows from these presentation checks.

All three local products refreshed:429963/319115/327275bytes. DOS SHA256
`a7567e3b8d2a08a712c541436382fd57b10fbf0d469d4d9cce4435fc6e5419e9`;
x86 `fd4bacdc12cb8d6f1278254262df2a8e342a80a7d4795bb8f18fd7875de1677b`;
x64 `e4287bf0389721c0403982e47ee330132ca3fa2d1d69fc0dba8dff86c0f5cb87`.
Each local package matches its build;protected EXEs/ROM/captures remain ignored.

Hardware research uses published VGA register semantics from
[Abrash's Mode X discussion](https://www.phatcode.net/res/224/files/html/ch47/47-02.html),
as a read-only technical reference;no book code is imported or redistributed.
The original NES similarly fetches/decodes CHR and composites sprites,using its
hardware PPU rather than game-CPU pixel loops;see
[PPU rendering](https://www.nesdev.org/wiki/PPU_rendering).
VGA has no NES tile/sprite unit,so this port's shared compositor produces the
indexed source before the platform adapts it. This is not a CPU emulator.

Scope/expected/actual labels remain[],new0. Historical1992/1992,local scoped
nodes1991/1992 and feasible controls4260/4261(raw4342,infeasible81),unchanged.
P2 delivers the requested display correction. S2/T26 remain active:original
nominal cadence under the unchanged installed configuration is still unproven.
Physical486SX,heap/stack peak and broader M2 certification remain open.
