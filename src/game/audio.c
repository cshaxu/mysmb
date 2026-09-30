#include "game/audio.h"

enum {
    MYSMB_RAM_SQUARE1_BUFFER = 0x00f1U,
    MYSMB_RAM_SQUARE2_BUFFER = 0x00f2U,
    MYSMB_RAM_NOISE_BUFFER = 0x00f3U,
    MYSMB_RAM_AREA_MUSIC_BUFFER = 0x00f4U,
    MYSMB_RAM_EVENT_MUSIC_BUFFER = 0x07b1U,
    MYSMB_RAM_PAUSE_BUFFER = 0x07b2U,
    MYSMB_RAM_SQUARE1_LENGTH = 0x07bbU,
    MYSMB_RAM_SQUARE2_LENGTH = 0x07bdU,
    MYSMB_RAM_SFX_SECONDARY = 0x07beU,
    MYSMB_RAM_NOISE_LENGTH = 0x07bfU,
    MYSMB_RAM_AREA_MUSIC_ALT = 0x07c5U,
    MYSMB_RAM_PAUSE_MODE = 0x07c6U,
    MYSMB_RAM_PAUSE_QUEUE = 0x00faU,
    MYSMB_RAM_AREA_MUSIC_QUEUE = 0x00fbU,
    MYSMB_RAM_EVENT_MUSIC_QUEUE = 0x00fcU,
    MYSMB_RAM_NOISE_QUEUE = 0x00fdU,
    MYSMB_RAM_SQUARE2_QUEUE = 0x00feU,
    MYSMB_RAM_SQUARE1_QUEUE = 0x00ffU,
    MYSMB_RAM_OPERATING_MODE = 0x0770U,
    MYSMB_EVENT_DEATH_MUSIC = 0x01U,
    MYSMB_SFX_EXTRA_LIFE = 0x40U
};

enum {
    /* Local PRG offsets for ROM $fb72 DeathMusData and ROM $ff66
     * MusicLengthLookupTbl.  They are read only through the owner-local
     * area binding; no music data is tracked in this repository. */
    MYSMB_ROM_DEATH_MUSIC_DATA = 0x7b72U,
    MYSMB_ROM_MUSIC_LENGTH_TABLE = 0x7f66U,
    MYSMB_ROM_MUSIC_HEADER_DATA = 0x790dU,
    MYSMB_RAM_MUSIC_LENGTH_OFFSET = 0x00f0U,
    MYSMB_RAM_MUSIC_OFFSET_SQUARE2 = 0x00f7U,
    MYSMB_RAM_MUSIC_OFFSET_SQUARE1 = 0x00f8U,
    MYSMB_RAM_MUSIC_OFFSET_TRIANGLE = 0x00f9U,
    MYSMB_RAM_MUSIC_OFFSET_NOISE = 0x07b0U,
    MYSMB_RAM_NOISE_LOOPBACK_OFFSET = 0x07c1U,
    MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET = 0x07c7U,
    MYSMB_RAM_ALT_REGISTER_CONTENT = 0x07caU,
    MYSMB_RAM_SQUARE2_NOTE_LENGTH = 0x07b3U,
    MYSMB_RAM_SQUARE2_NOTE_COUNTER = 0x07b4U,
    MYSMB_RAM_SQUARE2_ENVELOPE = 0x07b5U,
    MYSMB_RAM_SQUARE1_NOTE_COUNTER = 0x07b6U,
    MYSMB_RAM_SQUARE1_ENVELOPE = 0x07b7U,
    MYSMB_RAM_TRIANGLE_NOTE_BUFFER = 0x07b8U,
    MYSMB_RAM_TRIANGLE_NOTE_COUNTER = 0x07b9U,
    MYSMB_RAM_NOISE_BEAT_COUNTER = 0x07baU,
    MYSMB_RAM_DAC_COUNTER = 0x07c0U
};

/* ROM HandleSquare2Music's death-event stream.  The existing audio command
 * model owns presentation elsewhere, but PlayerHole observes EventMusicBuffer
 * as real gameplay state.  Advance the original Square 2 length stream until
 * its terminator clears that buffer, exactly as EndOfMusicData does. */
