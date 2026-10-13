# M3 T45 Mine import and shared-host adoption

T45 was reopened after S3 for the owner-requested Mario Win16 window-text
join. S1-S3 retain their original closure evidence; S4 below owns the
corrective implementation and final task closure.

## Receiving baseline and admission gate

T44 S6-S13 closes the shared-host capability correction. The
[fixed gap register and receipts](../history/M3-T44-library-readiness-correction.md)
show all12required gaps closed, independent libraries and current platform
joins. Mine import can now be admitted separately; this does not certify the
unimported Mine app or remove its provenance and per-app verification gates.

The final topology is `src/lib/{kvm,dos16,win16,win32}` and
`src/app-mario/{core,kvm}`. Shared physical input, variable graphics,16-slot
text colour/glyph output, Win32 Console/window lifecycle, Win16 retained
window text, DOS mouse/VGA, PCM/file and clock mechanisms are available.
Apps retain every input meaning, menu, save format, refresh policy and game
logic. `src/app-mine` contains only receiving documentation; its build hook
is off. DOS text profiles are80x25/80x50. Win16 text is in a Windows window,
not a real DOS prompt. Small-model libraries must be built separately from
Mario large-model objects. No Mario memory footprint is imposed on Mine.

Owner admits T45 on2026-10-13 to migrate Mine, build/test and commit/push.
The sibling is read-only; only the receiving repository may change. Source
inspection found no Git repository, so there is no history to merge. Use a
hash-qualified source snapshot, never invent an upstream revision. Local
provenance identifies adapted XP WinMine routines and three XP bitmap strips;
it explicitly supplies no redistribution licence. Owner chose independent core/art and reviewed app/text adaptation; protected/derived inputs stay in build. No original vendor tree or binary is imported by default.

## Admitted S roadmap

| S | Scope | Estimate | Exit |
| --- | --- | --- | --- |
| S1 closed | Source/provenance and unchanged baseline | Governance only | Source decision and three-width baseline complete |
| S2 closed | Independent core/art, reviewed app/text, shared hosts and three products |20-30files/1500-2500lines | Owner-local tests, native/DOS/Win16 builds and products |
| S3 closed | Combined integration/regression and T closure | Receipts and bounded fixes | Platform joins, Mario regression, cleanup and reviewed push |

S1 is source-only/baseline work. Import and publication cannot advance until
the provenance decision is explicit. Scope/expected/actual ROM credit0;
historical1992/1992, retained1991/1992nodes and4260/4261feasible controls stay
unchanged. Apps own all input meanings and update policy.

## Proposed bounded sequence

1. Record the exact Mine revision, ownership and redistribution receipt;
   import its qualified snapshot beneath `src/app-mine`, retaining source
   hashes and the approved provenance boundary. Establish its unchanged target baseline before
   shared-host adoption. Do not copy game source during the audit.
2. Adopt KVM and Win32/DOS16 services for the platforms Mine declares. Each
   app continues to own every keyboard/mouse binding and presentation choice.
   Verify input vocabulary/mouse capture requirements explicitly instead of
   assuming Mario's current controls cover Mine. Preserve separate product
   targets and app tests; libraries acquire no app/game dependency.
3. Adopt the existing Win16 USER/GDI, file and audio mechanisms. Qualify
   Mine's own NE/MZ entry and actual Windows 3.x behavior without duplicating
   the Mario host. Any newly discovered app requirement beyond the fixed readiness scope,
   needs its own scoped implementation and runtime evidence.

## Acceptance

Scope the receiving S before each implementation chain. Test each shared
owner and app binding once, then the real platform join. Win32/x64 host tests
must use actual PE32/PE64 images and cover borrowed/owned consoles, Tab holds
and releases, palette policy, input/focus and teardown. DOS and Win16 must
retain their actual toolchain/runtime evidence. Close only with explicit
per-app target/capability results, source-policy receipts and no duplicate
owners. Any missing app capability remains named work, not a supported target.

S1 local snapshot: 17source/test/resource files; aggregate SHA256 `18f568c8bd57361e513d08ae3849a3988c1eeeece92a556a4224d95ce3b42600`. No Git revision exists; vendor/reference files are excluded.

## S1 P1 baseline checkpoint

The17-file source/test/resource snapshot remains under ignored build. No vendor
reference tree is copied. Local Ninja/ccache builds compile the unchanged
window/Console product for x86 and x64. The unchanged core/app/text test reports
423checks,0failures,hash5f3c8245 on x86, x64 and actual DOSBox small-model DOS16.
The baseline build uses installed DOSBox defaults; no CPU/cycles change. This
proves the unchanged test corpus, not migrated-host runtime acceptance.

