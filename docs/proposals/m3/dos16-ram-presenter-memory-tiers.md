# DOS16 RAM presenter memory-tier qualification

## Objective

Qualify the accepted DOS16 RAM-composition presenter on real allocation tiers
without changing the translated game, shared PPU decisions, or final pixels.
The product policy is fixed: D/A/B must exist for graphical presentation, and
C is optional.

| Tier | Storage | Bytes | Policy |
| --- | --- | ---: | --- |
| D | Final 256-by-240 RAM screen | 61,440 | required |
| A | Decoded CHR cache | 8,192 | required |
| B | Packed two-nametable background | 63,488 | required |
| C | Byte-background upgrade | 61,440 | optional |

The derived presentation allocation is about 133 KiB for ABD and about 193 KiB
for ABCD.  The candidate must report actual DOS allocation receipts instead of
claiming a universal conventional-memory threshold from estimates.

## Scope

- `src/platform/dos16` allocation receipt and presenter measurement only.
- Existing exact PPU byte oracle, actual DOS16 link, and ignored DOSBox probes.
- The same warmed graphical route with pacing waits excluded from cost figures.

## Non-goals

- No core, ROM, shared PPU, input, audio, Win32, text, DOS4GW, emulator
  configuration, or extra full-frame cache.
- No changed allocation policy or hidden compact-presenter fallback.

## Planned S tasks

### S1 — runtime allocation receipt

Record whether D, A, B and C were actually retained across the admitted DOS16
launch configurations.  Verify that a missing required D/A/B follows the clean
exit path and that C failure retains the ABD presenter.

### S2 — matched memory-tier route comparison

Measure the same warmed title and gameplay route under ABD and ABCD, excluding
pacing waits and recording logical ticks, submitted frames, pixels and bytes.
Retain C only if its measured benefit justifies its additional 61,440 bytes.

## Acceptance

Both tiers must produce byte-identical PPU output, link and launch through the
existing DOS16 route, and preserve the owner-approved D/A/B-required rule.
The resulting receipt states measured cost, allocation outcome and the chosen
C policy; it does not make a NESticle-parity claim.
