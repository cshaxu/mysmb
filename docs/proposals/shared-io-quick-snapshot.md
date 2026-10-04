# M3 T10: shared I/O quick snapshot

Owner scheduling amendment (P153):remaining M2 acceptance verification is
queued after the three I/O/presentation candidates. Earlier proof completion
prerequisites are superseded by this explicit order;retain scoped evidence and
rebind affected dependencies at admission. This does not certify M2.

## Purpose and queue dependency

Add one quick-save slot shared by DOS16 and Win32. P saves to `mysmb.sav`
beside the running executable; O loads that file and immediately continues
gameplay. Owner admitted M3 T10 after T9 completed its shared I/O
component split. Its planned S slots are
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

## S1 admission

Owner admits the former queue head as M3 T10;S1 is active and S2-S5 remain
planned. Scope and expected new original nodes are both empty. Historical
mapping1992/1992,local1991/1992 nodes and4260/4261 feasible controls retain
existing scoped evidence;this feature earns no ROM conformance credit.

S1 owns the byte schema,codec,numeric transport and last-running-frame cache,
with a complete mutable-field census. Roots will marshal authoritative state;
IO treats the program-state block as opaque bytes and knows no original RAM
addresses. Numeric audio values use arithmetic sign/exponent/mantissa encoding,
not a host double memory dump. Decoding validates the whole file before any
caller output changes. S2 owns storage;S3/S4 own host and state binding.

Verification uses neutral deterministic bytes,exact wire-size/byte-order
assertions,wrong versions/resources,bit corruption,truncation,trailing bytes,
numeric round trips and paused-cache/no-cache cases. DOS staging remains below
one segment with no large automatic objects. Refresh the three local EXEs after
source changes using the existing builds and original OpenNT16 compiler.

## S1 schema contract

The v1 file is4782bytes:36header +4622program +124audio. All integers are
little-endian with specified widths. Header:magic `MYSMBSAV` bytes0-7,
format1 at8-9,state-schema1 at10-11,payload4746 at12-15,resource fingerprint
at16-31,and CRC32/ISO-HDLC at32-35. CRC covers bytes0-31 and36-4781.
The fingerprint is four CRC32 values over the currently bound immutable
PRG,CHR,title and title-icon byte arrays in that order. This is accidental
incompatibility detection,not an authentication or security boundary.

The composition schema consumes every mutable `mysmb_game` field once:

| Program offset | Byte count | Field order |
| ---: | ---: | --- |
| 0 | 4 | frame_number |
| 4 | 1 | startup_phase |
| 5 | 2048 | ram |
| 2053 | 2048 | name_table0 then1 |
| 4101 | 256 | visible_oam |
| 4357 | 1 | oam_dma_primed |
| 4358 | 32 | palette |
| 4390 | 5 | ppu_control_0,ppu_mask,ppu_name_table,scroll_x,scroll_y |
| 4395 | 6 | visible_ppu_control_0,visible_ppu_mask,visible_ppu_name_table,visible_scroll_x,visible_scroll_y,visible_sprite0_split |
| 4401 | 3 | apu_delta_counter_load,apu_channel_enable,apu_frame_counter |
| 4404 | 24 | apu_registers |
| 4428 | 1 | apu_write_count |
| 4429 | 128 | 64 ordered index/value write pairs |
| 4557 | 1 | area_command_count |
| 4558 | 64 | 16 ordered column/row/page/dispatch_id command records |

All four resource pointers and their lengths are immutable bindings and remain
current after restore. Derived frame/bitmap storage is rebuilt. The saved
ordered APU writes are state history,not pending playback;load must not submit
them again. Device handles,pending samples,input-edge and wall-clock debt are
excluded and reset by the applicable host binding.

Audio block:presence byte0;registers1-24;enabled25;15u16 counters26-55;
six flags56-61;noise_shift u16 at62-63;six numerical values64-123. Counter
order:length4,envelope_level3,envelope_divider3,pulse_timer2,sweep_divider2,
triangle_linear1. Flag order:envelope_start3,sweep_reload2,triangle_reload1.
Numerical order:pulse_phase2,triangle_phase,noise_phase,highpass_input,
highpass_output. Each numerical value is sign u8,biased exponent u16 and
53-bit integer mantissa u56 (ten bytes),computed arithmetically. Zero is ten
zero bytes;other finite values use `frexp(value)*2^53` and exponent+1074.
Decoder rejects noncanonical/unrepresentable encodings without touching output.
An absent audio state has a fully zero audio block;host bindings must explicitly
qualify restoration and preservation of active audio across unsupported devices.

