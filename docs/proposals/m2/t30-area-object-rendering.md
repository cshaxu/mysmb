# M2 T30: Area object rendering and metatile chains

T30 follows closed T29 geometry and resumes original source order at the first
uncompleted label after `FlagpoleObject`.  It owns the area-object rendering,
metatile and block-buffer portion of the recovery-plan range.  Each admitted S
receives one bounded chain from the existing T18 custody; future T30 chains
remain unadmitted until their exact predecessor and source route are recorded.

All behavior stays in portable `src/game`.  Windows and DOS provide only
input, timing and completed-frame submission.  The owner-supplied SMB1 NROM
and reviewed disassembly are local-only evidence inputs; no ROM-derived source
or trace becomes tracked product data.

## T30/S1 admission: rope object rendering chain

| Field | Record |
| --- | --- |
| Entry and exit | `EndlessRope -> DrawRope` |
| Exact source-order labels | `EndlessRope` (4018), `BalancePlatRope` (4023), `DrawRope` (4034) |
| Shared owner | `src/game/area.c`, including the neutral area-object state and its existing UnderPart collaborator |
| Receipt | `transfer-098-t18-s4-to-t30-s1-rope-rendering` transfers the three labels from T18 custody |
| Predecessor / successor | T29/S10's completed allocation/final-object boundary precedes this chain; `CoinMetatileData -> RowOfCoins` is the next unadmitted T30 chain |
| ROM-logic track | Audit `$99d0-$99ec`: Endless uses `X=0,Y=15`; balance saves/restores object offset, clears rows 1..15 using `$44`, obtains the lower-nibble length, then uses `X=1`; DrawRope tail-jumps with `$40`. The ordinary area-parser object route exercises the same parser dispatch; source-shaped object records cover the mutually exclusive endless and balance variants without leaf-PC or stack injection. |
| Operational track | Add focused project-owned rope/area smoke coverage, compare the chain-owned parser/metatile state against the original route, build x86/x64, link DOS16, run platform-purity, and refresh all three target artifacts once for implementation P1. |

Baseline: **430 / 1,992**.  Incoming state for every scope label is `open`.
Expected new matches: the same three labels.  Maximum result: **433 / 1,992**.
No renderer, platform adapter, unrelated area object, or `RenderUnderPart`
node receives credit in this S.

## T30 chain order after S1

T30 continues strictly in inventory source order.  The next admissions begin
with `CoinMetatileData -> RowOfCoins`, then retain the adjacent row/column,
cannon/stair, question/brick, hole/underpart, length/attribute and block-buffer
chains as separate receipts where their caller or ROM route changes.  This is
a boundary map only; no later T30 label is admitted or credited by S1.

## S1/P1: ROM rope chain and three-target delivery

`EndlessRope` at `$99d0` loads `X=$00`, `Y=$0f` and tail-enters
`DrawRope`.  `BalancePlatRope` at `$99d7` preserves the parser object offset
across its `$44` blanking pass at `X=$01,Y=$0f`, reloads the second object
byte's low nibble through `GetLrgObjAttrib`, then enters the same `DrawRope`
entry at `$99e9`.  Shared `area.c` now represents those three labels as
`mysmb_area_endless_rope`, `mysmb_area_balance_platform_rope` and
`mysmb_area_draw_rope`; the latter is the one `$40` call into the separately
owned `RenderUnderPart` primitive.

The project-owned `mysmb.area-rope-object-smoke` uses ordinary row-15
area-parser records, never a leaf-PC or stack entry.  It verifies the endless
13-row rope output and terminal height, then verifies the balance rope's
blanking-before-low-nibble-reload order, rope/blank boundary and terminal
height.  The existing special-object smoke remains green.  This is the
operational track; the ROM-logic track is the branch, register and shared-RAM
write audit above.

The manual C90 x64 and x86 smoke builds passed, and their Windows executables
passed `--self-test`.  OpenNT16 linked `mysmb-dos16.exe` as an `MZ` image.
`python test/test_platform_purity.py` passed.  The refreshed artifacts are
`assets/mysmb16.exe` SHA-256
`8BB51F180C55172BA7E324AC1003E8010D3912DAC9659F53F6833A0C9314B241`,
`assets/mysmb32.exe` SHA-256
`5A31D204F5797B78DEA9828C443FB1A47A5080D677917D43D6F82353BD40C937`, and
`assets/mysmb64.exe` SHA-256
`FC89FD9626FFDC11A71F33E191F8A5F71F82CEAAF0309A7EF2C8EA9EC790A1DC`.

All three scope labels are ROM-match complete.  The result is **433 / 1,992**;
there are no uncompleted labels in this receipt.  `CoinMetatileData -> RowOfCoins`
remains the next unadmitted source-order chain.

## S1 closure

The registered scope contains only `EndlessRope`, `BalancePlatRope` and `DrawRope`; all three are recorded as actual matches, and no unfinished node remains in M2 T30 S1 custody. The node checker validates closure at **433 / 1,992** using this proposal as the evidence record. No ownership transfer is needed. The next candidate remains unadmitted until it receives an exact source-order receipt.

## T30/S2 admission: coin metatile selector chain

| Field | Record |
| --- | --- |
| Entry and exit | `CoinMetatileData -> RowOfCoins` |
| Exact source-order labels | `CoinMetatileData` (4039), `RowOfCoins` (4042) |
| Shared owner | `src/game/area.c`, with separately owned `GetRow`/`DrawRow`/`RenderUnderPart` collaborators |
| Receipt | `transfer-099-t18-s4-to-t30-s2-coin-selector` transfers the two labels from T18 custody |
| Predecessor / successor | T30/S1 is closed; `C_ObjectRow -> ColObj` is the next unadmitted source-order chain |
| ROM-logic track | Audit `$99ed-$99f5`: exact `{ $c3,$c2,$c2,$c2 }` table order, `AreaType` in Y, indexed metatile load, and tail jump to `GetRow`. An ordinary row-object parser route exercises the selector without a leaf-PC or stack injection. |
| Operational track | Add a focused project-owned coin-row smoke, compare parser metatile/length state for all four area types, build x86/x64, link DOS16, run platform purity, and refresh all three target artifacts for implementation P1. |

Baseline: **433 / 1,992**. Both incoming labels are `open`; both are expected
to match. Maximum result: **435 / 1,992**. `GetRow`, `DrawRow` and
`RenderUnderPart` are dependencies only and receive no S2 credit.

## S2/P1: coin selector and three-target delivery

The shared C90 owner now gives the ROM table and selector explicit names.
The focused parser smoke covers each `AreaType`: ground selects `$c3`; water,
underground and castle select `$c2`. It also confirms the shared parser's
post-handler length decrement. The ROM-logic evidence is the exact table,
`LDY AreaType`, indexed load and `JMP GetRow` audit; the operational evidence
is the coin-row, rope and special-object smoke suite, x86/x64 `--self-test`,
OpenNT16 MZ link and platform-purity pass.


## S2 closure

The two-label receipt has no unfinished custody. Both actual matches are recorded at **435 / 1,992**, and the closure checker validates this proposal as its evidence record. C_ObjectRow -> ColObj remains unadmitted.

## T30/S3 admission: castle-column object chain

| Field | Record |
| --- | --- |
| Entry and exit | `C_ObjectRow -> ColObj` |
| Exact source-order labels | `C_ObjectRow` (4049), `C_ObjectMetatile` (4052), `CastleBridgeObj` (4055), `AxeObj` (4060), `ChainObj` (4064), `EmptyBlock` (4070), `ColObj` (4074) |
| Shared owner | `src/game/area.c`, with separately owned `ChkLrgObjFixedLength`, `GetLrgObjAttrib`, and `RenderUnderPart` collaborators |
| Receipt | `transfer-100-t18-s4-to-t30-s3-castle-column` transfers the seven labels from T18 custody |
| Predecessor / successor | T30/S2 is closed; `SolidBlockMetatiles -> RowOfSolidBlocks` is the next unadmitted source-order family |
| ROM-logic track | Audit `$99fb-$9a24`: two three-byte tables, CastleBridge's fixed `$0c` length then ChainObj tail, Axe's `$08` VRAM address-control store and fall-through, the decoder-selected `Y` table index, and EmptyBlock's attribute-row result with `$c4` before the common `Y=$00` Column tail. Ordinary row-13 object records exercise selector values 2..4; an ordinary normal-object record exercises the EmptyBlock entry without leaf-PC or stack injection. |
| Operational track | Add a focused project-owned castle-column parser smoke, compare the selected row/metatile, fixed length, VRAM control and common one-column render result; build x86/x64, link DOS16, run platform-purity, and refresh all three target artifacts once for implementation P1. |

Baseline: **435 / 1,992**. Every scope label is `open`; all seven are expected
to match. Maximum result: **442 / 1,992**. No fixed-length helper,
attribute helper, render primitive, platform adapter, or later block-table
node receives S3 credit.

## S3/P1: castle-column implementation, verification still open

The source audit found a concrete mismatch in small-object selector ten:
`EmptyBlock` loads `$c4`, while the previous C wrote `$60` directly. The
shared owner now uses the `ColObj -> RenderUnderPart` path and preserves
`GetLrgObjAttrib`'s row write to `$07`. `ChainObj` reads the decoder's `$00`
selector and the paired row/metatile tables. Axe writes control eight before
that chain; CastleBridge initializes twelve only when its slot is negative.

The focused ordinary-parser test covers axe, chain, thirteen consecutive
bridge columns and termination, empty-block row/height state, and foreground
preservation versus coin-block replacement. It and the existing parser-column
test pass with strict C90 x86 and x64 builds. Both resource-bound Windows
executables pass `--self-test`; that check covers the adapter only, not a
playable game route. OpenNT16 links an MZ with existing compiler warnings and
the OLDNAMES library warning. Its DOS startup still lacks resource binding;
DOS playability is not claimed. Platform-purity and documentation gates are
required before the P commit.

Similar-issue sweep: the small-object selector-ten direct write was the one
incorrect empty-block hit in `area.c`. The row-13 selectors 2..4 now share the
table-indexed chain. The distinct hidden-one-up `$60` output is retained under
its separate ROM owner. Neither platform receives gameplay changes.

All seven labels remain open at **435 / 1,992**. The static source comparison
and native parser tests do not yet supply the admitted original-ROM executed
route comparison. S3 remains active for that evidence and the resulting
node-by-node disposition; no completion credit is taken by P1.

P1 package SHA-256: `mysmb16.exe`
`12AA2A8FDE54429FB3746DFAC259D3A30C16A8AEF370B87E74B51B3E4E18D3BE`;
`mysmb32.exe`
`080718C70B6DD7292854E9D825780C67FCA84900FAF21FEDAD77E89C4365A7CE`;
`mysmb64.exe`
`1F6F0F405B1896B0486154EA80E5F916638F2410D6096AAB2617EB589EC8338F`.
The package checker accepted DOS MZ, x86 PE and x64 PE headers. Platform
purity and documentation governance passed. CMake configuration remained
pending in compiler ABI detection; the recorded tests were direct compiler
builds and executions, not CTest results.

## S3/P2: executed original-ROM chain evidence

The local owner ROM is the existing reviewed SMB1 NROM. It is used only as
an executable reference and immutable area-data input; no redistribution
permission is assumed. Trace containment is `build/m2-t30-s3`: six scenarios,
600 warmup NMIs and two recorded NMIs each, with the recorder's existing
131072-instruction per-frame cap. Each trace is exactly 8,830 bytes. The S3
executor owns cleanup after evidence review; only neutral summaries are
tracked. PC coverage is aggregate addresses/counts, never instruction bytes.

`test/castle_column_fixture.h` supplies identical source-RAM preconditions
to both recorders at an ordinary NMI boundary. The stream pointer selects
`L_CastleArea1` at `$a1af`; real object offsets `$5a/$54/$52/$10` reach axe,
chain, bridge and empty-block records. No PC, stack, ROM byte or return
address is injected. Middle/end bridge cases retain the real slot-two object
at offset `$52`, with remaining lengths five/zero and columns seven/twelve.

Reproduction uses the normal recorder command shapes below; substitute the
existing owner-local ROM and freshly built recorder paths. Run each fixture
suffix `axe`, `chain`, `bridge`, `empty`, `bridge-mid`, `bridge-end`:

```text
reference <ROM> build/m2-t30-s3/rom-<suffix>.msfr 2 0 --warmup=600 --fixture=t30-column-<suffix> --pc-coverage=build/m2-t30-s3/pc-<suffix>.txt 120:8,121:0
native build/m2-t30-s3/native-<suffix>.msfn 2 120 121 --warmup=600 --fixture=t30-column-<suffix>
python test/verify_castle_column_routes.py build/m2-t30-s3
```

The comparison validates trace format/count, original-PC entry hits,
non-vacuous first-frame metatiles and lengths, and both frames' complete
staging column `$06a1-$06ad`, parser/slot/height `$072c-$0735`, and VRAM
control `$0773`. All six routes have zero differences in these fields.
All reach `$9508 ProcessAreaData` through the ordinary GameEngine route.

| Node | Source semantics and executed evidence | Disposition |
| --- | --- | --- |
| `C_ObjectRow` | Owner-ROM bytes at `$99fb` equal the three C rows; axe/chain/bridge select indices zero/one/two and rows six/seven/eight. | ROM-match complete |
| `C_ObjectMetatile` | Owner-ROM bytes at `$99fe` equal the paired C metatiles; all three indices have observed parser results. | ROM-match complete |
| `CastleBridgeObj` | `$9a01` runs in start/middle/end routes; negative length initializes twelve, positive five and zero are preserved before parser decrement to eleven/four/255. | ROM-match complete |
| `AxeObj` | `$9a09` writes control eight before `$9a0e`; output row six/metatile `$c5` and control eight agree. | ROM-match complete |
| `ChainObj` | `$9a0e` reads decoder `$00`, indexes both tables minus two and tails to `$9a20`; all three selectors execute. | ROM-match complete |
| `EmptyBlock` | `$9a19` calls the attribute helper, loads row from `$07`, selects `$c4`, and falls into ColObj; real empty-block route agrees and focused tests verify scratch-row write and overwrite rules. | ROM-match complete |
| `ColObj` | `$9a20` supplies zero height then tails to RenderUnderPart for every route; all thirteen staging rows and resulting height agree. | ROM-match complete |

