# M3 T8 DOS Runtime Structural Evidence

## Outcome

The configured local DOS build now retains an ignored linker map alongside
the ignored MZ artifact.  The latest MZ has signature `MZ`, 295 relocations,
and 159,969 bytes; the link map is 2,222 bytes.  This is reproducible
structural evidence for the native DOS composition path.

## Bounded Runtime Disposition

No graphical DOS workload was launched in the available NTVDM validation
host.  Its local evidence explicitly says terminal presentation does not
claim graphical pixel presentation, and its historical records explicitly do
not claim a DOS graphics program executed.  Launching the infinite MZ loop
there would not demonstrate the VGA or B800 output and would not be a bounded
test.  The host capability gap therefore satisfies this task's documented
alternative exit condition.

## Containment

The MZ and map remain beneath an ignored build directory.  They are not
tracked evidence and contain no owner ROM material in the normal no-ROM
configuration.  The runtime wrapper remains build-only and does not become a
product dependency for Win32.

## Verification

- Configured OpenNT large-model DOS target linked the MZ and map.
- MZ signature, relocation count, and file sizes were read from local outputs.
- NTVDM host capability evidence was read-only and not modified.
- Documentation governance and `git diff --check` passed.

