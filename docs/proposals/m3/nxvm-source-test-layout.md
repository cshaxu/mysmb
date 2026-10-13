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

### S2 - DOS dual-mode and native Win16 graphical NE/MZ product

Owner-directed insertion before any source relocation. Research the Mine
dual-format build, available Win16 compiler/SDK and Win3.x runtime. Retain
the functional DOS executable as the MZ stub, with its existing graphics/text
Tab behavior; add a native NE graphical entry for Windows 3.x using the same
portable game/PPU sources. Do not start a DOS game in a window and call that
a Win16 implementation. The owner's subsequent scope decision makes Win16
graphical-window-only for this S: Tab does not change its presenter or launch
a DOS task. Win16 text and real DOS-prompt switching are deferred and are not
closure gates. DOS retains its existing Tab graphics/text switching.

Acceptance separates the two entries of the same executable: actual DOS
graphics/text/input/exit regression and native Win16 game drawing/input/exit.
The NE entry reuses the portable game and PPU sources, not a DOS child game.
Synthetic window probes establish feasibility only; they do not close S2.

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
real game host/build, Win16 graphical/input/audio and DOS dual-mode regressions.
The owner subsequently deferred all Win16 Tab/text/prompt behavior; the prompt
research above is retained as findings, not an implementation requirement.
No product EXE has been replaced by the
research probe, and no game logic or M2 equivalence status has changed.

## S2 P2 implementation progress (not a closure)

The actual translated core now compiles with the existing /AL /G2sw compiler
and links with LIBW plus the qualified Windows EXE runtime. A project-owned
USER/GDI host receives physical events and canonical PPU bands. Mario's Win16
root binds the same local PRG/CHR/title sources and calls the original shared
startup and tick entries; there is no emulator or separate gameplay route.
The app declares graphical-only presentation, and ignores Tab. DOS retains
the functional original graphics/text executable as the MZ entry.

The neutral Windows keyboard wire decoder is now shared by Win16 and Win32;
Mario keeps WSAD, J=B, K=A, Enter, Shift and Escape meanings. The Win16 host
uses coarse USER timer delivery with a sixty-tick accumulator and paints only
after synchronous ticks finish. DIB bands reverse row order explicitly. The
default client fits the VGA desktop instead of extending below it.

Actual private Win3.1 enhanced-mode runs show title and game frames, movement
and continued graphical presentation after Tab. These are partial runtime
receipts, not complete input/timing/exit acceptance. Canonical pixel and RGB
dumps are correct; standard sixteen-colour VGA GDI/display conversion remains
under investigation. A synthetic FillRect/StretchDIBits/DDB comparison isolates
device conversion from Mario data. Its independent solid-colour GDI paths
produce the same display palette differences; DOSBox's built-in VGA capture
confirms them too, ruling out the SDL screenshot as their cause. No speculative
palette compensation or screenshot correction is retained. Eight-bit DIBs retain master indices;
sixteen-colour devices receive explicit four-bit projection. Final colour
acceptance, other supported display depths and the complete DOS regression
remain open. No hybrid executable is published to assets yet.

The binder verifies loaded DOS program bytes, every relocation and CS/IP/SS/SP,
then adjusts minimum and maximum allocation by the changed image paragraph
count. The linked hybrid preserves the stub's resident range: 385,392 to
389,488 bytes excluding the 256-byte PSP, or 385,648 to 389,744 including it.
Appended NE file bytes are not DOS resident bytes. Synthetic binder tests cover
allocation correction and corrupt image, relocation, entry/header rejection.

The x64 configured suite ran 294 tests: 293 initially passed and the existing
platform-topology gate rejected the newly admitted Win16 component. The gate
now explicitly checks three independent app adapters and the Win16 host's
allowed dependencies. Its corrected run and the four new/focused Win16/key
checks pass. The other initial suite results remain retained. The complete
x86 suite now passes 294/294; product packaging acceptance remains pending.
The only shared PPU edit names the existing
61,440-byte constant directly, avoiding signed 16-bit constant-expression
overflow without changing array capacity. ROM-node and edge credit is zero.

Win16 sound-device and save/load adapters are not yet integrated; the original
core still generates the same ordered APU writes. Their required disposition
must be explicit before S2 is closed. Directory relocation remains S3.

### Fixed-cycle runtime limitation accepted by owner