Reviewer confirms there is no upstream Git metadata and no supplied
redistribution licence for the XP-derived core/bitmaps. Asked the owner to
choose local-only source material with publishable adapters/build, or an
independent core/art replacement. That question remains pending. S1 stays
open and S2 is not admitted. No Mine production files, bitmaps or executables
are committed; no Mario source/product changed. This P is the bounded
admission/provenance/baseline record only, not T closure.

## S1 P2 owner source decision and closure

Owner explicitly approves independent core/art implementation and importing
reviewed application code. XP-derived core/header, three bitmap strips,
resource script and vendor references are excluded from the tracked import.
The new core uses independent storage/algorithms and original procedural art;
it does not promise the old XP cell encoding or old random-board hash. The
retained423-check hash is only the incoming baseline. New rule tests and
cross-width deterministic checks own acceptance of the replacement.

Only owner-supplied application gesture and text-layout code is adapted, with
snapshot hashes recorded; no upstream Git history exists. S1 source/baseline
exit is satisfied. To deliver complete products with implementation commits,
combine the former S2-S4 into one vertical S2 (core/app/text/render + shared
Win32/DOS/Win16 adapters and build), estimated20-30files/1500-2500lines.
S3 then owns final combined regression/receipts/cleanup and T closure. The
former S3-S5 slots were plans only and had no admitted identifiers.

| S | Final delivery | Exit |
| --- | --- | --- |
| S1 closed | Source decision and unchanged baseline | Three-width423checks passed; independent-source policy approved |
| S2 closed | Independent Mine core/art and reviewed app/text; shared-host products | Rule/input/presentation tests plus native/DOS/Win16 builds and three Mine EXEs |
| S3 closed | Combined host regression and readiness closure | Actual platform joins, Mario regression, commit/push and cleanup |

## S2 admission

Owner approval admits independent core/art, reviewed app/text adaptation and shared-host roots. Empty ROM scope/expected0; historical1992/1992 unchanged. Rule, gesture, colour/geometry and platform integration own separate tests. Product outputs are local assets/mine/mine16.exe, mine32.exe and mine64.exe. No XP core/header/art or sibling modification enters this change.

## S2 P1 implementation and closure

Independent core and procedural art are present under app-mine; only the
four hash-qualified app/text files listed in its README are adapted.
No XP core/header/bitmap/resource/vendor bytes entered the tracked import.
All hosts consume one Mine game/session; neutral KVM cells carry canonical16
slots. Win32 uses the existing parent-console, VT/fallback, window and input
libraries. DOS uses shared IRQ/PIT/mouse/text devices. Win16 uses the existing
retained USER/GDI host, with Mine-owned sizing, menus and text/window choice.
The neutral DOSBox SDL proxy moved from Mario tests to lib/dos16 and gained
physical mouse/modifier events. It is not linked into any product.

Verification: x86 and x64 each25/25 configured tests pass. Actual DOS16 tests
pass279core checks and50application checks; the core board hash00d790d1 and
presentation hash62cf853d match both native widths. GCC instrumentation of
six portable owners executes322/322lines, all548branch sites and all163call
sites;472/548branch outcomes are exercised. This is scoped test coverage,
not an all-path or OS-failure proof. Native app device joins, not portable
unit mocks, own actual window/Console behavior and cleanup. Hardware creation
failure branches are source-reviewed; no synthetic allocation-failure claim.

Actual PE32 and PE64 private-desktop runs pass detached graphical, ordinary
console-subsystem graphical and borrowed CMD startup; graphical left-release,
text level input, retained Tab cycles and normal exit. Actual DOSBox uses
unchanged installed CPU/cycles and proves text board, mouse reveal, clock,
expert/help keys and quit. Windows3.x proves its NE entry, graphical mouse
reveal/clock, expert board, window text/graphics Tab and exit. The default
DOSBox auto-capture consumes the first Windows mouse click; the second click
is the game action. No user desktop or sibling installation is modified.

Similar-issue sweep: both text and pixel counters used platform CRT varargs;
Win16 visibly corrupted them. Both now use the same bounded decimal owner,
including negative/minimum/maximum tests. The graphical face-release path
retained stale suppression; it now clears it on release and has a focused
regression. Console DEFER preserves dirty state, resize requests repaint,
and Tab's physical latch survives presenter focus changes. Win16 presentation
resizes on app geometry/view changes; pointer mapping follows client size.

| Local product | Bytes | SHA256 |
| --- | --- | --- |
| assets/mine/mine16.exe |40157|525868524884a74eb1f10fcda02ff3c8fb89ee9eb3ff4389610829ec3e56a0e4|
| assets/mine/mine32.exe |155358|edea074d0bb7de7bf650e077456687216551218676d5a521cec375299c246699|
| assets/mine/mine64.exe |149044|34e690ddd46e0119488b450062de80de5a581e2d7b400b2470ee8f2abc2afa98|

