# Retained Presentation Performance Qualification

## Purpose

M3 T39 continues performance work after closed T38. It preserves T38 S18's
accepted current-background sprite-union presenter and has zero ROM-node and
control-edge scope. The task first investigates why the owner-observed
NESticle reference is stable where the current DOS product visibly flickers
and stalls; it then uses only independently derived, compatible ideas to
qualify further MySMB work.

## Third-party research boundary

S1 may copy the owner-provided historical 1997 NESticle source archive into
an ignored `build/` directory. It is an unredistributable research reference:
no third-party source, binary, ROM, generated output, assembly, data table or
translation may be committed, copied, transliterated or linked into MySMB.
The receipt records archive identity only in ignored local evidence and tracks
neutral findings in the eventual closure record. Its exact purpose is to
inspect the video presentation, cache invalidation, sprite priority and frame
submission mechanisms, and to compare their cost model with the current
MySMB PPU and DOS device boundary. An optional local build/probe stays below
`build/`; it cannot alter DOSBox's persistent settings or become an
implementation dependency.

Historical public 0.2-source observations are context only. The S1 archive
must identify itself before conclusions are attributed to it; source-version
claims and binary-version claims remain distinct.

## Planned S sequence

| S | bounded owner | completion condition |
| --- | --- | --- |
| S1 | Read-only source/probe comparison of the owner-provided historical NESticle video pipeline and MySMB's selected retained presenter. | Archive/version receipt; concrete render/cache/transfer findings; a compatible/rejected opportunity matrix; zero product edits. |
| S2 | Rebuild a no-readback PIT fixture from selected product source and time the post-Start route at `core=normal`, `cycles=fixed 3000`. | Same source/presenter identity as the selected MZ; a separate prior 260-frame physical oracle; comparable root-step delta against T38 S10's 39,026 ticks. |
| S3 | Attribute retained graphics only if S2 still exceeds the 16.67ms frame budget. | One named >=20% owner and one bounded candidate, or explicit no-change rejection. |
| S4 | Attribute DOS and Win32 text paths separately; test at most one exact changed-cell or batched-output improvement. | Exact neutral cells, colors, request order and text-mode lifecycle. |
| S5 | Package and target-era qualification. | Current x86/x64/DOS16 artifacts, DOS memory/stack receipt, and explicitly limited 486-class or calibrated run receipt. |

The prior private `cycles=max` result remains diagnostic only. It cannot be
compared with fixed-3000 evidence. S1 does not reopen S18 exactness, change
game/PPU policy, reduce cadence, skip frames, change output dimensions, or
introduce DOS4GW, a 32-bit DOS dependency, a helper process, or a persistent
DOSBox configuration change.
## S1 research result: historical NESticle video pipeline

S1 inspected two strictly local-only inputs below ignored build output: the
owner-provided x.xx binary package and a read-only historical source tree at
public revision `7ede7dab54bc0cef85774b424025a7d6b8133d28`. The owner archive
hash matches the earlier local binary receipt. It contains only the executable
and README; it is not source. The source tree's own front end identifies
version 0.2, so its render architecture is evidence about that historical
source line, not proof of the x.xx binary's exact implementation.

### Direct source facts

- A `natablecache` owns a 256x240 surface per real nametable. It records
  per-tile and per-line dirty flags. A nametable byte write dirties one tile;
  an attribute write dirties its affected 4x4 tile region. Cache refresh locks
  a surface only if a dirty line exists, redraws only marked 8x8 tiles, then
  clears those marks.
- Every displayed background section first attempts a clipped blit from those
  cached surfaces. It falls back to tile drawing only when its selected pattern
  table differs. Pattern-table changes are converted to affected-tile marks,
  rather than forcing the entire surface to be repainted.
- Palette-slot information is stored in the cached pixels. Palette refresh
  updates only marked entries of a 32-entry palette; it does not recolor every
  cached background pixel.
- Moving objects are still redrawn every displayed frame: the video draw path
  does background-behind-sprites, then walks all 64 sprites in descending
  order, then draws foreground-priority background. Therefore NESticle does
  **not** become smooth by leaving Mario unchanged; the background cache is
  what removes most of the static-world reconstruction work.
- The visible tile and sprite fast paths use flat 32-bit assembly (`.486`,
  `MODEL flat`, 32-bit registers and DWORD stores). The supplied binary README
  separately declares DOS4GW, VESA support, optional VSync and manual/auto
  frameskip. Those are incompatible as a direct MySMB implementation source:
  MySMB remains a real-mode DOS16 program with no frame skipping.

### Presentation/flicker finding

The source declares distinct `video` and virtual `screen` pointers, and its
README exposes a VSync option. That supports a buffered/paced presentation
model, but the supplied source tree omits the DOS implementation of the
surface/present interface. Its DOS project includes a missing private make
fragment; the expected historical compiler is also unavailable locally.
S1 therefore cannot claim that the x.xx executable page-flips, waits for
retrace by default, or uses any particular VESA mode.

By contrast, the selected MySMB DOS retained presenter writes current HUD and
sprite tile bytes directly to the presently visible A000 aperture while
presenting. There is no vertical-retrace gate or display-page swap in that
path. End-of-frame pixels are exact, but the monitor/emulator can expose the
intermediate writes; this is a concrete explanation for the owner's observed
Mario refresh flicker. It is separate from game logic and from the static
background-cache mechanism.

### Opportunity matrix

| Finding | MySMB status | Next action |
| --- | --- | --- |
| Background dirty tracking and current-background reconstruction | Already present through the selected S18 retained presenter. | Keep; do not duplicate a full nametable surface. |
| Indexed palette slots and palette-only updates | Already present in the shared slot compositor/DOS DAC path. | Keep; quantify no change. |
| Full 64-sprite redraw each visible frame | Required by both the historical source and MySMB semantics. | Do not suppress Mario redraw. |
| 32-bit flat assembly/DOS4GW | Incompatible with DOS16/MS-DOS 5 baseline and higher memory/runtime requirements. | Reject. |
| Frameskip | Changes observed presentation cadence. | Reject. |
| Buffered display page plus vertical-retrace handoff | Plausible cure for visible tearing, but historical source does not prove the exact DOS backend. | S2 first establishes source-matched fixed-cycle timing; a later device-only feasibility S may inspect CRTC page-flip/retrace capacity, memory cost and exact frame semantics. |
| Full 256x240 cached nametable surfaces | Historical source likely consumes at least two 61,440-byte surfaces in its 32-bit DOS runtime. | Reject as a direct DOS16 copy; compare only against MySMB's existing compact derived cache and memory policy. |

S1 does not change product source, artifacts, ROM-node status or control-edge
status. It identifies direct-visible VRAM updates as a separate presentation
quality question, but does not yet establish the cost, hardware feasibility or
correctness of a page-flipped MySMB device path.