This proves the scoped chain, not full-frame RAM equivalence. The comparison
also reports residual addresses in `$00-$07`, `$eb`, and the 6502 stack.
NMI-end scratch is overwritten by later, separately owned routines; those
differences are not hidden by an assertion of whole-RAM equality. Stack
storage is not a native C calling convention. Existing unfinished parser
collaborators retain custody and receive no credit here. M2 remains open.

P2 modifies validation only. The P1 three-target builds remain the identical
production source baseline; refresh the three delivery files from those
verified builds and recheck their hashes and adapter self-tests. The native
recorders themselves were rebuilt, and the reference recorder links the
local validation-only MyNES libraries, never the product.

## S3 closure

Expected and actual matches are the same seven labels listed above. The
result is **442 / 1,992**, with no unfinished label retained by S3. The
source audit, six executed ROM routes, focused x86/x64 tests, DOS16 link,
platform-purity and package records are distinct evidence tracks. The next
source-order family begins at `SolidBlockMetatiles`; it is not yet admitted.

## T30/S4 admission: block row and column chain

Entry/exit: `SolidBlockMetatiles -> GetRow2`; shared owner `src/game/area.c`.
Predecessor: closed T30/S3; successor: unadmitted BulletBillCannon family.
Receipt `transfer-101-t18-s4-to-t30-s4-row-column` accepts the ten open labels
from T18 S4 under the owner's source-order continuation approval.

Exact scope and expected matches: `SolidBlockMetatiles`, `BrickMetatiles`,
`RowOfBricks`, `DrawBricks`, `RowOfSolidBlocks`, `GetRow`, `DrawRow`,
`ColumnOfBricks`, `ColumnOfSolidBlocks`, `GetRow2`.
Baseline **442 / 1,992**, expected **10**, maximum **452 / 1,992**.

Source audit: paired AreaType tables, row-only cloud override, metatile
preservation across attribute/length helpers, scratch-row write, horizontal
length initialization/continuation, zero row height versus decoded column
height, and RenderUnderPart tail. ChkLrgObjLength, GetLrgObjAttrib and
RenderUnderPart are dependencies with no credit; the completed coin selector
must retain its call into GetRow. Cannon and staircase behavior is excluded.
ROM-logic evidence must include ordinary parser routes using immutable owner
ROM records, without leaf PC/stack injection. Native tests cover all four
area types, cloud on/off, length progression and column height. Each P
refreshes three artifacts; tests, source proof, ROM replay and platform purity
are separate requirements. No node is complete on admission.

## S4/P1: block row/column migration and ROM proof

The shared C90 owner now has the original named entries and tails. GetRow
retains the metatile across the length helper, writes the attribute row to
`$07`, and enters DrawRow with zero vertical height. GetRow2 instead retains
the decoded low-nibble height. Both scratch-row writes were missing from the
previous combined C branches. RowOfCoins now calls the same GetRow owner;
its existing four-area selector test passes without duplicate helper logic.

| Node | Control/data audit and independent execution evidence |
| --- | --- |
| `SolidBlockMetatiles` | ROM `$9a25` four bytes match C; all AreaType indices are consumed by row and column routes. |
| `BrickMetatiles` | ROM `$9a29` five bytes match C; four AreaType indices plus cloud index four are observed. |
| `RowOfBricks` | `$9a2e` loads AreaType then tests CloudTypeOverride; both branches execute, including `$9a36` index-four override. |
| `DrawBricks` | `$9a38` selects the indexed metatile before GetRow; every brick-row route executes this entry. |
| `RowOfSolidBlocks` | `$9a3e` selects its four-entry table then falls through GetRow; cloud does not alter selection. |
| `GetRow` | `$9a44` preserves metatile across ChkLrgObjLength; first-frame row lengths are four and one after the caller decrement. |
| `DrawRow` | `$9a48` reloads `$07`, supplies height zero, restores metatile and tails into RenderUnderPart; all row routes execute it. |
| `ColumnOfBricks` | `$9a50` selects AreaType without the cloud override, then enters GetRow2; cloud-on and cloud-off results agree. |
| `ColumnOfSolidBlocks` | `$9a59` selects its AreaType entry then falls through GetRow2; all four indices execute. |
| `GetRow2` | `$9a5f` preserves metatile across GetLrgObjAttrib, reloads row and retains height; original routes render three/four vertical cells and do not initialize horizontal lengths. |

Owner-local execution uses the reviewed SMB1 NROM only for validation and
immutable data. No redistributability is assumed. The fixtures select real
records at `$a2f1`, `$a1b1`, `$a35e`, `$a22a` by source RAM at an ordinary
NMI boundary. `test/block_row_column_fixture.h` is shared by both recorders;
it changes no PC, stack, program byte, or return path. IDs 0..31 enumerate
four kinds, four AreaTypes and two cloud states. The recorders retain one
warmup NMI and two samples; every case hits ProcessAreaData and its expected
entry and tails. The comparator rejects missing coverage or missing expected
metatile/length/height, then compares the complete staged column and parser
slots/height in both samples. All 32 cases have zero scoped differences.

```text
reference <ROM> build/m2-t30-s4/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-blocks=<id> --pc-coverage=build/m2-t30-s4/pc-<id>.txt
native build/m2-t30-s4/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-blocks=<id>
python -B test/verify_block_row_column_routes.py build/m2-t30-s4
```

Containment: 64 raw traces of exactly 8,830 bytes each under ignored
`build/m2-t30-s4`, bounded by the existing per-frame 131072-instruction cap.
The S4 executor owns cleanup after evidence review. Aggregate PC coverage
contains addresses/counts only. The comparator reports all other RAM
differences explicitly; it certifies this chain's outputs, not whole-frame
RAM equivalence. Unfinished collaborator nodes retain their prior owners.

The separate native smoke exercises the same 32-way selection matrix,
scratch-row and height state, horizontal continuation through expiration,
and untouched rows. It, the coin-row smoke and parser-column smoke pass
under strict C90 x86 and x64 builds. Both Windows products pass their adapter
self-test. DOS16 links an MZ with existing warnings; the known missing DOS
resource binding still prevents claiming a playable DOS runtime. Platform
purity passes. Similar-issue sweep found the combined row/column branches
and the separate coin GetRow implementation; all now use the shared owners.
Cloud overrides elsewhere and cannon/staircase code remain outside this S.

Three-target delivery SHA-256: `mysmb16.exe`
`101CFDF60A262F13FD0369C76CEFE1F0497EDFD5B699165A2CEE960887A88081`;
`mysmb32.exe`
`BF29E107C44A619FDA444341BD4A68397A8C86A46EE1B1C500825242ED71F551`;
`mysmb64.exe`
`BB190F341BB58ED5FA2C157EFD3ACF0D35A63F7D885FB491BAD1BEA19B8885BB`.

## S4 closure

All ten admitted labels above are ROM-match complete. Expected/actual: ten/
ten; **442 -> 452 / 1,992**. No unfinished label remains in S4 custody.
Tracker, census and ledger must agree and pass closure gates before commit.
The next unadmitted source-order family begins at `BulletBillCannon`.

## T30/S5 admission: cannon geometry and registration chain

Entry/exit: `BulletBillCannon -> StrCOffset`; shared owner `src/game/area.c`.
Exact scope and expected matches: `BulletBillCannon` (4120), `SetupCannon`
(4135), `StrCOffset` (4146), all incoming open. Baseline **452 / 1,992**,
expected **3**, maximum **455 / 1,992**. Transfer-102 accepts these labels
from T18 S4. Closed S4 precedes this chain; StaircaseHeightData is next.
Attribute/position helpers and RenderUnderPart remain separately owned
collaborators, without node credit. Cannon actor firing is out of scope.

ROM-logic audit covers decoded height, top and middle direct stores, base
RenderUnderPart, scratch row, Y/page/X coordinate write order and six-slot
index wrap. Native tests cover short/tall cannon geometry, lower boundary,
all six slots and repeat registration. Controlled ordinary parser ROM routes
use immutable owner-ROM records with source RAM only, never PC/stack edits.
Focused tests, x86/x64 products and self-tests, DOS16 link, platform purity
and three refreshed artifacts provide the separate operational track.

Provenance: reviewed owner-local SMB1 NROM and local SMBDIS are restricted
validation inputs; no third-party translation is imported. Raw traces and
coverage stay in ignored build/m2-t30-s5 with two sample frames per route,
131072 instructions per frame and a 1 MB aggregate raw-trace budget. The S5
executor owns cleanup after review; only neutral evidence is retained here.

S5 dependency amendment: cannon row 11 with height >= 2 enters UnderPart at
row 13. Its existing equality-only bottom check differs from ROM INX/CPX/BCS.
The coordinator admits the minimal >= bottom guard repair as a required
collaborator fix, with boundary regression; no RenderUnderPart node credit.

## S5/P1: cannon geometry registration and ROM proof

| Node | Original control/data semantics and execution evidence |
| --- | --- |
| `BulletBillCannon` | `$9a69`: GetLrgObjAttrib saves row in `$07`; unconditional `$64` top; DEY/BMI either skips or writes `$65` middle; second DEY/BMI either skips or renders `$66` base through UnderPart. Named shared C entry preserves both branches and overlap behavior. Five shapes execute the ordinary parser entry. |
| `SetupCannon` | `$9a85`: read `$046a`; write Y=`($07<<4)+32` at `$0477+slot`, current page at `$046b+slot`, then X=`CurrentColumnPos<<4` at `$0471+slot`; increment slot and reset at six. All six slots and wrap execute with exact coordinate arrays. |
| `StrCOffset` | `$9aa1`: store the selected offset at `$046a` and return. Represented by the final store in the named setup owner, without a forwarding-only wrapper. Every route executes this entry; both increment and reset results match. |

The old C branch always drew three cells and never registered coordinates.
It is replaced by the above shared owner, with no gameplay added to platforms.
The required UnderPart bottom guard now follows the original CPX/BCS stop
for starts at or below the last visible row. It retains its existing owner
and is not credited by this S.

Thirty original-ROM routes use five immutable records and six starting slots.
Three ordinary 7-1 cannon records at `$ab8c`, `$ab84`, `$ab92` cover heights
zero, one and two. Two controlled parser routes select 3-3 records at `$a473`
and `$a48f` with source-RAM AreaStyle=2, covering height five and a row-eleven,
height-fifteen bottom exit. Both recorders share `test/cannon_fixture.h`;
neither modifies program bytes, PC, stack or return flow. One warmup plus two
sample frames run via normal GameEngine/ProcessAreaData. PC coverage confirms
`$9508`, `$9a69`, `$9a85`, `$9aa1` and the selected middle/base entries.

`test/verify_cannon_routes.py` first requires non-vacuous expected geometry,
coordinates and ring index, then compares all nineteen cannon bytes, sixteen
staging bytes and ten parser slot/style/height bytes in both samples. All
thirty routes have zero scoped differences. The row-thirteen route also
matches the original remaining height thirteen. Other RAM differences are
reported separately (scratch, stack and PPU control mirrors); this receipt
does not claim whole-frame equivalence. Those collaborators keep their
existing source-order receivers.

```text
reference <ROM> build/m2-t30-s5/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-cannon=<id> --pc-coverage=build/m2-t30-s5/pc-<id>.txt
native build/m2-t30-s5/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-cannon=<id>
python -B test/verify_cannon_routes.py build/m2-t30-s5
```

Containment: ids 0..29 produce sixty local traces, each 8,830 bytes, total
529,800 bytes, below the admitted 1 MB budget. Per-frame instruction limits
remain in force. Only neutral assertions and the evidence summary are tracked.

Operational evidence is separate: the native smoke passes 1,152 combinations
(12 start rows, 16 heights, six slots), checking complete geometry, scratch
row/height, selected coordinates, untouched slots/timers and length state.
It and row/column/parser-column regressions pass strict C90 x86/x64 builds.
Both Windows adapter self-tests exit zero through an argument-preserving
subprocess with a ten-second timeout. A separate hidden two-second startup
probe observes each real MySMB window and successful bounded WM_NULL response;
only its own processes are terminated. This proves startup/responsiveness,
not full gameplay. The initial PowerShell self-test launcher supplied trailing
argument whitespace and entered the hidden normal window; the independent
probe replaces that invalid harness run. OpenNT16 links an MZ with existing
warnings. The previously recorded missing DOS resource binding still prevents
claiming DOS playability. Platform-purity and package checks pass.

Similar-issue sweep: the one AreaStyle=2 branch was the only cannon geometry
writer; new Cannon slots have one shared area owner. No platform owns those
RAM fields. Cannon firing and whirlpool activation are already recorded debt,
retained for their source-order tasks. All UnderPart callers retain their
usual row<=12 behavior; the added cannon boundary matrix exercises the newly
corrected out-of-range entry without unrelated helper credit.

Artifact SHA-256: `mysmb16.exe`
`CF85426161096A36D9C1BCE7D1284C5215F95A325C447EF731A143A66787DEF8`;
`mysmb32.exe`
`A55138CB5E5015D1FA5BDE1BBF16709589899CC5A22C53A70B5829F1659C815E`;
`mysmb64.exe`
`8A91923F0999FE0BCF1057EC51DB189ED2ACD51C3524E26CC7582045C0C7ED3F`.

## S5 closure

Expected and actual new matches: three. `BulletBillCannon`, `SetupCannon`,
`StrCOffset` are complete in both tracks; **452 -> 455 / 1,992**. No unfinished
scope label remains, and no collaborator gets completion credit. Tracker,
census and ledger must pass their closure gates before commit. The next
unadmitted source-order chain starts at `StaircaseHeightData`.

## T30/S6 admission: staircase rendering chain

