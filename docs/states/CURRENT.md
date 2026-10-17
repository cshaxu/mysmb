# Project Status

## M3 T47 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation M3 T47 S2 after S1 P4 e3296c80; S2 P2 closed for owner acceptance; T47 remains open. |
| Admission And Approval | Owner requests pure DOS16c, current NE hybrid16w and unchanged32/64 names, following P1 --turbo delivery. Single-person executor/coordinator review. |
| Objective | P2: publish four Mario executables: pure DOS mysmb16c, hybrid DOS/Win16 mysmb16w, unchanged mysmb32/mysmb64 names; preserve accepted S2 P1 runtime behavior. |
| Non-goals | No ROM core/PPU/art/cache alteration, third-party import, emulator edit, max test, Win32/Win16 behavior change or hardware/parity claim. |
| Reference Baseline | d86cb0ca S2 P1; reuse its qualified pure DOS/hybrid/PE binaries and runtime receipts. |
| Candidate Proposal | [Owner S2 admission](../proposals/m3/nesticle-forensic-performance-audit.md#s2-admission--dos-normal-and---turbo-presentation-policy). |
| Files And ABI Surface | Packaging tool, product packaging test, build/test registration, delivery rules and local product documentation. No runtime ABI or game source changes; estimate under100tool lines plus tests. |
| Applicable Rules | Task Reading Set, C90/segmented ABI, source policy, library/app boundary, test-owner closure, continuable build/test, ignored generated outputs. |
| Verification | Retain P1 runtime evidence; packaging positive/negative contract test and actual four-file package, matching DOS stub/NE verification, documentation/ledger gates. No unchanged runtime matrix repetition. |
| Expected Markers | Historical1992/1992,scope=[],expectedMatches=[],actualMatches=[],maximum1992/1992; no new node/edge credit. |
| Asset Needs | Existing owner-local ROM only for original build/local joins; no publication/import. Existing NE product payload reused only if unchanged Win16 code binding verifies. No NESticle run required. Generated build/t47-s2,16MiB raw counters,180seconds/run; no max or E-drive writes. |
| Reporting Requirements | Four artifact names/kinds/hashes, packaging tests and unchanged P1 runtime/ROM counts. |
| Stop Conditions | Core/PPU diff, wrong-option policy, normal skipped frame, segment/loader overrun, unreviewed shared-library game semantics, unexplained test failure; two identical failed probe attempts. |
| Exit Criteria | Met: P1 retained; P2 validates MZ-only versus NE hybrid and matching DOS payload, publishes four current local artifacts and updates future delivery rules. |
| Original Owner Request | Owner specifies 16c pure DOS,16w current NE hybrid,32/64 unchanged. |
| Similar-Issue Sweep | Package caller sweep, pure MZ/native NE distinction, DOS payload/loader equality, retired alias cleanup, current versus historical artifact names. |

## Current Technical Baseline

S1 bounded comparison closed. At fixed3000/no physical audio and stationary
mode1/task3, unchanged MySMB gives approximately60ticks/s and14.1admitted images/s;
original NESticle0.2 gives19.4virtual frames/s and5.19display loops/s. Native
outputs differ256x240/256x224. No x.xx/hardware/whole-game or renderer-only ratio.
The first73tick/s sample was startup catch-up debt, excluded from steady data.
Detailed transfer/retrace/mode binding remains unverified S3-S5 census work.

User now supersedes always-skipping with normal per-tick presentation and
optional legacy turbo. Shared ROM state/order stay unchanged. Historical1992/1992,
retained exact1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81).


## S2 P1 Closure (retained)

`mysmb16` now publishes every game tick; `mysmb16 --turbo` retains old catch-up
and video suppression. At fixed3000/no physical audio, normal573ticks/573images
in19.999s; turbo1199ticks/280images in19.999s after startup debt settles. DOS
Tab/exit, default text1:1 and invalid arguments pass. Native318/318tests and
15private-desktop host joins pass per width. Three local assets/mario EXEs
refreshed; original DOS build and unchanged accepted native NE payload binding
verified. Loaded bounds increase1600bytes, no new persistent cache. Core/PPU
and Windows/Win16 bindings unchanged. Full evidence/test-owner review is in
the proposal. Node counts unchanged. No successor admitted before owner
acceptance; S3-S5 remain the existing bounded research plan.


## S2 P2 Closure

Four local products now ship together under assets/mario: mysmb16c.exe is pure
DOS MZ, mysmb16w.exe is the unchanged DOS/Win16 NE hybrid, mysmb32.exe and
mysmb64.exe retain their names. Old mysmb16.exe is removed. Packager enforces
kind and matching DOS payload/loader bounds. Both Ninja builds and319/319tests
per width pass. Actual16c Enter/Tab/exit/default-text join passes; P1 runtime
and private-host receipts retained, no runtime source changed. Current delivery
rules require all four on subsequent Mario implementation delivery. S2 closed
for owner acceptance; T47 open, no successor admitted. ROM counts unchanged.
