# Project Status

## M3 T9 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation:M3 T9 S2 P1 complete;S2 closed,T9 open;automatic S3 admission follows commit. |
| Admission And Approval | Owner admits unified I/O T and automatic sequential S admissions,advance briefs and closure reports. |
| Objective | Migrate Win32 decoded input,read-only video submission and ordered waveOut audio to IO contracts,preserve current output and pause behavior. |
| Non-goals | No original game logic migration,visible ASCII scene,host switching or game proof promotion. |
| Reference Baseline | Historical1992/1992;local1991/1992 nodes,4260/4261 feasible controls;M2 incomplete,deferred at queue tail. |
| Candidate Proposal | [T9 plan](../proposals/shared-io-and-presentation-switching.md#t9-admission-and-s1-plan). |
| Files And ABI Surface | Win32 main/audio output/renderer and related focused tests;optional IO/root boundary/build hook. Expected8-12 source/test files,250-400 changed lines. |
| Applicable Rules | README Task Reading Set,Execution,Architecture,Coding,Documentation,source policy and admitted proposal. |
| Verification | C90 x86/x64 contract and existing PPU/audio/focus/purity tests;OpenNT16 contract compilation and full DOS16 link;three product builds. |
| Expected Markers | Original node scope[],expectedMatches[],fresh0;historical1992/1992 and local scoped counts unchanged. |
| Asset Needs | Existing owner-local generated ROM data,read-only build input;not redistributable,no import;all intermediate/log outputs below ignored build. |
| Reporting Requirements | Before each S component/scope/size estimate;after S tests,three artifacts,actual diff scale,commit and push result,then automatic next admission. |
| Stop Conditions | Scoped contract failure or discovered business-logic diff requires repair/review within admitted owner before advancing. |
| Exit Criteria | Win32 consumes neutral output contracts,old/current output equivalence and focused cross-width tests/builds pass;three EXEs,reviewed S2 commit,push if remote available,next S3 admitted. |
| Original Owner Request | Unify non-game/non-system-dependent I/O components;single-person dual-role execution,automatic sequential S delivery. |
| Similar-Issue Sweep | Host dependencies and game-state leakage in new contracts;byte widths,far pixel pointer,ordered repeated writes and full frame dimensions. |

## Current Technical Baseline

- M2 T70/S17 closed by owner-approved deferred-verification transfer (P153);
  [closure record](../history/M2-T70-deferred-verification-closure.md).
  This is not successful full-game acceptance;M2 certificate remains incomplete.
- Historical mapping1992/1992;local scoped nodes1991/1992,feasible controls
  4260/4261(raw4342,infeasible81). CheckForEnemyGroup/control-01480 needs evidence.
- [Audit ledger](M2_AUDIT_LEDGER.md):10691 retained sites/4171 accesses,
  6/136 groups and42/952 facets closed,130 groups/910 facets pending.
  Material993 partial,not a denominator;two findings/all13 coverage slots open.
  Final packages2/6 closed,material/pixels/routes/snapshot pending.
- Remaining verification is the last [queue](QUEUE.md) candidate:
  [remaining certification](../proposals/m2/remaining-current-certification.md).
  M3 T9 S1 active;the remaining two I/O candidates precede queued verification.
- Existing P144 three products/original DOS16 compile-link receipts retained;
  P153 makes no game-code change and does not refresh products.

## Compact closure status

M2 T70 S17 P153:owner-directed administrative S/T closure;all unfinished
verification transferred to an unnumbered candidate,not marked passed.
P152 victory/terminal35labels/214sites/95controls and seven operational tests
per width remain scoped receipts. [Archived T70](../history/m2/t70-final-current-certification.md)
preserves all earlier P evidence and limitations. Full M2 remains incomplete.

M3 T9 S1 P1:four neutral contracts and dependency/ABI test delivered;8 source/build files,+184/-1;6tests eachwidth,OpenNT16 compile/link and3localEXEs. No game logic/node credit;push unavailable,no remote.

M3 T9 S2 P1:Win32 IO consumers and shared composition glue;14 source/test/build files,+253/-121,9tests eachwidth,1024ticks/752640PCM samples eachwidth zero old/current diff,OpenNT16 compile/link and3localEXEs. No game logic/node credit,push unavailable without remote.