The NE/MZ binder verifies the preserved19143-byte DOS image and36896-byte
minimum DOS resident requirement. This minimum is not peak allocation.
Mario source and its products are unchanged. ROM scope/expected/actual0;
historical1992/1992 and retained1991/1992nodes,4260/4261feasible controls remain
unchanged. S2 closes; S3 owns final combined builds/platform receipt refresh,
source-boundary review and T closure. Generated work is retained only until
that admitted final verification consumes it; no binary is committed.

## S3 admission

Automatic owner-authorized final verification of0028ca55. Initially no production changes planned;4-8receipt/governance files expected. The bounded Win16 warning correction changes this S to implementation accounting, with no ABI or game-rule change. Reuse the qualified small-model and native builds, run combined Mine/Mario suites and exact current products through private-desktop and DOS/Win3.x routes. Empty ROM scope/expected0; retained accounting unchanged. Final history records actual results and preserved unrelated work.

## S3 P1 combined regression and T closure

Both combined Ninja/ccache Release builds pass310/310 configured tests
(Mario, independent Mine and libraries). The x86 build had one compiler
subprocess terminate without a diagnostic; a bounded rebuild compiled that
same object and completed the full suite. No compiler defect is inferred.
Both widths also pass the shared device joins and all15Mario launch/Console
routes, including interactive CMD Tab/return/prompt. Both final Mine products
pass all3launch routes (detached, ordinary owned console, borrowed console),
mouse reveal, expert-level input, repeated Tab and clean exit.

The final Mine16 was compiled and linked again using the qualified small-model
DOS and Win16 tools. The only production change aligns cached Win16 dimensions
with the unsigned host fields (two added lines, one removed); no ABI or game
rule changed, and the product SHA256 remains identical to S2. Review found
no other signed comparison warning in this build. All three products retain
the exact sizes and hashes in the S2 table.

Windows3.x actual pixels show opened cells, timer advancement, expert board,
window text and graphical return; the NE exits normally. DOS actual product
input covers two separated clicks, expert/help/escape and quit. The first
click may be consumed by DOSBox mouse acquisition, so the fixture now reserves
startup time and explicitly sends a second click. A hidden SDL dummy surface
can lose unchanged cells after capture: its partial screenshot cannot certify
VGA contents. A build-only diagnostic copy read all4000bytes of B800 text
memory after opening cells: the board, numbers, timer and footer are intact.
That hook is absent from the shipped product. This distinguishes guest state
from the host capture limitation; it is not a claim of visible real-machine
or RDP manual acceptance. Installed DOSBox CPU/cycles were never changed.

Test ownership remains core rules, app gestures/clock, presentation conversion
and actual host lifecycle joins; S3 adds no duplicate rule assertions.
Independent Mine-only builds and both combined app builds pass. Portable
line/branch coverage and DOS rule hashes are retained in S2; no all-path claim
is added. Source review confirms app input/policy stays in app-mine and reusable
mechanisms stay in lib; no Mario or library production source changed in T45.
No XP core/header/bitmap/resource/vendor input is published. Reviewed app/text
imports retain their source hashes; no sibling is modified.

S1, S2 and S3 meet this T's bounded import exit. DOS is text-only, Win3.x has
window graphics/text, and Win32/x64 support parent-console/window Tab over
one game. Mine custom difficulty, persistence, high scores and sound were
not part of the imported baseline and are not claimed here. Local products
are available under assets/mine; binaries and local runtime/source copies
are excluded from commits. Seventeen pre-existing assets/resources deletions
remain unstaged and untouched. Queue order is unchanged; no next T is admitted.

ROM scope, expected and actual additions are empty. Historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls (4342raw,81infeasible)
remain unchanged. T45 is not a ROM final-certification task.

Acceptance cleanup removed3task-owned generated directories,3850 files and246755389 bytes. Build is empty; products and qualified tools remain.

## S4 corrective reopening: Mario Win16 window text

Owner reopens T45 and admits S4 to give Mario the shared Win16 window-text
capability already qualified for Mine. Same process/window/game, Tab between
canonical graphics and the existing authored80x25text scene. No DOS prompt,
no ROM/core/PPU semantic change, no Mine behavior change or library game policy.
Estimate5-8source/test/build files,150-300lines plus governance.

Reuse io/control's physical-edge gate, text/scene and layout's neutral view,
and lib/win16's retained text/graphics lifecycle. The Win16 root owns choice,
observer enablement and text workspace allocation; required allocation failure
must cleanly return, not publish an incomplete frame. Presentation changes
request redraw independently of a logical tick. Focus, save/load, audio and
exit retain their current owners. Similar-issue sweep covers inert Tab gates,
observer initialization, segmented storage and host source manifests.