Cache starts invalid and accepts only composition-declared completed running
boundaries. Pause/title observations cannot overwrite it. S3/S4 determine that
boundary using authoritative game status and commit it after audio consumption;
IO contains no RAM addresses or mode decisions. S1 does not claim those host
integrations are implemented.

S1 implementation amendment:the original DOS16 runtime lacks the compiler's
floating comparison/conversion helper symbols. Keep host-double numerical
conversion under Win32 audio adaptation;the shared codec uses integer-only
canonical-record validation,including subnormal precision checks. This keeps
the same bytes and original DOS compiler/runtime without introducing an FPU
requirement. Portable `string.h` memory operations are allowed by the purity
gate;game and device includes remain forbidden.

## S1 closure

The shared v1 codec and cache are implemented. The integer-only codec and
host-double adapter are separate owners. Neutral tests cover all4782truncated
lengths,each byte corrupted (all eight bits for header bytes),wrong resources,
trailing data,unaltered rejected output,canonical zero/subnormal/extreme
numerical round trips,and invalid/nonrunning/paused/running cache selection.
Both x86 and x64 pass5focused tests,including boundary,purity and hidden-window
self-test. The focused suite takes about2seconds per width. The original
OpenNT16 compiler/runtime compiles and links the same shared byte codec.
Three local EXEs are refreshed;Windows bytes remain identical because P/O
is not bound yet. DOS link includes the new shared module. No resource bytes
or products are committed;all receipts remain under ignored build.

Similar-issue sweep covers every mutable game field and every existing audio
renderer field in the schema census. No native struct,pointer,padding,device
queue or floating memory layout is serialized. Roots still need to provide
running eligibility,capture/restore and resource rebinding in S3/S4;S1 does not
claim gameplay save/load already works. No ROM labels or edges are promoted:
historical1992/1992;local1991/1992 nodes,4260/4261 feasible controls unchanged.
No remote exists;closure is a local P commit followed by automatic S2 admission.

## S2 admission

S1 local commit retained;S2 now owns common transaction orchestration and
host-neutral file-service hooks. Filesystem adapters expose open/read/write/
flush-close/replace/remove/append only. Shared IO owns fixed filenames,error
codes,write completion,close-before-replace and separate load staging.
A failed log attempt is ignored,not logged again. Tests inject short reads/
writes,truncation,oversize,read/write/close/replace/log failures and compare
prior save/live bytes. Win32 atomic replace and the documented DOS delete/
rename window are separate thin services;directory discovery remains S3/S4.
Scope and expected ROM matches are both empty;all existing counts unchanged.

## S2 closure

Shared transaction and portable file services are complete. Actual Win32
replacement uses MoveFileEx replacement/write-through;DOS removes the old
file only after the new candidate has been fully flushed/closed and then
renames,retaining its explicitly non-atomic interruption window. Shared load
uses separate fixed-size staging and verifies EOF,close,format,integrity and
resource binding before returning a candidate. Each failure attempts one
short log record;logging failure is ignored. Live game state is never touched.

Both widths pass4focused tests;storage retest after the legacy FILE cast
repair passes on both. Partial17-byte writes/23-byte reads,open/write/close/
replace/read failures,truncation,extra bytes,corruption and unchanged prior
save/staging are checked. Real files verify save replacement,load,missing and
oversized file diagnostics,cleanup and simultaneous save/log failure through
a missing directory. The original DOS16 toolchain compiles/links its same
codec/transaction/stdio service and DOS replacement path. Three products
refreshed locally. Similar-issue sweep covers stdio macros/opaque handles,
close-before-replace,EOF/read errors and nonrecursive logging. Physical P/O,
executable-directory discovery and gameplay integration remain S3/S4.
No ROM credit;all prior node/control/facet counts retained. Local commit only,
no remote. Owner authorization automatically admits S3 after this closure.

