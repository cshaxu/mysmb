# Project Status

## Current Work

## M3 T44 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation - M3 T44 S3 P1, source/build migration admitted |
| Admission And Approval | Owner accepts S2 and requests admission of the next S. S2 closes at accepted implementation c308fa7e; S3 follows the existing T44 proposal. |
| Objective | Move production ownership to src/lib and src/app-mario/core plus src/app-mario/kvm, updating build/include/generator paths without changing function semantics. |
| Non-goals | No Mine code import, game/PPU/audio behavior change, Win16 Tab feature, or test-tree migration; mirrored tests remain S4. No new performance or ROM-equivalence claims. |
| Reference Baseline | Owner-accepted c308fa7e: DOS dual-mode and native Win16 graphical MZ/NE product with P/O and music. x86/x64 each 299 pass plus one unavailable host-audio skip. S2 proposal retains bounded runtime receipts and limitations. |
| Candidate Proposal | [M3 T44 proposal](../proposals/m3/nxvm-source-test-layout.md#s3---source-and-build-ownership-migration). |
| Files And ABI Surface | Approximately 300 production source/header paths, shared component build definitions, root/app CMake, presets, tools and current source-map links. Test paths stay explicit. No runtime ABI change. |
| Applicable Rules | Execution, Documentation, Architecture and Coding rules; Source Layout and source policy. Historical evidence remains historical. |
| Verification | Record old/new path manifest and source identity apart from reviewed include/path edits; configure and build x86/x64 with Ninja/ccache and DOS/Win16 with existing tools; run configured tests, dependency/purity and binder checks; refresh three products. |
| Expected Markers | Single production owner per file below src/lib or src/app-mario; no forwarding copies, duplicate includes or symlink bridges. Same controls and DOS/Win16/Win32 behavior. |
| Asset Needs | Existing owner-local tools/SDK/ROM remain private inputs under the S2 provenance contract. No new material or imports. Generated outputs remain ignored; local products remain assets/mario. |
| Reporting Requirements | Report moved-file count, substantive versus path-only changes, tests/builds and product identities. Scope and expected/actual new ROM nodes/edges are empty; no certification promotion. |
| Stop Conditions | Unexpected semantic diff, ownership cycle, missing tool provenance, failed platform build/test, or source duplication. Resolve within scope before claiming closure. |
| Exit Criteria | Source topology and build/include paths migrated; source semantics preserved; applicable suites and target checks pass; three local EXEs refreshed with reviewed evidence. S4 remains planned. |
| Original Owner Request | NXVM-style src/lib/{dos16,win16,win32,kvm}, src/app-mario/{core,kvm}, mirrored tests and per-app assets. Complete Mario/library separation before Mine import. |
| Similar-Issue Sweep | Find stale production paths in CMake, scripts, code generators, includes, purity tests and current authorities; account for every hit, including the newly accepted Win16 save/audio owners. |

S2 owner acceptance is recorded in the proposal. Its obsolete build/probe and
native build outputs were removed; published assets/mario products are retained.
S3 is admitted; source relocation has not yet begun. T44 remains open.

## Current Technical Baseline

The Win32 text adapter has two projections of the same shared text frame.
Normal or visible Console devices that accept output VT use authored RGB SGR.
The hidden no-window 2x4 carrier used by run16 uses indexed sixteen-colour
`CHAR_INFO` output even when it accepts a VT mode bit. Capability selection
does not inspect process identity, window title, launcher, run16 name or game
input; it emits no terminal query and normal Escape remains the text exit key.

## Recent M3 Closures

| Task | Compact result |
| --- | --- |
| T43 | Mario/shared KVM, Win32 and DOS16 owners separated; Win16/Mine receiving contracts prepared. Actual x86/x64 291/291 and 13 real Console routes each pass; DOS MZ/ABI/device evidence passes. Local three EXEs refreshed. Mine import remains future work. [History](../history/M3-T43-mygames-code-unification.md). |
| T42 | DOS Sound Blaster backend closes: unchanged shared frames feed the DOS16 integer renderer, DSP/DMA/IRQ route, and actual DOSBox product PCM capture. DOSBox host sound output remained unavailable in the owner's environment, while run16 is a documented no-device host. [History](../history/M3-T42-dos16-game-music.md). |
| T41 | Text-presentation quality closes: shared DOS/Win32 indexed colour projection, bounded conservative Win32 RGB VT presentation, owner-local tests and private-desktop host integration. x86/x64 283-test matrices and DOS16 link/I/O evidence passed; owner accepted and generated build outputs were removed. [History](../history/M3-T41-text-presentation-quality.md). |
| T40 | Win32 console-session identity and capability presentation close with owner-accepted CMD, graphical-Tab and run16 corpus. Normal/visible devices retain RGB VT; the hidden 2x4 carrier uses the stable standard-colour projection. Zero ROM nodes and edges. [History](../history/M3-T40-win32-console-session-identity.md). |
