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

### S3 — Cross-adapter closure

Run complete unit and integration matrices, x86/x64 builds and product self
tests, link DOS16, run platform-purity and documentation governance checks,
refresh all three local executable artifacts for code changes, and record a
coverage/ownership receipt.  After owner acceptance, remove generated build
artifacts while retaining concise tracked evidence.

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