/* ROM LoadHeader. Header selectors address MusicHeaderData directly, while
 * each byte in that table is an offset from the same PRG base. */
static mysmb_u8 mysmb_audio_load_header(struct mysmb_game *game,
                                        mysmb_u8 selector)
{
    mysmb_u16 table_offset;
    mysmb_u16 header_offset;

    if (game->area_prg == 0 || selector >= 0x40U) return 0U;
    table_offset = (mysmb_u16)(MYSMB_ROM_MUSIC_HEADER_DATA + selector);
    if (table_offset >= game->area_prg_size) return 0U;
    header_offset = (mysmb_u16)(MYSMB_ROM_MUSIC_HEADER_DATA +
                                 game->area_prg[table_offset]);
    if (header_offset >= game->area_prg_size ||
        (mysmb_u16)(game->area_prg_size - header_offset) < 6U) return 0U;
    game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET] = game->area_prg[header_offset];
    game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2] = 0U;
    game->ram[0x00f5U] = game->area_prg[(mysmb_u16)(header_offset + 1U)];
    game->ram[0x00f6U] = game->area_prg[(mysmb_u16)(header_offset + 2U)];
    game->ram[MYSMB_RAM_MUSIC_OFFSET_TRIANGLE] =
        game->area_prg[(mysmb_u16)(header_offset + 3U)];
    game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1] =
        game->area_prg[(mysmb_u16)(header_offset + 4U)];
    game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE] =
        game->area_prg[(mysmb_u16)(header_offset + 5U)];
    game->ram[MYSMB_RAM_NOISE_LOOPBACK_OFFSET] =
        game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE];
    game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] = 1U;
    game->ram[MYSMB_RAM_SQUARE1_NOTE_COUNTER] = 1U;
    game->ram[MYSMB_RAM_TRIANGLE_NOTE_COUNTER] = 1U;
    game->ram[MYSMB_RAM_NOISE_BEAT_COUNTER] = 1U;
    game->ram[MYSMB_RAM_ALT_REGISTER_CONTENT] = 0U;
    return 1U;
}

static mysmb_u8 mysmb_audio_find_header_selector(mysmb_u8 music,
                                                   mysmb_u8 base)
{
    mysmb_u8 selector;

    selector = base;
    while ((music & 1U) == 0U) {
        music >>= 1U;
        selector++;
    }
    return selector;
}
/* ROM $ff00 FreqRegLookupTbl: a zero low frequency byte makes SetFreq
 * return through NoTone, so LoadControlRegs must not set an envelope. */
static mysmb_u8 mysmb_audio_note_is_audible(const struct mysmb_game *game,
                                            mysmb_u8 data)
{
    mysmb_u16 address;

    address = (mysmb_u16)(0x7f00U + (data & 0x3eU) + 1U);
    if (game->area_prg == 0 || address >= game->area_prg_size) return 0U;
    return game->area_prg[address] != 0U ? 1U : 0U;
}
/* ROM LoadControlRegs: a rest retains no envelope.  Audible event music
 * follows the water/event branch ($28); end-castle has its dedicated $04. */
static mysmb_u8 mysmb_audio_envelope_control(const struct mysmb_game *game,
                                              mysmb_u8 data)
{
    if (mysmb_audio_note_is_audible(game, data) == 0U) return 0U;
    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x08U) != 0U) return 4U;
    if ((game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0x7dU) == 0U) return 0x28U;
    return 8U;
}

/* Return nonzero only when ROM EndOfMusicData returns from SoundEngine.
 * The caller must then skip the later channel handlers for this frame. */
