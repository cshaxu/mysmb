# Project Status

## M3 T10 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New:M3 T10 S1 P1 complete;T10 remains open,S2 next. |
| Admission And Approval | Owner approves queue-head task admission and execution;automatic subsequent S after reviewed closure. |
| Objective | Shared quick-snapshot schema,portable codec,resource/integrity validation and last-running-frame cache. |
| Non-goals | No P/O host binding,file transaction,game semantic repair,ROM credit or emulator compatibility investigation. |
| Reference Baseline | Historical1992/1992;local1991/1992 nodes,4260/4261 feasible controls;42/952facets,M2 incomplete. |
| Candidate Proposal | [T10 quick snapshot](../proposals/shared-io-quick-snapshot.md#s1-admission). |
| Files And ABI Surface | New src/io snapshot codec and test;CMake/original DOS build registration;design and governance. Estimate8-12files,400-650source/test lines. |
| Applicable Rules | Task Reading Set,Execution,Architecture,Coding,Documentation,source policy and admitted proposal. |
| Verification | Neutral fixed-format fixtures,corruption/atomic-decode/cache/numeric round trips,x86/x64 tests,original DOS16 compile/link,purity and governance gates;three local products refreshed. |
| Expected Markers | Exact scope[],expectedMatches[],new0;all retained ROM counts unchanged. |
| Asset Needs | Existing owner-local ROM and OpenNT16 tools only for local product refresh;provenance retained from T9,distribution unreviewed/forbidden,outputs confined to ignored build/assets;neutral codec tests need no ROM. |
| Reporting Requirements | Before/after scope,size,tests,three products and local commit;no push without remote;auto-admit S2 after S1 closure. |
| Stop Conditions | Any width/schema/state omission or dependency violation blocks S1 closure until repaired. |
| Exit Criteria | Byte-defined bounded snapshot,no raw structs/pointers/floating layout,complete mutable-state map and passing validation/cache tests on both widths and DOS compile/link. |
| Original Owner Request | Admit new queue-head task and start;retain per-S briefs and build/test/commit reports. |
| Similar-Issue Sweep | All mutable game/audio fields,state pointers,padding,paused-frame selection and failure-before-commit paths. |

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
  M3 T9 closed;quick snapshot and text-frame candidates precede queued verification.
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

M3 T9 S5 P1:actual headless DOSBox title/Start/24seconds gameplay/run/jump/left/release/Esc passed;4test/tool files,+281/-0,no product source edit;13focused+1friction test eachwidth,three builds/products retained,no ROM credit/no remote.

M3 T9 S6 P1:shared Escape exit/short-press lifecycle and integrated closure;16source/test/build files,+130/-26,14tests eachwidth,fresh originalDOS16 link/actualDOSBox route/3EXEs. T9closed,DOSaudio unavailable/M4speed pending,zeroROMcredit,no remote.

M3 T10 S1 P1:4782byte codec,integer canonical numeric validation,last-running cache;5focused tests eachwidth,originalDOS16 link and3localEXEs. ZeroROMcredit,no remote;P/O host binding pending.
