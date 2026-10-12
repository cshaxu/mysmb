# M3 T41: Text presentation quality and test ownership

## Objective

Make the non-core text-presentation implementation have one shared sixteen-colour
projection, a documented conservative VT capability contract, bounded Win32 VT
storage, focused host adapters, and owner-closed tests.  The same neutral text
frame remains the sole input to DOS16, Win32 indexed Console API, and Win32 RGB
VT output.

## Scope and boundaries

- `src/io`: one portable projection from the frame's sixteen neutral RGB slots
  to standard sixteen-colour attributes.
- `src/platform/dos16`: consume that projection when writing B800 cells.
- `src/platform/win32`: separate session/input/geometry ownership from
  presentation; use the shared projection for `CHAR_INFO`; allocate a VT stream
  from the selected 25/50-row capacity.
- `test`: owner-local unit tests for the shared projection and presentation
  branches, plus one Windows/DOS integration route per changed adapter join.
- Architecture, coding and execution documentation, including closure cleanup
  and test-ownership rules.

No translated ROM/core/PPU/text-scene semantics, resource data, timing, DOS
graphics, process topology, terminal query, or third-party dependency changes.

## Capability contract

VT selection is deliberately **not** Microsoft Edit device-attribute
negotiation.  MySMB owns one game `CONIN$` path; querying a terminal through
that path was shown to surface a relay reply as Escape.  The adapter therefore
uses only output-buffer mode support plus its documented hidden-carrier
exclusion.  It must call this a conservative output selection, not proof that
an arbitrary host implements RGB VT.  The standard indexed projection remains
the safe fallback.

## Audit disposition

The audit found and closed one duplicated device conversion: DOS B800 and
Win32 `CHAR_INFO` now call `io/color` for the same neutral sixteen-slot
projection. They intentionally retain separate glyph and physical-write
owners because CP437/Unicode mapping and B800/Console API writes are distinct
host boundaries.

The adapter does **not** duplicate Microsoft Edit's device-attribute query.
That detector is unsuitable for this product: MySMB owns one `CONIN$` stream
and a query reply can be consumed as an Escape key by the game. The retained
contract is therefore narrower and testable: enable RGB output only when a
normal visible Console accepts the output mode; a hidden 2x4 carrier always
uses indexed cells. This is a deliberate, documented difference rather than
a process-name special case.

The former Win32 console monolith is split into lifecycle, input, geometry,
presentation and pure policy owners. The two composition-root fixtures that
include a `main_*.c` remain documented integration exceptions; no
`text_console*.c` implementation is included by a unit test. During closure,
the Console-write error/threshold decision was found to have only indirect
coverage, moved to the pure policy owner, and given one exhaustive owner-local
test.

## Planned S tasks

### S1 — Shared 16-colour projection and quality governance

Add a pure `io` projection helper and its owner-local unit test.  Route DOS
B800 output and Win32 indexed `CHAR_INFO` attributes through it, preserving
CP437-versus-Unicode glyph conversion in their respective adapters.  Add the
build-cleanup and test-owner/coverage requirements to project rules.  The
focused test compares canonical and source RGB palettes, all sixteen slots,
both foreground/background attributes, and output equivalence in each adapter.

### S2 — Win32 presentation boundary and bounded VT stream

Split the monolithic Win32 console source into session/input/geometry and
presentation owners without changing its public lifecycle contract.  Allocate
the RGB VT stream from `80 * selected_rows` and a documented per-cell bound;
test 25- and 50-row worst cases.  Correct stale test comments and ensure the
test seam observes public presentation behavior rather than depending on an
included production `.c` file.

The similar-issue sweep finds two remaining `main_win32.c` inclusions. They
are explicitly retained integration fixtures for the composition root's
file-scope lifecycle state and message joins;they do not unit-test static leaf
helpers,which have owner-local tests. Each fixture records that reason beside
its include. No `text_console*.c` source is included by a test.

## Test ownership receipt

| Owner and decision | One owner-local assertion | Distinct integration evidence |
| --- | --- | --- |
| `io/color`: canonical identity and authored RGB nearest-index projection | `mysmb.io-color-text-projection-smoke`, all sixteen slots per branch | DOS B800 and Win32 indexed writers consume the same helper. |
| Win32 policy: selected rows, bounded VT capacity, carrier/mode selection and Console write-result classification | `mysmb.win32-console-capability-smoke` | Product self-test covers the selected presenter path. |
| Win32 presentation: exact RGB SGR encoder, bounds and invalid glyph failure | `mysmb.win32-console-capability-smoke` | `mysmb.win32-x86/x64-self-test` and `mysmb_win32_text_switch_smoke` prove the device/session join. |
| Win32 lifecycle/input/geometry | Their public return contracts stay in their owners | `mysmb_win32_parent_console_smoke` exercises borrowed-console restore and real Console API geometry. |
| DOS B800 text join | The shared projection unit provides the conversion assertion | `dos16_video_lifecycle_probe` verifies the physical B800 attributes, glyphs, mode restoration and keyboard join. |