static mysmb_u8 mysmb_audio_step_death_music(struct mysmb_game *game)
{
    mysmb_u16 offset;
    mysmb_u16 table_offset;
    mysmb_u8 data;

    if (game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] != MYSMB_EVENT_DEATH_MUSIC ||
        game->area_prg == 0 ||
        game->area_prg_size <= MYSMB_ROM_MUSIC_LENGTH_TABLE + 0x1fU) {
        return 0U;
    }
    game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER]--;
    if (game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] != 0U) return 0U;
    offset = (mysmb_u16)(MYSMB_ROM_DEATH_MUSIC_DATA +
                         game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]++);
    if (offset >= game->area_prg_size) return 0U;
    data = game->area_prg[offset];
    if (data == 0U) {
        game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = 0U;
        game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = 0U;
        return 1U;
    }
    if ((data & 0x80U) != 0U) {
        table_offset = (mysmb_u16)(MYSMB_ROM_MUSIC_LENGTH_TABLE +
            (data & 7U) + game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET]);
        if (table_offset >= game->area_prg_size) return 0U;
        game->ram[MYSMB_RAM_SQUARE2_NOTE_LENGTH] =
            game->area_prg[table_offset];
        offset = (mysmb_u16)(MYSMB_ROM_DEATH_MUSIC_DATA +
            game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]++);
        if (offset >= game->area_prg_size) return 0U;
        data = game->area_prg[offset];
    }
    if (game->ram[MYSMB_RAM_SQUARE2_BUFFER] == 0U) {
        game->ram[MYSMB_RAM_SQUARE2_ENVELOPE] =
            mysmb_audio_envelope_control(game, data);
    }
    game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] =
        game->ram[MYSMB_RAM_SQUARE2_NOTE_LENGTH];
    return 0U;
}

static mysmb_u8 mysmb_audio_first_square1(mysmb_u8 queue)
{
    if ((queue & 0x80U) != 0U) return 0x80U;
    if ((queue & 0x01U) != 0U) return 0x01U;
    if ((queue & 0x02U) != 0U) return 0x02U;
    if ((queue & 0x04U) != 0U) return 0x04U;
    if ((queue & 0x08U) != 0U) return 0x08U;
    if ((queue & 0x10U) != 0U) return 0x10U;
    if ((queue & 0x20U) != 0U) return 0x20U;
    return 0x40U;
}

static mysmb_u8 mysmb_audio_square1_length(mysmb_u8 effect)
{
    if (effect == 0x04U || effect == 0x08U) return 0x0eU;
    if (effect == 0x10U) return 0x2fU;
    if (effect == 0x20U) return 0x05U;
    if (effect == 0x40U) return 0x40U;
    if (effect == 0x02U) return 0x0aU;
    return 0x28U;
}

static mysmb_u8 mysmb_audio_first_square2(mysmb_u8 queue)
{
    if ((queue & 0x80U) != 0U) return 0x80U;
    if ((queue & 0x01U) != 0U) return 0x01U;
    if ((queue & 0x02U) != 0U) return 0x02U;
    if ((queue & 0x04U) != 0U) return 0x04U;
    if ((queue & 0x08U) != 0U) return 0x08U;
    if ((queue & 0x10U) != 0U) return 0x10U;
    if ((queue & 0x20U) != 0U) return 0x20U;
    return 0x40U;
}

static mysmb_u8 mysmb_audio_square2_length(mysmb_u8 effect)
{
    if (effect == 0x80U) return 0x38U;
    if (effect == 0x01U) return 0x35U;
    if (effect == 0x02U) return 0x10U;
    if (effect == 0x04U) return 0x20U;
    if (effect == 0x08U) return 0x20U;
    if (effect == 0x10U) return 0x06U;
    if (effect == 0x20U) return 0x36U;
    return 0x30U;
}

static void mysmb_audio_step_square1(struct mysmb_game *game)
{
    mysmb_u8 queue;
    mysmb_u8 effect;

    queue = game->ram[MYSMB_RAM_SQUARE1_QUEUE];
    if (queue != 0U) {
        effect = mysmb_audio_first_square1(queue);
        /* The ROM retains the complete bitset in the buffer.  The selected
         * bit decides this frame's effect, while the raw command remains
         * observable to a future audio adapter. */
        game->ram[MYSMB_RAM_SQUARE1_BUFFER] = queue;
        game->ram[MYSMB_RAM_SQUARE1_LENGTH] = mysmb_audio_square1_length(effect);
    }
    if (game->ram[MYSMB_RAM_SQUARE1_BUFFER] == 0U) return;
    game->ram[MYSMB_RAM_SQUARE1_LENGTH]--;
    if (game->ram[MYSMB_RAM_SQUARE1_LENGTH] == 0U) {
        game->ram[MYSMB_RAM_SQUARE1_BUFFER] = 0U;
    }
}

