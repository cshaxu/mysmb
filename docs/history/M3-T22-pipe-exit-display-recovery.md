# Pipe exit display recovery

M3 T22 S1 P1 admitted under owner request:both graphic and character modes
show stale/partial scenery and an invisible pipe after exiting,until movement.
Owner7-2 before/after images bind this diagnostic. No host capture/input needed.

One S audits SecondaryGameSetup -> next NMI -> visible nametable presentation.
Reviewed local ROM NMI loads RAM Mirror_PPU_CTRL_REG1($0778);current output
bridge overwrites that producer with stale ppu_control_0 cache. Inspect and
repair this integration boundary,not scenery repainting. Expected shared
frame_root.c plus nmi_parent_integration_check.c,two files,40-70changed lines.
Original control/table provenance and entry/exit timing must remain intact.
No platform/game-rule/ABI/artwork changes. T19 remains suspended.

Existing owner-local ROM and reviewed local disassembly are nonredistributable
research/build inputs only;no imports. Bounded temporary probes/logs under
ignored build/m3-t22-s1;remove raw program products after diagnostic use.
Source review covers NMI$8082 control mirror load and SecondaryGameSetup page
selection. Retained isolated-node proofs did not cover divergent RAM/cache
values between setup and next NMI;this S supplies that missing integration
receipt without claiming whole-game certification or reopening other chains.

Check stale odd/even page both directions,all other control bits,NMI current
versus following frame,area-entry/backload/VRAM route tests,native controlled
pipe exit at7-2 using original area parsing and snapshots,indexed/text state
consistency,x86/x64 build,original DOS16,DOSBox and three local products.
Similar-issue sweep:all writes to$0778 versus ppu_control_0 and NMI consumer;
RAM is authoritative there. Test both page parities and retain physical NMI
restoration phases. Other discovered semantics require explicit scope entry.

Empty new-node scope/expected/new0;historical1992/1992,local1991/1992nodes and
4260/4261feasible controls(raw4342,infeasible81) retained. This is a missing
output integration repair,not a new node promotion. Exit:source read/write
contract and focused regressions agree,pipe background present on first
restored frame without movement,three products and ledger/docs gates pass.

## S1 closure and missing integration clause

T22/S1 closes. NMI's output bridge overwrote RAM$0778 with its prior physical
control cache. SecondaryGameSetup correctly wrote page parity into RAM but
that write was lost at the following NMI. Scrolling later updated both RAM
and cache,explaining spontaneous recovery after walking. Both presenters saw
the wrong shared nametable,including partial terrain and old scenery.

Read RAM$0778 at NMI entry before clearing d7;preserve source writes and the
existing current-frame saved-control restoration. Original owner ROM NMI
vector$8082 and its first LDA$0778/AND$7f/STA$0778 opcode sequence match the
reviewed disassembly. SecondaryGameSetup's LSR/ROR/ROL page-selection contract
is retained. This is source-level correspondence plus bounded native behavior,
not a new whole-ROM/end-to-end certificate or CPU replay claim.

The old isolated leaf/current-frame phase receipts lacked the divergent
RAM/cache producer-to-next-NMI condition. Add that explicit integration check:
16page handoffs across both parities,current versus following NMI,and128
control-bit combinations with intentionally conflicting cache. Before repair,
this regression fails52. After repair,it passes on both widths. Similar-issue
sweep covers boot write/control binding,VRAM WritePPUReg1,SecondaryGameSetup,
ScrollScreen and NMI consumer. Only NMI's cache-to-RAM overwrite is defective;
boot/VRAM synchronize physical and RAM deliberately,scroll cache refresh is
not the authoritative NMI input. No platform or game-rule change.

