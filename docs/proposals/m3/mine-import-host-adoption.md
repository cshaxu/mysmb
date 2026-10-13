# Mine import and shared-host adoption

## Receiving baseline and admission gate

The Mario-first split closes in M3 T43. `app-mario` owns its application;
KVM, Win32 and DOS16 reusable owners are separate libraries. `app-mine`
contains receiving documentation only, and its optional build hook defaults
off. Win16 provides an interface contract, not a working host.

The owner limited the current goal to completing this split and preparing
for import. The former T43 S8/S9 plan is retained here as a future unnumbered
candidate. It has no admitted task identifier or approval to import now.

## Proposed bounded sequence

1. Record the exact Mine revision, ownership and redistribution receipt;
   import its history beneath `app-mine` through a subtree or equivalent
   history-preserving merge. Establish its unchanged target baseline before
   shared-host adoption. Do not copy game source during the audit.
2. Adopt KVM and Win32/DOS16 services for the platforms Mine declares. Each
   app continues to own every keyboard/mouse binding and presentation choice.
   Verify input vocabulary/mouse capture requirements explicitly instead of
   assuming Mario's current controls cover Mine. Preserve separate product
   targets and app tests; libraries acquire no app/game dependency.
3. Review and extract Mine's generic Win16 USER/GDI/bootstrap mechanics into
   the receiving Win16 contract. Add Mario's Win16 adapter and qualify actual
   NE/MZ builds and Win3.x runtime, including app-requested text/graphics
   switching. The existing interface test is not runtime evidence.

## Acceptance

Scope the receiving S before each implementation chain. Test each shared
owner and app binding once, then the real platform join. Win32/x64 host tests
must use actual PE32/PE64 images and cover borrowed/owned consoles, Tab holds
and releases, palette policy, input/focus and teardown. DOS and Win16 must
retain their actual toolchain/runtime evidence. Close only with explicit
per-app target/capability results, source-policy receipts and no duplicate
owners. Any missing app capability remains named work, not a supported target.
