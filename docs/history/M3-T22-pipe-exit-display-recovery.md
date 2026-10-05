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
