# M3 T44: NXVM-style source, test and product layout

## Owner-directed destination

The owner requests a single src/test topology like NXVM, with shared hosts
under src/lib, app-specific code directly under src/app-mario and src/app-mine,
and separate local product directories. This replaces the T43 directory
shape while retaining its shared ownership and application input policy.

```text
src/lib/{kvm,dos16,win32,win16}/
src/app-mario/core/
src/app-mario/kvm/{app,io,ppu,text,platform}/
src/app-mine/{core,kvm}/                 receiving boundary until import
test/lib/{kvm,dos16,win32,win16}/
test/app-mario/{core,kvm}/
test/app-mine/{core,kvm}/                receiving boundary until import
assets/mario/{mysmb16.exe,mysmb32.exe,mysmb64.exe}
assets/mine/                            future Mine products
```

Mario's translated ROM code remains core. Its input policy, snapshots,
audio/video marshalling, PPU pixel composition, authored text scenes and
app-specific host assembly belong to its kvm tree. Shared KVM types/palette,
DOS hardware services and Windows Console/window mechanisms remain src/lib
owners. No gameplay moves into a shared library.

Tests mirror their production owner, including nested subsystem directories.
Cross-owner fixtures name their composition owner. Reference harness code is
test-only. Do not retain the old flat app test directory as a shortcut, or
introduce forwarding copies, duplicate include owners or symlink bridges.

## Admitted S sequence

### S1 - migration contract and per-app local products

Inventory the existing source/test/build ownership and declare deterministic
destination rules. Move the three existing local Mario products into
assets/mario, preserving bytes and names; declare assets/mine for future
products. Update current delivery requirements and source-layout authority.
No compilation or game code changes are needed for this package move.

### S2 - source and build ownership migration

Move shared code to src/lib and remove the extra app-mario/src layer. Move
Mario core directly to src/app-mario/core and its presentation/I/O assembly
to src/app-mario/kvm. Update includes, CMake, presets, generators and DOS16
tool paths consistently. Keep test paths temporarily explicit during this S;
test ownership relocation is S3. No C function semantics may change.

### S3 - mirrored tests and evidence paths

Move tests to test/lib and test/app-mario subtrees matching their production
owners. Resolve each current flat fixture's owner before moving it. Reconcile
test source paths, Python root discovery, reference-only sources, tool entry
points and current audit-ledger paths as metadata. Historical evidence keeps
its recorded behavior and does not gain new ROM-equivalence credit.

### S4 - final three-platform and host acceptance

Build actual PE32/PE64 with Ninja/ccache and the existing OpenNT DOS16 route.
Run complete tests, real Console lifecycle routes, the DOS device probe,
dependency/purity and topology checks. Publish the three local EXEs only in
assets/mario and verify product headers. Close with a clean worktree and
bounded build cleanup. Mine remains a receiving boundary with no import.

## Fixed boundaries

NXVM is read-only layout evidence; no code is imported. Existing owner-local
products and ROM-derived build inputs remain uncommitted. All generated maps,
inventories, logs, traces and intermediates remain below ignored build.
Scope/expected/actual ROM-node matches are empty throughout this relocation.
Preserve game/PPU semantics, controls, Console/graphics behavior, executable
names and actual compiler widths. The active packet admits one S at a time.

## S1 closure and S2 admission

The inventory identifies 267 tracked Mario source entries, 636 Mario test
entries and 45 shared-library entries (including their tests/build/docs).
Mario core contains 167 files; its app/io/platform/ppu/text components have
6/24/42/4/16 files. Eight validation projection files are test-only and will
be assigned to their tested core or PPU owner in S3, not treated as game code.
The empty legacy game directory contributes no source and will not be kept.

All three local EXEs moved to assets/mario with identical SHA-256 values and
unchanged names. Their sizes remain DOS16 361,691 bytes, PE32 411,787 bytes and
PE64 365,675 bytes. assets/mine is reserved for future products. Package
delivery authority now uses these per-app paths. No executable is tracked,
no game function changed, and no compilation is claimed for this move.

S2 owns the source moves, include and build-path rewrites. Shared headers and
implementations flatten directly below src/lib/component rather than adding
another src/include layer. Mario source owners flatten below src/app-mario,
with core and kvm as its production boundaries. Existing test paths remain
explicit until their owner-by-owner S3 move. Acceptance checks source identity
apart from include/path edits, configure/include resolution and actual target
widths. Neither a directory rename nor a passing build promotes ROM nodes.