Entry/exit: `StaircaseHeightData -> NextStair`; shared owner `src/game/area.c`.
Exact source-order scope and expected matches: `StaircaseHeightData` (4151),
`StaircaseRowData` (4154), `StaircaseObject` (4157), `NextStair` (4162).
All four are incoming open; baseline **455 / 1,992**, expected **4**,
maximum **459 / 1,992**. Transfer-103 accepts these from T18 S4 under the
owner-approved continuation. Closed S5 precedes the chain; Jumpspring is next.
GetLrgObjAttrib/ChkLrgObjLength and RenderUnderPart remain existing
collaborators without credit. No later object or platform logic is admitted.

ROM-logic verification audits both nine-byte tables at `$9aa5/$9aae`, the
length-helper carry and `$07` write, initial control nine, pre-decrement,
indexed row/height lookup and the `$61` RenderUnderPart tail. Controlled
ordinary parser routes cover first and continuing columns and all nine
indices, using source RAM and immutable owner-ROM records without PC/stack
injection. Native tests cover full width, length expiration and preservation
of foreground metatiles. Separate operational proof builds x86/x64 and
DOS16, runs focused regressions and purity checks, then refreshes three EXEs.

The owner-local SMB1 NROM and reviewed SMBDIS remain restricted validation
inputs; no third-party translation is imported. Two samples after a bounded
warmup, 131072 instructions/frame and an aggregate 1 MB raw-trace limit apply.
All raw output stays under ignored build/m2-t30-s6; S6 owns cleanup after
review. No node is complete on admission.

## S6/P1: staircase chain and ROM proof

| Node | Source audit and original-ROM execution evidence |
| --- | --- |
| `StaircaseHeightData` | Nine bytes at `$9aa5` match the shared C table, indexed after DEC. All indices zero through eight are consumed by the parser routes. |
| `StaircaseRowData` | Nine bytes at `$9aae` match the shared C table; the two top columns share row three. Every row/index pair is observed in original execution. |
| `StaircaseObject` | `$9ab7` calls ChkLrgObjLength: row `$07=$0f` is written even on continuation; negative length initializes from the object nibble and carry causes control nine. The first-column route executes `$9abc`; continuation preserves its control before NextStair. |
| `NextStair` | `$9ac1` decrements control before row/height reads, selects `$61` and tails into RenderUnderPart. Both metatile preservation and final AreaObjectHeight are now owned by that existing primitive. All nine normal indices plus controlled index nine/255 match source execution. |

The previous C loop overwrote every staged metatile, omitted `$07` and
AreaObjectHeight, and discarded out-of-range control values. The named shared
owner replaces it with the original call order. Normal table indices use the
verified constants; adjacent-ROM reads for other indices use the bound
immutable source, with a missing-resource check instead of host out-of-bounds
access. This is a data read, not interpreted execution or a second game path.
The two extra source-RAM cases prove those reads at indices nine and 255.

The immutable staircase record at `$a57f` is entered through ordinary
GameEngine/ProcessAreaData. Shared `test/staircase_fixture.h` selects initial
or resident-slot state without changing PC, stack, program bytes or returns.
Twelve routes retain one warmup and two samples, with coverage at `$9508`,
`$9ab7`, `$9ac1`, `$9b7d` and the initialization branch where applicable.
The comparator first requires actual step geometry, control, remaining height
and length. It then compares all thirteen staging bytes, ten parser/control
bytes and the two adjacent-index write locations in both samples. All twelve
routes have zero scoped differences. Other differences remain explicitly
reported in scratch RAM, stack and PPU mirrors `$0778/$0779`; no whole-frame
RAM equivalence or collaborator completion is claimed.

```text
reference <ROM> build/m2-t30-s6/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-stair=<id> --pc-coverage=build/m2-t30-s6/pc-<id>.txt
native build/m2-t30-s6/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-stair=<id>
python -B test/verify_staircase_routes.py build/m2-t30-s6
```

Ids 0..11 produce 24 raw traces of 8,830 bytes, total 211,920 bytes under the
admitted 1 MB limit, retained only in ignored build output for review. The
S6 executor owns cleanup after review. Neutral route assertions alone are
tracked; owner ROM material remains local input with no redistribution claim.

The independent native smoke runs 72 full object scenarios (length zero
through eight, eight foreground/background types), totaling 432 column
checks including post-expiration columns. It checks all staged rows, control,
length, scratch row and remaining height. It and cannon/parser-column smokes
pass strict C90 x86/x64 builds; Windows self-tests exit zero. Hidden bounded
startup probes create both MySMB windows and receive WM_NULL responses, then
terminate only their own processes. OpenNT16 links an MZ with existing
warnings; DOS resource binding/playability remains the already-recorded debt.
Platform purity and package checks pass. No platform file changed.

Similar-issue sweep found one staircase control/table/render path, now moved
to the named shared owner; no duplicate staircase or platform control writer
remains. RenderUnderPart and length/attribute helpers retain their existing
receivers and receive no credit. Jumpspring and later brick/object code are
unchanged and unadmitted.

Artifact SHA-256: `mysmb16.exe`
`70E63FB1E365EA2251E040C5EBE09C7D174E1BED918DDC2B410127DF29C8D2CD`;
`mysmb32.exe`
`65EFBE246DC621C42C6F5A127E709D1FB06C12474366C2B15FDD41234B454988`;
`mysmb64.exe`
`2C0093EB6BC522DA51E192D9FA2C97123F131C11513066325B582B02AB6F1DF4`.

## S6 closure

Expected/actual: four/four. `StaircaseHeightData`, `StaircaseRowData`,
`StaircaseObject` and `NextStair` are complete in both tracks: **455 -> 459 /
1,992**. No unfinished scoped node remains and no collaborator gets credit.
Tracker, census and ledger must pass the closure gates before commit.
Jumpspring is the next unadmitted source-order entry.

## T30/S7 admission: jumpspring creation chain

Exact scope and expected match: `Jumpspring` (4172), incoming open. Baseline
**459 / 1,992**, expected **1**, maximum **460 / 1,992**. Transfer-104 accepts
the node from T18 S4 under source-order continuation. This is the complete
allocation/creation chain at `$9ad3-$9b00`; it splits from the later hidden/
question/brick selection family because the latter has different calls and
ROM routes. Shared owner: area.c. Predecessor S6 is closed; Hidden1UpBlock
is next. Existing FindEmptyEnemySlot and attribute/position helpers are
collaborators without credit; runtime jumpspring animation is excluded.

ROM-logic audit follows attribute decode, five-slot search/fallback slot five,
X/page/Y/fixed-Y/ID/high-Y writes, flag INC including byte wrap, then the two
unconditional metatile stores. Native tests cover all slots, coordinate
boundaries and overwritten metatiles. Original-ROM ordinary parser routes
use immutable jumpspring records with source RAM only, never PC/stack edits.
Build x86/x64 and DOS16, run focused tests and purity, refresh three EXEs.

Reviewed owner-local SMB1 ROM/disassembly are restricted validation inputs;
no third-party implementation is imported. Trace containment is ignored
build/m2-t30-s7, one warmup plus two samples per route, existing 131072
instructions/frame and 1 MB total raw-trace budget. S7 owns cleanup after
review. No completion is credited at admission.

S7 route refinement: initial GameEngine fixtures let already-live jumpspring
actors run before parsing. Their existing offscreen differences change free
slots before the admitted routine. The creation proof therefore uses the
ordinary ScreenRoutines/AreaParserTaskControl build route (mode task one,
screen task eight, one column set), with no actor runtime or instruction
injection. This is the ROM's own pre-game creation path, not a bypass helper.
The known jumpspring offscreen unsigned-underflow discrepancy stays with
its runtime/offscreen receivers and is not repaired or credited by S7.

## S7/P1: jumpspring creation and ROM proof

`Jumpspring` at `$9ad3-$9b00` now has the shared C owner
`mysmb_area_jumpspring`. The existing decoder's small-object selector eleven
calls it. Source order is preserved: GetLrgObjAttrib writes `$07`; the existing
FindEmptyEnemySlot scans five ordinary slots and returns five when full;
X, page, Y and fixed Y are written, then ID `$32`, high Y one, flag INC, and
unconditional metatiles `$67/$68`. Coordinate helpers retain eight-bit shift
and add semantics. No early return is invented for a full pool; flag wrap
remains observable. Allocator/position helpers keep their original receivers.

The original ScreenRoutines/AreaParserTaskControl route selects the immutable
7-1 record at `$abc8`, row nine/column seven. Eight shared source-RAM fixtures
exercise each free ordinary slot and slot-five fallback with flags zero, one
and 255. One column set is built before actor runtime. Reference PC coverage
requires `$8567`, `$86e6`, `$9508`, `$994a`, `$9ad3` and attribute/X/Y helper
entries. No PC, stack, program byte or return flow is replaced.

The comparator requires actual creation outputs (X `$70`, page one, Y and
fixed Y `$b0`, ID `$32`, high Y one, flag one/two/zero), plus persistent block
buffer metatiles at `$0590/$05a0`. The staging column has already advanced by
the NMI checkpoint, so zero staging bytes alone are not accepted as evidence.
All 42 creation-array bytes, both block buffers, staging and parser slot/height
state match in both samples for all eight cases. Residual RAM differences
remain explicitly reported; no whole-frame or runtime-handler equivalence is
claimed. Initial GameEngine probes exposed the existing jumpspring offscreen
underflow and are superseded for creation proof by the legitimate pre-game
build route. The finding is recorded in TODO: JumpspringHandler currently
belongs to T24 S2 custody; OffscreenBoundsCheck belongs to T19 S5. Neither
node is admitted or credited by this creation receipt.

```text
reference <ROM> build/m2-t30-s7/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-spring=<id> --pc-coverage=build/m2-t30-s7/pc-<id>.txt
native build/m2-t30-s7/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-spring=<id>
python -B test/verify_jumpspring_routes.py build/m2-t30-s7
```

Ids zero through seven retain sixteen final traces of 8,830 bytes, total
141,280 bytes, under the 1 MB limit and existing instruction cap. They remain
ignored local research output; S7 owns cleanup after review. Only neutral
harnesses and summaries are tracked, without imported ROM/program bytes.

The independent native matrix passes 1,536 combinations of twelve rows,
sixteen columns and eight slot states. It checks all seven creation arrays
including untouched slots, row scratch, non-length status, and overwrites of
both metatiles even over palette-three foreground. Strict C90 x86/x64 builds
pass this, staircase and parser-column tests. Both Windows self-tests exit
zero; separate hidden bounded probes confirm window creation and responsive
message dispatch. OpenNT16 links an MZ with existing warnings; playable DOS
remains unproven due to the recorded resource-binding debt. Purity and package
checks pass; no platform gameplay code changed.

Similar-issue sweep confirms selector eleven previously had no production
creation branch. The new area owner is the only creation writer; runtime
animation/fixed-Y reads remain in their existing handler and no platform
writes those fields. Other actor allocation callers and later brick selectors
remain outside scope.

Artifact SHA-256: `mysmb16.exe`
`E993815556E081F8F86F6A2A619197F0A08CC7AAA7A4A8CDA774B493949BF7AC`;
`mysmb32.exe`
`7E026FCBE7798E727EC700753676849DFB70BCD42F4F0B87FEAFBF4593B8B122`;
`mysmb64.exe`
`0D5B4B041D67715F8A1B646CB852C37EA3091656092969F56A48E0C38E52ACC9`.

## S7 closure

Expected/actual: one/one. `Jumpspring` creation is complete in both tracks:
**459 -> 460 / 1,992**. No scoped node remains unfinished; runtime animation
and offscreen debt retain their existing receivers with no credit. Tracker,
census and ledger must pass closure gates. Hidden1UpBlock begins the next
unadmitted source-order family.

## T30/S8 admission: hidden/question/item block selection chain

Exact scope and expected matches, all incoming open: `Hidden1UpBlock` (4197),
`QuestionBlock` (4204), `BrickWithCoins` (4208), `BrickWithItem` (4212),
`BWithL` (4220), `DrawQBlk` (4223), `GetAreaObjectID` (4228), `ExitDecBlock`
(4233). Baseline **460 / 1,992**, expected **8**, maximum **468 / 1,992**.
Transfer-105 accepts the chain from T18 S4. Closed S7 precedes it; HoleMetatiles
is next. Shared owner: area.c. Table storage moves to area/block_metatile.c
with declaration in area.h; objects.c classifier and legacy area selectors
only consume the same data, without changing their control flow. The table,
length/attribute, DrawRow and UnderPart collaborators retain their receivers;
none receive node credit. Runtime collision, block bumps and powerups are
excluded.

ROM audit covers hidden flag gate/clear, coin timer flag reset, `$00` ID,
`$07` preservation, AreaType adder zero/five, table lookup, row decode and
DrawRow/UnderPart tail. Original-ROM parser fixtures cover selectors zero
through eight, four area types and both hidden flag states. No PC/stack or
program-byte changes are permitted. Native tests additionally cover overlap
preservation and untouched state. Separate x86/x64, DOS16, purity and package
checks supply operational evidence and three fresh artifacts.

Owner-local NROM and reviewed SMBDIS are restricted research inputs, with no
third-party code import. Traces stay under ignored build/m2-t30-s8: one warmup
plus two samples per route, 131072 instructions/frame and 2 MB aggregate raw
trace cap. S8 owns cleanup after review. No completion credit at admission.

## S8/P1: item-block selection and ROM proof

| Node | Original control/data semantics and consumer evidence |
| --- | --- |
| `Hidden1UpBlock` | `$9b01` tests Hidden1UpFlag, exits without row/height writes when zero, otherwise clears it and tails into BrickWithItem. Both flag branches execute for all four area types. |
| `QuestionBlock` | `$9b0e` gets the decoder ID and enters DrawQBlk without the area-type adder. Selectors zero, one and two all execute. |
| `BrickWithCoins` | `$9b14` clears `$06bc` then falls through to BrickWithItem. A nonzero seeded flag becomes zero only for selector seven. |
| `BrickWithItem` | `$9b19` reads decoder `$00`, saves ID in `$07`, tests AreaType and supplies adder zero for ground or five otherwise. Hidden selector three retains its original unusual alternate index eight. |
| `BWithL` | `$9b28` adds the saved ID to the selected adder before the metatile lookup; every brick/hidden-enabled area-type route executes this tail. |
| `DrawQBlk` | `$9b2c` reads BrickQBlockMetatiles, preserves the tile across GetLrgObjAttrib, and tails to DrawRow, so UnderPart owns overlap/height behavior. All enabled selectors execute both tails. |
| `GetAreaObjectID` | `$9b36` returns `$00`; SEC/SBC zero preserves the byte. Its callers consume the ID, not the carry. Original execution covers every selector. |
| `ExitDecBlock` | `$9b3c` is the ID-return and hidden-disabled return; both uses are represented by the corresponding C return without an invented forwarding wrapper. |

