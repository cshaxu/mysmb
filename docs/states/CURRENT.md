# Project Status

**Active: M3 T41 S1. Win32 Console API palette presentation.**

## M3 T41 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New owner-directed M3 T41 S1. M3 T40 S2 is suspended and retained in the queue. |
| Admission And Approval | Owner directed: “始终使用 Console API 设置 16 项调色板，再输出带颜色索引的字符格，不因为 VT 开启成功就改发 RGB。” |
| Objective | Replace the Win32 VT-RGB text renderer with one Console API palette/index output path. |
| Scope | `src/platform/win32/text_console.*`, its focused platform tests and required composition declarations. |
| Non-goals | No game/ROM/PPU/IO/text-scene semantics, DOS16 behavior, console-host configuration, NTVDM64 source edit or process changes. |
| Reference Baseline | The current adapter enables VT output and then emits RGB escape sequences; otherwise it sets a 16-slot console palette and uses indexed `CHAR_INFO` cells. |
| Candidate Proposal | [Win32 Console API palette presentation](../proposals/m3/win32-console-palette-api.md). |
| Files And ABI Surface | Win32-only private text-console implementation and tests; no shared or public ABI change. |
| Applicable Rules | Execution, Architecture, Coding and Documentation rules. |
| Expected Markers | ROM scope `[]`; expectedMatches `[]`; actualMatches `[]`; new `0`; historical `1992/1992` unchanged. |
| Asset Needs | Existing local Win32 and DOS16 toolchains; no ROM or third-party input. |
| Stop Conditions | Any shared game/IO/DOS source edit, host configuration change, product helper process, loss of console-session identity, or palette/index test unable to distinguish an RGB stream. |
| Verification | Focused console-capability and text-switch tests force successful VT negotiation and verify all 16 Console API palette entries, indexed `CHAR_INFO` attributes, and absence of `WriteConsoleW` escape output; then run platform purity, x86/x64 build/test and the DOS16 route. |
| Exit Criteria | Both Win32 targets use the same API palette/index renderer with successful and failed VT-mode negotiation; no RGB escape renderer remains reachable. |
| ROM scope | `[]`; zero nodes and zero control edges. |
| Reporting | Report exact palette/index selection evidence, the 16-slot mapping, touched Win32-only files, test/build result and no ROM-equivalence credit. |
| Reporting Requirements | State that this is a platform adapter repair, not gameplay or NTVDM16 certification. |
| Original Owner Request | “始终使用 Console API 设置 16 项调色板，再输出带颜色索引的字符格，不因为 VT 开启成功就改发 RGB。” |
| Similar-Issue Sweep | Successful/failed VT-mode negotiation, classic console and ConPTY-style handles, source palette changes, canonical palette, inherited reverse attributes, clipping/resize and borrowed/owned session switches. |

## Current Technical Baseline

M3 T40 S1 is closed: it selects text by actual parent-console capability,
retains borrowed sessions across Tab, clears stale game frames, and closes
temporary owned console sessions on graphics return. M3 T40 S2 remains
suspended in the queue. M3 T41 S1 fixes the now identified incompatible
VT-RGB output selection entirely within the Win32 adapter.
