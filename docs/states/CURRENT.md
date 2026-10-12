# Project Status

**Active: M3 T40 S3. Win32 VT capability and standard Console fallback.**

## M3 T40 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of active M3 T40 after S2 closure. |
| Admission And Approval | Owner directed: “你能支持both VT (64色）和非VT（16色）吗？这样有足够灵活度”。 |
| Objective | Select VT-authored RGB output only after the current output buffer accepts VT mode and its terminal replies to a bounded VT device query; otherwise preserve S2 standard 16-colour Console API output. |
| Scope | `src/platform/win32/text_console.*`, focused Win32 console tests, the S2 proposal record, packet and product artifacts. |
| Non-goals | No game, ROM, PPU, shared IO/text-scene, DOS16, NTVDM64, host configuration, process-name or launcher-specific behavior. |
| Reference Baseline | S2 closed with stable P2 session/geometry behavior and a standard Console `WriteConsoleOutputW` fallback that maps authored slots to fixed 16-colour attributes. |
| Candidate Proposal | [Win32 console-session identity](../proposals/m3/win32-console-session-identity.md#s3-vt-capability-presentation). |
| Files And ABI Surface | Win32-private text-console implementation and test only; no public/shared ABI change. |
| Applicable Rules | Execution, Architecture, Coding and Documentation rules. |
| Expected Markers | ROM scope `[]`; expectedMatches `[]`; actualMatches `[]`; new `0`; historical `1992/1992` unchanged. |
| Asset Needs | Existing x86/x64 Win32 toolchains and retained DOS16 artifact; no ROM or third-party input. |
| Stop Conditions | Any game/shared-IO/DOS16/NTVDM64 change, host setting, helper process, process-name detection, window-title detection, or change to P2 session/geometry semantics. |
| Verification | Focused fixture proves a completed VT device-query reply selects authored RGB, while failed/expired negotiation keeps standard indexed `CHAR_INFO`; x86/x64 builds and focused tests, platform purity, product self-tests and three target artifacts. |
| Exit Criteria | Both paths consume the same neutral text frame; successful VT capability emits authored RGB, failed capability uses standard 16-colour Console API cells; no host identity policy exists and P2 session/geometry behavior remains intact. |
| ROM scope | `[]`; zero nodes and zero control edges. |
| Reporting | Report exact capability selection evidence, both output contracts, touched Win32-only files, build/test/artifact results and no ROM-equivalence credit. |
| Reporting Requirements | State that this is a platform adapter repair, not gameplay or NTVDM16 certification. |
| Original Owner Request | “你能支持both VT (64色）和非VT（16色）吗？这样有足够灵活度”。 |
| Similar-Issue Sweep | VT enabled/disabled negotiation, RGB output ownership, standard indexed fallback, source/canonical palette changes, inherited terminal attributes, clipping/resize and borrowed/owned session switches. |

## Current Technical Baseline

S1 established session ownership. S2 is closed: it retains the P2 hidden-carrier
font/geometry safeguards and, where a Console host ignores a mutable
`ColorTable`, maps authored colours explicitly to standard sixteen-colour
`CHAR_INFO` attributes. S3 adds a capability-only VT path above that fallback;
the platform adapter must not infer a host type from its process, window or
launcher.
