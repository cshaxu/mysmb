# M3 T5 DOS16 Composition Root

## Outcome

`mysmb_dos16_root` is the first real-mode composition contract.  One step
reads buttons through a DOS-owned hook, calls the existing native game tick,
builds one neutral render frame, derives VGA and colored-text frames, and
submits both through DOS-owned presentation hooks.  It creates no alternate
logic or scheduler.

## Ownership

The game layer remains unaware of DOS.  `mysmb_dos16_hooks` is the only
platform boundary: future BIOS keyboard/timer polling and VGA/text memory
writes belong to its callbacks.  The root owns the translated game state,
frame adapters, and caller-provided VGA pages.  The test host proves the
order with mock hooks and verifies exactly one VGA and text presentation per
step.

## Toolchain Link Evidence

The local OpenNT bundle contains `cl16.exe` and `link16.exe`; it successfully
compiles the game, render, text-frame, VGA-frame, and DOS-root units.  Its
supplied tree contains no 16-bit C runtime library directory, so a valid MZ
link command cannot be formed from local material.  No fabricated executable
or third-party runtime is introduced.  Restoring a reviewed DOS runtime and
linking it is admitted separately as M3 T6.

## Similar-Issue Sweep

The DOS root, hooks, and smoke test were searched for game-RAM access outside
the game API, DOS API leakage into `src/game`, duplicate tick paths,
host-owned game mutation, and protected asset references.  The only tick is
the root's call to `mysmb_game_tick`; production hooks do not yet perform
hardware writes.  Game state is initialized only by the game API.  No
production hit or protected asset was found.

## Verification

- ROM-free CTest: 27 of 27 passed.
- Owner-local CTest: 29 of 29 passed.
- Win32 x86 and x64 builds passed.
- OpenNT large-model target compiled the DOS root and all frame adapters.
- Documentation governance and `git diff --check` passed.

