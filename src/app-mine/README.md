# Mine

Independent Minesweeper rules and procedural artwork, assembled through the
shared KVM and DOS16/Win16/Win32 devices. No Mario or owner-ROM dependency.

Configure the root with `MYGAMES_BUILD_MARIO=OFF` and `MYGAMES_BUILD_MINE=ON`.
Use Ninja and the ccache compiler launcher. Each compiler width builds its own
mine32.exe or mine64.exe. `tools/Build-Mine16.ps1` compiles with the qualified
small-model DOS toolchain and an explicitly supplied Win16 SDK/CRT; its
LinkOnly pass binds the DOS MZ and Windows NE entries into mine16.exe.
Local products live under assets/mine and are not tracked.

Win32/x64 borrow a parent Console for text; graphical launch opens a window.
Tab switches over one game state; --text/--window override initial selection.
DOS uses80x25 text and requires an installed mouse driver. Win3.x opens a
window and Tab selects text within that window. It does not launch a DOS prompt.

Left release opens; right cycles flag/question/clear; both buttons or middle
perform a chord. F2/N starts again,1/2/3 select difficulty,M toggles questions,
F1/H shows help,Q exits; Esc dismisses an overlay before exiting. Mouse gestures
cancel at focus/capture/view boundaries. Updates are input/clock driven.

## Source disposition

Owner approved independent implementation and reviewed app/text adaptation in
[M3 T45](../../docs/proposals/m3/mine-import-host-adoption.md). The sibling has
no Git history. No XP-derived core/header, bitmap/resource script or vendor
source is imported. The independent core uses separate hazard and cover arrays,
a fixed32-bit RNG and iterative flood; artwork is authored procedural C.
No claim is made that the new board sequence reproduces the original XP code.

The adapted owner-supplied snapshot files have these SHA256 values:

| Input | SHA256 |
| --- | --- |
| src/app/app.c |8c372a8bcb3c1ce4977a98b680e8270b0c04e6880d87040d70f80f99450be417|
| src/app/app.h |c01a43ee8a59394fa20458aee01567dc887a92a3e5badbfefe591572cc41d21e|
| src/text/scene.c |b4988d70d6c39eaa13bc4fea8947c81c3c642824040eed54534de27ceeddfde6|
| src/text/scene.h |72e1cf626aff0c831f12cc1d5ba5737c6fd2aea9efd2e8b371dabee7990e4ad0|

Those receipts identify reviewed app gestures/layout, not a licence grant for
excluded XP material. The receiving implementation replaces packed attributes
with neutral KVM cells and removes platform-CRT varargs formatting.