static void mysmb_audio_step_square2(struct mysmb_game *game)
{
    mysmb_u8 queue;
    mysmb_u8 effect;

    if ((game->ram[MYSMB_RAM_SQUARE2_BUFFER] & MYSMB_SFX_EXTRA_LIFE) == 0U) {
        queue = game->ram[MYSMB_RAM_SQUARE2_QUEUE];
        if (queue != 0U) {
            effect = mysmb_audio_first_square2(queue);
            game->ram[MYSMB_RAM_SQUARE2_BUFFER] = queue;
            game->ram[MYSMB_RAM_SQUARE2_LENGTH] = mysmb_audio_square2_length(effect);
            /* GrowItemRegs alone owns this counter initialization. Other
             * Square2 effects leave its last value intact in the ROM. */
            if (effect == 0x02U || effect == 0x04U) {
                game->ram[MYSMB_RAM_SFX_SECONDARY] = 0U;
            }
        }
    }
    if (game->ram[MYSMB_RAM_SQUARE2_BUFFER] == 0U) return;
    effect = mysmb_audio_first_square2(game->ram[MYSMB_RAM_SQUARE2_BUFFER]);
    /* ROM ContinueGrowItems increments its separate counter and uses half of
     * it as the frequency-table index.  It never decrements the ordinary
     * Square2 SFX length counter on this path. */
    if (effect == 0x02U || effect == 0x04U) {
        game->ram[MYSMB_RAM_SFX_SECONDARY]++;
        if ((mysmb_u8)(game->ram[MYSMB_RAM_SFX_SECONDARY] >> 1U) ==
            game->ram[MYSMB_RAM_SQUARE2_LENGTH]) {
            game->ram[MYSMB_RAM_SQUARE2_BUFFER] = 0U;
        }
        return;
    }
    game->ram[MYSMB_RAM_SQUARE2_LENGTH]--;
    if (game->ram[MYSMB_RAM_SQUARE2_LENGTH] == 0U) {
        game->ram[MYSMB_RAM_SQUARE2_BUFFER] = 0U;
    }
}

static void mysmb_audio_step_noise(struct mysmb_game *game)
{
    mysmb_u8 queue;

    queue = game->ram[MYSMB_RAM_NOISE_QUEUE];
    if (queue != 0U) {
        if ((queue & 0x01U) != 0U) {
            game->ram[MYSMB_RAM_NOISE_BUFFER] = queue;
            game->ram[MYSMB_RAM_NOISE_LENGTH] = 0x20U;
        }
        else {
            game->ram[MYSMB_RAM_NOISE_BUFFER] = queue;
            game->ram[MYSMB_RAM_NOISE_LENGTH] = 0x40U;
        }
    }
    if (game->ram[MYSMB_RAM_NOISE_BUFFER] == 0U) return;
    game->ram[MYSMB_RAM_NOISE_LENGTH]--;
    if (game->ram[MYSMB_RAM_NOISE_LENGTH] == 0U) {
        game->ram[MYSMB_RAM_NOISE_BUFFER] = 0U;
    }
}

/* ROM HandleSquare2Music through Squ2NoteHandler, excluding APU register
 * writes. The source stream stores CPU addresses; NROM PRG is $8000-based. */
