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
