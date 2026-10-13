# Project Status

## Current Work

## M3 T44 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation - M3 T44 S5 P1, final platform and host acceptance |
| Admission And Approval | Owner explicitly authorizes automatic S closure/admission; S4 native and ownership gates pass. |
| Objective | Qualify the final app/lib and mirrored-test layout, actual host joins and three local products; close T44. |
| Non-goals | No Mine import, gameplay/PPU change, Win16 Tab, new performance claim or ROM-certification promotion. |
| Reference Baseline | S3 source identities and actual DOS/Win16 links; S4 x86/x64 300/300. Hybrid remains byte-identical to owner-accepted S2. |
| Candidate Proposal | [T44](../proposals/m3/nxvm-source-test-layout.md#s5---final-platform-and-host-acceptance). |
| Files And ABI Surface | Expected zero production changes; final receiving/governance documents and build-only evidence. |
| Applicable Rules | Execution, Documentation, Architecture and Coding; source policy and Source Layout. |
| Verification | Reuse unchanged S4 complete suites; actual private-desktop x86/x64 host routes, DOS device probe, DOS/Win16 link and binder, product headers, purity/topology and documentation gates. |
| Expected Markers | src/lib and src/app-mario have single owners; mirrored test owners; three products only under assets/mario. |
| Asset Needs | Previously qualified owner-local ROM, SDK/compiler and DOSBox inputs only; generated evidence below build and no distribution. |
| Reporting Requirements | Report test/host/build results and product hashes; expected/actual ROM scope empty, no node or edge credit. |
| Stop Conditions | Integration failure, semantic diff or ownership violation must be repaired before closure. |
| Exit Criteria | Scoped gates pass, local products ready, bounded evidence retained, generated workspaces cleaned and only unrelated resource deletions remain unstaged. |
| Original Owner Request | Complete NXVM-style Mario/library split and prepare Mine receiving paths; automatic closure/admission of each S. |
| Similar-Issue Sweep | Check obsolete paths, production/test leakage, caller and fixture discovery, actual host lifecycle and final package identities. |

S1-S4 are closed. S5 is the only active S. The inherited historical source
snapshot binding gaps remain assigned to queued final certification; this
layout task does not certify all ROM behavior.

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