static mysmb_u8 mysmb_audio_step_square2_music(struct mysmb_game *game)
{
    mysmb_u16 address;
    mysmb_u16 length_address;
    mysmb_u8 data;
    mysmb_u8 area;

    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] == 0U &&
         game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] == 0U) ||
        game->area_prg == 0 || game->ram[0x00f6U] < 0x80U) return 0U;
    game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER]--;
    if (game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] != 0U) return 0U;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[0x00f6U] - 0x80U) << 8U) |
                          game->ram[0x00f5U]);
    address = (mysmb_u16)(address + game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]++);
    if (address >= game->area_prg_size) return 0U;
    data = game->area_prg[address];
    if (data == 0U) {
        area = (mysmb_u8)(game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0x5fU);
        if (area == 0U) {
            game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = 0U;
            game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = 0U;
            return 1U;
        }
        game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = area;
        game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = 0U;
        if (area == 1U) {
            game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET]++;
            if (game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] == 0x32U)
                game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] = 0x11U;
            (void)mysmb_audio_load_header(game, (mysmb_u8)(
                game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] - 1U));
        }
        else {
            (void)mysmb_audio_load_header(game,
                mysmb_audio_find_header_selector(area, 8U));
        }
        return mysmb_audio_step_square2_music(game);
    }
    if ((data & 0x80U) != 0U) {
        length_address = (mysmb_u16)(MYSMB_ROM_MUSIC_LENGTH_TABLE +
            (data & 7U) + game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET]);
        if (length_address >= game->area_prg_size) return 0U;
        game->ram[MYSMB_RAM_SQUARE2_NOTE_LENGTH] = game->area_prg[length_address];
        game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]++;
        data = game->area_prg[address + 1U];
    }
    /* Squ2NoteHandler's LoadControlRegs returns envelope offset 8 for each
     * audible note; a zero rest retains zero. */
    if (game->ram[MYSMB_RAM_SQUARE2_BUFFER] == 0U) {
        game->ram[MYSMB_RAM_SQUARE2_ENVELOPE] =
            mysmb_audio_envelope_control(game, data);
    }
    game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] =
        game->ram[MYSMB_RAM_SQUARE2_NOTE_LENGTH];
    return 0U;
}

/* ROM HandleTriangleMusic through TriNoteHandler, excluding the APU writes. */
static void mysmb_audio_step_triangle_music(struct mysmb_game *game)
{
    mysmb_u16 address;
    mysmb_u16 length_address;
    mysmb_u8 data;

    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] == 0U &&
         game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] == 0U) ||
        game->area_prg == 0 || game->ram[0x00f6U] < 0x80U) return;
    game->ram[MYSMB_RAM_TRIANGLE_NOTE_COUNTER]--;
    if (game->ram[MYSMB_RAM_TRIANGLE_NOTE_COUNTER] != 0U) return;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[0x00f6U] - 0x80U) << 8U) |
                          game->ram[0x00f5U]);
    address = (mysmb_u16)(address + game->ram[MYSMB_RAM_MUSIC_OFFSET_TRIANGLE]++);
    if (address >= game->area_prg_size) return;
    data = game->area_prg[address];
    if ((data & 0x80U) != 0U) {
        length_address = (mysmb_u16)(MYSMB_ROM_MUSIC_LENGTH_TABLE +
            (data & 7U) + game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET]);
        if (length_address >= game->area_prg_size) return;
        game->ram[MYSMB_RAM_TRIANGLE_NOTE_BUFFER] = game->area_prg[length_address];
        game->ram[MYSMB_RAM_MUSIC_OFFSET_TRIANGLE]++;
    }
    game->ram[MYSMB_RAM_TRIANGLE_NOTE_COUNTER] =
        game->ram[MYSMB_RAM_TRIANGLE_NOTE_BUFFER];
}
/* ROM HandleSquare1Music through AlternateLengthHandler.  Square 1 encodes
 * its three-bit duration selector in bits 0, 7 and 6, unlike Square 2 and
 * Triangle which use the low three bits directly. */
