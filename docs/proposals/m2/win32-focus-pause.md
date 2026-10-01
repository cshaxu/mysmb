# M2 candidate: Win32 focus-loss pause

## Purpose and queue status

The owner requests that losing focus in the Win32 x86/x64 game pause the
ongoing game as an Enter/START press would. Regaining focus must not resume it;
the player must release and press Enter again. If Enter does not mean pause in
the current game state, focus loss must not create a START action. This is one
unnumbered future T candidate. It is not part of the active current-equivalence
packet, and its planned S slots are not admitted work.

The present `src/platform/win32/main_win32.c` polls `GetAsyncKeyState` every
frame, maps Enter to `MYSMB_BUTTON_START`, and has no focus handling. The shared
`src/game/frame_root.c` consumes START in `PauseRoutine` only when operating
mode is 2, or mode is 1 with task 3. Its pause timer, controller mask, pause
status and held-key latch can delay or suppress a press. In title mode,
`src/game/title_modes.c` instead uses START to begin play; game-over mode can
also consume START for termination. A window-only mode guess or unconditional
synthetic START would be incorrect.

## Behavior contract

1. On focus loss, capture a pause request only if the started shared game is
   currently in a START-to-pause mode and is not already paused. Repeated
   focus messages must not create multiple requests. Other modes receive no
   synthetic START, including title/bootstrap, game-over and game setup.
2. Before each attempted synthetic input frame, ask a **read-only shared-game
   query** for the same mode/task, paused, timer and START-latch eligibility
   used by `PauseRoutine` and `ReadJoypads`. Do not replicate RAM offsets or
   pause rules in the Win32 adapter. Cancel the request if START no longer
   denotes pause; finish it if the game became paused independently.
3. If the existing pause timer or input latch blocks START, supply neutral
   input and retain the request while the shared 60 Hz ticks continue. Once
   eligible, supply exactly one START pulse through `struct mysmb_input` and
   confirm that the shared pause state actually changed to paused. Never write
   original RAM or call a game routine directly from the platform adapter.
   Record the bounded delay caused by the current 0x2b-frame pause timer in
   acceptance evidence; do not claim an ignored START immediately paused.
4. While unfocused, do not forward `GetAsyncKeyState` results from keys used
   in another application. On focus restoration, send no automatic START and
   do not replay a key held across the focus boundary. A fresh physical Enter
   press after release is required to resume. If focus returns before a
   pending pause is accepted, finish or cancel the request under rule 2 before
   accepting a manual unpause press. Keep the message pump and existing
   frame-cap behavior responsive.
5. This is Win32 host input policy for both x86 and x64. Shared translated
   pause logic, DOS input behavior and ROM-node conformance semantics remain
   unchanged. Minimize/restore, Alt+Tab, click-away/return and repeated
   activation messages follow the same rules.

Use `WM_KILLFOCUS`/`WM_SETFOCUS` for keyboard-focus transitions and
`WM_ACTIVATEAPP` for application deactivation/activation where needed;
deduplicate messages from the same transition. The frame loop owns synthetic
input and result checks. Avoid performing a game tick or activating another
window inside the window procedure. The event choice follows Microsoft's
[keyboard focus](https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-killfocus)
and [application activation](https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-activateapp)
contracts; the background-key filter accounts for the current
[`GetAsyncKeyState` polling](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate).

## Planned S decomposition

| Planned S | Scope and output | Primary ROM-node estimate | Expected new ROM matches |
| --- | --- | ---: | ---: |
| S1 | Define the shared read-only START/pause eligibility and paused-state contract, including cooldown and controller-latch cases; add focused contract tests without changing translated behavior. | 0 | 0 |
| S2 | Implement Win32 focus transition, pending one-shot START, physical-key filtering and manual-resume arming; verify x86/x64 integrated behavior and close the T with an exact outcome report. | 0 | 0 |

At admission, rebase the historical and current-equivalence counts, register
each S in the node/task ledger with an explicit empty node scope and forecast,
pin the existing pause route evidence, and record named focused checks. This
candidate claims no original-ROM node or graph-edge credit. Any discovered
shared-game semantic defect needs separately scoped admission; this host
feature may not silently alter `PauseRoutine` to make focus handling pass.

## Acceptance matrix

| Case | Required result |
| --- | --- |
| Title, boot/setup, game over | Focus loss/restoration never starts play, selects a menu action or terminates a game. Other-application keys are not forwarded while unfocused. |
| Running game mode 1/task 3 | One focus loss eventually yields exactly one real shared-game pause transition and pause sound; a focus return leaves it paused. |
| Victory mode 2 | Same pause semantics as the existing shared routine, without adding a separate platform pause state. |
| Already paused | Focus loss and return do not toggle or unpause. |
| Pause cooldown or START latch active | The request waits through neutral frames, is rechecked before delivery, and is recorded complete only when pause state changes. |
| Mode changes before delivery | Pending input is canceled; no delayed START can start a title or trigger game-over behavior. |
| Enter held across loss/return; rapid repeated focus changes | No accidental resume, no second pause toggle, no duplicate pulse; only release followed by a new focused Enter press resumes. |
| Four-frame catch-up and minimized window | One-shot input remains one-shot across all logical ticks; the loop remains responsive and catches up under its existing cap. |

Run the existing shared `mysmb.pause-root-smoke` and relevant NMI/input focused
tests, add a focused Win32 host-state test, build and run the x86 and x64
products and their self-tests, and perform an actual-window focus/restore smoke
for each architecture. Verify the shared DOS16 link and platform-purity gate.
The admission packet chooses the exact commands and current reference route.
Any product-code P refreshes and reports all three locally built executables
under the M2 artifact rule; protected or owner-local artifacts stay untracked.

## Boundaries and evidence

`game/` owns the meaning and state of pause; `platform/win32` owns focus
messages, physical-key filtering and neutral input delivery. The proposal
introduces no ROM or third-party material. Record the original focus state,
mode/task, pause eligibility, pending state, injected input count, resulting
pause state and x86/x64 outcome in neutral test evidence. Keep temporary logs
and build outputs below ignored `build/`. Do not treat a queued proposal as an
implemented or admitted feature.
