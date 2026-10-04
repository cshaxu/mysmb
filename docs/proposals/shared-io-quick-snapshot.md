# Candidate: shared I/O quick snapshot

Owner scheduling amendment (P153):remaining M2 acceptance verification is
queued after the three I/O/presentation candidates. Earlier proof completion
prerequisites are superseded by this explicit order;retain scoped evidence and
rebind affected dependencies at admission. This does not certify M2.

## Purpose and queue dependency

Add one quick-save slot shared by DOS16 and Win32. P saves to `mysmb.sav`
beside the running executable; O loads that file and immediately continues
gameplay. This is an unnumbered T candidate at the end of the queue. Admit it
only after the preceding shared I/O graphic-frame candidate has completed its
`src/io` component split. Its planned S slots are
a forecast, not admitted work or ROM-node completion credit.

The feature belongs to `src/io`: it owns the snapshot schema, validation,
save/load orchestration, transaction rules, and error-log contract. DOS16 and
Win32 adapters only translate physical P/O key edges and supply the few
host-specific services needed to find the executable directory, read/write
files, replace a completed file, and reset device output. The game layer owns
translated state and remains unaware of filenames, filesystem calls, and
physical keys. The two hosts read and write the same versioned file format.

## User behavior and files

- P saves one complete running-frame boundary, replacing the previous slot.
  While the game is paused, P saves the cached last completed running frame;
  loading that snapshot resumes gameplay without another Enter press. P on a
  screen without a running gameplay frame has no effect.
- O may be pressed at the title screen or during gameplay. A valid snapshot
  replaces the current state and resumes immediately. P and O are handled
  once per physical key press, only by the focused/active host, without
  injecting controller buttons or repeating while the key is held.
- The directory is the executable's directory, independent of the process
  working directory. The only fixed filenames are `mysmb.tmp` for the pending
  save, `mysmb.sav` for the completed slot, and `mysmb.log` for diagnostics.
  DOS16 and Win32 both implement this behavior.
- Every save or load failure is silent to the player: no dialog, title change,
  pause, reset, input change, or partially loaded state. Attempt to append a
  short diagnostic record to `mysmb.log` for each failure, including a missing,
  corrupt, or incompatible save. Failure to open or write the log is also
  silent and never recursively logged. Do not log snapshot contents or
  owner-local resource bytes.

## Snapshot boundary and format

The existing visible `frame_snapshot` is not sufficient to resume execution.
Capture the authoritative game state required by the next logical tick:
frame number, CPU RAM, both name tables, visible OAM and PPU state, palette,
APU command/register state, and any remaining mutable game-owned fields.
Capture the audio renderer's playback state too; restoring only APU register
values would lose active envelopes, lengths, sweep timing, and oscillator
phase. Save at a boundary after the previous tick's audio writes have been
consumed, and do not replay those writes on load. Rebuild the presented frame
from restored game state.

The wire format has an explicit magic, version, payload length, integrity
check, state-schema revision, and owner-local resource fingerprint. Encode
fields with fixed widths and byte order; never dump a C struct, pointer,
padding, Win32 handle, DOS pointer, floating-point layout, or queued audio
device buffer. Rebind immutable PRG/CHR/title resources from the current
executable after loading. A resource or schema mismatch fails without
changing the live game. The save may contain ROM-derived working data, so it
is local user output and must never enter source control or release fixtures.

Saving writes and flushes the complete candidate to `mysmb.tmp` in the same
directory. Only after validation and successful close does the host replace
`mysmb.sav`. Win32 uses an atomic replacement where available. DOS file
renaming cannot be assumed to replace an existing destination atomically;
with only the specified temporary and final names, interruption during the
short DOS replacement window may lose the old slot. The DOS adapter must
minimize and test that window, while all failures leave the running game
unchanged. Loading first parses and validates into separate
staging storage, then performs one commit at a frame boundary. Staging must
fit the DOS16 memory model without large automatic stack objects.

On successful load, reset wall-clock catch-up debt, physical-key edge latches,
focus-pause pending input, and queued device audio; restore logical audio
renderer state before the next audio submission. Presentation switching must
not alter the save format or create a second game instance. If the host lacks
audio hardware, gameplay still restores correctly.

## Planned S decomposition

| Planned S | Bounded deliverable | ROM-node scope / expected new matches |
| --- | --- | --- |
| S1 | Define the `src/io` snapshot state and fixed-format codec, resource/schema checks, paused-frame capture rule, and corruption/round-trip tests. | 0 / 0 |
| S2 | Implement the `src/io` save/load transaction and best-effort `mysmb.log` contract with DOS16 and Win32 storage services; prove old-save preservation and silent failure paths. | 0 / 0 |
| S3 | Connect Win32 x86/x64 P/O key edges, frame-boundary commit, audio-buffer reset, and immediate title/gameplay load. | 0 / 0 |
| S4 | Connect DOS16 P/O key edges, executable-directory path resolution, bounded staging, presentation redraw, and any available audio-device reset. | 0 / 0 |
| S5 | Run integrated DOS16/Win32 cross-load, pause/save/load, input/focus, corruption, permission, and interrupted-save checks in the graphical presentation; refresh applicable local products. The later text-frame task verifies P/O across presentation switches. | 0 / 0 |

At admission, rebase this forecast against the completed I/O component and
the then-current active packet. Register infrastructure S scopes as exact
empty node sets with zero expected matches. This host feature claims no
original-ROM node or graph-edge credit and must not modify translated logic
to make storage tests pass.

## Acceptance

1. Win32 x86, Win32 x64, and DOS16 can each save and load the same supported
   `mysmb.sav` from their executable directory; a restored game continues
   from the saved frame without requiring Enter.
2. P while paused saves the last running frame. O at the title screen or in
   gameplay loads once per press. Neither shortcut becomes a game controller
   input or changes the meaning of Enter, focus loss, or presentation keys.
3. Corrupt, truncated, incompatible, absent, read-only, and interrupted
   operations leave the live game intact. A failed Win32 replacement preserves
   the prior valid slot; the DOS replacement limitation stated above is
   explicitly tested and reported. All failures remain invisible in gameplay
   and attempt one `mysmb.log` append; a logging failure remains invisible.
4. Restored visuals, gameplay state, and active music/sound continue without
   replaying a completed APU write or playing stale queued host audio. Tests
   compare subsequent frame and audio-command sequences across save/load and
   uninterrupted execution.
5. The codec stays C90-compatible and fixed-width; the Win32 and DOS16
   adapters own OS calls only. Cross-width builds, DOS16 link, focused codec
   tests, and operational host checks pass.