The old direct-store branches omitted scratch/height writes and overlap
preservation, and multi-coin selection did not reset its timer flag. Named
shared area entries now preserve the original sequence. The fourteen-byte
table has one definition in area/block_metatile.c; DrawQBlk, the existing
collision classifier and legacy area selectors consume that definition.
Both the original LDA operand at `$9b2c` and all fourteen bytes at `$bde8`
were verified against the owner ROM. This is collaborator data extraction
without table-node credit or collision control-flow changes. Legacy area
scan entry points have no external production caller in the current tree;
their table selection remains behavior-preserving, and they are not certified
as original-ROM routes by this S.

Seventy-two original-ROM routes select nine immutable records at `$a29f`,
`$a31c`, `$a1ed`, `$a559`, `$a4e4`, `$a5ba`, `$a5de`, `$a51e`, `$ab1f`.
`test/item_block_fixture.h` varies selector, four AreaTypes and hidden flag
clear/set using source RAM before an ordinary GameEngine/ProcessAreaData
entry. It never alters PC, stack, program bytes or returns. One warmup and
two samples retain target-entry coverage, including each shared tail and
hidden-disabled exit. The comparator requires expected non-vacuous tile,
hidden flag and coin-timer outputs before comparing the full staged column,
parser slots/height and both flags in both samples. All 72 routes have zero
scoped differences. Residual scratch/stack, VRAM-command and PPU-mirror RAM
differences are separately reported; whole-frame equivalence and unrelated
collaborator completion remain unclaimed.

```text
reference <ROM> build/m2-t30-s8/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-items=<id> --pc-coverage=build/m2-t30-s8/pc-<id>.txt
native build/m2-t30-s8/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-items=<id>
python -B test/verify_item_block_routes.py build/m2-t30-s8
```

Ids zero through 71 retain 144 local traces, each 8,830 bytes, total 1,271,520
bytes below the 2 MB limit; instruction limits remain enabled. Raw output is
ignored and S8 owns cleanup after review. Tracked evidence contains neutral
harnesses, addresses and conclusions; no owner-ROM trace is a product fixture.

Independent native coverage passes 1,152 selector/type/flag/background/edge
combinations, checking all rows, hidden flag, timer flag, scratch row, height
and untouched horizontal length. Strict C90 x86/x64 builds also pass jumpspring
and parser-column regression. Shared-table consumers pass collision regression
and block-graphics smoke tests on both widths. An existing same-line final
return in the collision test was split to satisfy misleading-indentation
warnings; no assertion or test logic changed. Windows self-tests exit zero,
and separate hidden probes create responsive windows. DOS16 links an MZ with
existing warnings; the known resource-binding debt still prevents claiming
DOS playability. Platform purity and package checks pass.

Similar-issue sweep removed both parser copies and the collision classifier's
private table, retaining one shared definition. Legacy ground/question table
copies now use it too. Other coin timer writers belong to runtime block logic
and were left unchanged; no platform owns selection, table data or flags.

Artifact SHA-256: `mysmb16.exe`
`A85BE0A0D24BF6260EA832388A66D29AC54F93E054ABF7838FD3B7DC2B734A45`;
`mysmb32.exe`
`13D269DBFC1D13F521725C96257DEC4AE707683BB9947B87DAF098887D302365`;
`mysmb64.exe`
`C6E8D99133B6CFA9E50DB2629F248C0056763A53B9CD0DB6BF8E341BF0085E0D`.

## S8 closure

Expected/actual: eight/eight. All eight admission labels above are complete
in both tracks: **460 -> 468 / 1,992**. No scoped label remains unfinished;
table/render/attribute and runtime collaborators retain their receivers
without credit. Tracker, census and ledger must pass closure gates.
HoleMetatiles begins the next unadmitted source-order chain.

## T30/S9 admission: hole/whirlpool and UnderPart chain

Exact scope and expected matches, all incoming open: `HoleMetatiles` (4237),
`Hole_Empty` (4240), `StrWOffset` (4265), `NoWhirlP` (4266),
`RenderUnderPart` (4273), `DrawThisRow` (4289), `WaitOneRow` (4290),
`ExitUPartR` (4296). Baseline **468 / 1,992**, expected **8**, maximum
**476 / 1,992**. Transfer-106 accepts the labels from T18 S4. Entry/exit:
HoleMetatiles through ExitUPartR, shared owner area.c. Closed S8 precedes;
ChkLrgObjLength begins the next unadmitted helper chain. Length/attribute/X
helpers remain collaborators without credit; whirlpool runtime is excluded.

Audit the initial-length carry, water gate, shared cannon/whirlpool slot,
X-minus-sixteen and page borrow, wrapped (length+2)*16, five-entry index wrap,
four-entry hole table and UnderPart tail. UnderPart must retain original
height stores, protected metatiles, cracked-rock/stem exception, byte X
increment, bottom compare, byte Y decrement and BPL exit. Native tests cover
all initial/continuing gates, slots, page edges and common render callers.
Original-ROM ordinary parser routes cover hole registration and rendering;
existing source-reachable consumers may supply additional UnderPart branch
coverage without crediting their nodes again. No PC/stack edits are allowed.

Separate x86/x64 tests/builds and DOS16 link, platform purity and three-EXE
refresh are required. Owner-local NROM and reviewed SMBDIS are restricted
research inputs; no third-party implementation is imported. Raw traces stay
under ignored build/m2-t30-s9, with one warmup and two samples per route,
131072 instructions/frame and 2 MB aggregate budget. S9 owns cleanup after
review. No completion at admission.

## S9/P1: hole registration and UnderPart ROM proof

| Node | Original control/data semantics and execution evidence |
| --- | --- |
| `HoleMetatiles` | Four bytes at `$9b3d` match `$87,0,0,0`; all AreaType indices are consumed. |
| `Hole_Empty` | `$9b41` decodes row/length; only a newly initialized water hole registers a whirlpool. Left extent subtracts sixteen with borrow into page, size is `(length+2)<<4` modulo 256. Initial/continued, water/nonwater and both borrow branches execute. |
| `StrWOffset` | `$9b70` stores the incremented index, reset at five. Routes cover each ordinary slot plus shared cannon slot five, which also wraps to zero. |
| `NoWhirlP` | `$9b73` loads AreaType metatile and enters UnderPart with X eight/Y fifteen regardless of registration gates. All 96 hole routes exercise this tail. |
| `RenderUnderPart` | `$9b7d` stores height before inspecting each existing metatile; preserves ledge centers and palette-three objects except `$c0`, and preserves `$54` only for incoming `$50`. Native overlap matrix and ordinary mushroom-center ROM route cover these rules. |
| `DrawThisRow` | `$9b9d` writes only after those guards. Expected hole/stem geometry is required before trace equality is accepted. |
| `WaitOneRow` | `$9ba0` increments an eight-bit row, tests bottom, reloads/decrements height and repeats only while its sign bit is clear. Normal fill, row-wrap native cases and the original-ROM height `$90` route cover the distinct exits. |
| `ExitUPartR` | `$9bab` returns on bottom or negative decremented height, retaining the last stored AreaObjectHeight. Both exits have non-vacuous output/height evidence. |

The old hole branch never registered whirlpools and omitted the decoded row
write. The shared owner now follows the complete registration sequence,
using the existing aliased cannon/whirlpool RAM. The UnderPart loop formerly
used a private height decrement and equality-style termination. It now uses
byte row increment, original bottom comparison, shared height reload and
signed decrement semantics. This also handles row 255 wrap and a high-bit
height without turning it into an invented long positive fill.

Ninety-six original-ROM parser routes combine four AreaTypes, six shared
slots, initial/continued length and records `$a30c`/`$ae18` (column zero/twelve).
The comparator requires exact whirlpool page/left/size/index, drawing and
remaining height, then compares all nineteen shared registration bytes,
thirteen staged tiles and ten parser/control bytes in two samples. Two
additional ordinary consumer routes use staircase record `$a57f`, controlled
index 21 (row seven/height `$90`), and mushroom record `$a473` at its center.
The former must draw only one row; the latter must preserve the cracked-rock
bottom while drawing the stem. All 98 cases have zero scoped differences.
Reference coverage requires the original parser and every relevant entry/tail;
there is no PC, stack, code-byte or return injection.

```text
reference <ROM> build/m2-t30-s9/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-hole=<id> --pc-coverage=build/m2-t30-s9/pc-<id>.txt
native build/m2-t30-s9/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-hole=<id>
python -B test/verify_hole_underpart_routes.py build/m2-t30-s9
```

Ids zero through 97 retain 196 local traces of 8,830 bytes, total 1,730,680
bytes below the 2 MB budget, with the existing instruction cap. Raw output
stays ignored; S9 owns cleanup after review. Recorder-only fixture identifiers
were widened from a byte to unsigned int because this family crosses 255;
existing IDs and production game state widths are unchanged. Other RAM
differences remain explicitly reported, including scratch/stack, VRAM/PPU
mirrors, actor state and cannon/whirlpool runtime fields. ProcessCannons and
ProcessWhirlpools are already recorded missing-path debt; neither is admitted
or credited by this creation/render receipt. No whole-frame claim is made.

Independent native coverage passes 9,216 hole combinations, 21 byte-height/
row-boundary cases and six mushroom-overlap cases. It checks untouched slots,
flag storage, page wrap, size wrap, length state, every staged row and height.
Strict C90 x86/x64 builds pass these plus item-block, cannon, staircase,
row/column, parser-column, special-object and rope regression. Both Windows
self-tests exit zero; separate hidden bounded probes confirm responsive game
windows. DOS16 links an MZ with existing warnings; resource binding and DOS
playability remain deferred debt. Purity and packaging pass; no platform
source changed.

Similar-issue sweep confirms the one hole branch now owns registration and
one common UnderPart owner serves all callers. Cannon/whirlpool aliasing is
explicit, with respective six/five-slot wrap rules. Formerly certified
consumer chains were regression-tested without awarding their nodes again.
Generic length/attribute/position helpers remain the next source-order work.

Artifact SHA-256: `mysmb16.exe`
`4184CE8304E441AF2314F4A32AD6B3A375DC89200D5863A7AE9ACEACF6A0FA1E`;
`mysmb32.exe`
`4D54135598D102C1332C331DDA67C9ABC5BFC427F94BFDA8FC8EE2043EA47218`;
`mysmb64.exe`
`0594604B8506EC8C791DE18D573CAC47D5F6A720A606758A3D0EE7D16AEA3EC8`.

## S9 closure

Expected/actual: eight/eight. All eight admission labels are complete in both
tracks: **468 -> 476 / 1,992**. No scoped label remains unfinished. Runtime
and generic helper collaborators retain their receivers without credit.
Tracker, census and ledger must pass closure gates. ChkLrgObjLength begins
the next unadmitted source-order helper chain.

## T30/S10 admission: common object attribute and coordinate chain

Exact source-order scope and expected matches, all incoming open:
`ChkLrgObjLength` (4300), `ChkLrgObjFixedLength` (4303), `LenSet` (4310),
`GetLrgObjAttrib` (4313), `GetAreaObjXPosition` (4326),
`GetAreaObjYPosition` (4336). Baseline **476 / 1,992**, expected **6**,
maximum **482 / 1,992**. Transfer-107 receives all six from T18 S4.
The shared owner is area.c. S9's UnderPart chain precedes; BlockBufferAddr
starts the next unadmitted source-order chain.

ROM-logic track: audit $9bac-$9bdc and every original area-object caller.
Attribute reads must use AreaObjOffsetBuffer and the current AreaData pointer,
with eight-bit INY wrap; the first low nibble writes $07 and the second is
returned. Fixed-length checking preserves nonnegative slots and returns the
source carry meaning (new initialization); dynamic checking decodes first.
X and Y arithmetic wraps at eight bits, with Y adding 32 after the shift.
Integrate original call sites without moving unrelated actor state machines
into the parser. Focused parser and original-ROM consumer routes cover both
length branches, row/length distinction, fixed lengths and coordinate writes.
No leaf PC/stack or ROM-code injection. Any concrete caller discrepancy is
recorded against its node rather than concealed by a helper compatibility path.

Operational track: focused helper/parser tests, prior consumer regressions,
strict C90 x86/x64 builds, DOS16 link, platform purity, startup probes and
three refreshed EXEs per implementation P. The owner NROM and reviewed
SMBDIS remain local research inputs, not redistributable material; no external
implementation is imported. Raw traces remain under ignored build/m2-t30-s10,
with 2 MB aggregate budget, 131072 instructions/frame, one warmup and two
samples for controlled cases. S10 owns cleanup after review. Six labels remain
unfinished until both tracks pass; no completion credit on admission.

## S10/P1: common helper ROM proof

The six helpers now have one shared C90 owner in area.c; signatures no longer
pass stale predecoded row/length values through the object renderer wrappers.
Public area declarations expose the same neutral primitives to deterministic
native tests, with no platform branching or CPU interpreter.

