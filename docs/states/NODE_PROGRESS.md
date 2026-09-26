# M2 ROM conformance node progress

This is the quantitative progress report for the native C port. Its complete named ledger is the [SMB1 ROM migration inventory](../etc/architecture/smb1-rom-migration-inventory.md): every one of its 1,992 rows is one ROM label node.

## Current baseline

| ROM-match state | Nodes | Named source |
| --- | ---: | --- |
| ROM-match complete | 0 | None. |
| C owner mapped, route trace still pending | 57 | The exact names are listed below. These are **not** completed matches. |
| Open / unmatched | 1,935 | Every `open` row in the canonical inventory; that table is the complete named list. |
| **Total** | **1,992** | Canonical inventory. |

The progress fraction is therefore **0 / 1,992 ROM-matched nodes**. A C file, structural extraction, focused smoke test, or executable build does not make a node a match. It becomes complete only after the original branch semantics, state writes, and affected ROM-reference frame trace are recorded in its inventory row.

## Completed matches

None.

## Mapped but not yet matched (57)

These names have a current C owner but have not passed the required source-route comparison. They remain unfinished.

| ROM line | Node |
| ---: | --- |
| 6298 | `ProcFireball_Bubble` |
| 6352 | `FireballObjCore` |
| 12805 | `GetFireballBoundBox` |
| 14254 | `DrawFireball` |
| 14283 | `DrawExplosion_Fireball` |
| 14424 | `PlayerGraphicsTable` |
| 14457 | `SwimKickTileNum` |
| 14460 | `PlayerGfxHandler` |
| 14466 | `CntPl` |
| 14489 | `SwimKT` |
| 14495 | `BigKTS` |
| 14497 | `ExPGH` |
| 14499 | `FindPlayerAction` |
| 14503 | `DoChangeSize` |
| 14507 | `PlayerKilled` |
| 14511 | `PlayerGfxProcessing` |
| 14532 | `SUpdR` |
| 14535 | `PlayerOffscreenChk` |
| 14547 | `PROfsLoop` |
| 14551 | `NPROffscr` |
| 14561 | `IntermediatePlayerData` |
| 14564 | `DrawPlayer_Intermediate` |
| 14566 | `PIntLoop` |
| 14587 | `RenderPlayerSub` |
| 14601 | `DrawPlayerLoop` |
| 14610 | `ProcessPlayerAction` |
| 14626 | `ProcOnGroundActs` |
| 14642 | `NonAnimatedActs` |
| 14649 | `ActionFalling` |
| 14654 | `ActionWalkRun` |
| 14659 | `ActionClimbing` |
| 14666 | `ActionSwimming` |
| 14676 | `GetCurrentAnimOffset` |
| 14680 | `FourFrameExtent` |
| 14684 | `ThreeFrameExtent` |
| 14687 | `AnimationControl` |
| 14701 | `SetAnimC` |
| 14702 | `ExAnimC` |
| 14705 | `GetGfxOffsetAdder` |
| 14712 | `SzOfs` |
| 14714 | `ChangeSizeOffsetAdder` |
| 14718 | `HandleChangeSize` |
| 14728 | `CSzNext` |
| 14729 | `GorSLog` |
| 14734 | `GetOffsetFromAnimCtrl` |
| 14741 | `ShrinkPlayer` |
| 14750 | `ShrPlF` |
| 14753 | `ChkForPlayerAttrib` |
| 14767 | `KilledAtt` |
| 14774 | `C_S_IGAtt` |
| 14781 | `ExPlyrAt` |
| 14786 | `RelativePlayerPosition` |
| 14797 | `RelativeFireballPosition` |
| 14846 | `GetPlayerOffscreenBits` |
| 14851 | `GetFireballOffscreenBits` |

| 3737 | `CastleObject` |
| 10509 | `StarFlagExit` |

## Reporting contract

At **S admission**, the proposal and active packet must state the baseline as `ROM-match complete / 1,992`, name every inventory label the S may change, and state the node's incoming status. At **S closure**, the closure report must repeat the fraction, name every label whose status changed, link the evidence that allows each changed label to count as a match, and name every deferred label and its owner. No aggregate increase is allowed without matching inventory-row updates.

Every M2 P report also retains the existing delivery record: refreshed `assets/mysmb16.exe`, `assets/mysmb32.exe`, and `assets/mysmb64.exe`, their build/validation result, and the ordinary source/evidence/deferred-issue summary. The three executables demonstrate target delivery; they do not replace per-node ROM conformance evidence.
