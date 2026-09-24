# M3 T6 OpenNT MZ Link

## Outcome

The local OpenNT large-model toolchain now produces an ignored MySMB DOS MZ
artifact from the actual native game, render adapters, DOS root, and DOS main
unit.  The artifact is 159,117 bytes; its header begins `MZ`, declares 288
relocations, and has a six-paragraph header.  It is a local build product and
is not tracked or distributed.

## Runtime Boundary

The build uses a local historical large-model C runtime only when the explicit
`MYSMB_DOS_RUNTIME_DIR` CMake configuration is supplied.  It requires
`LLIBCE.LIB` and `LVARSTCK.OBJ`; the project copies neither one.  OpenNT is
compiled with `/AL /Gs`, avoiding an otherwise unresolved stack-check helper.
The linker warns that optional `OLDNAMES.LIB` is absent but emits the MZ file
with no unresolved externals.

The four 16,000-byte VGA pages are explicitly far only under the DOS OpenNT
compile define.  This keeps them outside the 64KB DGROUP and leaves modern
platform builds unchanged.

## Scope Limit

The DOS main currently drives one native frame through no-op input and
presentation callbacks.  It proves a real executable link and the code/data
model; it does not yet program BIOS input, VGA memory, timing, or continuous
play.  Those hardware hooks are M3 T7 work.

## Verification

- ROM-free CTest: 27 of 27 passed.
- Owner-local CTest: 29 of 29 passed.
- Win32 x86 and x64 builds passed.
- Configured OpenNT DOS target compiled and linked the ignored MZ artifact.
- Documentation governance and `git diff --check` passed.

