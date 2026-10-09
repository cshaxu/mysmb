# Queue

## To-Do

This file lists pending work,including explicitly owner-suspended work. It is not a source-order archive,
a task ledger, or a record of completed work. Active work is recorded only in
[CURRENT.md](CURRENT.md); closed tasks remain in their proposal/history record
and in the generated [node/task ledger](NODE_TASK_LEDGER.md).

1. [DOS16 contiguous VGA-copy code-generation qualification](../proposals/m3/dos16-contiguous-vga-copy.md) - new owner-directed candidate; first force the existing C path to compile as a fixed 61,440-byte contiguous far transfer and inspect the generated DOS16 loop. Admit a tiny assembly fallback only if that C code-generation gate fails. Preserve shared PPU/game semantics and measure exact output plus fixed-cycle cost.

2. [DOS16 RAM presenter memory-tier qualification](../proposals/m3/dos16-ram-presenter-memory-tiers.md) - close the accepted RAM presenter with actual D/A/B/C allocation receipts and matched ABD-versus-ABCD route timing; D/A/B remain required and C remains optional.

3. [NTVDM16 MySMB DOS launch compatibility](../proposals/m3/ntvdm16-mysmb-launch.md) - new owner-directed candidate; reproduce why the current mysmb16.exe cannot start in the owner run16 NTVDM environment, then repair the smallest DOS16 platform/startup incompatibility. Acceptance requires NTVDM graphics, controls and clean exit; DOSBox remains a separate compatibility check.

4. [Bounded Windows audio startup](../proposals/m3/bounded-windows-audio-startup.md) - retained M3 T19 S1,unfinished and suspended by owner;single-process lifetime prototypes,implementation and verification remain. Resume existing identifiers after the active VGA/performance task;no repair acceptance.

5. [Remaining current-equivalence certification](../proposals/m2/remaining-current-certification.md) - queue tail;130 owner groups/910 facets,two evidence gaps,13 route/pixel slots and four pending final packages. Includes the owner's [RAM/cache and display-phase handoff checks](../proposals/m2/remaining-current-certification.md#owner-directed-state-handoff-checks),with a named applicability recheck of retained NMI evidence. Retain prior scoped proofs;planned S slots and exact IDs are in the proposal/ledger. No task number or admission yet.

6. [Embedded C resource source](../proposals/m3/embedded-rom-c-source.md) - new owner-directed candidate; convert the complete owner ROM resource image into reviewed C hexadecimal arrays for common PRG, CHR/sprites/background tiles, title, area, music and sound data, then remove all build/runtime ROM-file dependencies. The task requires a scoped source-policy exception and explicit provenance/distribution decision before generated source is committed; allocate its T identifier only on admission.
