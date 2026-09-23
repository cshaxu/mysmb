# M1 Native Title-Scene Runtime

## Purpose

Use the generated static C boot/title dependency slice to produce the first
native Win32 SMB1 title scene. The executable embeds only locally generated
owner material and is ignored.

## Dependencies

Requires the platform foundation and static-C source pipeline. The Win32
renderer consumes direct tile/sprite/palette commands; it does not run a NES
CPU or generic PPU.

## Acceptance

Both Win32 architectures launch to the translated title scene, accept title
buttons, and retain 16-bit-compatible core compilation. Every participating
routine has source-address provenance.
