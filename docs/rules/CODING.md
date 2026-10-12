# Coding Standard

The concrete source map is [Source Layout](../design/CODING.md).

## Source Discipline

- Shared translation code uses portable C90 unless an admitted task records a narrow compatibility exception.
- Use explicit `unsigned char`, `unsigned short`, and bounded arrays for original machine-width state; do not depend on host `int` or pointer width.
- A translated unit names its reviewed address range and uses clear symbols only after that mapping is documented.
- Keep source and comments English and ASCII. Keep each file focused on one owner and do not create wrappers that merely forward the same state.
- Platform-specific APIs belong below the platform boundary.

## Test Boundaries

Tests live under `test/` and follow their source owner. Owner-ROM oracle runs, raw traces, generated comparison data, and protected artifacts stay local and ignored; tracked tests contain only project-owned harness logic and neutral metadata.

Each production owner has focused tests for every changed decision and return
contract.  A unit test names one owner and asserts each behavior once; a second
test may cover it only when it proves a distinct boundary or lifecycle join.
Avoid tests that include production implementation files merely to reach static
internals when a narrow declared test seam can exercise the same contract.

An integration fixture that requires a real host capability unavailable to a
normal CTest worker (for example a private desktop or a classic borrowed
Console) must have a named, non-default CMake host-integration target. Its
command, required capability and result are recorded in the owning task. It
must not be silently omitted merely because a headless/ConPTY CTest worker
cannot represent that host contract.