static void mysmb_audio_step_square1_music(struct mysmb_game *game)
{
    mysmb_u16 address;
    mysmb_u16 length_address;
    mysmb_u8 data;
    mysmb_u8 length_index;

    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] == 0U &&
         game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] == 0U) ||
        game->area_prg == 0 || game->ram[0x00f6U] < 0x80U) return;
    game->ram[MYSMB_RAM_SQUARE1_NOTE_COUNTER]--;
    if (game->ram[MYSMB_RAM_SQUARE1_NOTE_COUNTER] != 0U) return;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[0x00f6U] - 0x80U) << 8U) |
                          game->ram[0x00f5U]);
    address = (mysmb_u16)(address + game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1]++);
    if (address >= game->area_prg_size) return;
    data = game->area_prg[address];
    while (data == 0U) {
        game->ram[MYSMB_RAM_ALT_REGISTER_CONTENT] = 0x94U;
        address = (mysmb_u16)(address + 1U);
        game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1]++;
        if (address >= game->area_prg_size) return;
        data = game->area_prg[address];
    }
    length_index = (mysmb_u8)(((data & 1U) << 2U) |
        ((data & 0x80U) >> 6U) | ((data & 0x40U) >> 6U));
    length_address = (mysmb_u16)(MYSMB_ROM_MUSIC_LENGTH_TABLE + length_index +
        game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET]);
    if (length_address >= game->area_prg_size) return;
    game->ram[MYSMB_RAM_SQUARE1_NOTE_COUNTER] = game->area_prg[length_address];
    /* SetFreq_Squ1 returns zero for a rest, bypassing LoadControlRegs. */
    if (game->ram[MYSMB_RAM_SQUARE1_BUFFER] == 0U) {
        game->ram[MYSMB_RAM_SQUARE1_ENVELOPE] =
            mysmb_audio_envelope_control(game, data);
    }
}
/* ROM HandleNoiseMusic through NoiseBeatHandler, excluding APU writes. */
static void mysmb_audio_step_noise_music(struct mysmb_game *game)
{
    mysmb_u16 address;
    mysmb_u16 length_address;
    mysmb_u8 data;
    mysmb_u8 length_index;

    if ((game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0xf3U) == 0U ||
        game->area_prg == 0 || game->ram[0x00f6U] < 0x80U) return;
    game->ram[MYSMB_RAM_NOISE_BEAT_COUNTER]--;
    if (game->ram[MYSMB_RAM_NOISE_BEAT_COUNTER] != 0U) return;
    address = (mysmb_u16)(((mysmb_u16)(game->ram[0x00f6U] - 0x80U) << 8U) |
                          game->ram[0x00f5U]);
    address = (mysmb_u16)(address + game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE]++);
    if (address >= game->area_prg_size) return;
    data = game->area_prg[address];
    while (data == 0U) {
        game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE] =
            game->ram[MYSMB_RAM_NOISE_LOOPBACK_OFFSET];
        address = (mysmb_u16)(((mysmb_u16)(game->ram[0x00f6U] - 0x80U) << 8U) |
                              game->ram[0x00f5U]);
        address = (mysmb_u16)(address + game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE]++);
        if (address >= game->area_prg_size) return;
        data = game->area_prg[address];
    }
    length_index = (mysmb_u8)(((data & 1U) << 2U) |
        ((data & 0x80U) >> 6U) | ((data & 0x40U) >> 6U));
    length_address = (mysmb_u16)(MYSMB_ROM_MUSIC_LENGTH_TABLE + length_index +
        game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET]);
    if (length_address >= game->area_prg_size) return;
    game->ram[MYSMB_RAM_NOISE_BEAT_COUNTER] = game->area_prg[length_address];
}
/* ROM MiscSqu2MusicTasks and MiscSqu1MusicTasks decrement each envelope
 * offset after a note load, except while the channel is owned by SFX or
 * the death/castle event route. */