Controlled7-2 destination fixture uses resident area$25,entrance page11 and
alternate entrance2,before native InitializeArea/backloading/parser/setup.
No direction input precedes the first restored frame145. Old root linked into
the same current harness fails page check14:scene page11 but physical table0.
Fixed x86/x64 select table1 at that frame,scroll0,with four pipe metatiles;
all4000authored cells agree. Console readback matches4000glyphs/attributes.
Inspected authored buffer preview has pipe,stairs,cloud and full terrain.
Each native run also passes2048boundary indexed comparisons and1198native
frame/state/scaling comparisons. These compare shared compositor implementations
and read-only state,not unchanged gameplay against the old defective root.
The fixture does not claim naturally playing through the preceding water area.

Both widths pass eight rebuilt focused tests and seven private-desktop host
route groups. Original DOS16 build passes with retained OLDNAMES warning;
actual final DOSBox EXE passes text/Tab/held-Tab/snapshot/return/Escape and
paused indexed-frame equality. DOSBox is not a DOS7-2 encounter or486qualification.
Three local products364801/312971/320107bytes match build hashes. Product/test
files2,+44/-1lines,no ABI. Probe binaries/raw cells/old-root copy removed;
neutral evidence and authored preview retained below ignored build/m3-t22-s1.

Ledger/admission/docs gates pass. Empty new-node scope/expected/actual,new0.
Historical mapping1992/1992;retained local nodes1991/1992 and feasible controls
4260/4261(raw4342,infeasible81) unchanged. The repaired clause concerns output
integration,does not promote any node or complete M2 certification. T19 stays
owner-suspended;other verification remains queued. Local commit,no remote.

## S2 concentrated handoff audit admission

Owner admits one bounded concentrated S for analogous RAM/cache/consumer
handoff defects. Corrective M3 T22 S2 P1 follows latest closed T22. Review
exactly ten output-boundary contracts below;do not re-audit unrelated game
nodes or claim remaining M2 certification complete. Its queued broad state
handoff applicability work remains with the final-certification candidate.

| ID | Original/declared producer -> consumer |
| --- | --- |
| H01 | RAM$0778 -> NMI control cache/current physical control |
| H02 | RAM$0779/$0774 -> NMI display mask and restore |
| H03 | SecondaryGameSetup/ScrollScreen page -> following nametable selection |
| H04 | RAM$073f/$0740 -> committed scroll and both compositors |
| H05 | RAM$0722 -> current-frame sprite0 split |
| H06 | RAM$0200-$02ff -> NMI visible OAM |
| H07 | RAM$0773/$0300/$0340 -> VRAM transfer and header clear |
| H08 | Ordered VRAM palette commands -> committed shared palette |
| H09 | Text producer -> OAM DMA committed observer |
| H10 | Snapshot capture/restore -> original RAM,caches,visible phases |

Inspect all writers/consumers of these ten contracts within shared game/app
owners. Deliberately diverge RAM and cache in focused cases;never assume all
representations equal at every phase. Bound transition review to pipe exit,
death/halfway initialization,next-area/vine and snapshot restore entry callers.
Existing local ROM/ASM are nonredistributable source evidence only,no imports.
All scripts/logs/local probes below ignored build/m3-t22-s2. Before any repair,
record exact affected contract/source and pre-fix failure;repeat until scoped
diff resolved. No platform/game-rule/ABI or unrelated artwork changes.

Expected product code0files,test1file under120added lines,plus current/history
and ledger records. Audit-only work needs no three-EXE refresh;product repair
requires all three builds/products. Scope/expected/new-node credit empty,new0;
historical1992/1992,local1991/1992nodes,4260/4261feasible controls retained.
Exit:all ten have explicit source/consumer disposition and focused evidence;
no unexplained scoped difference,ledger/docs gates and local reviewed commit.
Finite coverage is not all-input or whole-game equivalence.

### S2 H07 scoped repair amendment

WriteBufferToScreen source $8e92-$8eec loads RAM$0778 before selecting
address increment. Current packet helper instead loads its cached control.
Deliberately opposite RAM/cache regression fails62 before repair. Normal NMI
entry synchronizes these fields,so this is a helper contract mismatch,not
proof of another observed pipe defect. Repair only game.c packet header to
reload the source mirror;retain all command ordering and physical writes.
Product1file/test1file,no ABI;refresh original DOS16 and both Windows products.

