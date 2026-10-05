# Windows Window And Console Integration

M3 T24 S1-S3 closed after T23. CURRENT is authoritative.

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

## Admitted S plan

| S | Scope and closure | Estimate |
| --- | --- | --- |
| S1 | Parent console startup/borrow/input/Tab/exit restoration,owned/sibling paths;direct interactive CMD waits | Windows entry/launch/console/header,CMake,test/tool,300-500lines |
| S2 | Client-area scaling,aspect sizing,min/max/DPI/repaint | Windows geometry/root and tests,150-300lines |
| S3 | Owned/borrowed console maximize/Restore and joint Tab/input/snapshot/exit | console geometry,test/tool,150-300lines |

Each S begins with its own packet/evidence scope,repairs its findings,builds
three local products,commits before next admission. No game/text/IO artwork
changes,new nodes0. Historical1992/1992,local1991/1992nodes,4260/4261controls
retained. S1 policy changes console-subsystem product entry so CMD waits;
non-shell entry detaches startup console before showing graphics. Borrowed
game buffer preserves shell buffer;input mode/title restored on Tab/error/exit.
No helper process or shell termination. Microsoft primary Win32 Console Screen
Buffers and start documentation support separate buffers and GUI wait limits;
no third-party code imported. Owner-local ROM used only by original builds.

### S1 implementation and evidence boundaries

The product now uses a console-subsystem CRT entry;WinMain still composes the
same graphical game. Direct interactive CMD waits for this process. Non-shell
entry detaches its initial console and shows graphics. Windows may briefly
allocate a console before entry on Explorer launch;no persistent console or
helper process remains. Shell selection checks actual parent membership in
an inherited console;START-created unrelated consoles detach and probe the
parent,while detached-shell launches remain graphical.

Borrowed text opens a separate screen buffer. The device retains the original
buffer,title,input mode and window placement;the original buffer retains font,
palette,cursor and contents. Tab/error/exit restore before detachment and the
same parent is reacquired on re-entry. A long title uses a65536-WCHAR owned
buffer released on every path. No shared gameplay,IO text or DOS policy changes.
Source sweep:AllocConsole/AttachConsole/FreeConsole only occur at launch policy
and text-device lifecycle;root only chooses/cleans presenters. No game worker.

Closing the borrowed host window itself is shared Windows console-close and
may terminate the attached shell;normal Escape/root close never does. Earlier
own-console close probes cannot be relabeled borrowed-shell preservation.
Borrowed probes exit through root/Escape;owned close behavior remains separate.
Inactive-desktop foreground gating is intentional:live Tab injection is not
accepted as evidence there. The embedded root fixture supplies explicit owned
focus and exercises real borrowed-device Tab transitions with unchanged game,
audio and indexed frame. Actual interactive CMD verifies same HWND/one console,
wait until Escape and accepts a following command at the restored prompt.
Three borrowed cycles and an injected acquisition failure verify shell cells,
buffer/cursor/attributes,font,title and input-mode preservation.

