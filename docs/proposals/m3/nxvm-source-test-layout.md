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

### S2 - DOS16/Win3.x NE/MZ product and Tab feasibility

Owner-directed insertion before any source relocation. Research the Mine
dual-format build, available Win16 compiler/SDK and Win3.x runtime. Retain
the functional DOS executable as the MZ stub, with its existing graphics/text
Tab behavior; add a native NE graphical entry for Windows 3.x using the same
portable game/PPU sources. Do not start a DOS game in a window and call that
a Win16 implementation. Examine app-requested in-window text, child DOS prompt
handoff and suspended/resumed state as distinct mechanisms. Report whether
the ideal DOS prompt Tab round trip can preserve one game's state, input,
timing, memory and failure/exit ownership before committing to that route.

Mine is owner-managed read-only reference, not imported material. Its supplied
workspace has no Git metadata, so provenance is pinned by hashes: build.ps1
171c9ac150586a5936483b74bf4417201eb854877f79ea4d067d741525e68cf2;
Windows adapter 1cb36ef11bac5f6823c02ea7dd157266e54ea0d3792e76357467a19f99234f5f;
DOS entry c6b674264ca1551ef095c3cfbe44b13fba9df79784770c14edc0bf85a7890e5a.
Redistribution/license permission is unreviewed; no source or vendor binary is
copied into tracked MySMB material. SDK/compiler and Windows runtime inputs
remain owner-local build/test tools. The active packet records additional
tool identities if needed. Generated dual-format products remain local.

### S3 - source and build ownership migration

Move shared code to src/lib and remove the extra app-mario/src layer. Move
Mario core directly to src/app-mario/core and its presentation/I/O assembly
to src/app-mario/kvm. Update includes, CMake, presets, generators and DOS16
tool paths consistently. Keep test paths temporarily explicit during this S;
test ownership relocation is S4. No C function semantics may change.

### S4 - mirrored tests and evidence paths

Move tests to test/lib and test/app-mario subtrees matching their production
owners. Resolve each current flat fixture's owner before moving it. Reconcile
test source paths, Python root discovery, reference-only sources, tool entry
points and current audit-ledger paths as metadata. Historical evidence keeps
its recorded behavior and does not gain new ROM-equivalence credit.

### S5 - final platform and host acceptance

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
be assigned to their tested core or PPU owner in S4, not treated as game code.
The empty legacy game directory contributes no source and will not be kept.

All three local EXEs moved to assets/mario with identical SHA-256 values and
unchanged names. Their sizes remain DOS16 361,691 bytes, PE32 411,787 bytes and
PE64 365,675 bytes. assets/mine is reserved for future products. Package
delivery authority now uses these per-app paths. No executable is tracked,
no game function changed, and no compilation is claimed for this move.

The unexecuted original S2 now becomes planned S3 after the owner's Win16
insertion. S3 owns the source moves, include and build-path rewrites. Shared headers and
implementations flatten directly below src/lib/component rather than adding
another src/include layer. Mario source owners flatten below src/app-mario,
with core and kvm as its production boundaries. Existing test paths remain
explicit until their owner-by-owner S4 move. Acceptance checks source identity
apart from include/path edits, configure/include resolution and actual target
widths. Neither a directory rename nor a passing build promotes ROM nodes.

## S2 P1 feasibility receipt (S2 remains open)

### Proven build and runtime facts

Mine uses a functional DOS MZ as the NE module's STUB. Its Win16 Tab selects
a GDI text view within the same window; it does not open a DOS prompt.
The MySMB research probe is independently written, synthetic and build-only.
It embeds the current owner-local DOS game as its stub. LINK16 is a PE32
host tool: the sandbox's system-DLL relocation conflict disappears outside
the sandbox, where the existing linker succeeds. This is not a DOS linker
compatibility failure and needs no new compiler or DOS4GW runtime.

Both medium-model and original-style large-model Win16 probes compile and
link. The DLL-oriented LDLLCEW library has no EXE startup and is rejected;
the proper LLIBCEW EXE runtime is available in the owner's OpenNT tool tree.
The /AL /G2sw probe passes in a private Windows 3.1 enhanced-mode installation:
native WinMain, visible window creation, TextOut, a red FillRect/GetPixel
round trip and timer/teardown are checked. The existing installation and
global DOSBox configuration are untouched. Its supplied permanent-swap
configuration initially blocked boot; the private test copy disables paging
and uses the synthetic probe as its shell. This is runtime qualification,
not a performance result or a playable Mario Windows product.

The source/runtime tool identities are pinned (local-only, no redistribution):
LINK16 910ed26e6c8d72d64faa82a7eeabb6d5c002b347024c8f1d778fddbb8ac1b00;
Win16 windows.h 0e26530e07a6b6d6e6c6442d4a5092a186ca94520ddcf43f95387712c1330738;
LIBW c1a31b79f9667558055302a36a6682570c97cb84840cd8c1264c41dd7c15834a;
LLIBCEW 31fc73c38ccda379d14c09b93de606a4dd051e184b1fbb21be36d0e7b154ded4;
MLIBCEW 4e9f08311a8ef4f6c178b097b86b04b93bd4e9bd9e0be6b0aa02292debf9636d;
Win3.1 WIN.COM 0e34b06601b2c9056186c937e2baa8adf14bd572fd15bc72b8b7fff679aa2e47.
The probe NE requests Windows 3.1; 3.0 and standard-mode operation are not
claimed from this enhanced-mode receipt.

### Required MZ safety gate

LINK embeds the original DOS loaded image and relocation entries intact, but
changes its minimum extra allocation from 2,153 paragraphs to 4. The probe
repairs minimum/maximum allocation relative to the new MZ image paragraph
count, preserving original minimum and maximum resident sizes. Original
CS/IP/SS/SP and every relocation must remain equivalent. The final binder
must validate this after link/resource processing before product publication;
a syntactically valid NE header alone is insufficient DOS acceptance.

The [Open Watcom linker guide](https://open-watcom.github.io/open-watcom-v2-wikidocs/lguide.html)
documents the executable STUB mechanism; the Microsoft tool behavior above
is established by the actual local probe rather than inferred from a modern
PE/VxD-only documentation page.

### Text switching findings and implementation order

First integrate the shared translated C/core/PPU route into a native Win16
GDI host, retaining the original /AL DOS build and an app-owned input mapper.
The same-window 80x25 text route is a straightforward host projection of the
existing authored KVM frame, with one running state and no process handoff.

A real DOS prompt is a distinct execution context. WinExec/PIF launch does
not turn a Win16 task into DOS. A same-game round trip needs suspension of the
NE app tick/audio, a versioned state handoff, a forced and verified MZ/text
entry, a completion/failed-child route, and clock/input rebasing on return.
Do not assume launching the same NE-bearing file selects its DOS entry.
COMMAND.COM routing versus a temporary MZ-only extraction must be tested,
including Windows standard/enhanced mode behavior and available conventional
memory. Preserving a held Tab until its physical release is also required.

That prompt bridge is feasible to investigate but not yet validated. A newly
started DOS game cannot be called a retained-state view switch. Its complexity
does not block the requested native graphical entry. Remaining S2 work is the
real game host/build, graphical/text/input/audio and DOS regressions, then a
concrete prompt-bridge disposition. No product EXE has been replaced by the
research probe, and no game logic or M2 equivalence status has changed.