| Node | Original behavior and evidence |
| --- | --- |
| `ChkLrgObjLength` | `$9bac` calls attribute decode before fixed-length checking and preserves decoded Y. All three slots/all byte states and nibble lengths pass native tests; ROM hole routes distinguish one initialization from zero initializations. |
| `ChkLrgObjFixedLength` | `$9baf` clears carry, preserves a nonnegative slot, otherwise stores Y and sets carry. Three slots x 256 old states x 256 incoming bytes pass; ROM fixed pipe routes cover new, continued and final columns. |
| `LenSet` | `$9bba` returns the same carry/result without additional writes. Original return coverage is required and persistent slot/consumer state matches in both samples. |
| `GetLrgObjAttrib` | `$9bbb-$9bca` reads the saved object offset, stores first low nibble in $07, increments an eight-bit index and returns the second low nibble. Native matrix covers all 256 offsets against a nonaligned base, including wrap; ROM output distinguishes row from length through hole, cannon, spring and pipe consumers. |
| `GetAreaObjXPosition` | `$9bcb-$9bd2` shifts CurrentColumnPos four times with byte truncation. Every input byte passes; original cannon, spring, hole borrow and pipe-center coordinates match. |
| `GetAreaObjYPosition` | `$9bd3-$9bdc` shifts $07 four times, clears carry and adds 32. Every input byte passes; varied cannon rows, spring row nine and pipe row eight match. |

The source-order caller sweep covers tree/mushroom/pulley ledges; castle,
water/intro/exit/vertical pipes; bridges, water holes and question rows;
flag balls and flagpole; balance rope; castle bridge and empty block;
brick/solid/coin rows and columns; cannon, staircase, spring, question/item
blocks and empty holes. Each now uses its actual source helper sequence.
TreeLedge retains its original direct length store rather than inventing a
ChkLrgObjLength call. Fixed-length consumers retain their fixed Y constants.
Hidden-disabled blocks still return before attribute decoding.

The sweep found and repaired a concrete GetAreaObjYPosition substitution in
VerticalPipe: the old caller added eight, making the piranha start 24 pixels
too high before InitPiranhaPlant subtracted another 24 for its upper limit.
The caller now receives row*16+32 from the shared helper. Original ROM pipe
routes require creation X=$68, Y/down=$a0 and up=$88, including continued
length one. Final-column and full-pool routes require no creation. No actor
runtime implementation changed. GetPipeHeight now passes the attribute
helper's height through its original $06 scratch handoff.

Twenty source-RAM-only ScreenRoutines/AreaParserTaskControl routes exercise
immutable hole, cannon, spring and pipe records. They require each relevant
helper entry/return PC, exact initial-length branch counts, non-vacuous
registration/coordinate/metatile witnesses and equality of all 1,782 RAM
bytes outside scratch $00-$07, stack $0100-$01ff and PPU mirrors $0778-$0779.
Both samples pass for all twenty routes. The excluded bytes are reported
individually: the original later name-table renderer overwrites helper scratch
before the frame boundary, so final $07 is not the helper's return value.
Direct primitive tests and source instruction audit separately check that
write. This is not whole-frame, rendering, or actor-runtime certification.
No program bytes, entry PC, stack or return address were injected.

```text
reference <ROM> build/m2-t30-s10/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-helper=<id> --pc-coverage=build/m2-t30-s10/pc-<id>.txt
native build/m2-t30-s10/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-helper=<id>
python -B test/verify_area_helper_routes.py build/m2-t30-s10
```

Cases zero through nineteen retain forty 8,830-byte traces (353,200 bytes)
under the admitted ignored directory and 2 MB budget; each recorder process
has a twenty-second deadline and the reference retains its instruction cap.
The reference helper IDs are observation fixtures only. Recorder state is
fully zero-initialized to satisfy optimized compiler checks.

Operational verification: 221,440 primitive matrix cases per width and all
nineteen area smoke programs pass on x86 and x64 (38 program runs). Product
self-tests and hidden two-second window/message probes pass. OpenNT16 links
MZ with the existing OLDNAMES warning; no DOS runtime claim is made. Platform
purity passes and no platform file changed. Two old test families asserted
intermediate dispatch scratch after the complete handler returned; these now
expect the original attribute overwrite, not the obsolete dispatch addend.
The pipe smoke checks both down/up coordinates instead of accepting the old
incorrect starting position.

## S10 adjacent-node revalidation findings

Source audit also contradicts two prior completion claims outside this receipt:

- `DecodeAreaData`: the current parser preloads its second byte at effective
  address+1, whereas the source INY wraps the saved index at $ff. The new
  attribute helper is correct, but the earlier dispatch read is independently
  wrong at that boundary. Its prior completion is revoked pending a parser
  boundary route and repair; custody remains with its existing receiving S.
- `DrawPipe`: the existing zero-height fallback fills to the bottom and its
  row-12 early return suppresses the source call. ROM always increments X,
  loads $06, decrements Y as a byte and tail-enters UnderPart, including zero
  height. Its prior completion is revoked pending explicit edge-route proof
  and repair; custody remains with its existing receiving S.

These are named source contradictions, not failures of the six new helper
implementations. Their inventory/census entries become audited mismatch;
TODO and queue retain the exact repair requirement. No hidden scope expansion,
new node credit or source-order task number is assigned to those repairs.
The historical closure evidence remains immutable and qualified by this audit.

Artifact SHA-256: `mysmb16.exe` `879D080EAFF2861D695FCBA1A385AE0BD1EE7B9FDD4A4015488CF33C23589635`.

Artifact SHA-256: `mysmb32.exe` `0B3234BD889F6946C9DB6529BA79D28B0618AC23485665A9A7011CA0C458CF35`.

Artifact SHA-256: `mysmb64.exe` `24738AF386629159C1E32FFAC3B7604F2D47798D1738C0D72B473B76CAA29BA6`.

## S10 closure

Expected/actual newly completed: six/six, all admission labels. No scoped
label remains unfinished and no transfer out of S10 is needed. Independently,
two older matches are revoked by the adjacent-node audit above. Thus the
actual total is **476 + 6 - 2 = 480 / 1,992**, below the 482 upper forecast;
mapped/audited incomplete rises to 105 and open becomes 1,407. This correction
is required for honest conformance accounting. The helper chain is closed;
M2 remains open. Prior-node repair candidates precede the next unadmitted
BlockBufferAddr chain, with exact receipts required at admission.

## T30/S11 admission: parser byte-index corrective chain

Scope and expected new match: `DecodeAreaData` (3393), incoming audited
mismatch. Baseline **480 / 1,992**, expected **1**, maximum **481 / 1,992**.
Transfer-108 receives its maintenance responsibility from T29 S7. This is the
first queued correction from S10's caller audit, not a new source-slice T.
The bounded chain is current/saved area offset -> first-byte terminal test ->
wrapped second-byte read -> existing object dispatch. Shared owner: area.c.
The other 31 previously certified parser/control labels are regression
collaborators without new credit. DrawPipe correction follows, then the
unadmitted BlockBufferAddr chain resumes the normal source sequence.

ROM-logic verification audits ProcessAreaData's preliminary INY and
DecodeAreaData's saved-offset/terminal/row paths against the local reviewed
SMBDIS and owner NROM. The eight-bit index must wrap before addition to
AreaData; the pointer must not advance a page when Y wraps. A terminal first
byte requires no second-byte resource access. Original ScreenRoutines parser
routes use controlled RAM pointers and offsets over immutable ROM bytes,
covering fresh and resident slots, ordinary reads and offset $ff. No ROM,
PC, stack or return-address edits. Full parser and consumer state is compared;
retained renderer scratch/PPU discrepancies are reported separately.

Operational verification adds a project-owned parser-boundary smoke, runs
prior parser/consumer tests, x86/x64 and DOS16 builds, startup/purity checks and
three target artifacts. Research inputs remain owner-local, unredistributable
and ignored. Raw traces stay under build/m2-t30-s11, at most 2 MB total,
131072 instructions/frame, one warmup/two samples per case and twenty seconds
per process. S11 owns cleanup after review. No match is claimed at admission.

## S11/P1: parser index-wrap ROM proof

`DecodeAreaData` at $9595 selects current versus saved object offset from the
slot length sign, then follows the first-byte terminal and row/selector paths.
The shared parser now retains AreaData base separately: both the preliminary
ProcessAreaData second-byte read and decoded resident-object read use
`base + (u8)(offset + 1)`, preserving INY wrap before pointer addition. The
first-byte bounds check stands alone; $fd returns through the existing
ChkLength/ProcADLoop route without requiring a second resource byte. There
is no new page increment, object shortcut, CPU interpreter or platform branch.

The remaining decoder controls retain the previously reviewed T29 S7 source
mapping: page-select, page-control and backload handling; terminal/resident
slots; row 12/13/14/15 selectors; loop commands; warp-pipe classification;
saved offsets, column gating, dispatch and post-handler length decrement.
Their focused regressions pass without new node credit. The correction fixes
the read boundary feeding these existing controls rather than changing their
rules. The ordinary area-header reader uses fixed offsets zero and one, so its
address+1 is correct and is intentionally unchanged. GetLrgObjAttrib already
has the correct byte-index read from S10.

Twenty-four ordinary ScreenRoutines parser routes combine six immutable ROM
pointer bases with fresh object / resident lengths 0, 1 and 127 (the latter
three occupy all three saved slots). Bases are $a20e, $a4cc, $a68c, $a9cc,
$aebe and $a6f1. Offset $ff supplies the first byte, offset zero supplies the
second, and offset one is an original terminal marker. The adjacent wrong-page
byte deliberately decodes differently. The high-bit page-select variants and
low-bit variants both finish at page one. No ROM bytes, CPU PC, stack or return
address are written by the fixture.

Every route requires ProcessAreaData, DecodeAreaData, Chk1stB, ChkSRows,
RunAObj, ChkLength and EndAParse coverage, with six decoder calls for two
columns and three slots. The comparator requires the expected coin/brick
metatile, wrapped stream cursor one, page/select state, saved $ff offset and
remaining length, then compares 1,782 persistent RAM bytes in both samples.
All 24 routes pass. Scratch $00-$07, stack and the two PPU mirrors remain
individually reported residuals from later frame work; no whole-frame claim.

As a negative control, the committed pre-fix area.c from `318afa8` was built
with the same recorder/fixtures and unchanged remaining game objects. It
fails the new native boundary smoke and all 24 ROM routes have persistent
mismatches. This proves the boundary cases detect the repaired read error.

```text
reference <ROM> build/m2-t30-s11/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-parser-boundary=<id> --pc-coverage=build/m2-t30-s11/pc-<id>.txt
native build/m2-t30-s11/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-parser-boundary=<id>
python -B test/verify_parser_boundary_routes.py build/m2-t30-s11
```

The 48 positive and 24 negative traces total 635,760 bytes under the 2 MB
budget and remain ignored. The twenty-second per-process deadline and
reference instruction cap held. S11 retains them for the enclosing T review.
Native coverage passes 9,984 combinations of all 256 offsets, three rows,
fresh/resident states and all three saved slots, plus terminal-at-resource-end
and missing-second-byte cases. All twenty area smokes pass on x86 and x64
(40 program runs); product self-tests and hidden responsive-window probes
pass. OpenNT16 MZ link and platform purity pass. DOS resource binding/runtime
remain previously recorded debt; no DOS playability is claimed.

Similar-issue sweep found one inactive legacy reader, mysmb_area_next_object,
with the same flat-address approximation. Its callers are only the legacy
lookahead/emitter cluster and tests; no active frame/root calls that cluster.
It receives no node credit and is recorded for legacy-path removal or
consolidation before full M2 certification. This does not create another
runtime implementation of the corrected parser.

Artifact SHA-256: `mysmb16.exe` `301E725BF377C9FD0DF9450F7B4433B79B9DC726E5CFAB5403552FE0D87AB4BE`.

Artifact SHA-256: `mysmb32.exe` `A39D8CB25A5CBA939D8EA3CED02291FE6B49873C8C574C9B7941FEE694ED03F1`.

Artifact SHA-256: `mysmb64.exe` `6FDEB9849016A99F2BBE6D84B0A9DCEDF1713D6C4AE56A569CD29B55048A6265`.

## S11 closure

Expected/actual restored match: one/one, `DecodeAreaData`. The previous
revocation is resolved by the original read audit, discriminating ROM routes
and independent native/build verification. **480 -> 481 / 1,992**; mapped
incomplete is 104, open remains 1,407. No scoped label is unfinished. DrawPipe
remains explicitly audited mismatch and is the next queued correction; the
block-buffer chain remains unadmitted. M2 is not complete.

## T30/S12 admission: DrawPipe corrective tail

Exact scope/expected match: `DrawPipe` (3900), incoming audited mismatch.
Baseline **481 / 1,992**, expected **1**, maximum **482 / 1,992**. Transfer-109
accepts maintenance responsibility from T29 S9. This is the remaining queued
correction from S10, after closed S11 and before BlockBufferAddr. Shared owner:
area.c; entry/exit $9925-$9938, VerticalPipe/GetPipeHeight inputs through the
already verified UnderPart tail. Collaborator nodes receive no new credit.

Source audit preserves saved table selector, $07 row, unconditional top store,
byte row increment, second table lookup, $06 height load, byte DEY and tail
call. Delete the invented zero-height bottom fill and row-12 early return.
Normal parser rows zero through eleven can reach this family; row twelve is
selected by the special-object table and is not claimed as an executable
DrawPipe path. Original immutable-ROM pipe records with source-RAM resident
slots cover heights zero through seven, usage bit and left/right columns.
No PC, stack, return or code-byte injection is permitted.

Native tests cover the full reachable row/height/usage/side matrix and prior
pipe creation/area consumers. Build and test x86/x64, link DOS16, check platform
purity/startup, and refresh all three EXEs. Owner NROM and reviewed SMBDIS are
local-only research inputs; raw traces remain ignored under build/m2-t30-s12,
with 2 MB total, twenty seconds/process, one warmup/two samples and the existing
131072-instruction frame cap. S12 owns cleanup after the enclosing T review.
No completion is credited at admission.

## S12/P1: DrawPipe tail ROM proof

`DrawPipe` ($9925-$9938) now has a named shared C owner. Its saved-selector
parameter represents PLA/TAY, then $07 supplies X, the original table writes
the top unconditionally, X increments as a byte, the second table lookup
selects the shaft, and $06 is decremented as a byte before tail-entering
RenderUnderPart. Height zero therefore passes $ff and draws one shaft row
before UnderPart's signed-decrement exit. The previous C bottom-fill policy
is removed. No actor state, collision policy or platform implementation changed.

