# Withdrawn: DOS16 full-screen VGA-copy candidate

Owner-directed T46 S5 removes D and the full-screen presenter. This unadmitted
candidate is superseded and removed from QUEUE; no T identifier was allocated.
The accepted band-copy primitive remains. Original proposal follows as history.

# DOS16 contiguous VGA-copy code-generation qualification

## Objective

Keep the final `256 x 240` selected-pixel RAM surface and its exact shared PPU
semantics, but qualify whether the OpenNT large-model C compiler can emit an
efficient, fixed-length contiguous VGA transfer for its `61,440` bytes.  This
candidate is confined to the physical DOS16 submission boundary.

## Why this is first

The RAM-composition path leaves exactly one high-volume hardware transfer:
copying the completed frame from conventional/far RAM to A000.  The transfer
contains no game, PPU, palette, scroll, sprite, priority, clipping or input
decision.  A compiler-directed bulk copy preserves the existing architecture
while avoiding an unnecessary assembly ownership boundary.

## Scope

- `src/platform/dos16` only, principally the final RAM-screen presenter.
- A focused DOS16 assembly/listing inspection and ignored DOSBox timing probe.
- Existing exact RAM-compositor byte oracle and actual product route.

## Non-goals

- No core, translated-ROM, shared PPU, Win32, text, cadence, frame-skip,
  DOSBox configuration or resource change.
- No gameplay logic in a platform component.
- No handwritten assembly unless the C code-generation gate explicitly fails.

## Planned S tasks

### S1 — fixed-copy C code-generation and listing receipt

Replace the general-purpose final-copy loop with one DOS16-only C function
whose source and destination are explicit far pointers and whose size is the
constant `61,440` bytes.  It has no callback, per-pixel condition, palette
work, plane selection or variable length.  Build with the current OpenNT
large-model toolchain, preserve the generated listing/disassembly below
`build/`, and inspect its inner loop.

Accept S1 only when the generated loop uses contiguous word/DWORD transfer
without repeated far-address setup or helper calls per pixel.  It must retain
an exact byte-output check and a fixed-cycle measurement against the current
submission function.  If it is not materially better, restore the current C
path and record the rejection.

### S2 — bounded assembly fallback decision

Only if S1 proves the compiler cannot generate a suitable contiguous loop,
implement a minimal DOS16 assembly-equivalent transfer with the same typed C
interface.  It may copy exactly the already-composed `61,440` bytes and may
not read game/PPU state or write VGA registers other than the transfer's
existing destination.  Compare listing, exact bytes, register preservation,
DOS16 link/run and the same fixed-cycle route before accepting it.

## Acceptance

The selected implementation must preserve every final pixel byte and all
platform boundaries, improve or match the current final-copy cost on the
identical DOSBox fixed-cycle route, keep conventional-memory use unchanged,
and leave an ordinary C fallback available.  A source change refreshes the
three local target artifacts under the repository's delivery policy.