Verification: existing control/mapping/text/host owner tests, a focused
read-only game-to-text integration join, actual Win3.x Tab hold/release and
return, gameplay and P/O continuity; refreshed three Mario EXEs and native
regression. Scope/expected matches[]; historical1992/1992, retained1991/1992
nodes and4260/4261feasible relations unchanged. Owner ROM and SDK/CRT are the
same qualified local-only build inputs; generated data/screenshots/probes stay
below build/t45-s4 and are not published. Single-person implement/review passes.

### S4 implementation and review receipt

Mario's Win16 root now enables its existing text observer, allocates a
segmented text workspace, and supplies the shared host with graphics and
80x25 authored text views. Physical Tab press edges change the app's view;
held/repeated input does not toggle repeatedly. A view change requests paint
without requiring a game tick. Focus loss clears the latch. One game, audio,
scheduler and snapshot path remain in place; no real DOS prompt is launched.

Actual Win3.x testing found a reusable host gap: arbitrary source RGB passed
straight to GDI on standard VGA could map a blue background to white and hide
white captions. The neutral Win16 painter now uses the same canonical16
nearest-colour conversion as its DIB path when device depth is at most4bits.
It converts16slots once per paint; higher depths retain source RGB. No Mario
palette or input meaning enters the library. Existing Mine canonical-slot
text follows its unchanged route. Diagnostic guest frame dumps established
that Mario's scene cells and palette were correct before the host conversion.

The source-manifest sweep adds the existing scene, layout, actor, background,
caption, authored-element and neutral glyph owners to Win16. The required
text allocation failure releases previous allocations; optional background
cache failure remains supported. No core, PPU, DOS or Win32 production logic
changes. DOS payload/load-memory preservation is checked by the hybrid binder.

Test-owner closure:

- The Mario root integration fixture compiles the production root separately.
  It owns immediate Tab redraw, hold/repeat, focus/release,80x25neutral view,
  required allocation/lock failures, optional cache failures, cleanup and
  Escape. Full pixel output is unchanged by repeated text composition and
  view switching without elapsed ticks.
- The existing Win16 host test owns low-depth source-palette reduction and
  high-depth RGB retention, alongside canonical-slot and device failure paths.
- Combined Release Ninja/ccache builds and complete CTest suites pass311/311
  each on x86 and x64. Both named Mario Win32 host-integration targets pass
  all15routes, including real private-desktop graphics and borrowed/owned
  Console input/Tab/restore. No active desktop was driven.
- The actual large-model Win16 build and MZ/NE binding pass. The original DOS
  load image is retained:352990image bytes,2658relocations,
  387088minimum and391184maximum resident bytes. Compile diagnostics include
  existing old-compiler width warnings; this is not a warning-free claim.
- The tracked Win16 input script runs in a private Win3.x copy with a hidden
  SDL probe and unchanged DOSBox CPU/cycles. It checks held Tab, return to
  pixels, active gameplay, save, subsequent movement, load, text and Escape.
  Guest-frame and GDI diagnostics are build-only and absent from the product.
  The standard VGA driver and dummy capture limit displayed colour fidelity;
  this verifies the window text lifecycle, not SVGA or physical-machine speed.

Implementation/reviewer passes confirm input meanings and game cadence stay
app-owned, the library fix is only device colour conversion, and no unrelated
ROM-node ledger row or existing task was edited. There is no new ROM proof:
scope/expected/actual additions are empty; historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls (4342raw,81infeasible)
remain unchanged. The six queued candidates retain their order.

S4 actual change size: seven source/build/test files,224additions and13deletions,
plus six governance/design files. The additional shared-host colour conversion
was required by the actual Win3.x test, within the same window-text join.
The final probe exits normally; its10035-byte save is created and restored
without a snapshot-error log. Manual owner colour/play acceptance is pending.
Three local product receipts (SHA-256):

| Product | Bytes | SHA-256 |
| --- | --- | --- |
| assets/mario/mysmb16.exe | 695397 | 515b160e92975c1543d24769bb31ff87ae3c85c20dab2ea0bf7c1bfcdbe9ba47 |
| assets/mario/mysmb32.exe | 419979 | d47636b8dcdbe10bccb191795d4449c49c538e137aad40b5d677e1b727cdd215 |
| assets/mario/mysmb64.exe | 383595 | 88084ba6d3fa77b2a571aab134ae1d1d57df142403c0e7de331f54c00c9274bb |

T45 corrective implementation is closed. Task-generated build outputs remain
only for pending owner acceptance and will then be removed by the acceptance
cleanup rule. Local executable publication is not a ROM/source distribution.
