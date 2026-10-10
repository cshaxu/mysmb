# Project Status

**Active: M3 T40 S1. Win32 console-session identity repair.**

## M3 T40 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New corrective M3 task after closed M3 T39. |
| Admission And Approval | Owner directed repair: retain the actual attached console session across Tab text/window switches; parent-shell discovery is forbidden on resume. |
| Objective | Make graphical/text presenter switching resume the first successful Win32 console object rather than detach and heuristically attach a new shell console. |
| Scope | `src/platform/win32` console lifecycle and composition root; focused platform tests and product build evidence. |
| Non-goals | No game/ROM/PPU/IO/text semantics, DOS16, product process creation, or host console configuration. |
| Reference Baseline | The existing close path calls `FreeConsole`; later Tab calls `mysmb_win32_start_in_text`, which used a shell-name whitelist before attaching a different console. |
| Candidate Proposal | [Win32 console-session identity](../proposals/m3/win32-console-session-identity.md). |
| Files And ABI Surface | Win32 console object, root presenter switching and project-owned Win32 lifecycle fixtures only. |
| Applicable Rules | Execution, Architecture, Coding and Documentation rules. |
| Expected Markers | ROM scope `[]`; expectedMatches `[]`; actualMatches `[]`; new `0`; historical `1992/1992` unchanged. |
| Asset Needs | Existing local Win32 and DOS16 toolchains; no ROM or third-party input beyond the normal local product build. |
| Stop Conditions | Any parent/process-name policy lookup on resume, changed shared behavior, new product helper process, lost device cleanup, or inability to prove handle identity. |
| Verification | Handle-identity and acquisition-count fixture for owned/borrowed cycles; existing text-switch, launch-policy and parent-console tests; x86/x64 builds, DOS16 link, platform purity and refreshed products. |
| Exit Criteria | Repeated text -> graphics -> text cycles resume the same console object without `AttachConsole`/`AllocConsole` or parent-name discovery; genuine device loss and shutdown still close safely. |
| ROM scope | `[]`; zero nodes and zero control edges. |
| Reporting | Report actual changed component size, same-handle/acquisition evidence, both console ownership modes, builds/artifacts and any retained host limitation. |
| Reporting Requirements | State that this is platform lifecycle work, not ROM-equivalence credit. |
| Original Owner Request | “当前win32，tab从console切换到window的时候，没有保存当前附着的console的句柄，以至于从window再返回console的时候，会去hardcode找cmd和powershell的console去attach。这种特判是极其错误的”。 |
| Similar-Issue Sweep | Initial console selection, asynchronous owned acquisition, borrowed buffer restore, terminal/ConPTY host capability, presenter-loss fallback and shutdown cleanup. |

## Current Technical Baseline

The Win32 product currently distinguishes initial shell-launch selection from
text-device operation, but it incorrectly destroys an established console
object on a normal Tab return to graphics.  M3 T40 S1 changes only that
platform lifecycle boundary.