## S3 admission

S2 is closed. S3 binds every mutable game field through app composition while
preserving resource pointers/lengths. Public completed-frame mode and shared
pause status determine running-cache eligibility;no platform RAM inspection.
Win32 audio adapter owns numerical export/import and validates a complete
candidate before restoring its renderer. The root resets queued device audio,
wall-clock debt,physical request edges and focus pause bookkeeping on success.
P/O requests are once per key transition,focused only,independent of controller
bits. Files live beside the EXE,not the working directory. Neutral state/PCM
continuation tests plus current local title/game tests exercise the bound path.
Scope/expected original labels remain empty;all retained counts unchanged.

## S3 closure

App composition explicitly marshals all mutable program fields;immutable
resource addresses and lengths remain bound to the current executable.
Win32 P/O is focused,edge-triggered and excluded from controller bits.
Paused P uses the last running cache;title O restores immediately at a frame
boundary,validating both owners before mutation. Device queue,clock debt and
focus/request bookkeeping reset;consumed APU writes are not submitted again.

Both widths pass7focused tests. Mutable-field census/re-encoding,different
resource addresses,invalid candidate atomicity,240subsequent ROM-free state
and pixel comparisons and64active audio continuation checkpoints with
735samples each pass. The Win32 production-root harness uses controlled
focus/key services and a private hidden window;it proves paused-file/title
load/cache/typematic/queue-reset paths without claiming physical desktop
input acceptance. Actual product hidden-window self-test also passes.
Original DOS16 compiles/links and three local products are refreshed.

Similar-issue sweep covers every game/audio field,pointer/padding exclusion,
completed audio boundary,key repeat after restore,focus-loss pending requests
and all validation-before-commit paths. DOS physical integration remains S4;
integrated cross-host and additional failure routes remain S5. No game logic
or original labels change. Historical1992/1992,local1991/1992 nodes and
4260/4261feasible controls,42/952facets remain unchanged. No remote.

## S4 admission

S3 closed;DOS root now receives the same store/codec and app state binding.
Physical adapter emits P/O make edges once;load resets clock debt and stale
controller/request bookkeeping while keeping held P/O blocked until break.
DOS executable directory is read from its DOS3+ PSP environment image path,
with bounded parsing and no dependency on current directory. Storage/staging
and cached snapshots are static root-owned objects,not large stack locals.

DOS has no audio renderer/device. It accepts Win32 game state but does not
advance imported oscillator/envelope/filter state. A newly captured DOS
snapshot declares absent audio;Win32 importing it initializes its audio
renderer and continues subsequent game-produced APU writes. Cross-host game
state/commands are comparable;PCM continuity across intervening DOS gameplay
is explicitly unsupported by the existing unavailable audio capability.
S5 will verify and report that distinction. No game translation changes or
ROM credit. Original DOS16 compiler/runtime remain unchanged.

## S4 closure

DOS root binds the shared store and app state codec. P/O uses make edges,
never controller bits;successful restore rebuilds the common PPU output and
resets physical bookkeeping/clock debt while held shortcuts remain blocked.
PSP environment parsing locates the full executable path independently of CWD.
Snapshot/cache/store staging are static;the original large-model link retains
about40KB DGROUP including its2KB stack,well below a64KB segment.

Both widths pass10focused tests. The real original-toolchain DOS executable
runs a41-second headless DOSBox route:Start,P save,move right,O restore,
Esc/text return. Save is4782bytes with correct CRC/schema and absent audio;
EXE runs from a GAME subdirectory while CWD remains the drive root,and the
slot appears only beside EXE. Player X bounds return exactly to the recorded
starting bounds after O. No device/global desktop input is injected. This is
operational storage/graphics/input evidence,not ROM or486speed qualification.

Similar-issue sweep covers ordinary/extended/typematic shortcut inputs,
held O through reset,absolute/root/relative/truncated paths,bounded PSP scan,
all staging objects and load failure before commit. DOS has no sound hardware
or renderer and cannot preserve PCM across intervening DOS gameplay;the
shared game state/APU commands remain intact. Three local EXEs refreshed.
S5 owns cross-width/cross-host continuation and integrated failure routes.
No original nodes/edges/facets changed;all retained counters remain. No remote.