At unchanged 3,000 cycles, the existing DOS product and the hybrid show the
same blank scanout. A local current-source diagnostic executes 403 logical
frames, reaches running mode/task 1/3, retains an 8,192-byte CHR binding and
visible mask 30, but records no presentation-cache initialization: the existing
late-frame gate continuously skips presentation. This is not an NE/MZ resource
or relocation regression. The owner accepts this DOSBox performance limitation
for this work; do not change emulator speed to hide it or claim a visible
functional-play result from the blank frame. Preserve the DOS entry and
separate format, mode/input/exit evidence from low-speed playability.

Win16's input receipt records a short Enter down/up as a start controller
sample, transition to running mode and subsequent directional samples. The
decoded-input latch retains a press for one sample and has focused tests for
release, held input, focus clear, repeats and both controller ports. Win32's
private-desktop integration must run serially: parallel host runs exceeded an
existing fixture deadline; the serial x64 run passes all thirteen routes.
The serial x86 run also passes all thirteen routes. A same-frame Win16 PPU
comparison at running mode/task 1/3 matches cached and uncached pixels for
the audited band; it provides scoped cache evidence only. Final scene and
input presentation acceptance still requires complete visible game frames,
not mode counters alone.

### P2 cross-width and presentation receipts

A bounded local same-input replay compares 720 successive 2,048-byte CPU RAM
and 2,048-byte nametable records. Actual Win3.1 large-model execution and the
current Win64 core match all records, plus the complete final 61,440 master
pixels. These are cross-width native receipts, not a new original-ROM
certificate. In the actual GUI, the corresponding running frame also matches
RAM, nametables and all eleven PPU control/scroll/split bytes. All thirty
eight-row bands match cached and uncached PPU output in that frame.

The USER host now limits each timer dispatch to four logical ticks, retains
remaining credit and skips obsolete presentation while catching up. Completed
frames use UpdateWindow after invalidation to avoid a deferred paint remaining
behind timer traffic. The neutral clock owner tests fractional periods,
backlog retention, four-tick bounds, timestamp wrap and discontinuities. Native
x86/x64 configured suites each pass 296/296, and private-console host routes
each pass thirteen cases when run serially. Final product GUI input/publish
acceptance is still pending; low-speed scripted input must follow visible
menu readiness instead of assuming a fixed short startup duration.

Ordinary application lifetime is tested with the private Program Manager
desktop and auto-run, not only with the game substituted as Windows shell.
The game window draws on that desktop and Escape returns to Program Manager.
The original Windows installation remains read-only. Win16 DOS file names
use eight-dot-three spelling when reading native diagnostic receipts.

## S2 P2 delivery receipt

This receipt supersedes the earlier P2 progress/pending statements above.
S2 implementation is delivered for owner acceptance; T44 source/test moves
remain unexecuted S3/S4. No whole-game or all-input certificate is claimed.

The actual Win3.1 enhanced-mode run uses Program Manager as shell, auto-runs
the native game and injects finite physical events into a private headless
DOSBox SDL queue. A fresh Enter press after title initialization transitions
from mode 0/task 3 to mode 1/task 0, then task 1. Direction and jump samples
follow; Tab leaves the graphical host active; Escape closes it and returns
to Program Manager. Final diagnostic state is mode 1/task 3 with the shared
exit latch set. A final non-diagnostic product run repeats the GUI route.
The script stops at 125 seconds. Owner desktop input is never used.

The bounded cross-width replay protocol is retained in Mario's owned
win16_core_replay test harness, outside product and default CTest linkage.
Call its declared function from an owner-local native entry wrapper with
build-contained filenames, link the same core/PPU and local generated
resources, then run the Win16 wrapper on the qualified Windows runtime.
Start is sampled at tick 100 and right at ticks 300 through 339. Compare
all 720 RAM/nametable records and the final canonical frame byte for byte.
State SHA-256 is
05f685782ebde90fdd48f37484d0c95277ab75fec6ff1e148d464195a52fca85;
pixel SHA-256 is
712fb240bc5f1a78550341ba6040faa448a12cb34a37e3f7385a0750b65114d3.
The tracked fixture's modern result matches the actual Win16 receipt.

Final builds use the explicit compiler/SDK/CRT inputs above, first
Build-OpenNt16Windows CompileOnly, then LinkOnly. LinkOnly refreshes the
supplied real DOS stub before linking and re-verifies its program image,
relocations, entry/stack registers and resident bounds. x86/x64 configured
suites pass 296/296 each; the thirteen private-console host routes pass on
each width serially. Four synthetic binder tests, platform-purity checks
and the focused clock, DIB, input-latch and Windows-key owners pass.

