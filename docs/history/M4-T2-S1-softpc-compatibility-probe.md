# M4 T2 S1 — SoftPC Compatibility Probe

## Outcome

An isolated local SoftPC copy booted a copied DOS floppy carrying the current
16-bit MZ probe for fifteen seconds without the host process exiting. The
probe is compatibility evidence for the DOS loader, BIOS-facing composition
root, and sustained VM execution only. It is not a substitute for the M4
physical 25 MHz 486SX qualification, a measured frame rate, or a visual
gameplay claim.

## Local-Only Media Boundary

- The owner authorized use of a local SoftPC executable, configuration, DOS
  boot floppy, and the local MySMB MZ.
- The probe used copied media only. To make room for the MZ, the copied disk
  removed the non-boot-critical QBASIC executable; the supplied disk remained
  unchanged.
- The copied AUTOEXEC command starts `MYSMB.EXE`. The injected MZ was 159969
  bytes and had SHA-256 `8bd21f4d0d267b6e21d03e10affbd674afa1afece23fbda5e4a2d62d7b041b63`.
- No copy, guest-media byte, ROM, screenshot, configuration, or generated
  executable is tracked or distributed.

## Observation

The isolated VM process remained alive after a bounded fifteen-second boot.
The probe instance was then terminated by the invoking test. No display
capture or interactive input was used, so this record does not assert a
visible title, gameplay state, keyboard response, or graphics fidelity.

## Disposition

Physical-host M4 T2 remains open. The owner-local ROM-bound Win32 packages
are separate from this ROM-free DOS probe.
