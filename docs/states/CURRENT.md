# Project Status

## M3 T9 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation:M3 T9 S4 P1 complete;S4 closed,T9 open;automatic S5 admission follows commit. |
| Admission And Approval | Owner authorizes automatic sequential S admissions,advance briefs and closure reports. |
| Objective | Stabilize DOS clock/pacing,device lifetime and explicit unsupported audio capability while preserving shared IO contracts. |
| Non-goals | No game semantic change,ASCII mode,new sound hardware or full-game ROM certification. |
| Reference Baseline | Historical1992/1992;local1991/1992 nodes,4260/4261 controls;M2 incomplete and queued. |
| Candidate Proposal | [T9 plan](../proposals/shared-io-and-presentation-switching.md#s4-admission---dos-device-stabilization). |
| Files And ABI Surface | Shared pacing/audio capability contracts,DOS devices/root/main,focused tests/build registration. Expected8-12 source/test/build files,300-500 changed lines. |
| Applicable Rules | README Task Reading Set,Execution,Architecture,Coding,Documentation,source policy and admitted proposal. |
| Verification | Pacing rollover/late-frame tests,ordered DOS audio submission/lifecycle,existing Win32 IO regressions eachwidth,original OpenNT16 build,scoped DOS graphic probe,three products. |
| Expected Markers | Original scope/expectedMatches[],fresh0;retained node/control counts unchanged. |
| Asset Needs | Owner-local ROM resources and read-only SoftPC tool/media inputs;local nonredistributable. Public Intel8254 manual for hardware facts only,no code import. Outputs below ignored build,no sibling edits. |
| Reporting Requirements | Before each S scope/size;after S tests,three products,diff scale,commit/push result and next admission. |
| Stop Conditions | Scoped failure or business logic diff repaired/reviewed before advancement. |
| Exit Criteria | Scoped pacing/device/audio capability tests and real DOS16 build/runtime probe pass;reviewed commit,next S5 admitted. |
| Original Owner Request | Unify non-game/non-system-dependent IO;single-person dual roles,automatic sequential delivery. |
| Similar-Issue Sweep | IRQ state restore,clock rollover/slow frames,unbounded catch-up,audio output silently discarded or host types crossing IO. |

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
  M3 T9 S4 active;the remaining two I/O candidates precede queued verification.
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

M3 T9 S3 P1:DOS neutral IO/64-color palette/scaling/resource and lifecycle repair;18 source/test/build files,+432/-292,11tests eachwidth,OpenNT16 link and scoped SoftPC graphic startup/Esc restore,3localEXEs. No game-node credit,no remote.

M3 T9 S4 P1:DOS PIT/clock pacing and explicit audio capability;16 source/test/build files,+161/-20,13tests eachwidth,65536 cycle positions,OpenNT16 build/scoped graphic probe,3localEXEs,no node credit/no remote.
