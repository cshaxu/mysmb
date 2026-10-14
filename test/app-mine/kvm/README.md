# Mine KVM tests

application_test.c owns gesture cancellation, command/input mapping, hit
regions, view requests and clock policy. presentation_test.c owns authored
cells/bands, bounds, palette slots and number formatting. Mine's private-
desktop integration target exercises actual window/Console startup, mouse,
keys, retained Tab and exit. DOS/Win3.x joins use the neutral SDL test proxy
under ignored build, with installed DOSBox CPU/cycles unchanged.

The DOS script reserves startup time and supplies two distinct clicks: the
first may acquire DOSBox mouse capture, the second opens a cell. Under SDL's
dummy driver, mouse acquisition can invalidate the captured surface while
unchanged guest cells remain correct. A partial host screenshot is not a VGA
memory oracle. T45 S3 checked a local diagnostic copy's complete B800 text
page (board, opened cells, timer and footer) to distinguish that limitation;
the shipped executable contains no diagnostic hook. Win3.x actual pixels
and native private-desktop pixels are separately checked.

Win16 menu-cycle.script covers the in-window text/native-menu ownership join:
Tab into text, toggle Marks, return to graphics, repeat Tab and quit while the
native menu is detached. Capture checks require one Game/Help row in each view;
text keeps the authored row and graphics restores USER's menu. Run beside the
existing graphical-exit route in the private Win3.x image, with unchanged
DOSBox configuration. Host unit tests own failure/no-op and destruction counts.
