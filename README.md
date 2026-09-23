# MySMB

MySMB is a planned source-level C translation of the NES **Super Mario Bros.**
program. Its aim is to preserve the original program logic and data semantics,
then compile the shared C implementation for 16-bit, 32-bit, and 64-bit hosts.

## Start Here

Project authorities, task lifecycle, and active work are in the [Documentation Guide](docs/README.md). The product is intentionally at M0: there is no admitted ROM import or game translation yet.

## Project Boundary

MySMB does not distribute Nintendo ROM bytes, graphics, music, derived C/data, or ROM-embedded executables. An owner may provide a local ROM to an admitted research or build task; all resulting protected material stays ignored and local. The portable C source, validation harnesses, and host adapters are the only intended tracked product material.
