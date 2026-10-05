# Windows Window And Console Integration

Owner retains this queue-head candidate for admission as T24 after the
interposed T23 princess repair. Not active;CURRENT is authoritative.

Owner expands this same candidate to cover graphical window scaling/aspect
and console maximize/restore. Keep these issues in one integration proposal.

## Problem And Required Behavior

Launching the Windows product from cmd.exe selects text but opens a separate
console. The current text_console open path unconditionally calls AllocConsole;
the current launch policy only probes the parent console temporarily. This
implements the earlier own-console design,not the owner's requested integration.

Use the invoking CMD console for text presentation when it is available;do not
open another console window. Escape exits the game and returns a usable CMD
prompt. Tab switches graphics/text on the same game instance;returning to text
reuses that console. Explorer/other launchers retain graphical startup and DOS
retains graphical startup. No additional production process or game logic.

In graphical mode,the displayed game must grow and shrink with the client
area. Resizing must preserve the game's width/height ratio;dragging just a
horizontal or vertical edge must adjust the other dimension correspondingly.
Do not accept distortion,cropping or unused black/colored client-area borders
as the aspect-ratio solution. Account for non-client borders/title bar:the
ratio applies to the drawable client area,not the outer window rectangle.

In text mode,maximize already works and keeps the same80x50game presentation
and character size. Preserve that working behavior;the owner is not requesting
that text scale up to fill the maximized host. The specific defect occurs when
the user clicks the Windows title-bar Restore button at the upper right:
console presentation fails/closes and the game falls back to its graphical
window. This is not a reported whole-game process exit. Restore must leave the
same game in text mode with its complete80x50view at the usable restored size.
This host geometry operation must not become a presenter switch or exit request.

The owner requirement supersedes the own-console design for this admitted
repair's future implementation. Update Architecture and related lifecycle
documentation when implementing;this candidate does not silently rewrite the
current technical baseline. Also audit the existing PowerShell shell-launch
path for the same defect class and state its supported behavior explicitly.

## Proposed Bounded Work

The planned bounded delivery chains are parent-console lifetime,graphical
window geometry/scaling,and console maximize/restore,followed by their joint
Tab/input/exit regression. Assign S identifiers and final file/size estimates
at admission;each S reports its scope before changing code. The first chain is
launch policy -> console acquisition -> presentation/input ownership -> Tab
-> normal/error exit and restoration. Distinguish a borrowed
parent console from a game-owned console. Consider a separate game screen
buffer within the parent console so the shell's contents and buffer remain
available for restoration;attachment alone is insufficient acceptance.

Preserve and restore every borrowed setting actually changed,including active
buffer,input mode,title and any font/color/cursor/window geometry. Shell and
game must not compete for keyboard input or interleave prompt/game output.
Investigate direct invocation and waiting invocation explicitly;do not assume
a GUI-subsystem executable makes CMD wait. Record any launch limitation before
closure rather than masking it with a new helper process.

Keep console ownership/lifetime in Windows adapters and composition roots.
Shared game/text cells remain unchanged. Console-close handling must respect
borrowed versus owned host lifetime;game cleanup must not explicitly terminate
or close the parent shell. Retain Escape,Tab,P/O,focus and RDP input behavior.

For graphical geometry,inspect current size messages,client rectangle usage,
bitmap destination rectangles and repaint scheduling. Enforce the existing
game-image ratio at the window sizing boundary and use the resulting client
rectangle for whole-frame scaling. Cover all edge/corner drags,minimum size,
maximize/restore and DPI changes. Maximum geometry must fit the available
work area while retaining the ratio;do not achieve this by adding presenter
letterboxing. Minimize/zero-sized clients must not cause invalid drawing or exit.

For console geometry,reproduce the actual title-bar Restore operation after
maximize,including its host size-event sequence;Tab or an arbitrary manual
resize is not equivalent evidence. Distinguish transient host resize
notifications from an actual device failure. Inspect buffer/window/font dimensions and the restore
rectangle before writing the80x50frame. Normalize the restored view using
current cell metrics and valid buffer/window sizing order;do not interpret a
temporary clipped write during resize as permission to exit or switch modes.
Retain the original usable restored geometry across repeated maximize/restore
and Tab cycles,and restore the shell's own geometry on game exit. Cover both
borrowed-parent and game-owned consoles;no artwork or game state belongs here.

## Acceptance And Delivery

- x86/x64 direct CMD launch uses the same console and creates no new console
  window;game input and shell ownership are coherent.
- Text -> graphics -> text reuses the borrowed console,with one game instance.
- Escape,initialization failure and presentation recovery restore shell state,
  original contents and a working prompt without terminating CMD.
- Own-console Explorer/other-launcher paths and shell-launch sibling paths have
  explicit regression results;shared console-close behavior is documented.
- Graphical content tracks client-area resizing immediately and fills the
  client area without stretch/crop/unused borders;edge/corner drags retain the
  game-image ratio on both x86/x64,including maximum/minimum and restored sizes.
- Maximize preserves the currently working80x50presentation and character
  size. Repeated clicks on the Windows upper-right Restore button retain text
  mode,the same game instance,and a fully visible80x50view;the console must not
  fail/close or fall back to graphics. Check the actual restore-button path.
- Joint sequences CMD text -> maximize -> restore -> Tab graphics -> resize
  -> Tab text -> maximize -> restore -> Escape preserve input,snapshot,focus
  behavior and return the shell to its original state. Check ordinary desktop,
  applicable DPI/font configurations and RDP resize delivery separately.
- Use owned isolated host probes;no desktop focus or global keyboard injection.
- Run focused geometry/resize/input/startup/Tab/snapshot/lifetime tests,platform purity and
  original DOS16 build. Product changes refresh all three local EXEs;no ROM or
  ROM-derived product is committed. All temporary evidence stays under build.

At admission report the final component scope and size estimate and register
the receiving S under MTSP. This platform-lifecycle repair earns no new ROM
node/control certification credit. Existing suspended audio and deferred M2
verification remain behind this candidate in the queue.