### S2 closure: ten bounded contract dispositions

| ID | Disposition and evidence |
| --- | --- |
| H01 | No additional diff. frame_root.c reloads RAM$0778;16page and128control divergent cases retained. |
| H02 | No diff. frame_root.c consumes RAM$0779/$0774 and reloads mirror after VRAM;512mask/disable cases. Cold physical mask differs intentionally from boot mirror. |
| H03 | No additional diff. game.c SecondaryGameSetup writes page parity to RAM;scroll.c updates from RAM. Following NMI consumes it. Pipe/vine change-area,NextArea and death/halfway feed shared InitializeArea/setup;no parallel renderer page producer. |
| H04 | No diff. frame_root commits RAM$073f/$0740;graphics/text consume committed visible fields. Added opposite-cache/current-vs-next-phase checks. |
| H05 | No diff. frame_root commits RAM$0722 at the NMI phase. Later RAM writes do not mutate current visible split. Added both split states;entry callers clear RAM for following frame. |
| H06 | No diff. boot.c submit_oam copies all256bytes before producer clear;first cold DMA is intentionally unprimed. Added primed256byte checks and subsequent producer mutation. |
| H07 | Source mismatch repaired. game.c packet header now reloads RAM$0778 before changing increment bit,as WriteBufferToScreen/WritePPUReg1 require.512opposite-cache/control cases fail62 before repair and pass afterward. Added selectors6/7 transfer and distinct source header-clear rules. |
| H08 | No diff. game.c ordered commands commit palette aliases;added two writes to shared$3f00/$3f10 alias,last write wins. Existing VRAM/parser and text palette cases retained. |
| H09 | No diff. boot.c DMA commits text receipt producer;observation.c clear_producer preserves visible receipts. Existing partial overwrite/committed color and snapshot observation cases pass. |
| H10 | No diff. app/game_snapshot.c separately serializes RAM,cache,visible control/mask/scroll/split/OAM and receipt phases. Existing poisoned mutable-field roundtrip and240tick continuation pass. Legacy schema1 missing receipts is declared limitation. |

All production assignments/consumers of the named fields reviewed within shared
game/app,including initialization,scroll,NMI,output snapshots and transition
callers. Other control assignments are boot initialization,source RAM-backed
scroll and WritePPUReg1 publication;none adds a second stale-cache packet path.
The ten dispositions concern named boundary semantics and finite tests,not
instruction-by-instruction physical PPU phases or arbitrary invalid selectors.
Selectors0-18 remain the admitted table domain;malformed/out-of-domain inputs
and broad whole-game dataflow certification remain outside this S.

Both widths pass11rebuilt focused tests including platform purity;final added
selector/palette cases pass again. Seven isolated Windows host groups per width
pass without taking user focus. Controlled7-2 first visible frame145 retains
table1,scroll0,pipe/stairs;each width passes2048indexed boundary comparisons and
1198native frame/state/scaling comparisons,with authored cells equal. These
compositor comparisons are not a new original-ROM whole-game replay certificate.
Original DOS16 compiles/links with retained OLDNAMES warning. Final DOSBox text,
Tab,held-Tab,snapshot return,graphics equality and Escape probe passes;not a
486qualification or naturally played7-2 route. All three local packaged hashes
match their build sources:364817/312971/320107bytes. Builds include preserved
unrelated workspace changes;those are not owned or staged by this S.

Actual product/test2files,+96/-0lines,no ABI or platform change. Local evidence
below ignored build/m3-t22-s2;protected raw probe outputs deleted after checks.
Scope/expected/actual new nodes empty,new0. Historical1992/1992;retained local
nodes1991/1992 and feasible controls4260/4261(raw4342,infeasible81) unchanged.
Ten contracts reviewed,one mismatch repaired,re-audit leaves no scoped diff;
no full-game certificate or increased node/edge numerator. Remaining broad M2
verification stays queued,T19 owner-suspended. Gates and local commit required.
