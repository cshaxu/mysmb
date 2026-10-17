# Project Status

## M3 T47 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation M3 T47 S2 after S1 P4 e3296c80; S2 closed for owner acceptance; T47 remains open. |
| Admission And Approval | Owner explicitly requests mysmb16 --turbo: skip/catch-up only when enabled; default publishes every tick. Single-person executor/coordinator review. |
| Objective | Add bounded DOS command-tail access and Mario-owned option parsing; default tick/presentation synchronization, legacy policy under --turbo. |
| Non-goals | No ROM core/PPU/art/cache alteration, third-party import, emulator edit, max test, Win32/Win16 behavior change or hardware/parity claim. |
| Reference Baseline | e3296c80; unchanged product SHA/settled fixed3000 baseline: MySMB60ticks/s and14.1admitted displays/s. |
| Candidate Proposal | [Owner S2 admission](../proposals/m3/nesticle-forensic-performance-audit.md#s2-admission--dos-normal-and---turbo-presentation-policy). |
| Files And ABI Surface | Generic DOS command tail, Mario parser/assembly, shared pacing arithmetic, build lists and owner tests. Estimate8-14production/build files,100-180production lines plus tests; one policy flag and transient bounded command buffer. |
| Applicable Rules | Task Reading Set, C90/segmented ABI, source policy, library/app boundary, test-owner closure, continuable build/test, ignored generated outputs. |
| Verification | Parser/tail/pacing branch tests, full native x86/x64 suites, optimized DOS build, preserved unchanged NE payload, actual-EXE default/turbo/invalid arguments and Enter/Tab/exit, three current Mario artifacts. |
| Expected Markers | Historical1992/1992,scope=[],expectedMatches=[],actualMatches=[],maximum1992/1992; no new node/edge credit. |
| Asset Needs | Existing owner-local ROM only for original build/local joins; no publication/import. Existing NE product payload reused only if unchanged Win16 code binding verifies. No NESticle run required. Generated build/t47-s2,16MiB raw counters,180seconds/run; no max or E-drive writes. |
| Reporting Requirements | Actual normal versus turbo tick/display counts, startup debt behavior, code size/resident cost, test owners, three artifact hashes and unchanged ROM counts. |
| Stop Conditions | Core/PPU diff, wrong-option policy, normal skipped frame, segment/loader overrun, unreviewed shared-library game semantics, unexplained test failure; two identical failed probe attempts. |
| Exit Criteria | Met: default ticks all publish with no stale-debt catch-up; --turbo preserves existing suppression; clear bounded parse failure; focused/full checks and three packaged local products. |
| Original Owner Request | If turbo enabled use skipping; otherwise wait for every frame; mysmb16 --turbo. |
| Similar-Issue Sweep | Startup/midnight/reset pacing, transient parser lifetime, quoted DOS tail bounds, cache probe command ownership, graphics/text policy, unchanged Windows/Win16 linkage. |

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


## S2 Closure

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
