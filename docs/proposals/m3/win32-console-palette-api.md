# M3 T41: Win32 Console API palette presentation

## Problem

The current Win32 text adapter treats successful enabling of virtual-terminal
output as permission to emit true-RGB escape sequences. That is a host-policy
decision, not a MySMB presentation requirement. A console hosted through
NTVDM64/run16 can accept the mode call while forwarding or interpreting the
RGB stream differently from a direct cmd.exe launch; color slots and the
region outside the intended 80-column frame then render incorrectly.

## Required behavior

Every Win32 text frame uses the Console API path:

1. Set all sixteen `CONSOLE_SCREEN_BUFFER_INFOEX.ColorTable` entries from the
   frame palette.
2. Encode each `CHAR_INFO.Attributes` value as the frame's four-bit foreground
   and background color indices.
3. Submit the bounded 80×25 or 80×50 character grid with
   `WriteConsoleOutputW`.

Successful `ENABLE_VIRTUAL_TERMINAL_PROCESSING` negotiation must not select
an RGB escape-stream renderer. The adapter may retain ordinary console input
mode negotiation, but it must not emit `WriteConsoleW` color sequences or
depend on terminal escape interpretation for game pixels.

## S1: palette/index renderer

- Remove the VT-RGB output selection and its dynamically allocated terminal
  stream buffer from the Win32 text-console ownership path.
- Apply the complete 16-entry palette through
  `SetConsoleScreenBufferInfoEx` for every new source palette, including the
  initial canonical palette.
- Always construct the existing `CHAR_INFO` grid from character glyphs plus
  four-bit foreground/background indices, then use `WriteConsoleOutputW`.
- Preserve current geometry, parent-console identity, Tab suspend/resume,
  input, close and output-loss behavior.
- Extend the platform fixture to make VT mode negotiation succeed and prove
  that the API palette/index path is still selected. It must reject any RGB
  escape write, and verify all sixteen palette entries and representative
  foreground/background index attributes.

## Boundaries

Only `src/platform/win32/text_console.*`, its Win32-only tests and necessary
composition declarations may change. This task changes neither game logic,
ROM/PPU/text-scene semantics, DOS16 behavior, console host configuration nor
the external NTVDM64 project. It receives zero ROM nodes and zero control
edges.

## Acceptance

The Win32 adapter must use one palette/index implementation whether VT mode
enabling succeeds or fails. Focused x86/x64 capability tests must prove this
selection and the exact 16-slot/attribute contract. Product changes require
platform-purity checks, x86/x64 builds and tests, the unchanged DOS16 build
route, and refreshed local target artifacts.