static void mysmb_audio_step_square_envelopes(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_SQUARE2_BUFFER] == 0U &&
        (game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x91U) == 0U &&
        game->ram[MYSMB_RAM_SQUARE2_ENVELOPE] != 0U) {
        game->ram[MYSMB_RAM_SQUARE2_ENVELOPE]--;
    }
    if (game->ram[MYSMB_RAM_SQUARE1_BUFFER] == 0U &&
        (game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x91U) == 0U &&
        game->ram[MYSMB_RAM_SQUARE1_ENVELOPE] != 0U) {
        game->ram[MYSMB_RAM_SQUARE1_ENVELOPE]--;
    }
}
static void mysmb_audio_step_music(struct mysmb_game *game)
{
    mysmb_u8 event;
    mysmb_u8 area;

    event = game->ram[MYSMB_RAM_EVENT_MUSIC_QUEUE];
    area = game->ram[MYSMB_RAM_AREA_MUSIC_QUEUE];
    if (event != 0U) {
        game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = event;
        if (event == MYSMB_EVENT_DEATH_MUSIC) {
            /* StopSquare1Sfx clears its own buffer. StopSquare2Sfx only
             * writes APU control registers, so Square2SoundBuffer survives. */
            game->ram[MYSMB_RAM_SQUARE1_BUFFER] = 0U;
        }
        (void)mysmb_audio_load_header(game,
            mysmb_audio_find_header_selector(event, 0U));
        game->ram[MYSMB_RAM_AREA_MUSIC_ALT] = game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER];
        game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = 0U;
        /* ROM Silence's Square 2 stream ends immediately.  EndOfMusicData
         * therefore clears the event buffer in this SoundEngine pass, before
         * InitializeArea has a chance to queue the replacement area header. */
        if (event == 0x80U) {
            /* The initialized counter is consumed by Silence's zero datum
             * before EndOfMusicData returns from SoundEngine. */
            game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] = 0U;
            game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = 0U;
            return;
        }
    }
    else if (area != 0U) {
        /* ROM LoadAreaMusic seeds this counter before selecting any area
         * header, including the Silence header used by setup transitions. */
        game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] = 0x10U;
        game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = 0U;
        game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = area;
        if (area == 1U) {
            game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET]++;
            (void)mysmb_audio_load_header(game, (mysmb_u8)(
                game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] - 1U));
        }
        else {
            (void)mysmb_audio_load_header(game,
                mysmb_audio_find_header_selector(area, 8U));
        }
    }
    /* SoundEngine leaves the music-channel tasks once both queues and both
     * active music buffers are clear.  This also retains final envelopes. */
    if (event == 0U && area == 0U &&
        game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] == 0U &&
        game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] == 0U) return;
    if (game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] == MYSMB_EVENT_DEATH_MUSIC) {
        if (mysmb_audio_step_death_music(game) != 0U) return;
    }
    else {
        if (mysmb_audio_step_square2_music(game) != 0U) return;
    }
    mysmb_audio_step_square1_music(game);
    mysmb_audio_step_square_envelopes(game);
    mysmb_audio_step_triangle_music(game);
    mysmb_audio_step_noise_music(game);
}

/* ROM SoundEngine writes these APU registers from shared game logic. */
static void mysmb_audio_write_apu(struct mysmb_game *game, mysmb_u8 index,
                                  mysmb_u8 value)
{
    game->apu_registers[index] = value;
    if (index == 17U) game->apu_delta_counter_load = value;
    if (index == 21U) game->apu_channel_enable = value;
    if (index == 23U) game->apu_frame_counter = value;
}

/* PlaySqu1Sfx is a T48 S2 dependency.  This directly follows its source
 * register writes for the pause tones; S2 still owns node certification. */
static void mysmb_audio_pause_tone(struct mysmb_game *game, mysmb_u8 tone)
{
    mysmb_u16 frequency;

    mysmb_audio_write_apu(game, 1U, 0x7fU);
    mysmb_audio_write_apu(game, 0U, 0x84U);
    frequency = (mysmb_u16)(0x7f00U + tone);
    if (game->area_prg == 0 ||
        frequency + 1U >= game->area_prg_size) return;
    if (game->area_prg[frequency + 1U] == 0U) return;
    mysmb_audio_write_apu(game, 2U, game->area_prg[frequency + 1U]);
    mysmb_audio_write_apu(game, 3U,
        (mysmb_u8)(game->area_prg[frequency] | 8U));
}