Test-owner closure: KVM owns physical Windows-key decoding; Mario IO owns
short-press/held/release/two-port/focus behavior; Win16 owns clock and DIB
projection branches; the binder owns executable integrity/allocation
rejections. Actual USER/GDI creation, focus, timer, paint, key and teardown
joins are integration-only because their API capability is absent from a
modern headless CTest worker. Device allocation failures are handled at
their owner returns but are not claimed as injected Win3.1 runtime cases.
Win32's existing key meaning and controller routes remain unchanged.

Similar-issue sweep covers signed-width frame capacity, MZ resident bounds,
all grouped OMF member names, stale LinkOnly stubs, physical key decoding,
coarse timer short presses and paint starvation. The existing unsigned
61,440-byte frame constant replaces the overflowing 16-bit expression;
no core function or PPU semantic changes. Node and edge credit is zero.

Local product receipt (bytes; SHA-256):

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe, MZ plus NE | 617185 | 49269d786d296cf9c301e9355c39437eaa4871eb126a69fca244fff003360f66 |
| mysmb32.exe, PE32 | 411787 | 31175e55969dc8497e4ef363ed0f531fd50c4bf5df03ce06f6005ba27577cde1 |
| mysmb64.exe, PE32+ | 376939 | 63f5aaeb7b0a4e64c0da29221e2a6d3ed85736f7e68877467b1b207514dd8a73 |

All three are refreshed under the ignored assets/mario boundary; no ROM,
generated resource, tool, protected screenshot or binary is staged. The
hybrid's larger file does not increase its MZ resident minimum: 385,648 bytes
including PSP, unchanged from the supplied DOS product. Runtime caches are
additional DOS allocations, not included in that loader minimum.

Qualification is bounded: actual Windows evidence is Win3.1 enhanced mode
and standard VGA16. Its fixed device palette visibly approximates source
colours. The 8bpp projection passes unit tests but no 256-colour Windows
driver is runtime-qualified. Win3.0 and standard mode remain unqualified.
DOS format, Tab mode transition and exit are preserved; at unchanged 3,000
cycles the prior and hybrid products both skip video continuously, as already
accepted by the owner. This does not establish low-speed DOS playability.
Win16 audio-device and save/load adapters are not part of this graphical
entry baseline and are recorded with text/prompt handoff as receiving debt
in TODO. Core APU writes remain common, not audible Win16 output.

## S2 P3 owner-directed save and music extension

The owner extends the active S2 to implement Win16 save/load and music with
reusable libraries. No new S number or directory relocation is admitted.
Win16 remains graphical-only. Expected scope is 15-25 implementation/test/build
files plus governance; ROM node/edge scope and credit remain empty.

lib/win16 owns waveform-device buffers/lifetime and executable-path/file
replacement mechanisms. Mario owns P/O semantics and the existing snapshot
codec/validation; its integer PCM renderer is extracted from the DOS adapter
into shared app IO without changing synthesis. DOS and Win16 consume that
same renderer. Each logical tick consumes original ordered sound writes even
when video is skipped; device failure must not stop gameplay.

Validation includes owner-local PCM/input/snapshot/file failure contracts,
all configured native suites, real Win3.1 save/load and waveform output,
original DOS-stub preservation and refreshed three local products. Only the
private Windows test copy may receive an owner-local waveform-driver setup;
no global DOSBox speed or existing Windows installation is changed. Third-party
drivers/SDK remain local-only, provenance-pinned verification inputs.

## S2 P3 delivery receipt

P3 supersedes the P2 audio/save deferral. Mario Win16 owns P/O meanings and
uses the common fingerprint, codec, validation and single snapshot workspace.
File operations are synchronous between ticks; timing is rebased afterwards.
The waveform queue is reset at load/focus loss and before teardown. Saved game
and APU state are complete; physical oscillator phase is not serialized and
is reinitialized on load, as in the existing DOS route. No sample-exact audio
continuation or Win32 synthesizer parity is claimed.

Reusable Win16 file/device owners live in lib/win16. The existing DOS integer
synthesizer moves intact to Mario io/audio_renderer; only API names change,
plus a restored-register synchronization entry. DOS device discovery remains
DOS-owned. No core or PPU implementation changes; zero new node/edge credit.
The source-tree relocation is still the separate, unexecuted S3.

Tests own separate contracts: shared synthesis covers ordered writes, exact
11025 samples over sixty ticks, capacity and restored registers; Win16 audio
covers dynamic discovery, allocation/lock/open/prepare failure, queue saturation,
write/reset/unprepare/close failures, memory retention and transient-ownership
retry. File owners cover explicit module instance, path bounds and backup
replacement/self-collision. Existing snapshot owners retain corrupt-header,
CRC, fingerprint and restore validation; these are not duplicated per host.
The configured x86 and x64 suites each have 300 cases: 299 pass and the actual
Win32 audio-device case skips because the worker lacks that host capability.

