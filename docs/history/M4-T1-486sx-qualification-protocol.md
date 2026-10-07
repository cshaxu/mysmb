# M4 T1 486SX Qualification Protocol

## Purpose

This protocol prepares the physical-host evidence required to qualify the
native DOS build.  It records observations; it does not make a performance
claim before a 25MHz 486SX test run.

## Build Input

1. Configure the local OpenNT compiler and reviewed DOS runtime directory.
2. Build the `mysmb_opennt16_dos` target.
3. Transfer only the generated local MZ executable and any required local
   runtime files to a physical MS-DOS test disk.  Do not transfer ROM-derived
   material or commit the executable.
4. Record executable size, MZ signature, relocation count, and link-map size
   before transfer.

## Physical Host Record

| Field | Required observation |
| --- | --- |
| CPU | Exact 486SX model and measured or documented clock rate. |
| Memory | Conventional and extended-memory configuration. |
| DOS | Exact MS-DOS version and boot configuration. |
| VGA | Adapter identity and monitor mode. |
| Storage | Boot and executable media type. |
| Build identity | Git commit and local MZ structural values. |

## Route Script

1. Launch the MZ in VGA mode and observe the first frame for at least ten
   seconds; record visual corruption, mode-reset behavior, and control
   response.
2. Hold Right through the native title-to-play route.  Record title transfer,
   entrance completion, and held-Right checkpoint state using the same
   neutral checkpoints as M2 T8.
3. Press Tab. Confirm that the 80x25 colored-object view has full background
   fill and object glyph overlays. Press Tab again and confirm VGA return.
4. Repeat the route three times.  Record elapsed wall-clock time for a fixed
   600-frame window, input latency observations, mode-switch outcome, and
   any halt, corruption, or reset.
5. Record all deviations rather than compensating with a host-specific code
   change.

## Acceptance Evidence

The completed physical report must include the above host facts, three route
outcomes, bounded timing samples, observed keyboard behavior, both display
modes, and the exact executable build identity.  Absence of a physical host
is a missing observation, not a failed or successful qualification.