The former row-12 early return is also removed because it has no original
instruction. It is unreachable through ordinary vertical-pipe dispatch:
record rows 12..15 select special families before the large-object pipe path;
the unchanged immutable record is then reread by GetLrgObjAttrib. The highest
reachable pipe row is eleven, whose shaft starts at row twelve and exits
through UnderPart's original bottom check. No fake PC/stack route is claimed
for an impossible row-12 pipe dispatch.

VerticalPipeData at $98dd retains its eight exact bytes and now has one named
file-local table shared by DrawPipe and the intro-pipe consumer. This is a
binding/consolidation change, not an extra data-node credit. The similar-issue
sweep finds no remaining pipe zero-height fill or invented row early return.
Other row-12 branches are legitimate special-object dispatch and remain intact.

Thirty-two original-ROM routes use sixteen immutable data-region byte pairs,
interpreted by the ordinary parser through controlled AreaData pointers and
resident object slots. These are controlled semantic cases, not a claim that
every chosen pointer is a natural level entry. They cover all eight heights,
both usage-bit choices and left/right columns. The current stream points to
an existing $fd marker so unrelated new objects cannot hide the pipe result.
All source RAM is applied before normal ScreenRoutines execution; no code,
PC, stack or return-address injection.

Every route requires ProcessAreaData, DrawPipe, its row increment/DEY/tail
instruction and UnderPart entry/exit coverage. It must execute DrawPipe twice
for a left-column start or once for a right-column start. The comparator
requires all thirteen first-column collision tiles, the expired fixed-length
slot, and equality of 1,782 persistent RAM bytes for both samples. All 32
routes pass; scratch, stack and PPU-mirror residuals are separately recorded.
This is not whole-frame or actor-runtime equivalence.

```text
reference <ROM> build/m2-t30-s12/rom-<id>.msfr 2 0 --warmup=1 --fixture=t30-pipe-tail=<id> --pc-coverage=build/m2-t30-s12/pc-<id>.txt
native build/m2-t30-s12/native-<id>.msfn 2 0 1 --warmup=1 --fixture=t30-pipe-tail=<id>
python -B test/verify_pipe_tail_routes.py build/m2-t30-s12
```

Negative control rebuilds pre-fix area.c from `00b7a50` against the same
fixture harness and other objects. Its native pipe-tail smoke fails, and its
four zero-height ROM routes mismatch persistent state; the remaining 28
routes match. The correction therefore repairs the specific zero-height
behavior without changing those nonzero-height paths.

The 64 positive and 32 negative traces total 847,680 bytes, below the 2 MB
budget, with twenty-second process deadlines and the reference instruction
cap. They remain ignored for the enclosing T review. The independent native
matrix passes 2,304 cases: twelve reachable rows x eight heights x two usage
bits x two columns x six protected/unprotected backgrounds. It checks every
staged row, unconditional top writes, clipped shaft extent, exact retained
height and fixed-length expiration. All twenty-one area smokes pass in strict
C90 on x86/x64 (42 program runs), as do product self-tests and hidden bounded
window/message probes. OpenNT16 links MZ with its existing OLDNAMES warning;
DOS resource binding/playability remains deferred. Platform purity passes.

Artifact SHA-256: `mysmb16.exe` `CCAC944DD3089393EB069E6BBF804303571D7DA87781C47525EF6FA60F0CA233`.

Artifact SHA-256: `mysmb32.exe` `77318159E1A6131A0596146E1843370862A07EEF3C687A574630C9E9512EAEF1`.

Artifact SHA-256: `mysmb64.exe` `9BE447AA61B7902B4D411C075CB63D32133BFA9416DE57B4F3BE6A3D18FF4554`.

## S12 closure

Expected/actual restored match: one/one, `DrawPipe`. Both verification tracks
pass and no scoped node remains unfinished. **481 -> 482 / 1,992**; mapped
incomplete returns to 103 and open remains 1,407. S10's two revoked claims now
have explicit corrective proofs in S11/S12. The next unadmitted chain begins
at BlockBufferAddr; M2 remains open.

## T30/S13 admission: shared block-buffer address chain

Entry/data `BlockBufferAddr` (4349, $9bdd) through `GetBlockBufferAddr`
(4353, $9be1-$9bf5). Both are open. Baseline **482 / 1,992**, expected
**2**, maximum **484 / 1,992**. Transfer-110 accepts both from T18 S4.
S12 closes the queued corrections; this resumes the source order after
GetAreaObjYPosition. AreaDataOfsLoopback is the next unadmitted chain.

Shared owner: area/block_buffer.c with its focused header, used by area.c
and world/collision.c. The original RendBBuf and BlockBufferCollision
call sites use one address primitive. Existing player, enemy and fireball
query adapters may change only to consume this helper and its $06/$07 stores;
their independent collision policy receives no credit or redesign.
Audit the four-byte table, high-nibble selector, high-before-low stores,
low-nibble addition without carrying into the stored high byte, and both
source callers. Production callers select 0..31; corrupted out-of-contract
selectors are not ROM-equivalence claims. Sweep duplicate address builders
and classify obsolete setup utilities separately from original call sites.

ROM-logic evidence: controlled source-RAM ScreenRoutines parser routes over
all 32 block columns and the original GetBlockBufferAddr PC path; no leaf
PC, stack, return or ROM-byte edits. Native tests separately exercise all
32 addresses and collision callers at page carry boundaries, including
scratch outputs. Build strict C90 x86/x64, DOS16 link, platform purity,
hidden bounded startup probes and three packaged EXEs once for P1.

Owner NROM and reviewed SMBDIS remain local-only inputs. Raw traces stay
under ignored build/m2-t30-s13, at most 2 MB, twenty seconds per recorder,
two samples after one warmup and the existing reference instruction cap.
S13 owns their cleanup after T review. No node is credited at admission.

### S13 admitted dependency correction

Caller audit found a concrete T28/S8 contradiction: SetInitNTHigh shifts the
unmasked start page, although original StartPage has already ANDed it with
one before the four ASLs. Existing area-initialize smoke incorrectly expects
$30/$20 for pages three/two. The formerly hidden error becomes an invalid
helper argument when removing RendBBuf's invented mask.

Coordinator revokes only `SetInitNTHigh` (2705) to audited mismatch and accepts
it from T28 S8 through transfer-111 into this same bounded S. Revised baseline
**481 / 1,992**, exact scope/expected set: `SetInitNTHigh`, `BlockBufferAddr`,
`GetBlockBufferAddr`; expected three, maximum **484 / 1,992**. The original
482 baseline remains the historical admission snapshot, not the revised
forecast. This explicitly admits the producer repair before changing it.

Add original GameMode task-zero InitializeArea routes for pages zero through
seven, from HalfwayPage and alternate EntrancePage (sixteen source-RAM
fixtures). Independently cover all byte pages and both selectors in C.
Only the page-parity shift and incorrect test expectations may change;
other InitializeArea nodes receive no additional credit. The existing raw
trace/process budget remains sufficient. Finish this dependency before P
packaging; do not restore RendBBuf's invented mask to conceal it.

## S13/P1: block address and initial page proof

Shared leaf: [area/block_buffer.c](../../../src/game/area/block_buffer.c)
and its focused header. Both area.c and world/collision.c depend on it;
it calls neither parent. CMake and OpenNT source lists include the leaf.

| Node | Original semantics and C binding | Evidence |
| --- | --- | --- |
| SetInitNTHigh, $9012 | area.c preserves StartPage AND-one before four ASLs; stores selected nametable high, $80 low and shifted column parity | Sixteen original InitializeArea paths; 512 byte-page/selector native cases; old code fails twelve page-2..7 routes |
| BlockBufferAddr, $9bdd | One four-byte low/low/high/high table in block_buffer.c | Four owner-ROM bytes checked at original offset; both rows consumed across all 32 columns |
| GetBlockBufferAddr, $9be1-$9bf5 | High-nibble selector; high to $07; low nibble plus table low byte to $06 without high-byte carry; pointer return | Entire instruction-byte interval checked; original PC path and 13-row output; direct helper and collision caller tests |

RendBBuf calls the helper after ProcessAreaData without its invented column
mask. Collision adapters call it after horizontal addition/page carry and
before the vertical probe. Player/enemy query parameters become mutable
because $06/$07 are original observable outputs. Original callers reload Y
immediately and consume neither helper flags nor its final A; X is preserved.

All producer contracts are audited: initialization now writes zero/sixteen,
parser increment wraps with AND $1f, and collision callers combine page
parity with the horizontal high nibble. The defensive invalid-column return
does not claim equivalence for corrupted RAM indexing beyond the source table.

The source-RAM fixture covers 32 ordinary ScreenRoutines parser entries with
a nonempty immutable pipe record at each physical column, including 15/16
and 31/0 boundaries. Sixteen GameMode task-zero entries cover pages zero
through seven from HalfwayPage and alternate EntrancePage. No ROM, PC, stack
or return-address changes occur. The verifier requires original PC coverage,
nonvacuous column/init outputs and equality of 1,782 persistent RAM bytes at
both samples on all 48 routes. Scratch $00-$07, stack and $0778/$0779 are
reported exclusions; this is not a whole-frame ROM certificate.

Independent native coverage: 32 direct helper cases with whole-RAM write
canaries, 32 RendBBuf columns with neighbor-buffer guards, and 327,680
player/enemy/fireball queries over every page/X byte and selected adders.
Caller scratch pointers are checked. The initialization smoke adds 512
byte-page/selector cases and corrects old self-confirming $30/$20 expectations.

Negative controls use commit 259f711: old collision consumers fail scratch
assertions with exit 3; old initialization fails exactly twelve routes at
$06a0 and matches four page-zero/one controls. A separate 600-tick native
Start/right/stop run compares its final 120 samples after 480 warmup ticks:
both versions remain in GameMode; persistent RAM and visible output are
unchanged, with differences confined to $06/$07. This compares two native
builds for regression, not additional original-ROM conformance credit.

Similar-issue sweep: world collision builders all use the shared leaf.
area.c background refresh, one-block emitters and old whole-page terrain
builders are in the recorded inactive legacy cluster with no frame/root
caller; they receive no credit. Block replacement/object writers instead
consume a saved pointer low byte plus row as their source routines require;
they are not duplicated GetBlockBufferAddr calls. Live column producers are
initialization and parser increment. Platform sources remain unchanged.

All 22 area smokes plus enemy-block-query pass on x86/x64 (46 program runs),
with strict C90 compilation, self-tests and hidden two-second window/message
probes. OpenNT16 links shared code into MZ with the known OLDNAMES warning.
DOS resource binding/playability remains deferred; MZ is link evidence only.
Platform purity passes. Recorders have twenty-second deadlines and the
existing reference instruction cap; ignored raw output remains for T review.

Raw trace total: 1914694 bytes, below 2 MB.

Artifact SHA-256: `mysmb16.exe` `167C33A86D690902C7A99FC72F8A2E1D68DFEE2A9587FEF40DE5D4D673708CFA`.

Artifact SHA-256: `mysmb32.exe` `3621C1B7BCFCEE1FA5090637E1CA13B119FD486974043C61A6B6FCED02478B71`.

Artifact SHA-256: `mysmb64.exe` `3132D7FBFF31C981B82BF34301AAAC9895D27868DC33C869AED5DDCF57975995`.

## S13 closure

Expected/actual: three/three, SetInitNTHigh restored, BlockBufferAddr and
GetBlockBufferAddr new. No scoped node is unfinished. Revised **481 -> 484 /
1,992**, net two from the initial 482 snapshot. Mapped incomplete returns to
103; open falls to 1,405. The producer revocation/receipt/repair is explicit;
its restored match is not counted as a new label. No S is active; the next
unadmitted source chain begins at AreaDataOfsLoopback. M2 remains open.

## T30/S14 admission: area pointer and header chain

Entry LoadAreaPointer / GetAreaDataAddrs, exit StoreStyle pointer advance;
the adjacent world/area/enemy index and pointer tables are consumed by the
same area-entry route. Shared owner: area/area_data.c with declarations in
area.h. Original initialization, title and terminal callers may be changed
only to restore their source call boundaries and order. No platform or
downstream level/actor behavior is admitted.

Exact scope and expected matches (all open), in source order:
`LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`, `GetAreaDataAddrs`, `StoreFore`, `StoreStyle`, `WorldAddrOffsets`, `AreaAddrOffsets`, `World1Areas`, `World2Areas`, `World3Areas`, `World4Areas`, `World5Areas`, `World6Areas`, `World7Areas`, `World8Areas`, `EnemyAddrHOffsets`, `EnemyDataAddrLow`, `EnemyDataAddrHigh`, `AreaDataHOffsets`, `AreaDataAddrLow`, `AreaDataAddrHigh`.

Baseline **484 / 1,992**, expected **22**, maximum **506 / 1,992**.
Transfer-112 accepts these labels from T18 S4. Transfer-113 separately moves
the preceding `AreaDataOfsLoopback` data node to the existing T19 S5 receiver
of ExecGameLoopback. Its runtime consumer is absent; it stays open and gets
no S14 credit. This is an explicit dependency handoff, not a source-order
skip or a new numeric T. The next unadmitted T30 chain is level-stream data.

ROM audit: exact table addresses/bytes and actual indexed consumers; byte
index sums; LoadAreaPointer writes only its pointer/type; GetAreaDataAddrs
derives type/low offset anew, loads both pointers, decodes both header bytes
and advances the area pointer by two with carry. Preserve background color
unless first-header low bits select it; preserve cloud override unless the
style field is three. InitializeArea must execute this chain before its
halfway entrance override and final mode-task writes, and terminal
LoadAreaPointer callers must not prefetch pointers or headers.

Source-RAM-only ordinary PlayerLoseLife/ContinueGame then InitializeArea
routes cover all 36 world/area entries; direct GameMode task-zero fixtures
cover all 34 legal data slots including bonus areas. No PC, stack, code or
return edits. C tests separately cover byte indices, stale caches, untouched
RAM, all header bytes and pointer carry, plus original caller regressions.
Build strict C90 x86/x64, link DOS16, test platform purity/startup and refresh
three EXEs. Parent nodes receive no new credit from this dependency splice.

