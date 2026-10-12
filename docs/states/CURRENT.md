# Project Status

**Active: M3 T40 S2. NTVDM64 run16 console-presentation audit.**

## M3 T40 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of active M3 T40 after S1 closure. |
| Admission And Approval | Owner directed: close S1 and investigate the NTVDM64 run16-only Win32 text color/viewport defect. |
| Objective | Determine why direct cmd.exe text output is correct while the run16-hosted route renders red bricks and a red outside-frame region. |
| Scope | Read-only MySMB Win32 console adapter and owner-local NXVM NTVDM64/run16 host investigation; local diagnostics only below `build/m3-t40-s2/`. |
| Non-goals | No game/ROM/PPU/IO/text-scene semantics, DOS16 product behavior, NTVDM64 source edit, executable packaging, or speculative color repair. |
| Reference Baseline | MySMB selects VT RGB emission when the console output mode accepts virtual-terminal processing; otherwise it uses console palette attributes. Direct cmd.exe is correct; run16 route is not. |
| Candidate Proposal | [Win32 console-session identity](../proposals/m3/win32-console-session-identity.md). |
| Files And ABI Surface | No production ABI change. Diagnostics may inspect Win32 console capabilities and the read-only run16 host path. |
| Applicable Rules | Execution, Architecture, Coding and Documentation rules. |
| Expected Markers | ROM scope `[]`; expectedMatches `[]`; actualMatches `[]`; new `0`; historical `1992/1992` unchanged. |
| Asset Needs | Existing local Win32 and DOS16 toolchains; no ROM or third-party input beyond the normal local product build. |
| Stop Conditions | Any parent/process-name policy lookup on resume, changed shared behavior, new product helper process, lost device cleanup, or inability to prove handle identity. |
| Verification | Compare both launch routes' `GetConsoleMode`, `GetConsoleScreenBufferInfo`, VT capability, window/ConPTY status, palette behavior and one neutral color-cell frame. |
| Exit Criteria | A bounded evidence record identifies the responsible layer and a reproducible repair hypothesis, or proves a host limitation with a concrete compatible fallback. |
| ROM scope | `[]`; zero nodes and zero control edges. |
| Reporting | Report both capability records, identified compatibility boundary, minimal repair options and no ROM-equivalence credit. |
| Reporting Requirements | State that this is platform/host compatibility investigation, not gameplay or NTVDM16 certification. |
| Original Owner Request | “为什么这个游戏在 cmd.exe直接启动画面正常，而通过 ntvdm64项目的run16 mysmb64.exe启动，在console里面，砖块颜色都是红的，而且超出屏幕播放范围的区域全红？” |
| Similar-Issue Sweep | Windows Terminal/ConPTY VT path, classic console palette path, redirected handles, inherited reverse attributes, buffer/view clipping and run16 host allocation. |

## Current Technical Baseline

S1 is closed: it selects text by actual parent-console capability, retains
borrowed sessions across Tab, clears their stale game frames, and closes
temporary owned console sessions on graphics return. S2 now investigates the
reported run16-only host presentation discrepancy without changing production
behavior.
