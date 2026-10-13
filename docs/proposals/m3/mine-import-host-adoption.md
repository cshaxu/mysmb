# Mine import and shared-host adoption

## Receiving baseline and admission gate

The Mario-first ownership split closes in M3 T43; T44 supplies the final
NXVM-style paths. `src/app-mario` owns its application;
KVM, Win32 and DOS16 reusable owners are separate libraries. `src/app-mine`
contains receiving documentation only, and its optional build hook defaults
off. Win16 now provides the T44 S2 graphical host, file services and waveform queue.

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
   the Mario host. Any missing capability, including Win16 text switching,
   needs its own scoped implementation and runtime evidence.

## Acceptance

Scope the receiving S before each implementation chain. Test each shared
owner and app binding once, then the real platform join. Win32/x64 host tests
must use actual PE32/PE64 images and cover borrowed/owned consoles, Tab holds
and releases, palette policy, input/focus and teardown. DOS and Win16 must
retain their actual toolchain/runtime evidence. Close only with explicit
per-app target/capability results, source-policy receipts and no duplicate
owners. Any missing app capability remains named work, not a supported target.
