# M3 T42: DOS16 game music

M3 T42 adds a platform-only Sound Blaster-compatible output route for the
unchanged shared audio frame.  It owns no ROM nodes or control edges and does
not alter translated audio writes, game timing, text/graphics switching or
Win32 audio.

The implementation parses the standard DOS `BLASTER` environment through the
PSP environment pointer, probes the DSP, reserves two fixed 2 KiB 8-bit DMA
blocks, installs/restores the IRQ path, and renders shared ordered frames at
11,025 Hz with integer state.  It reserves its contiguous 4 KiB DMA span
before the product allocates PPU/text/snapshot workspaces, preventing a
product-only silent allocation fallback.  Missing hardware stays safely
silent and playable; run16 remains such a host because it provides no Sound
Blaster device.

The DOS16 MZ route, platform-purity review, source-frame joins, load reset and
DOSBox DSP/DMA/IRQ witness passed.  A DOSBox disk-audio capture of the actual
product after a normal Start transition contained nonzero PCM with normal
amplitude.  The owner could not hear DOSBox audio in the local/RDP host, and
the same host also lacked NESticle audio.  This is retained as a host-output
limitation rather than an unsupported claim that listening acceptance passed.

The owner accepted closure on 2026-10-12.  Generated task outputs were
removed after acceptance.  The full per-part receipts and source/test
contracts remain in the retained
[T42 proposal](../proposals/m3/dos16-game-music.md).
