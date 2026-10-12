# Project Status

**Active: M3 T40 S2. Win32 Console API palette presentation.**

## M3 T40 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of active M3 T40 after S1 closure. |
| Admission And Approval | Owner directed: “始终使用 Console API 设置 16 项调色板，再输出带颜色索引的字符格，不因为 VT 开启成功就改发 RGB。” |
| Objective | Replace the Win32 VT-RGB text renderer with one Console API palette/index output path, resolving the bounded run16 presentation defect without a host-specific branch. |
| Scope | `src/platform/win32/text_console.*`, its focused platform tests and required composition declarations. |
| Non-goals | No game/ROM/PPU/IO/text-scene semantics, DOS16 behavior, console-host configuration, NTVDM64 source edit or process changes. |
| Reference Baseline | The adapter enables VT output and emits RGB escape sequences when successful; otherwise it sets a 16-slot console palette and uses indexed `CHAR_INFO` cells. The first API-palette package exposed an unrelated hidden-console font-fit race: run16's NTVWM captures its 2x4 carrier while MySMB was changing it to a visible Console font. A later unconditional exclusive-bound conversion fixed that carrier but made standard Console palette writes fail. |
| Candidate Proposal | [Win32 console-session identity](../proposals/m3/win32-console-session-identity.md#s2-console-api-paletteindex-renderer). |
| Files And ABI Surface | Win32-only private text-console implementation and tests; no shared or public ABI change. |
| Applicable Rules | Execution, Architecture, Coding and Documentation rules. |
| Expected Markers | ROM scope `[]`; expectedMatches `[]`; actualMatches `[]`; new `0`; historical `1992/1992` unchanged. |
| Asset Needs | Existing local Win32 and DOS16 toolchains; no ROM or third-party input. |
| Stop Conditions | Any shared game/IO/DOS source edit, host configuration change, product helper process, loss of console-session identity, palette/index test unable to distinguish an RGB stream, or a hidden carrier requiring a different geometry protocol. |
| Verification | Focused console-capability and text-switch tests force successful VT negotiation and verify all 16 Console API palette entries, indexed `CHAR_INFO` attributes, absence of `WriteConsoleW` escape output, native inclusive and 2x4-carrier exclusive bounds, and no font mutation for a hidden carrier; then run platform purity, x86/x64 build/test and a bounded run16 probe. |
| Exit Criteria | Both Win32 targets use the same API palette/index renderer with successful and failed VT-mode negotiation; no RGB escape renderer remains reachable; native Console uses its inclusive bounds, an identified 2x4 carrier uses exclusive bounds, and a bounded hidden run16 probe survives the former worker-failure interval without a malformed viewport. |
| ROM scope | `[]`; zero nodes and zero control edges. |
| Reporting | Report exact palette/index selection evidence, the 16-slot mapping, touched Win32-only files, test/build result and no ROM-equivalence credit. |
| Reporting Requirements | State that this is a platform adapter repair, not gameplay or NTVDM16 certification. |
| Original Owner Request | “始终使用 Console API 设置 16 项调色板，再输出带颜色索引的字符格，不因为 VT 开启成功就改发 RGB。” |
| Similar-Issue Sweep | Successful/failed VT-mode negotiation, classic console and ConPTY-style handles, source palette changes, canonical palette, inherited reverse attributes, clipping/resize and borrowed/owned session switches. |

## Current Technical Baseline

S1 is closed: it selects text by actual parent-console capability, retains
borrowed sessions across Tab, clears stale game frames, and closes temporary
owned console sessions on graphics return. S2 now replaces the VT-RGB frame
output selection with one Console API palette/index implementation. Its first
package exposed a hidden-carrier font/geometry race in run16; the active repair
preserves that carrier font and suppresses non-window geometry probes. Palette
updates use the native inclusive bounds except for an identified 2x4 hidden
carrier, whose documented setter requires exclusive right/bottom bounds.
