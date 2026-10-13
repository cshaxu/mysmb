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
it explicitly supplies no redistribution licence. Publication treatment is
pending the owner's scoped decision; protected/derived inputs stay in build
until resolved. No original vendor tree or binary is imported by default.

## Admitted S roadmap

| S | Scope | Estimate | Exit |
| --- | --- | --- | --- |
| S1 active | Source/provenance snapshot and unchanged baseline |3governance files; no production change | Exact snapshot and native/DOS core checks; publication boundary decided |
| S2 planned | Core/app/text migration with mirrored tests and target build |12-20files/1000-1800lines | Source disposition obeyed; deterministic baseline retained; no Mario dependency |
| S3 planned | Win32/x64 shared-host adoption |6-12files/600-1200lines | Window/Console launch, Tab, palette, mouse/keyboard and teardown integration |
| S4 planned | DOS16 and Win16 shared-host adoption/NE-MZ binding |6-12files/500-1000lines | Actual DOS/Win3.x loading/input/text/window and model-qualified builds |
| S5 planned | Combined regression, local products and T closure |4-8files plus receipts | Mine and Mario suites pass; three Mine EXEs; reviewed commit/push and cleanup |

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