void mysmb_audio_step(struct mysmb_game *game)
{
    mysmb_u8 old_dac;
    mysmb_u8 pause_length;
    mysmb_u8 pause_started;

    if (game->ram[MYSMB_RAM_OPERATING_MODE] == 0U) {
        mysmb_audio_write_apu(game, 21U, 0U);
        return;
    }
    mysmb_audio_write_apu(game, 23U, 0xffU);
    mysmb_audio_write_apu(game, 21U, 0x0fU);
    pause_started = 0U;
    if (game->ram[MYSMB_RAM_PAUSE_MODE] != 0U ||
        game->ram[MYSMB_RAM_PAUSE_QUEUE] == 1U) {
        if (game->ram[MYSMB_RAM_PAUSE_BUFFER] == 0U &&
            game->ram[MYSMB_RAM_PAUSE_QUEUE] != 0U) {
            game->ram[MYSMB_RAM_PAUSE_BUFFER] = game->ram[MYSMB_RAM_PAUSE_QUEUE];
            game->ram[MYSMB_RAM_PAUSE_MODE] = game->ram[MYSMB_RAM_PAUSE_QUEUE];
            mysmb_audio_write_apu(game, 21U, 0U);
            game->ram[MYSMB_RAM_SQUARE1_BUFFER] = 0U;
            game->ram[MYSMB_RAM_SQUARE2_BUFFER] = 0U;
            game->ram[MYSMB_RAM_NOISE_BUFFER] = 0U;
            mysmb_audio_write_apu(game, 21U, 0x0fU);
            game->ram[MYSMB_RAM_SQUARE1_LENGTH] = 0x2aU;
            pause_started = 1U;
        }
        if (game->ram[MYSMB_RAM_PAUSE_BUFFER] != 0U) {
            pause_length = game->ram[MYSMB_RAM_SQUARE1_LENGTH];
            if (pause_length == 0x24U || pause_length == 0x18U)
                mysmb_audio_pause_tone(game, 0x64U);
            else if (pause_started != 0U || pause_length == 0x1eU)
                mysmb_audio_pause_tone(game, 0x44U);
            game->ram[MYSMB_RAM_SQUARE1_LENGTH]--;
            if (game->ram[MYSMB_RAM_SQUARE1_LENGTH] == 0U) {
                mysmb_audio_write_apu(game, 21U, 0U);
                if (game->ram[MYSMB_RAM_PAUSE_BUFFER] == 2U) {
                    game->ram[MYSMB_RAM_PAUSE_MODE] = 0U;
                }
                game->ram[MYSMB_RAM_PAUSE_BUFFER] = 0U;
            }
        }
    }
    else {
        mysmb_audio_step_square1(game);
        mysmb_audio_step_square2(game);
        mysmb_audio_step_noise(game);
        mysmb_audio_step_music(game);
        game->ram[MYSMB_RAM_AREA_MUSIC_QUEUE] = 0U;
        game->ram[MYSMB_RAM_EVENT_MUSIC_QUEUE] = 0U;
    }
    game->ram[MYSMB_RAM_SQUARE1_QUEUE] = 0U;
    game->ram[MYSMB_RAM_SQUARE2_QUEUE] = 0U;
    game->ram[MYSMB_RAM_NOISE_QUEUE] = 0U;
    game->ram[MYSMB_RAM_PAUSE_QUEUE] = 0U;
    /* ROM SoundEngine's final DAC_Counter update follows queue clearing. */
    old_dac = game->ram[MYSMB_RAM_DAC_COUNTER];
    if ((game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 3U) != 0U) {
        game->ram[MYSMB_RAM_DAC_COUNTER]++;
        if (old_dac >= 0x30U && old_dac != 0U)
            game->ram[MYSMB_RAM_DAC_COUNTER]--;
    }
    else if (old_dac != 0U) {
        game->ram[MYSMB_RAM_DAC_COUNTER]--;
    }
    mysmb_audio_write_apu(game, 17U, old_dac);
}