Owner NROM and reviewed disassembly are local-only inputs; raw traces stay
below ignored build/m2-t30-s14, budget 3 MB, twenty seconds/process, two
samples after one warmup and the existing reference instruction cap. S14
owns cleanup after the enclosing T review. No completion is claimed now.

### S14 admitted dependency correction

The original two-player TerminateGame route writes Silence ($80) to
EventMusicQueue; the current C writes zero. Coordinator revokes only
`TerminateGame` and accepts transfer-114 from T29 S4 for this immediate
ContinueGame caller dependency. Revised baseline **483 / 1,992**, scope and
expected matches are the original 22 names plus `TerminateGame`: 23,
maximum **506 / 1,992**. Restore this literal and revalidate both swap and
no-swap exits. No GameCoreRoutine repair is admitted.

Replace the 36 life-loss entries with original GameOver player-exchange
entries through the same ContinueGame/LoadAreaPointer chain. The life-loss
entry exposes the separately planned GameCoreRoutine missing early return;
its counterexample is retained and assigned to the dispatcher candidate.
The 34 direct InitializeArea entries remain unchanged. Original PC, stack,
code and all route RAM comparison assertions remain unchanged.

The old core-smoke and local-area-smoke fail the same timer fixtures on
commit d67f9f5 before these changes: task two (setup) and task $7f are not
normal GameEngine dispatch. They remain explicit regression debt, not green
evidence. Coordinator replaces local-area-smoke as the chain closure gate
with the independent exhaustive area-pointer-header smoke, all 23 focused
area smokes and enemy-block-query on both widths; legacy test results are
still retained and reported. No unrelated gameplay change is authorized.

Source-binding tool correction is admitted: smb_asm_index must count data
on the same line as its label. Its former omission made all WorldNAreas
aliases share one address and shifted subsequent data. Use a synthetic
project-owned indexing test and compare the corrected table map directly
to all 188 owner-ROM bytes. This does not certify other historic bindings.

## S14/P1: pointer header and caller proof

Shared owner: [area/area_data.c](../../../src/game/area/area_data.c).
Original table bytes remain local bound PRG, never copied into product C.
`LoadAreaPointer -> FindAreaPointer -> GetAreaType` writes only $0750/$074e.
`GetAreaDataAddrs -> GetAreaType -> StoreFore -> StoreStyle` freshly derives
$074f, loads enemy before area pointers, reads each header in original order,
and advances the CPU pointer by two with carry. Conditional background and
cloud writes preserve the source's untouched values. The resource guards
reject absent/truncated local inputs; those are outside the original-ROM
execution contract and get no ROM-equivalence credit.

InitializeArea now calls the complete pointer/header leaf before hard-mode,
halfway entrance override and task writes. Frame/title callers no longer
parse the header a second time or after the halfway override. Terminal
ContinueGame, NextArea and PlayerEndWorld call only LoadAreaPointer, preserving
zero-page pointers until the following InitializeArea. The combined legacy
load-pointers API is removed. These parent call edges are audited; only the
explicitly revoked TerminateGame receives renewed node credit.