Primary references:[Console screen buffers](https://learn.microsoft.com/en-us/windows/console/console-screen-buffers)
and [CMD start/wait semantics](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/start).
They are API evidence,not imported code or source artwork.

### S1 closure

Both widths pass eight focused tests and ten isolated-host groups,including
actual interactive CMD wait/same-console/Escape/following-command and borrowed
buffer/settings/error/Tab restoration. Original DOS16 compiler/link succeeds;
DOS source unchanged and product byte-identical to T23 validated DOSBox build.
Local products364939/313995/322155bytes;package hashes checked against builds.
Product/build/test/tool9files,+270/-15;no ABI or game change.
Historical1992/1992;local1991/1992nodes,4260/4261controls unchanged,new0.
Owner explicitly accepts console-subsystem launch tradeoff after discussing
possible Explorer console flash;retain console subsystem,no helper process.
Live RDP foreground interaction remains outside private-desktop observation.
S2 geometry and S3 console Restore are still pending and T24 stays open.

### S2 closure

Window root now scales the unchanged full bitmap to the positive client area.
Sizing constrains client16:15 integer units;all eight edges/corners and three
DPI parameters pass. Minimum256x240,max work-area fit,real maximize/restore,
programmatic sizes,DPI message and minimized painting pass the embedded root.
Both widths eight focused tests and ten private-host groups pass. Host geometry
restoration is asynchronous;the buffer-preservation probe now waits at most
one second for the original view instead of treating in-flight size as loss.
The other embedded root suppresses the new product CRT entry explicitly.
Product/test4files,+193/-5,no ABI/game change;products364939/317579/325227bytes.
Original DOS16 builds;DOS unchanged,retained byte-identical DOSBox receipt.
Window unit calculations cover96/144/192DPI parameters;actual private-host
monitor tests do not claim a physical multi-monitor DPI drag or live RDP trial.
Historical/local counters unchanged,new0. S3 Restore is next,T24 still open.

### S3 closure and final review

Old-device embedded-root probe fails113 on actual console maximize/Restore;
fixed x86/x64 pass. Both widths pass eight focused tests and eleven host groups.
Each width executes three borrowed opens with three maximize/Restore cycles
per open,plus three owned cycles:12pairs with unchanged font and full4000cell
readback at each phase. Borrowed Tab->graphical resize->Tab preserves original
RAM/game,audio and native pixel storage. Snapshot/P/O and physical-event input
remain covered by the same root fixture;interactive CMD verifies waiting,
Escape and a following prompt command. No user's foreground or global input.

The defect class is host geometry changing the buffer/view outside presentation.
The device repairs nonmaximized80x50view in shrink-view->size-buffer->expand-view
order;maximized host/font remains unchanged and buffer is at least80x50.
A valid in-flight clipped write is retried/deferred with a120attempt ceiling;
invalid handles or persistent failure retain existing recovery. Minimized hosts
skip device drawing. Geometry never requests exit or mutates shared game state.

A second bounded finding was shell restore rounding original view120x30 to
120x29 while buffer120x9001,cursor,attributes and contents stayed unchanged.
The device now captures and explicitly restores original shell cell view after
pixel placement. Thirty repeated lifecycle fixtures pass;both normal and
originally maximized parent probes verify settings/cells/error restoration.
The diagnostic fixture writes neutral dimension failures only below its explicit
ignored output path. All production hits are launch,open/close/present owners;
no shared game/text/DOS artwork,logic,or IO contract changed.

Original DOS16 compiler/link passes. Final DOSBox actual product regression
passes graphics/text roundtrip,held Tab,second text entry,P/O snapshot retained
text mode and Escape to DOS. This is operational proof,not486SX qualification.
Local products364939/318091/325739bytes;package SHA256 equals each build source.
S3 product/test/tool5files,+135/-16,no shared ABI or new ROM credit.

| Final bounded obligation | Disposition |
| --- | --- |
| Direct CMD/same console/automatic wait/prompt restore | Passed actual private interactive CMD |
| PowerShell/pwsh,detached/other launch policy | Passed both-width sibling fixtures |
| Borrowed buffer/font/palette/cursor/title/input/view/error lifetime | Passed normal/maximized parent and30repeat probes |
| Tab/input/snapshot/one game instance | Passed embedded root and actual device fixtures |
| Graphics client paint,8edges,minimum,maximize/restore | Passed root geometry and native host |
| DPI margins/message | Passed96/144/192parameter calculations and native message;physical monitor drag unobserved |
| Actual console SC_MAXIMIZE/SC_RESTORE,owned/borrowed | Passed12pairs per width,all4000cells/font/instance retained |
| Original DOS16 build and DOSBox product | Passed,default graphics retained |
| Live RDP foreground/physical multi-monitor DPI/486SX speed | Not claimed;existing event fixtures/parameter proofs only |

T24 closes its three bounded implementation chains. No pending T24 repair or
new helper process. Owner accepts console-subsystem Explorer flash tradeoff.
Shared borrowed-host Close remains Windows' shared shell-close semantics;
Escape/root exit restores shell without explicitly closing or killing it.
Historical1992/1992;retained local1991/1992nodes,4260/4261feasible controls
(raw4342/infeasible81);M2 final certification remains incomplete. New0.
