# MySMB

MySMB is a planned source-level C translation of the NES **Super Mario Bros.**
program. Its aim is to preserve the original program logic and data semantics,
then compile the shared C implementation for 16-bit, 32-bit, and 64-bit hosts.

## Start Here

Project authorities, task lifecycle, and active work are in the [Documentation Guide](docs/README.md). M2 is translating the native C game route after the M1 title foundation; owner-local ROM inputs remain outside the tracked product.

## Project Boundary

MySMB does not distribute Nintendo ROM bytes, graphics, music, derived C/data, or ROM-embedded executables. An owner may provide a local ROM to an admitted research or build task; all resulting protected material stays ignored and local. The portable C source, validation harnesses, and host adapters are the only intended tracked product material.

## Local builds

All normal CMake builds use Ninja and ccache. Build output, generated program
data, diagnostics and test files remain below the ignored `build/` directory.
The cache is developer-local and is not a repository artifact.

Set local inputs only through environment variables; do not add machine paths to
the repository:

```powershell
$env:MYSMB_ROM_PATH = '...'
$env:MYSMB_ASM_PATH = '...'
$env:MYSMB_OPENNT_CL16 = '...'
$env:MYSMB_DOS_RUNTIME_DIR = '...'
```

Configure and build the Win32 products with separate x64 and x86 trees:

```powershell
cmake --preset ninja-ccache-x64-release
cmake --build --preset win32-x64
ctest --preset test-x64

cmake --preset ninja-ccache-x86-release
cmake --build --preset win32-x86
ctest --preset test-x86
```

The `dos16` build preset uses the x64 Ninja configuration only as the CMake
driver; its product is still built by the configured OpenNT 16-bit toolchain.
It requires `MYSMB_OPENNT_CL16`, `MYSMB_DOS_RUNTIME_DIR`, and the owner-local
ROM path. `ccache -s` reports local compiler-cache reuse.
