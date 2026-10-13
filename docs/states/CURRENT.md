# Project Status

## Current Work

## M3 T44 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T44 S2 P3 - delivered, awaiting owner acceptance |
| Admission And Approval | Owner inserts this new S2 before the unexecuted directory migration; original source/test/final phases become planned S3/S4/S5. |
| Objective | Establish and implement one local mysmb16.exe with functional DOS MZ graphics/text Tab switching and a native Win3.x NE graphical window entry, now extended by the owner to P/O save/load and music through reusable Win16 libraries. |
| Non-goals | No Win16 Tab switching, text view or DOS-prompt handoff. No source-tree relocation, Mine game import, ROM logic change or Win32 behavior change. Owner accepts the fixed-3000-cycle DOSBox performance limitation; no emulator speed/configuration change to mask it. |
| Reference Baseline | P2 runs the same portable core in an actual Win3.1 enhanced-mode graphical game, receives Start/directional/jump input, ignores Tab and exits to Program Manager. A 720-frame Win16/Win64 RAM/nametable replay and final canonical pixels match. x86/x64 suites each pass 296 tests and thirteen host routes. Standard sixteen-colour VGA has visible colour approximations. MZ image/relocations and resident bounds pass the binder. |
| Candidate Proposal | [M3 T44 proposal](../proposals/m3/nxvm-source-test-layout.md). |
| Files And ABI Surface | Win16 PCM device and file services, shared Mario integer audio renderer, app snapshot/audio integration, NE/MZ build and owned tests. Shared game/PPU semantics remain common. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy, subject to the explicit owner Win16 insertion. |
| Verification | Mine/tool provenance review, format/stub validation, actual Win3.x graphical game launch/input/exit and DOS graphics/text Tab regression. Win16 Tab must not initiate a presenter or process switch. Verify P/O round trip and rejected corrupt loads; synthetic PCM and actual driver output; missing audio device, reset/focus and teardown. |
| Expected Markers | DOS executes the original MZ game with both presenters; Win3.x selects a native NE graphical entry and remains in its graphical window. |
| Asset Needs | Owner-local Mine reference is pinned by exact file hashes in the proposal; no Git revision or redistribution permission is claimed. Owner-local ROM, compiler/SDK and Windows runtime are local-only test/build inputs, with tool/library hashes in the proposal. Protected data and tool binaries are not committed. |
| Reporting Requirements | Report DOS dual-mode and native Win16 graphical-window evidence separately, including tested Windows versions, input, exit and MZ resident bounds. Prompt switching remains deferred. |
| Stop Conditions | Forked gameplay, copied unreviewed sibling/vendor material, DOS stub replaced by a message-only stub, generated binaries staged or unverified state continuity claims. |
| Exit Criteria | Functional DOS graphics/text switching and native Win3.x graphical game entry of the same dual-format product are verified. Win16 now also requires P/O save/load and waveform music output, with the related reusable libraries. No Tab/text/prompt support is required. |
| Original Owner Request | Same mysmb16.exe retains DOS Tab and opens a graphical window on Win3.x; research Tab to a DOS text prompt, like Mine NE/MZ packaging. |
| Similar-Issue Sweep | Inspect EXE/stub sizes and offsets, far/near Win16 ABI, timer/input/video ownership, snapshot/state handoff and cleanup of both launch routes. |

P3 result: Win16 P/O uses the shared snapshot contract, and its new reusable
waveform/file libraries are connected. Actual Win3.1 save/restore matches
core and presentation bytes; the final product rejects a corrupt slot,
saves/loads and exits successfully. Game and post-load PCM are captured,
with low-cycle gaps explicitly retained. Each native width passes 299 tests
plus one unavailable host-audio skip. All three local EXEs are refreshed;
ROM core/PPU and node/edge credit remain unchanged. S3 is not admitted.

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
