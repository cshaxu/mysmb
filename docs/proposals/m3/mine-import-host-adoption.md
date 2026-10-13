# Mine import and shared-host adoption

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

The owner limited the current goal to completing this split and preparing
for import. The former T43 S8/S9 plan is retained here as a future unnumbered
candidate. It has no admitted task identifier or approval to import now.

Owner amendment: T44 S2 now admits the Mario NE/MZ Win3.x host first. When
this candidate is admitted, consume its then-verified Win16 owner rather than
creating a competing host from Mine; review and import only capabilities that
the common owner actually lacks.

## Proposed bounded sequence

1. Record the exact Mine revision, ownership and redistribution receipt;
   import its history beneath `src/app-mine` through a subtree or equivalent
   history-preserving merge. Establish its unchanged target baseline before
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