Actual Win3.1 enhanced-mode verification uses the same private 3000-cycle
DOSBox/SDL test route as P2. The private Windows copy receives the owner's
Sound Blaster 2 wave driver and virtual device, configured for the existing
port 220/IRQ7. Neither the source Windows installation nor DOSBox timing is
changed. Local compressed driver identities, without redistributing them:

| Verification input | SHA-256 |
| --- | --- |
| SNDBLST2.DR_ | 137dd4cb208dbb29ced6378e876ac0a33cf7ea3c3864b46310a942c74a25f85b |
| VSBD.38_ | 3e4c7e9d7d0e5eab0fd62d0689e8293cdd60efe75d7e784006e72cdee93e32b8 |

The native waveform open initially returns MMSYSERR_ALLOCATED while Windows
plays its startup sound. Device-only retry recovers; the probe then records
1778 accepted tick buffers versus 22 initial unavailable buffers. P produces a
10035-byte file. Following movement, O restores all 4622 core-state bytes and
5253 presentation bytes exactly. SDL mixer capture uses signed16 stereo at
44100 Hz: title waiting at 20-40 seconds is silent, gameplay at 65-80 seconds
has RMS 452.64 and peak 18943, post-load at 98-110 seconds has RMS 462.75 and
peak 19837, and post-exit is silent. This separates game output from startup
sound. It proves the route, not smoothness: substantial silent gaps remain
at the accepted fixed low cycle budget. Host/RDP speaker audibility is not
certified by file capture.

The MZ payload links with the existing owned toolchain. The binder proves the
same DOS image, relocations, entry and stack in the final MZ/NE file. DOS minimum
resident allocation is 385840 bytes including PSP, maximum 389936, excluding
runtime cache allocations; DGROUP is 53088 with a 2048-byte stack. The new
Win16 audio/file heap is NE-only, not allocated by DOS. Product files remain
ignored local delivery outputs under assets/mario:

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 642781 | 43fec3438f2142fd3de7c9de01d43d021f74ccf1f18d789c7a818747de0299cb |
| mysmb32.exe | 411787 | 31175e55969dc8497e4ef363ed0f531fd50c4bf5df03ce06f6005ba27577cde1 |
| mysmb64.exe | 376939 | 63f5aaeb7b0a4e64c0da29221e2a6d3ed85736f7e68877467b1b207514dd8a73 |

Win16 remains window-only, Tab inert. Win3.0, standard mode, a 256-colour driver
and low-speed smooth audio remain unqualified. User-visible save/load and
music are submitted for owner acceptance; no next S is automatically admitted.

The final non-diagnostic hybrid repeats the native route: a deliberately
corrupted slot is rejected with snapshot error 11, gameplay continues, P
replaces it with a fresh 10035-byte CRC-valid slot, O resumes play, Tab stays
in the same graphical window, and Escape returns to Program Manager. This
run uses the exact published mysmb16.exe, not the receipt-instrumented build.
Build-only diagnostic code and SDL captures are never linked into products.

## S2 owner acceptance and S3 admission

On 2026-10-13 the owner accepts S2 and authorizes the next planned S.
S2 closes at c308fa7e with its P2/P3 bounded evidence, accepted fixed-cycle
performance limits and documented host/version/colour limitations. No unfinished
S2 obligation is silently transferred to source relocation. Win16 text/prompt
and unqualified hosts remain explicitly recorded in TODO. T44 remains open.

Acceptance cleanup removed the obsolete S1/S2 outputs and both native build
trees: 299984614 file bytes (about 286 MiB). The three published assets/mario
EXEs and the owned tools are preserved. The worktree's seventeen pre-existing
resource deletions remain unrelated and unstaged. Only S3 may now accumulate
active generated evidence under build.

S3 P1 is the admission/governance commit; it does not move production code or
rebuild unchanged products. The following implementation will inventory the
accepted source tree, record old/new paths and normalized source identities,
then move production code and repair build/include references as one coherent
change. Approximately 300 production files plus build/tool/current-authority
references are expected; the exact manifest precedes the move. Shared component
headers and implementations flatten directly into src/lib/component. Mario
core goes to src/app-mario/core; app/io/ppu/text/platform owners go below
src/app-mario/kvm. Reference-only harnesses stay test-only for S4.

S3 closure requires semantic identity apart from reviewed path/include edits,
no duplicate owners or compatibility bridges, passing native suites and purity
checks, actual DOS/Win16 links with MZ/NE validation, and three refreshed local
products. Existing tests retain explicit paths until S4; S5 retains the final
combined host acceptance. No Mine import or game behavior change is authorized
by this move. ROM node/edge scope, expected promotions and actual promotions
are all empty; prior conformance evidence is not expanded by relocation.