| Checked node | CPU address | Original behavior / live evidence |
| --- | --- | --- |
| [x] `TerminateGame` | `$9248` | Silence $80 before TransposePlayers; swap falls into ContinueGame; no-swap stores ContinueWorld and clears task/timer/mode. Both exits match ROM. |
| [x] `LoadAreaPointer` | `$9c03` | Find then store AreaPointer, fall through to type; 36 world entries preserve stale low-cache/data pointers on first sample. |
| [x] `GetAreaType` | `$9c09` | Mask $60, five shifts, store type; all 256 native input values and both source caller families. |
| [x] `FindAreaPointer` | `$9c13` | World table plus AreaNumber uses byte ADC/TAY index; 36 ROM entries and 2,048 independent native index cases. |
| [x] `GetAreaDataAddrs` | `$9c22` | Derive type/low cache, enemy and area tables, complete header tail; 34 legal slots and 36 world entries. |
| [x] `StoreFore` | `$9c68` | Conditional background selection, foreground store, entrance/timer fields; whole-RAM canaries on all header pairs. |
| [x] `StoreStyle` | `$9ca3` | Conditional cloud/style stores, low add-two and high carry; all header pairs plus all low-pointer bytes. |
| [x] `WorldAddrOffsets` | `$9cb4` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `AreaAddrOffsets` | `$9cbc` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World1Areas` | `$9cbc` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World2Areas` | `$9cc1` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World3Areas` | `$9cc6` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World4Areas` | `$9cca` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World5Areas` | `$9ccf` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World6Areas` | `$9cd3` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World7Areas` | `$9cd7` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `World8Areas` | `$9cdc` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `EnemyAddrHOffsets` | `$9ce0` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `EnemyDataAddrLow` | `$9ce4` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `EnemyDataAddrHigh` | `$9d06` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `AreaDataHOffsets` | `$9d28` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `AreaDataAddrLow` | `$9d2c` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |
| [x] `AreaDataAddrHigh` | `$9d4e` | Exact indexed PRG binding; source expressions match ROM bytes; live route consumer recorded for every table byte and alias. |

ROM track: 36 ordinary two-player GameOver/ContinueGame world entries plus
34 direct InitializeArea slots. Only source RAM inputs are seeded; code,
PC, stack and return addresses are untouched. Original PC coverage confirms
all admitted code entries. Two NMI-return samples per route agree on all
1,782 persistent RAM bytes; only scratch $00-$07, stack and $0778/$0779 are
excluded and reported. A one-sample no-swap TerminateGame route also agrees,
including $fc=$80 and ContinueWorld. This is bounded chain evidence, not a
whole-game certificate. All 188 table bytes at $9cb4-$9d6f are independently
matched to assembly expressions and consumed by the routes.

Operational track: 23 area smokes and enemy-block-query pass on both x86/x64
(48 executions); mode smoke with explicit Silence assertions passes twice.
Pointer/header smoke checks 2,048 world/area byte indices, 256 type values,
65,536 header pairs with whole-RAM write canaries, 256 pointer-low carry cases,
and all 34 slots with both bit-seven aliases and halfway caller overrides.
The previous commit fails the new mode assertion with exit four; fixed C
passes. A 600-tick Start/right/stop native regression (last 120 samples) is
byte-identical in RAM and visible output to d67f9f5 and reaches GameMode.
That comparison is regression evidence, not new ROM conformance credit.

Both native PE products pass self-test and hidden two-second window/message
probes. OpenNT16 compiles the same game sources and links MZ, retaining its
known OLDNAMES warning. DOS resource binding is still absent; link success
is not DOS playability. Platform-purity passes and no platform file changed.
Four legacy whole-smoke executions (core/local-area on two widths) remain
failed at the same preexisting timer fixtures; their failures are retained,
not counted as green or concealed by changed gameplay expectations.

The indexer now processes a label before its inline data directive. A
project-owned synthetic test covers byte/db/word/dw/hex, aliases and following
instructions. The corrected local listing reaches the ROM end without an
opcode mismatch (six non-executable metadata directives remain reported).
All scoped addresses are checked against the independent table audit. Old
unscoped address annotations are not silently recertified.

Similar-issue sweep: all production indexed pointer-table reads have this
single area owner. Only InitializeArea calls the full data/header chain;
terminal/title selection uses LoadAreaPointer and no platform sees it.
All Silence writers were inspected: NextArea still incorrectly queues zero;
it is already open and is recorded for its planned player-control chain.
GameCoreRoutine still runs the engine tail after a task-changing life-loss
return; its saved counterexample belongs to the dispatcher candidate.
Neither deferred defect is part of this node claim. AreaDataOfsLoopback is
accepted under T19 S5 with its missing ExecGameLoopback consumer (transfer-113).

Raw traces: 2320886 bytes, below the admitted 3 MB budget; twenty-second process limits. Local traces remain only for enclosing T review.

Artifact SHA-256: `mysmb16.exe` `890EE21514B3C0EEED59D7BF4BBEBAEA57C0104D038A7F99F05D37C24B919C84`.

Artifact SHA-256: `mysmb32.exe` `C0A3F43FCFA48C02CD97827020A08A71D95A7ACE0E9100E278CE37536CC114DD`.

Artifact SHA-256: `mysmb64.exe` `82A14582D72DEDB887B1B5CD551F31DC73E4DF4AB3917929F21FC9E0CF861D2B`.

## S14 closure

Expected/actual **23/23**: all original 22 pointer/header/table nodes complete,
and TerminateGame restored after explicit revocation and transfer. No scoped
node is unfinished. Revised **483 -> 506 / 1,992**, net 22 versus the original
484 snapshot. Mapped incomplete returns to 103; open falls to 1,383. M2 and
T30 remain open. No S is active; the next unadmitted source chain starts at
E_CastleArea1 and the level-stream data, with the accepted loopback dependency
remaining outside this completed chain.

## T30/S15 admission: enemy-data binding and consumer handoff

Audit-only continuation in source order, entry E_CastleArea1, exit
E_WaterArea3 before the L_CastleArea1 scene-data boundary. Exact scope, all
open, is:

`E_CastleArea1`, `E_CastleArea2`, `E_CastleArea3`, `E_CastleArea4`, `E_CastleArea5`, `E_CastleArea6`, `E_GroundArea1`, `E_GroundArea2`, `E_GroundArea3`, `E_GroundArea4`, `E_GroundArea5`, `E_GroundArea6`, `E_GroundArea7`, `E_GroundArea8`, `E_GroundArea9`, `E_GroundArea10`, `E_GroundArea11`, `E_GroundArea12`, `E_GroundArea13`, `E_GroundArea14`, `E_GroundArea15`, `E_GroundArea16`, `E_GroundArea17`, `E_GroundArea18`, `E_GroundArea19`, `E_GroundArea20`, `E_GroundArea21`, `E_GroundArea22`, `E_UndergroundArea1`, `E_UndergroundArea2`, `E_UndergroundArea3`, `E_WaterArea1`, `E_WaterArea2`, `E_WaterArea3`.

Baseline **506 / 1,992**; expected matches **none (0)**; maximum **506**.
These data are read by ProcessEnemyData and its initialization/group/loop
collaborators, still open under T19 S5. Concrete source/C differences include
page-control versus second-byte-MSB processing order and unconditional C
cursor advance after initialization instead of original Enemy_Flag gating.
No enemy-runtime repair is admitted ahead of its source-order slice. A byte
match alone cannot certify these consumers; that is the explicit zero-credit
audit boundary allowed by the chain rule.

Verify all 34 spans from the corrected assembly index, all byte literals
against owner ROM, every two/three-byte record and terminator, all enemy
pointer-table bindings, and every row-$0e destination against legal area
slots. Add a reusable local-only binding checker with project-owned synthetic
positive/negative tests. Report only neutral metadata, never stream bytes.
Accept the exact data names into existing T19 S5 with ProcessEnemyData for
planned enemy-stream admission, using an append-only transfer event. Scene
data and dispatcher remain unadmitted. No platform/game runtime edits.

Owner NROM and reviewed listing remain local research inputs; no third-party
code is imported. Generated reports/fixtures remain under ignored
build/m2-t30-s15, 1 MB output budget and twenty-second command limits.
Operational checks: checker synthetic tests, source-policy containment,
platform purity, existing x86/x64 self-tests and DOS MZ structural inspection;
reuse S14's unchanged three binaries with hashes, rather than claim a new
runtime build. All 34 nodes remain incomplete with an accepted consumer owner.

## S15/P1: enemy data bindings and accepted consumer debt

All 34 enemy labels bind to the original listing/ROM: **1,087 unique bytes**,
34 low/high pointer entries and all four type-base indices. Enemy pointer
order is castle/ground/underground/water; area type order is
water/ground/underground/castle. The checker verifies the mapping rather
than assuming those orders coincide. All row-$0e destination indices are
within the original legal area slots.

| Node | CPU start | Runtime end (exclusive) | Storage / consumed bytes | Ordinary / row-0f / row-0e records | Disposition |
| --- | --- | --- | --- | --- | --- |
| `E_CastleArea1` | `0x9d70` | `0x9d97` | 39 / 39 | 18 / 1 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_CastleArea2` | `0x9d97` | `0x9db0` | 25 / 25 | 9 / 3 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_CastleArea3` | `0x9db0` | `0x9ddf` | 47 / 47 | 23 / 0 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_CastleArea4` | `0x9ddf` | `0x9e0a` | 43 / 43 | 19 / 2 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_CastleArea5` | `0x9e0a` | `0x9e1f` | 21 / 21 | 8 / 2 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_CastleArea6` | `0x9e1f` | `0x9e59` | 58 / 58 | 13 / 5 / 7 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea1` | `0x9e59` | `0x9e7e` | 37 / 37 | 18 / 0 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea2` | `0x9e7e` | `0x9e9b` | 29 / 29 | 11 / 3 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea3` | `0x9e9b` | `0x9ea9` | 14 / 14 | 3 / 2 / 1 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea4` | `0x9ea9` | `0x9ed0` | 39 / 39 | 10 / 3 / 4 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea5` | `0x9ed0` | `0x9f01` | 49 / 49 | 21 / 0 / 2 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea6` | `0x9f01` | `0x9f1f` | 30 / 30 | 11 / 2 / 1 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea7` | `0x9f1f` | `0x9f3c` | 29 / 29 | 14 / 0 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea8` | `0x9f3c` | `0x9f51` | 21 / 21 | 7 / 3 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea9` | `0x9f51` | `0x9f7c` | 42 / 43 | 18 / 0 / 2 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea10` | `0x9f7b` | `0x9f7c` | 1 / 1 | 0 / 0 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea11` | `0x9f7c` | `0x9fa0` | 36 / 36 | 15 / 1 / 1 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea12` | `0x9fa0` | `0x9fa9` | 9 / 9 | 1 / 0 / 2 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea13` | `0x9fa9` | `0x9fce` | 37 / 37 | 17 / 1 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea14` | `0x9fce` | `0x9ff1` | 35 / 35 | 16 / 1 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea15` | `0x9ff1` | `0x9ffa` | 9 / 9 | 2 / 2 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea16` | `0x9ffa` | `0x9ffb` | 1 / 1 | 0 / 0 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea17` | `0x9ffb` | `0xa035` | 58 / 58 | 25 / 2 / 1 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea18` | `0xa035` | `0xa060` | 43 / 43 | 18 / 0 / 2 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea19` | `0xa060` | `0xa08e` | 46 / 46 | 19 / 2 / 1 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea20` | `0xa08e` | `0xa0aa` | 28 / 28 | 10 / 2 / 1 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea21` | `0xa0aa` | `0xa0b3` | 9 / 9 | 1 / 0 / 2 | Incomplete; accepted T19 S5 consumer proof |
| `E_GroundArea22` | `0xa0b3` | `0xa0d8` | 37 / 37 | 17 / 1 / 0 | Incomplete; accepted T19 S5 consumer proof |
| `E_UndergroundArea1` | `0xa0d8` | `0xa105` | 45 / 45 | 18 / 1 / 2 | Incomplete; accepted T19 S5 consumer proof |
| `E_UndergroundArea2` | `0xa105` | `0xa133` | 46 / 46 | 17 / 1 / 3 | Incomplete; accepted T19 S5 consumer proof |
| `E_UndergroundArea3` | `0xa133` | `0xa160` | 45 / 45 | 0 / 4 / 12 | Incomplete; accepted T19 S5 consumer proof |
| `E_WaterArea1` | `0xa160` | `0xa171` | 17 / 17 | 5 / 0 / 2 | Incomplete; accepted T19 S5 consumer proof |
| `E_WaterArea2` | `0xa171` | `0xa19b` | 42 / 42 | 14 / 2 / 3 | Incomplete; accepted T19 S5 consumer proof |
| `E_WaterArea3` | `0xa19b` | `0xa1af` | 20 / 20 | 8 / 0 / 1 | Incomplete; accepted T19 S5 consumer proof |

E_GroundArea9 consumes E_GroundArea10's one-byte empty-stream terminator;
its physical labeled span is shorter than its runtime stream. The checker
preserves that shared boundary, not a copied or inserted terminator. Record
counts above are byte framing, not a simulation of stateful page controls.
The source/ROM checker is [smb_enemy_data_audit.py](../../../tools/smb_enemy_data_audit.py);
its report excludes payload bytes and stays in ignored build output.

Concrete consumer counterexample: E_GroundArea8 at offset sixteen, initial
EnemyObjectPageLoc=0, EnemyObjectPageSel=0 and ScreenRight_PageLoc=255.
Original CheckRightBounds first processes the second-byte MSB, increments
page to one and sets page-select; CheckPageCtrlRow therefore branches to
PositionEnemyObj. Behind the right boundary, CheckThreeBytes/Inc2B consumes
one record, leaving page=1, cursor=18 and current-slot page=1. Current C
handles the row-$0f control first, sets page ten, continues to the next record
and leaves page=10, cursor=20 and current-slot page=10. A bounded native
probe with immutable owner PRG confirms those C outputs. This is source-branch
and native counterexample evidence, not a completed dynamic ROM-route claim.
The existing initializer cursor-advance gate must also be audited with the
consumer: original StrID advances only when initialization retains Enemy_Flag;
current C advances unconditionally.

Coordinator accepts transfer-115 from T18 S4 to existing T19 S5 for all 34
names, with ProcessEnemyData. The planned enemy-stream slice must cover the
MSB/page-select order, shared terminator, two/three-byte cursor behavior,
initialization result and group/loop collaborators before certifying data.
No future numeric task is admitted by this receipt. The next T30 source
chain is L_CastleArea1 through scene data.

Operational evidence: project-owned synthetic checker validates all 34
pointer entries, shared terminator and destination framing, and rejects
fourteen malformed framing/literal/pointer/base cases. The existing indexer
synthetic test and platform-purity test pass. No runtime source or ABI changed.
Three S14 products are intentionally unchanged: x86/x64 PE self-tests pass;
DOS MZ declared size, relocations and header bounds agree. No fresh build or
DOS playability is claimed for this audit P. Existing owner authorization
covers retention of the three tracked products; no ROM/research byte is added.

Artifact `mysmb16.exe`: 252913 bytes; SHA-256 `890EE21514B3C0EEED59D7BF4BBEBAEA57C0104D038A7F99F05D37C24B919C84`; MZ structure only.

Artifact `mysmb32.exe`: 309473 bytes; SHA-256 `C0A3F43FCFA48C02CD97827020A08A71D95A7ACE0E9100E278CE37536CC114DD`; PE self-test passed.

Artifact `mysmb64.exe`: 316466 bytes; SHA-256 `82A14582D72DEDB887B1B5CD551F31DC73E4DF4AB3917929F21FC9E0CF861D2B`; PE self-test passed.

## S15 closure

Expected/actual matches **0/0**; **506 / 1,992** remains unchanged. All 34
scoped labels are now mapped but incomplete and accepted by T19 S5. Mapped
incomplete is 137; open is 1,349. This audit retains no unfinished nodes.
S15 is closed; T30 and M2 remain open. Scene data is the next unadmitted chain.

## T30/S16 admission: castle scene streams

Exact scope and expected matches, all open: `L_CastleArea1`,
`L_CastleArea2`, `L_CastleArea3`, `L_CastleArea4`, `L_CastleArea5`,
`L_CastleArea6`. Baseline **506 / 1,992**, expected **6**, maximum **512**.
Entry is the six original header/table selections; exit is each stream's
terminator after its last object. Shared runtime owner remains area/area_data.c
and area.c. No copied scene payload or platform parser is permitted.

Accept transfer-116 from T18 S4. Bind each entire literal span and pointer,
then compare the existing original InitializeArea -> ScreenRoutines ->
AreaParserTaskControl consumer. Controlled source-RAM routes start at pages
zero and sixteen and request bounded repeated two-column screen parser sets;
this covers both halves without requiring unadmitted player/actor runtime.
The fixtures may change screen-task/column-set inputs after the original
header initialization, never PC, stack, return addresses or ROM bytes.
Require actual stream-cursor/terminator coverage and compare parser state,
metatile/block-buffer output and original object-creation writes. Any gap
must remain explicit; do not certify a whole stream from its first columns.

Independent C checks cover data framing/binding and complete native parser
traversals on x86/x64. Source-shaped repairs are limited to these admitted
scene consumers; a contradictory previously completed helper requires
explicit revocation and a corrective receipt before changing it. Other actor,
player, dispatcher and loopback behavior stays with existing receivers.
Each implementation P builds three EXEs and reports startup, purity and
DOS link limits. Owner NROM/listing remain local-only research inputs.
Raw trace budget: 20 MB under ignored build/m2-t30-s16; twenty-second process
limits, up to 130 samples per route and twelve original/native route pairs.
S16 retains cleanup responsibility through T review. No matches claimed yet.

### S16 traversal-route calibration

Exact literal spans bind: six streams, 700 unique bytes and 341 object
records. Native continuous parser probes reach terminal offsets 94, 124,
112, 106 and 136 for castles one through five from page zero. Castle six
reaches offset 86 after the first sixteen pages, then terminal offset 110
from its valid page-sixteen continuation. Both stages together cover its
full stream. These are native diagnostic results only, not ROM matches.

Replace the initial twelve-route estimate with seven routes: page zero for
all six castles and page sixteen only for castle six. Starting castle one
at page sixteen, beyond its scene end, stalls the current backloader; the
bounded process was terminated after twenty seconds. Do not present that
invalid-entry fixture as a proven ROM discrepancy. Preserve the diagnostic
and compare valid entries first. The other five page-sixteen starts are not
needed for complete stream coverage. The original-ROM comparison and
independent cross-width tests remain outstanding; S16 remains active.

### S16 admitted ChkRow13 correction

Seven original-ROM routes expose only one persistent-RAM difference class:
LoopCommand at $0745. First differences are samples 65, 35 and 26 for castle
streams two, five and six. Original ChkRow13 increments when decoding the
row-$0d loop selector, before NormObj checks page/column or InitRear returns.
C incorrectly increments only inside run_object. Coordinator revokes
`ChkRow13` and accepts transfer-117 from T29 S7 as this immediate consumer
dependency. No ExecGameLoopback runtime repair is admitted.

Revised baseline **505 / 1,992**; exact scope/expected set is ChkRow13 plus
the six named L_CastleArea nodes, expected seven, maximum **512**. Repair
only recognition timing in the shared parser and add focused pending-column,
future-page, behind-page and active-slot checks. Full traversal remains the
original-ROM gate. Initial visible-output baseline differences must be
separated from parser output by matching ordinary boot initialization; do
not mask a parser mismatch or claim full-frame equality without evidence.

## S16/P1: castle stream consumption and loop-command order

The original source chain is InitializeArea -> GetAreaDataAddrs ->
ScreenRoutines -> AreaParserTaskControl -> ProcessAreaData -> DecodeAreaData.
The shared C owners remain area/area_data.c and area.c; no platform code or
runtime ABI changes. Owner ROM/listing remain local research inputs; tracked
tests contain harness logic and neutral metadata, not scene payloads.

| Node | Original CPU address | Bound bytes / object records | Final disposition |
| --- | --- | --- | --- |
| `ChkRow13` | `$95c3` | Recognition before NormObj/InitRear | ROM-match complete; restored |
| `L_CastleArea1` | `0xa1af` | 97 / 47 | ROM-match complete |
| `L_CastleArea2` | `0xa210` | 127 / 62 | ROM-match complete |
| `L_CastleArea3` | `0xa28f` | 115 / 56 | ROM-match complete |
| `L_CastleArea4` | `0xa302` | 109 / 53 | ROM-match complete |
| `L_CastleArea5` | `0xa36f` | 139 / 68 | ROM-match complete |
| `L_CastleArea6` | `0xa3fa` | 113 / 55 | ROM-match complete |

Each scene's entire literal span, header, immutable PRG binding and terminator
matches the original listing. Together they contain 700 bytes and 341 object
records. The six page-zero routes plus castle six's page-sixteen continuation
exercise all six streams. Original LDA (AreaData),Y read coverage confirms
every byte was consumed; the observer counts only a completed two-byte LDA
step and rejects interrupt-redirection steps. It does not modify execution.
The first five terminal cursors are 94, 124, 112, 106 and 136. Castle six first
reaches cursor 86, then reaches its terminal cursor 110 on the continuation.

ChkRow13 increments LoopCommand before page/column rejection or InitRear.
CheckRear skips inactive behind-page records before DecodeAreaData; resident
slots enter DecodeAreaData directly. The C repair preserves these two entry
paths and unsigned-byte wrap, and removes the late run_object-only increment.
ExecGameLoopback behavior is unchanged and retains its existing receiver.
Similar-issue sweep searched every area.c LoopCommand reference: one address
declaration and exactly these two recognition writes remain. No platform
logic was added; platform-purity verification passes.

ROM-logic evidence: seven controlled original-ROM/native routes, each with
129 NMI-return samples, compare all 1,782 persistent RAM bytes and complete
recorded CIRAM, palette, OAM, audio and PPU output. All 903 samples match.
Only scratch bytes 0..7, the CPU stack and two PPU RAM mirrors are excluded
from RAM comparison; no output bytes are masked. Native --bootstrap-title
uses the same ordinary cold-start baseline as the original recorder instead
of applying precomputed title commands before the fixture. Fixtures seed
source RAM only; no PC, stack, return-address or ROM patch is used.
The reproducible checker is
[verify_castle_scene_routes.py](../../../test/verify_castle_scene_routes.py).

Independent operational evidence: 54 focused native executions pass across
x86/x64, including complete castle traversals and 2,304 loop-command cases
per width (all counter seeds, pending/matching columns, future/behind pages,
page-MSB, backloading and all three resident slots). The prior S14 object set
fails the new loop smoke and diverges at LoopCommand in castle two/five/six
samples 65/35/26 respectively; the corrected implementation passes all seven
routes. This negative control establishes that the tests detect the repaired
defect. Existing unrelated legacy core/local timer-fixture failures remain
documented debt; this is not an all-suite-green claim.

Both Windows products pass self-test and a bounded hidden-window creation/
message-response probe, repeated against the packaged assets themselves.
The owner's earlier startup failure has not been reproduced or diagnosed;
these checks do not establish a fix for it or whole-game playability.
DOS16 compiles and links with OpenNT; the existing DOS root still lacks local
PRG/CHR/title binding, so the MZ is link evidence, not DOS gameplay evidence.
All generated inputs, traces and logs remain in ignored build output. Raw
traces total 9,669,141 bytes, within the 20 MB budget; each recorded process
has a twenty-second limit. S16 owns retention through the T review.

All three existing tracked EXEs are refreshed under the owner's explicit
artifact-commit instruction. No new ROM or derived source file is committed.

Artifact `mysmb16.exe`: 252977 bytes; SHA-256 `98E1A618425B80AB8883375305A63208AB18CAD27A41FB7B6D0863AFC2B9FD21`.

Artifact `mysmb32.exe`: 309473 bytes; SHA-256 `44A367EE80D7FF8D7B0F273F0B1E9FEC2255C55AE5561945B2CE2C7404FE3F62`.

Artifact `mysmb64.exe`: 316466 bytes; SHA-256 `BA7DA53C53F3339EAD390F1D72D6B238F6DB1E92B5E1ADE044F4A811E822F074`.

## S16 closure

Expected/actual matches **7/7**: ChkRow13 restored and all six named castle
scene nodes complete. Revised admission **505 / 1,992** becomes
**512 / 1,992 (25.70%)**; this is six net new matches relative to S15's 506.
Mapped incomplete is 137 and open is 1,343. No scoped node is deferred or
retained unfinished. S16 is closed; T30 and M2 remain open. The next
unadmitted source chain starts at L_GroundArea1, followed by the remaining
ground, underground and water scene groups in original source order.
