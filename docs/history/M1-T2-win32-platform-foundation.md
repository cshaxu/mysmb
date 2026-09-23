# M1 T2 Win32 Platform Foundation

## Outcome

T2 establishes `mysmb_game` as a host-free C90 core, a neutral input/frame
contract, `mysmb_win32` as the first native window product, and
`mysmb_dos16_core` as the separately named future DOS compiler input. The
window uses a fixed 60 Hz QueryPerformanceCounter loop and a non-ROM smoke
scene; it contains no NES CPU, PPU, or APU emulation.

## Evidence

- S1 task sequence: `e6a6859`.
- S2 implementation: `62e2d22`.
- Default MinGW build produces `mysmb-win32-x64.exe`, confirmed by objdump as
  `pei-x86-64`; CTest `mysmb.core-smoke` passes.
- The MinGW32 build produces `mysmb-win32-x86.exe`, confirmed as `pei-i386`;
  its CTest smoke also passes.
- `rg` finds the only `windows.h` inclusion under `src/platform/win32`; no
  platform macro appears beneath `src/game`.
- The inspected OpenNT checkout contains source and SDK layout but no discovered
  built `cl.exe`, `link.exe`, `nmake.exe`, `wcc.exe`, or `wcl.exe`. Its 16-bit
  large-model compile remains a local tooling prerequisite, not a claim of
  passing compatibility.

## Transfer

T3 admits the owner-local ROM and reviewed disassembly only to implement the
static C source pipeline. T2's core and target boundaries must remain intact.
