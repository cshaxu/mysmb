# M3 T45 Mine import and shared-host adoption

## Receiving baseline and admission gate

T44 S6-S13 closes the shared-host capability correction. The
[fixed gap register and receipts](../../history/M3-T44-library-readiness-correction.md)
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
| S2 active | Independent core/art, reviewed app/text, shared hosts and three products |20-30files/1500-2500lines | Owner-local tests, native/DOS/Win16 builds and products |
| S3 planned | Combined integration/regression and T closure | Receipts and bounded fixes | Platform joins, Mario regression, cleanup and reviewed push |

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
| S2 next | Independent Mine core/art and reviewed app/text; shared-host products | Rule/input/presentation tests plus native/DOS/Win16 builds and three Mine EXEs |
| S3 planned | Combined host regression and readiness closure | Actual platform joins, Mario regression, commit/push and cleanup |

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
