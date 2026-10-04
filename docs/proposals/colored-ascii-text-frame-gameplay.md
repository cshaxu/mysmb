# Candidate: colored ASCII text-frame gameplay and presentation switching

Owner scheduling amendment (P153):remaining M2 acceptance verification is
queued after the three I/O/presentation candidates. Earlier proof completion
prerequisites are superseded by this explicit order;retain scoped evidence and
rebind affected dependencies at admission. This does not certify M2.

## Purpose and queue position

Replace the common I/O text placeholder with a playable 80x50 character
scene. Each cell has a printable ASCII character and foreground/background
color. The same cell grid feeds the DOS16 text-mode adapter and the Win32
console adapter. Implement bidirectional switching between DOS16 graphics and
text modes, and between the one Win32 GUI executable's graphical window and
its console window. This is an unnumbered T candidate at the queue tail,
after the shared I/O graphic-frame task and the queued quick-snapshot task.
Its S slots below are a forecast, not admitted work or ROM-node credit.

The preceding I/O task establishes the 256x240 graphic-frame path, a stable
`src/io` boundary, an inert 80x50 text-frame type, and an operational DOS16
graphical executable. It does not need to provide playable text or a mode
switch. This candidate turns that placeholder into the second presentation
without altering the translated game's 60 Hz logic, original RAM semantics,
controller meaning, audio command order, or the graphical output.

## Shared text picture

`src/io` owns a bounded 80x50 cell frame and deterministic game-scene-to-cell
conversion. A cell contains one 7-bit printable ASCII code (`0x20`-`0x7e`)
and portable foreground/background color values. The mapping must be legible
without color and improve recognition with color. It draws the title/menu,
world and HUD, terrain and interactive blocks, Mario/Luigi, enemies,
projectiles, moving objects, effects, pause, death, and end-state scenes from
game-owned identities and visible state. Priority, clipping, scrolling,
animation, and object disappearance follow the current game frame. Do not
derive characters from pixel luminance or make the text renderer infer game
logic from a low-resolution bitmap.

The admission design first identifies the existing neutral scene/object
commands or read-only game state needed for those identities. Any additional
read-only presentation data crosses an explicit shared contract; it must not
duplicate ROM control flow or become a second gameplay model. Text-frame
storage and conversion must fit DOS16's memory model without a large stack
allocation or a segment-unsafe array access. Both hosts consume identical
cell contents before adapting color attributes to their display APIs.

## Runtime switching

- Use F1 as the common presentation toggle unless the admission review finds
  an existing conflicting key contract. DOS16 changes between its supported
  graphics mode and VGA 80x50 text mode in one executable. Win32 keeps one
  GUI-subsystem executable and one game/audio instance, showing a real console
  text window in text mode and returning to its graphical window on F1.
- Switching changes only the active presenter and physical-key source. It
  neither resets the game nor adds/skips a logical tick, replays APU writes,
  changes pause/Enter semantics, or duplicates audio output. Only the active
  presenter performs device writes; no BIOS mode reset occurs every frame.
- A focus transition caused by the program's own window switch must not
  synthesize START or consume keys from another application. Held F1 is one
  toggle. Console close/detach and unavailable 80x50 mode have safe behavior:
  return to or retain the working graphical presentation without disturbing
  gameplay. Existing P/O snapshot shortcuts remain available in both views.

## Planned S decomposition

| Planned S | Bounded deliverable | ROM-node scope / expected new matches |
| --- | --- | --- |
| S1 | Audit game-visible semantic sources; fix the `src/io` 80x50 cell, color, layering, scrolling, and ASCII glyph contract with bounded DOS16 storage. | 0 / 0 |
| S2 | Implement deterministic object-aware terrain, actor, effect, and HUD-to-cell conversion with focused overlap, clipping, color, and monochrome-legibility checks. | 0 / 0 |
| S3 | Complete title/menu, pause, death, warp, and terminal text scenes; verify representative full-route frame sequences against the game-owned visible state. | 0 / 0 |
| S4 | Implement DOS16 graphical/text-mode F1 switching and 80x50 text presentation with safe mode setup, keyboard continuity, and real DOS runtime checks. | 0 / 0 |
| S5 | Implement Win32 GUI/console F1 switching in one executable, console cell/color output, focus/input transfer, close/failure recovery, and audio continuity on x86/x64. | 0 / 0 |
| S6 | Run integrated DOS16 and Win32 playable text routes, graphics/text round trips, snapshot P/O in both modes, frame/audio continuity, 16-bit memory/performance, and three-target regression. | 0 / 0 |

At admission, rebase the S forecast against the completed I/O and snapshot
contracts and register each infrastructure S with exact empty ROM-node scope
and zero expected matches. A discovered translated-logic mismatch needs its
own source-proof owner; this text presentation earns no ROM-node or graph-edge
credit by looking similar to the original graphics.

## Acceptance

1. DOS16 and Win32 display the same deterministic 80x50 ASCII/color cell
   scene for the same game state. The scene remains readable without color and
   covers title, sustained gameplay, major object interactions, pause, death,
   and completion, rather than showing a placeholder or a luminance filter.
2. F1 switches DOS16 graphics/text and Win32 GUI/console in both directions
   during gameplay. The game, audio, input, and frame count continue across
   repeated switches; returning to graphics reproduces the current 256x240
   frame rather than restarting or displaying stale pixels.
3. Console focus, held keys, Enter/pause, P/O snapshots, console closure, and
   unavailable text-mode setup behave safely and do not create a second game
   instance or double-submit a game tick or audio event.
4. Focused cell-rendering and mode-transition tests, Win32 x86/x64 builds and
   interactive checks, the real DOS16 link and graphics-capable DOS runtime
   route, platform-purity review, and 16-bit memory/performance checks pass.
   Owner-local ROM data and derived output remain local and untracked.
