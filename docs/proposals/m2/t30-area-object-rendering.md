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