`main_win32.c` and `main_dos16.c` includes are documented composition-root
integration exceptions: each fixture needs the root's file-scope state in one
translation unit. They must not add duplicated leaf-branch assertions. No
other production implementation file is included by a text-presentation unit
test.

`mysmb_win32_parent_console_smoke` and
`mysmb_win32_text_switch_smoke` require a classic borrowed Console and a
private desktop respectively. They are therefore grouped by the explicit
non-default `mysmb_win32_host_integration` CMake target rather than registered
as ordinary CTest tests, whose worker can be a ConPTY and cannot prove that
host contract. The target writes only below its build directory.

### S3 — Cross-adapter closure

Run complete unit and integration matrices, x86/x64 builds and product self
tests, link DOS16, run platform-purity and documentation governance checks,
refresh all three local executable artifacts for code changes, and record a
coverage/ownership receipt.  After owner acceptance, remove generated build
artifacts while retaining concise tracked evidence.

## S3 verification evidence

The closure uses the established DOS16 route, rather than treating a direct
host invocation of an obsolete linker wrapper as authoritative: OpenNT CL16
produces OMF, `PrepareDosLink365Omf.py` groups it, and the private DOSBox
Microsoft Segmented-Executable Linker 5.10 emits the MZ image. The current
route compiled 174 checked objects and emitted `mysmb-dos16.exe` (350,511
bytes). `VerifyDos16Memory.py` passed with 49 segments, 52,624 DGROUP bytes and
387,520 bytes page-rounded maximum loaded memory. `Invoke-DosBoxIoProbe.ps1`
then exercised actual title, gameplay input, release and Escape-exit behavior.

The corresponding x86 and x64 builds each completed their 283-test CTest
matrix, including the policy-owner smoke. The three local product outputs are
refreshed only from those validated builds. The active packet records their
hashes and awaits owner acceptance before generated task output cleanup.

P9 completed the named private-desktop host-integration target. Its owned
fixture is launched below a detached no-Console `cmd` parent, so it cannot
accidentally exercise the separately tested borrowed route. The test now
requires exact selected geometry and `CHAR_INFO` cells only for the indexed
Console API projection. A VT host may retain its own valid restored viewport
or omit classic maximize/system-menu decoration; the product clips RGB output
to that viewport. Exact RGB SGR formatting, capacity exhaustion and invalid
glyph rejection are asserted once by `mysmb.win32-console-capability-smoke`.

### P10 independent closure audit

A final source-level sweep confirms that the portable 64-to-16 text mapping
has its intended two scene consumers (`text/layout` and
`text/background_scene`), while DOS B800 and Win32 indexed Console are the
only physical-device consumers of `mysmb_io_color_text_attributes`. The RGB
VT encoder reads the resulting neutral text frame directly; it introduces no
second palette conversion or gameplay decision.

The only test-side production implementation includes are the three documented
composition roots (one DOS, two Win32). No `text_console*.c` implementation is
included by a test. The non-core source, test and CMake sweep has no
TODO/FIXME/TEMP markers, `git diff --check` is clean, and no source or product
change was made by this audit. This is a closure receipt, not a replacement
for owner acceptance and the required post-acceptance build cleanup.

## Acceptance

1. DOS and Win32 indexed output use the same tested 16-slot projection.
2. Win32 RGB VT remains available only through the documented conservative
   selection; no terminal input query is reintroduced.
3. A 25-row VT session allocates no 50-row stream capacity.
4. Source files have one named ownership role; tests exercise each changed
   decision/return path once under their owner, with integration tests limited
   to real cross-owner joins.
5. All configured unit/integration tests and required target builds pass.
6. Each owner-accepted closure leaves `build/` free of generated task outputs;
   only tracked evidence describes the completed run.

## Owner acceptance and archival

The owner accepted T41 on 2026-10-12. The generated build, probe, trace and
log outputs were removed after acceptance. This retained record is the
reviewable closure evidence; the task has no active packet or queue entry.
