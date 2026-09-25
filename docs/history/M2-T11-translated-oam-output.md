# M2 T11: Translated OAM Output

## Result

T11 closes the native OAM production route. The C core writes player, regular
and special enemy, projectile, item, effect, score, platform, boss, Retainer,
and Jumpspring OAM through source-owned writers before the NMI snapshot.

## Evidence

The owner-local ROM reference and the current native x64 recorder used the
same 600-frame script: Start on frames 0-1, then Right from frame 150. Both
used the normal title-bootstrap route. The derived build comparison records
zero differing bytes for CPU OAM RAM, submitted OAM, both CIRAM pages,
palette, and all seven PPU-visible scalar fields.

Focused C90 regressions cover the source semantics of the individual writers,
including the Retainer victory route, Jumpspring animation route, and the
player vertical-clipping condition derived from the former reference mismatch.
The x86 and x64 suites pass; the OpenNT large-model MZ links.

## Boundary

The comparison still reports differences in CPU stack, zero page, and
translated work RAM. Those are not waived by this OAM result. T12 audits the
Win32 consumer and controller boundary; T13 classifies every remaining
frame-state difference on its route-specific phase.