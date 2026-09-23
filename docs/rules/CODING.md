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