## S3 P2 closure and automatic S4 admission

Owner authorizes automatic closure/admission of each S after its gates.
S3 moved 318 files, including 311 C/header files whose SHA-256 identities
exactly match the pre-move source manifest. The mapping is deterministic:
app-mario/src/core goes to src/app-mario/core; the app/io/ppu/text/platform
owners go to src/app-mario/kvm; shared lib component src and include/component
flatten into src/lib/component. Seven build/readme files accompany their owners.
No function, declaration or source include changed in production. Existing
validation projections and tests remain at explicit old locations for S4.

CMake and fourteen tool entry points now use the moved owners. The similar-issue
sweep repaired dynamic DOS/Win16 source lists, direct entry-object selection,
OMF member discovery, probe include roots, two Windows fixture entry includes,
the DOS input fixture include, Python CTest entry paths and snapshot output
paths. The purity gate now rejects missing owner trees rather than silently
accepting an empty scan. Historical evidence paths are not reinterpreted.

Both configured widths pass 300/300 tests with no skip in this run. Actual
DOS and native Win16 builds pass; the hybrid binder checks 2651 relocations,
351131 DOS image bytes and resident bounds 385840-389936 including PSP.
The full DOS/Win16 product is byte-identical to the accepted S2 product.
Current documentation and responsibility-ledger gates pass. No new ROM-node
or control-edge credit is claimed. Published local artifacts:

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 642781 | 43fec3438f2142fd3de7c9de01d43d021f74ccf1f18d789c7a818747de0299cb |
| mysmb32.exe | 411787 | 85e18ac27f07aabf615e55463684186aa0095a968fd296333f1996262aac5ed5 |
| mysmb64.exe | 376939 | 306fdf8f7b47fa3cb2caa57b93c2093f2b05a5256758b006febb34aa827297a6 |

S4 now owns the mirrored test migration, fixture discovery, test-only reference
projection placement and current source-path metadata. Estimate: about 660
test/reference entries plus their CMake/tool callers. Each fixture receives a
production owner before moving; cross-owner tests name their composition owner.
Assertions and case counts must not be weakened or replaced by empty scans.
S4 does not change production C behavior or import Mine. Native build trees
are immediately reused as S4 active workspaces; obsolete S3-only probes and
intermediates are removed after this tracked receipt. S5 still owns final
combined host acceptance and complete active-build cleanup.


## S4 P1 closure and automatic S5 admission

S4 moves 661 test/reference files into mirrored owners. Core tests follow
core and its area/blocks/enemy/fireball/oam/player/world owners; presentation,
IO and host-composition checks follow kvm. Shared mechanism tests belong to
test/lib. Eight reference projection files belong to test-only ppu/validate.
Fixture includes are relative to their new owner; Python discovery finds the
repository independently of depth. A dormant dispatcher source-contract check
also receives its current core path and passes without assertion changes.

All moved C function bodies and assertions match HEAD after excluding include
directives. Production C/header files are unchanged from S3. Both configured
widths pass 300/300 tests with no skip. The dependency/purity and documentation
gates pass. Validation headers are absent from production include paths;
reference projections remain absent from product linkage. No product refresh
is required for these test/build-discovery-only changes; S5 publishes the final
integrated delivery. Mine receives core/kvm documentation directories only.

Current metadata has 10326 registry path references and 415 ledger references,
all resolving. Other registry evidence/dispositions and historical snapshot
hashes remain unchanged. The strict full-registry verifier still rejects an
inherited historical source hash: at the accepted S2 baseline seven paths
already mismatched and two former PIT paths were missing. These nine binding
gaps are recorded in TODO and the existing remaining-certification proposal;
path relocation is not a replacement ROM audit or a new certification claim.
Historical mapping is 1992/1992; retained local evidence is 1991/1992 nodes and
4260/4261 feasible controls (4342 raw, 81 infeasible). No counts are promoted.

S5 is automatically admitted under the owner's standing instruction. Scope:
final native build and real Console routes, qualified DOS/Win16 build inputs,
actual DOS device probe, product identities and final topology/documentation
review. Expected production changes: zero; expected tracked changes: fewer
than ten governance/receiving documents unless a concrete integration fault
requires a bounded repair. Existing native and DOS/Win16 object workspaces
are reused only as current S5 inputs; all obsolete generated outputs are
removed after the final tracked receipt. Seventeen unrelated resource
deletions remain preserved and unstaged. Mine import is still not admitted.
