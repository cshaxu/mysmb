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
    /* Local PRG offsets for ROM $f62b BrickShatterFreqData, $ffca
     * BowserFlameEnvData and $ffea BrickShatterEnvData. */
    MYSMB_ROM_BRICK_SHATTER_FREQ_DATA = 0x762bU,
    MYSMB_ROM_BOWSER_FLAME_ENV_DATA = 0x7fcaU,
    MYSMB_ROM_BRICK_SHATTER_ENV_DATA = 0x7feaU,
    MYSMB_RAM_MUSIC_LENGTH_OFFSET = 0x00f0U,
    MYSMB_RAM_MUSIC_OFFSET_SQUARE2 = 0x00f7U,
    MYSMB_RAM_MUSIC_OFFSET_SQUARE1 = 0x00f8U,
    MYSMB_RAM_MUSIC_OFFSET_TRIANGLE = 0x00f9U,
    MYSMB_RAM_MUSIC_OFFSET_NOISE = 0x07b0U,
    MYSMB_RAM_NOISE_LOOPBACK_OFFSET = 0x07c1U,
    MYSMB_RAM_NOTE_LENGTH_TABLE_ADDER = 0x07c4U,
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

static void mysmb_audio_write_apu(struct mysmb_game *game, mysmb_u8 index,
                                  mysmb_u8 value);

/* ROM HandleSquare2Music's death-event stream.  The existing audio command
 * model owns presentation elsewhere, but PlayerHole observes EventMusicBuffer
 * as real gameplay state.  Advance the original Square 2 length stream until
 * its terminator clears that buffer, exactly as EndOfMusicData does. */
/* ROM LoadHeader.  MusicHeaderOffsetData is deliberately one byte before
 * MusicHeaderData, so callers supply the source Y value after its initial
 * increment and bit scan. */
mysmb_u8 mysmb_audio_load_music_header(struct mysmb_game *game,
                                       mysmb_u8 selector)
{
    mysmb_u16 table_offset;
    mysmb_u16 header_offset;

    if (game->area_prg == 0 || selector == 0U || selector >= 0x40U)
        return 0U;
    table_offset = (mysmb_u16)(MYSMB_ROM_MUSIC_HEADER_DATA - 1U + selector);
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
    mysmb_audio_write_apu(game, 21U, 0x0bU);
    mysmb_audio_write_apu(game, 21U, 0x0fU);
    return 1U;
}

/* ROM FindEventMusicHeader.  Y is incremented before each LSR, including
 * the first bit test.  The caller only supplies nonzero music masks. */
static mysmb_u8 mysmb_audio_find_header_selector(mysmb_u8 music,
                                                   mysmb_u8 base)
{
    mysmb_u8 selector;
    mysmb_u8 carry;

    selector = base;
    do {
        carry = (mysmb_u8)(music & 1U);
        music >>= 1U;
        selector++;
    } while (carry == 0U && music != 0U);
    return selector;
}
/* ROM LoadControlRegs.  Callers reach this helper only after SetFreq has
 * returned nonzero; it supplies A plus the fixed X/Y control-register pair. */
static mysmb_u8 mysmb_audio_envelope_control(const struct mysmb_game *game)
{
    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x08U) != 0U) return 4U;
    if ((game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0x7dU) == 0U) return 0x28U;
    return 8U;
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

static void mysmb_audio_write_apu(struct mysmb_game *game, mysmb_u8 index,
                                  mysmb_u8 value);
static mysmb_u8 mysmb_audio_read_cpu(const struct mysmb_game *game,
                                     mysmb_u16 address);
static mysmb_u8 mysmb_audio_step_square2_music(struct mysmb_game *game);
static void mysmb_audio_handle_area_music_loop(struct mysmb_game *game,
                                                mysmb_u8 area);
static void mysmb_audio_load_event_music(struct mysmb_game *game,
                                         mysmb_u8 event);
static void mysmb_audio_square2_play_coin_timer(struct mysmb_game *game,
                                                  mysmb_u8 timer);
static void mysmb_audio_square2_continue_coin_timer(struct mysmb_game *game);
static void mysmb_audio_square2_play_blast(struct mysmb_game *game);
static void mysmb_audio_square2_continue_blast(struct mysmb_game *game);
static void mysmb_audio_square2_play_power_up(struct mysmb_game *game);
static void mysmb_audio_square2_continue_power_up(struct mysmb_game *game);
static void mysmb_audio_square2_decrement(struct mysmb_game *game);
static void mysmb_audio_square2_play_bowser_fall(struct mysmb_game *game);
static void mysmb_audio_square2_continue_bowser_fall(struct mysmb_game *game);
static void mysmb_audio_square2_play_extra_life(struct mysmb_game *game);
static void mysmb_audio_square2_continue_extra_life(struct mysmb_game *game);
static void mysmb_audio_square2_play_grow_item(struct mysmb_game *game,
                                                mysmb_u8 length);
static void mysmb_audio_square2_continue_grow_item(struct mysmb_game *game);

static void mysmb_audio_step_square1(struct mysmb_game *game)
{
    mysmb_u8 queue;
    mysmb_u8 effect;
    mysmb_u8 length;

    queue = game->ram[MYSMB_RAM_SQUARE1_QUEUE];
    if (queue != 0U) {
        /* Square1SfxHandler stores the unshifted queue in its buffer,
         * then shifts the live queue once for each lower-priority test. */
        game->ram[MYSMB_RAM_SQUARE1_BUFFER] = queue;
        if ((queue & 0x80U) != 0U) effect = 0x80U;
        else {
            effect = 0U;
            for (length = 0U; length < 7U; ++length) {
                effect = (mysmb_u8)(1U << length);
                game->ram[MYSMB_RAM_SQUARE1_QUEUE] >>= 1U;
                if ((queue & effect) != 0U) break;
            }
        }
        if (effect == 0x80U || effect == 0x01U)
            mysmb_audio_square1_play_jump(game,
                                           effect == 0x80U ? 1U : 0U);
        else if (effect == 0x02U || effect == 0x20U)
            mysmb_audio_square1_play_throw(game,
                                            effect == 0x20U ? 1U : 0U);
        else if (effect == 0x40U)
            mysmb_audio_square1_play_flagpole(game);
        else if (effect == 0x04U) {
            game->ram[MYSMB_RAM_SQUARE1_LENGTH] = 0x0eU;
            (void)mysmb_audio_play_squ1_sfx(game, 0x26U, 0x9eU, 0x9cU);
        }
        else if (effect == 0x08U) {
            game->ram[MYSMB_RAM_SQUARE1_LENGTH] = 0x0eU;
            (void)mysmb_audio_play_squ1_sfx(game, 0x28U, 0x9fU, 0xcbU);
        }
        else if (effect == 0x10U)
            game->ram[MYSMB_RAM_SQUARE1_LENGTH] = 0x2fU;
    }
    if (game->ram[MYSMB_RAM_SQUARE1_BUFFER] == 0U) return;
    effect = mysmb_audio_first_square1(game->ram[MYSMB_RAM_SQUARE1_BUFFER]);
    if (effect == 0x80U || effect == 0x01U)
        mysmb_audio_square1_continue_jump(game);
    else if (effect == 0x02U || effect == 0x20U)
        mysmb_audio_square1_continue_throw(game);
    else if (effect == 0x04U) {
        length = game->ram[MYSMB_RAM_SQUARE1_LENGTH];
        mysmb_audio_write_apu(game, 0U,
                               mysmb_audio_swim_stomp_envelope(game, length));
        if (length == 0x06U) mysmb_audio_write_apu(game, 2U, 0x9eU);
    }
    else if (effect == 0x08U && queue == 0U) {
        length = game->ram[MYSMB_RAM_SQUARE1_LENGTH];
        if (length == 0x08U) mysmb_audio_write_apu(game, 2U, 0xa0U);
        mysmb_audio_write_apu(game, 0U, length == 0x08U ? 0x9fU : 0x90U);
    }
    else if (effect == 0x10U) {
        length = game->ram[MYSMB_RAM_SQUARE1_LENGTH];
        if ((length & 0x0bU) == 0x08U)
            (void)mysmb_audio_play_squ1_sfx(game, 0x44U, 0x9aU, 0x91U);
    }
    game->ram[MYSMB_RAM_SQUARE1_LENGTH]--;
    if (game->ram[MYSMB_RAM_SQUARE1_LENGTH] == 0U) {
        game->ram[MYSMB_RAM_SQUARE1_BUFFER] = 0U;
        mysmb_audio_write_apu(game, 21U, 0x0eU);
        mysmb_audio_write_apu(game, 21U, 0x0fU);
    }
}

static void mysmb_audio_step_square2(struct mysmb_game *game)
{
    mysmb_u8 queue;
    mysmb_u8 buffer;

    /* ROM Square2SfxHandler checks an active 1-up before it reads the queue.
     * ContinueExtraLife owns the whole current invocation, including the
     * source's divide-by-eight decision and decrement trampoline. */
    buffer = game->ram[MYSMB_RAM_SQUARE2_BUFFER];
    if ((buffer & MYSMB_SFX_EXTRA_LIFE) != 0U) {
        mysmb_audio_square2_continue_extra_life(game);
        return;
    }

    queue = game->ram[MYSMB_RAM_SQUARE2_QUEUE];
    if (queue != 0U) {
        game->ram[MYSMB_RAM_SQUARE2_BUFFER] = queue;
        if ((queue & 0x80U) != 0U) {
            mysmb_audio_square2_play_bowser_fall(game);
            return;
        }
        else if ((queue & 1U) != 0U) {
            game->ram[MYSMB_RAM_SQUARE2_QUEUE] = (mysmb_u8)(queue >> 1U);
            mysmb_audio_square2_play_coin_timer(game, 0U);
        }
        else {
            queue >>= 1U;
            game->ram[MYSMB_RAM_SQUARE2_QUEUE] = queue;
            if ((queue & 1U) != 0U) {
                game->ram[MYSMB_RAM_SQUARE2_QUEUE] = (mysmb_u8)(queue >> 1U);
                mysmb_audio_square2_play_grow_item(game, 0x10U);
                return;
            }
            else {
                queue >>= 1U;
                game->ram[MYSMB_RAM_SQUARE2_QUEUE] = queue;
                if ((queue & 1U) != 0U) {
                    game->ram[MYSMB_RAM_SQUARE2_QUEUE] = (mysmb_u8)(queue >> 1U);
                    mysmb_audio_square2_play_grow_item(game, 0x20U);
                    return;
                }
                else {
                    queue >>= 1U;
                    game->ram[MYSMB_RAM_SQUARE2_QUEUE] = queue;
                    if ((queue & 1U) != 0U) {
                        game->ram[MYSMB_RAM_SQUARE2_QUEUE] =
                            (mysmb_u8)(queue >> 1U);
                        mysmb_audio_square2_play_blast(game);
                    }
                    else {
                        queue >>= 1U;
                        game->ram[MYSMB_RAM_SQUARE2_QUEUE] = queue;
                        if ((queue & 1U) != 0U) {
                            game->ram[MYSMB_RAM_SQUARE2_QUEUE] =
                                (mysmb_u8)(queue >> 1U);
                            mysmb_audio_square2_play_coin_timer(game, 1U);
                        }
                        else {
                            queue >>= 1U;
                            game->ram[MYSMB_RAM_SQUARE2_QUEUE] = queue;
                            if ((queue & 1U) != 0U) {
                                game->ram[MYSMB_RAM_SQUARE2_QUEUE] =
                                    (mysmb_u8)(queue >> 1U);
                                mysmb_audio_square2_play_power_up(game);
                            }
                            else {
                                queue >>= 1U;
                                game->ram[MYSMB_RAM_SQUARE2_QUEUE] = queue;
                                if ((queue & 1U) != 0U) {
                                    game->ram[MYSMB_RAM_SQUARE2_QUEUE] =
                                        (mysmb_u8)(queue >> 1U);
                                    mysmb_audio_square2_play_extra_life(game);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /* CheckSfx2Buffer performs LSR on A only.  The buffer retains the
     * original unshifted queue, so these masks encode the same branch order
     * without mutating game RAM. */
    buffer = game->ram[MYSMB_RAM_SQUARE2_BUFFER];
    if (buffer == 0U) return;
    if ((buffer & 0x80U) != 0U)
        mysmb_audio_square2_continue_bowser_fall(game);
    else if ((buffer & 0x01U) != 0U)
        mysmb_audio_square2_continue_coin_timer(game);
    else if ((buffer & 0x02U) != 0U || (buffer & 0x04U) != 0U)
        mysmb_audio_square2_continue_grow_item(game);
    else if ((buffer & 0x08U) != 0U)
        mysmb_audio_square2_continue_blast(game);
    else if ((buffer & 0x10U) != 0U)
        mysmb_audio_square2_continue_coin_timer(game);
    else if ((buffer & 0x20U) != 0U)
        mysmb_audio_square2_continue_power_up(game);
    else
        mysmb_audio_square2_continue_extra_life(game);
}

/* ROM BrickShatterFreqData and its paired source table.  The bytes remain in
 * the owner-local PRG binding: these helpers only preserve table,Y access. */
static mysmb_u8 mysmb_audio_brick_shatter_frequency(
    const struct mysmb_game *game, mysmb_u8 index)
{
    return mysmb_audio_read_cpu(game, (mysmb_u16)(0x8000UL +
        MYSMB_ROM_BRICK_SHATTER_FREQ_DATA + index));
}

static mysmb_u8 mysmb_audio_brick_shatter_envelope(
    const struct mysmb_game *game, mysmb_u8 index)
{
    return mysmb_audio_read_cpu(game, (mysmb_u16)(0x8000UL +
        MYSMB_ROM_BRICK_SHATTER_ENV_DATA + index));
}

/* ROM BowserFlameEnvData-1,Y.  The -1 is deliberate: ContinueBowserFlame
 * divides the remaining length first, then indexes the preceding byte. */
static mysmb_u8 mysmb_audio_bowser_flame_envelope(
    const struct mysmb_game *game, mysmb_u8 index)
{
    return mysmb_audio_read_cpu(game, (mysmb_u16)(0x7fffUL +
        MYSMB_ROM_BOWSER_FLAME_ENV_DATA + index));
}

/* ROM PlayNoiseSfx writes the noise envelope, period and length in order. */
static void mysmb_audio_play_noise_sfx(struct mysmb_game *game, mysmb_u8 a,
                                       mysmb_u8 x)
{
    mysmb_audio_write_apu(game, 12U, a);
    mysmb_audio_write_apu(game, 14U, x);
    mysmb_audio_write_apu(game, 15U, 0x18U);
}

/* ROM DecrementSfx3Length -> ExSfx3.  The terminal branch mutes noise and
 * clears only NoiseSoundBuffer; queue clearing remains SoundEngine's tail. */
static void mysmb_audio_decrement_noise_length(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_NOISE_LENGTH]--;
    if (game->ram[MYSMB_RAM_NOISE_LENGTH] != 0U) return;
    mysmb_audio_write_apu(game, 12U, 0xf0U);
    game->ram[MYSMB_RAM_NOISE_BUFFER] = 0U;
}

/* ROM PlayBrickShatter falls through ContinueBrickShatter. */
static void mysmb_audio_continue_brick_shatter(struct mysmb_game *game)
{
    mysmb_u8 length;
    mysmb_u8 index;

    length = game->ram[MYSMB_RAM_NOISE_LENGTH];
    if ((length & 1U) != 0U) {
        index = (mysmb_u8)(length >> 1U);
        mysmb_audio_play_noise_sfx(game,
            mysmb_audio_brick_shatter_envelope(game, index),
            mysmb_audio_brick_shatter_frequency(game, index));
    }
    mysmb_audio_decrement_noise_length(game);
}

static void mysmb_audio_play_brick_shatter(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_NOISE_LENGTH] = 0x20U;
    mysmb_audio_continue_brick_shatter(game);
}

/* ROM PlayBowserFlame falls through ContinueBowserFlame. */
static void mysmb_audio_continue_bowser_flame(struct mysmb_game *game)
{
    mysmb_u8 index;

    index = (mysmb_u8)(game->ram[MYSMB_RAM_NOISE_LENGTH] >> 1U);
    mysmb_audio_play_noise_sfx(game,
        mysmb_audio_bowser_flame_envelope(game, index), 0x0fU);
    mysmb_audio_decrement_noise_length(game);
}

static void mysmb_audio_play_bowser_flame(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_NOISE_LENGTH] = 0x40U;
    mysmb_audio_continue_bowser_flame(game);
}

/* ROM NoiseSfxHandler -> CheckNoiseBuffer.  Queue shifts mutate $fd just as
 * 6502 LSR does; buffer tests shift A only and leave $f3 unmodified. */
static void mysmb_audio_step_noise(struct mysmb_game *game)
{
    mysmb_u8 queue;
    mysmb_u8 buffer;

    queue = game->ram[MYSMB_RAM_NOISE_QUEUE];
    if (queue != 0U) {
        game->ram[MYSMB_RAM_NOISE_BUFFER] = queue;
        queue >>= 1U;
        game->ram[MYSMB_RAM_NOISE_QUEUE] = queue;
        if ((game->ram[MYSMB_RAM_NOISE_BUFFER] & 1U) != 0U) {
            mysmb_audio_play_brick_shatter(game);
            return;
        }
        if ((queue & 1U) != 0U) {
            game->ram[MYSMB_RAM_NOISE_QUEUE] = (mysmb_u8)(queue >> 1U);
            mysmb_audio_play_bowser_flame(game);
            return;
        }
        game->ram[MYSMB_RAM_NOISE_QUEUE] = (mysmb_u8)(queue >> 1U);
    }
    buffer = game->ram[MYSMB_RAM_NOISE_BUFFER];
    if (buffer == 0U) return;
    if ((buffer & 1U) != 0U)
        mysmb_audio_continue_brick_shatter(game);
    else if ((buffer & 2U) != 0U)
        mysmb_audio_continue_bowser_flame(game);
}

/* ROM ProcessLengthData.  This helper belongs to the later shared-music
 * helper chain, but S4 calls it at exactly the source call boundary. */
static mysmb_u8 mysmb_audio_process_music_length(struct mysmb_game *game,
                                                  mysmb_u8 data)
{
    mysmb_u8 index;

    index = (mysmb_u8)((data & 7U) +
        game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET] +
        game->ram[MYSMB_RAM_NOTE_LENGTH_TABLE_ADDER]);
    return mysmb_audio_read_cpu(game,
        (mysmb_u16)(0xff66UL + index));
}

/* ROM LoadEnvelopeData.  The owner-local tables remain bound through the
 * common CPU-address reader; S8 owns independent completion credit. */
static mysmb_u8 mysmb_audio_load_music_envelope(const struct mysmb_game *game,
                                                 mysmb_u8 index)
{
    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x08U) != 0U)
        return mysmb_audio_read_cpu(game, (mysmb_u16)(0xff96UL + index));
    if ((game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0x7dU) == 0U)
        return mysmb_audio_read_cpu(game, (mysmb_u16)(0xffa2UL + index));
    return mysmb_audio_read_cpu(game, (mysmb_u16)(0xff9aUL + index));
}

/* ROM EndOfMusicData.  Return nonzero only for the source RTS that ends this
 * SoundEngine invocation.  A loop branch reaches LoadHeader, which falls
 * directly back into HandleSquare2Music in the same invocation. */
static mysmb_u8 mysmb_audio_end_square2_music(struct mysmb_game *game)
{
    mysmb_u8 area;
    mysmb_u8 event;

    event = game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER];
    if (event == 0x40U) {
        area = game->ram[MYSMB_RAM_AREA_MUSIC_ALT];
        if (area != 0U) {
            mysmb_audio_handle_area_music_loop(game, area);
            return 0U;
        }
    }
    if ((event & 0x04U) != 0U) {
        mysmb_audio_load_event_music(game, event);
        return 0U;
    }
    area = (mysmb_u8)(game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0x5fU);
    if (area != 0U) {
        mysmb_audio_handle_area_music_loop(game, area);
        return 0U;
    }
    game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = 0U;
    game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = 0U;
    mysmb_audio_write_apu(game, 8U, 0U);
    mysmb_audio_write_apu(game, 0U, 0x90U);
    mysmb_audio_write_apu(game, 4U, 0x90U);
    return 1U;
}

/* ROM HandleSquare2Music through NoDecEnv1.  MusicData is a source CPU
 * pointer, so every fetch goes through the shared owner-ROM reader. */
static mysmb_u8 mysmb_audio_step_square2_music(struct mysmb_game *game)
{
    mysmb_u16 music_data;
    mysmb_u8 data;
    mysmb_u8 control_x;
    mysmb_u8 control_y;
    mysmb_u8 envelope;

    /* LoadHeader falls through into this label.  The loop is required for
     * EndOfMusicData's JMP routes: after a new header is loaded, its note
     * counter is one and the source immediately parses its first byte. */
    for (;;) {
        game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER]--;
        if (game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] != 0U) break;
        music_data = (mysmb_u16)(((mysmb_u16)game->ram[0x00f6U] << 8U) |
                                  game->ram[0x00f5U]);
        data = mysmb_audio_read_cpu(game, (mysmb_u16)(music_data +
            game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]));
        game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]++;
        if (data == 0U) {
            if (mysmb_audio_end_square2_music(game) != 0U) return 1U;
            continue;
        }
        if ((data & 0x80U) != 0U) {
            game->ram[MYSMB_RAM_SQUARE2_NOTE_LENGTH] =
                mysmb_audio_process_music_length(game, data);
            data = mysmb_audio_read_cpu(game, (mysmb_u16)(music_data +
                game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]));
            game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2]++;
        }
        if (game->ram[MYSMB_RAM_SQUARE2_BUFFER] == 0U) {
            control_x = 4U;
            control_y = data;
            if (mysmb_audio_set_freq_sq2(game, data) == 0U) {
                envelope = 0U;
            }
            else {
                envelope = mysmb_audio_envelope_control(game);
                control_x = 0x82U;
                control_y = 0x7fU;
            }
            game->ram[MYSMB_RAM_SQUARE2_ENVELOPE] = envelope;
            mysmb_audio_dump_sq2_regs(game, control_x, control_y);
        }
        game->ram[MYSMB_RAM_SQUARE2_NOTE_COUNTER] =
            game->ram[MYSMB_RAM_SQUARE2_NOTE_LENGTH];
        break;
    }
    if (game->ram[MYSMB_RAM_SQUARE2_BUFFER] != 0U ||
        (game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x91U) != 0U)
        return 0U;
    /* Source keeps Y at the pre-decrement envelope offset.  DEC changes
     * only memory, then LoadEnvelopeData indexes with the preserved Y. */
    envelope = game->ram[MYSMB_RAM_SQUARE2_ENVELOPE];
    if (envelope != 0U)
        game->ram[MYSMB_RAM_SQUARE2_ENVELOPE]--;
    mysmb_audio_write_apu(game, 4U,
        mysmb_audio_load_music_envelope(game, envelope));
    mysmb_audio_write_apu(game, 5U, 0x7fU);
    return 0U;
}

/* ROM HandleTriangleMusic through LoadTriCtrlReg. */
static void mysmb_audio_step_triangle_music(struct mysmb_game *game)
{
    mysmb_u16 music_data;
    mysmb_u8 data;
    mysmb_u8 length;
    mysmb_u8 control;

    game->ram[MYSMB_RAM_TRIANGLE_NOTE_COUNTER]--;
    if (game->ram[MYSMB_RAM_TRIANGLE_NOTE_COUNTER] != 0U) return;
    music_data = (mysmb_u16)(((mysmb_u16)game->ram[0x00f6U] << 8U) |
                              game->ram[0x00f5U]);
    data = mysmb_audio_read_cpu(game, (mysmb_u16)(music_data +
        game->ram[MYSMB_RAM_MUSIC_OFFSET_TRIANGLE]));
    game->ram[MYSMB_RAM_MUSIC_OFFSET_TRIANGLE]++;
    if (data == 0U) {
        mysmb_audio_write_apu(game, 8U, 0U);
        return;
    }
    if ((data & 0x80U) != 0U) {
        game->ram[MYSMB_RAM_TRIANGLE_NOTE_BUFFER] =
            mysmb_audio_process_music_length(game, data);
        mysmb_audio_write_apu(game, 8U, 0x1fU);
        data = mysmb_audio_read_cpu(game, (mysmb_u16)(music_data +
            game->ram[MYSMB_RAM_MUSIC_OFFSET_TRIANGLE]));
        game->ram[MYSMB_RAM_MUSIC_OFFSET_TRIANGLE]++;
        if (data == 0U) {
            mysmb_audio_write_apu(game, 8U, 0U);
            return;
        }
    }
    (void)mysmb_audio_set_freq_tri(game, data);
    game->ram[MYSMB_RAM_TRIANGLE_NOTE_COUNTER] =
        game->ram[MYSMB_RAM_TRIANGLE_NOTE_BUFFER];
    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x6eU) == 0U &&
        (game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0x0aU) == 0U)
        return;
    length = game->ram[MYSMB_RAM_TRIANGLE_NOTE_BUFFER];
    if (length >= 0x12U) control = 0xffU;
    else if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x08U) != 0U)
        control = 0x0fU;
    else control = 0x1fU;
    mysmb_audio_write_apu(game, 8U, control);
}
/* ROM HandleSquare1Music through DoAltLoad.  Square 1 encodes its three-bit
 * duration selector in bits 0, 7 and 6, unlike Square 2 and Triangle which
 * use the low three bits directly. */
static void mysmb_audio_step_square1_music(struct mysmb_game *game)
{
    mysmb_u16 music_data;
    mysmb_u8 data;
    mysmb_u8 control_x;
    mysmb_u8 control_y;
    mysmb_u8 envelope;
    mysmb_u8 length_index;

    /* HandleSquare1Music enters Triangle directly when this header supplies
     * no Square1 stream.  This is independent of the active music buffers. */
    if (game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1] == 0U) return;
    game->ram[MYSMB_RAM_SQUARE1_NOTE_COUNTER]--;
    if (game->ram[MYSMB_RAM_SQUARE1_NOTE_COUNTER] == 0U) {
        music_data = (mysmb_u16)(((mysmb_u16)game->ram[0x00f6U] << 8U) |
                                  game->ram[0x00f5U]);
        data = mysmb_audio_read_cpu(game, (mysmb_u16)(music_data +
            game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1]));
        game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1]++;
        while (data == 0U) {
            /* FetchSqu1MusicData's null bytes are audible control changes,
             * not merely an in-memory loop marker. */
            mysmb_audio_write_apu(game, 0U, 0x83U);
            mysmb_audio_write_apu(game, 1U, 0x94U);
            game->ram[MYSMB_RAM_ALT_REGISTER_CONTENT] = 0x94U;
            data = mysmb_audio_read_cpu(game, (mysmb_u16)(music_data +
                game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1]));
            game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE1]++;
        }
        /* AlternateLengthHandler: carry starts with original bit zero, then
         * three ROLs turn bits 0/7/6 into the length-table selector. */
        length_index = (mysmb_u8)(((data & 1U) << 2U) |
            ((data & 0x80U) >> 6U) | ((data & 0x40U) >> 6U));
        game->ram[MYSMB_RAM_SQUARE1_NOTE_COUNTER] =
            mysmb_audio_process_music_length(game, length_index);
        if (game->ram[MYSMB_RAM_SQUARE1_BUFFER] == 0U) {
            control_x = 0U;
            control_y = (mysmb_u8)(data & 0x3eU);
            if (mysmb_audio_set_freq_squ1(game, control_y) != 0U) {
                envelope = mysmb_audio_envelope_control(game);
                control_x = 0x82U;
                control_y = 0x7fU;
            }
            else {
                envelope = 0U;
            }
            game->ram[MYSMB_RAM_SQUARE1_ENVELOPE] = envelope;
            mysmb_audio_dump_squ1_regs(game, control_x, control_y);
        }
    }
    /* MiscSqu1MusicTasks branches around every tail write while a Square1
     * effect owns the channel. */
    if (game->ram[MYSMB_RAM_SQUARE1_BUFFER] != 0U) return;
    if ((game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] & 0x91U) == 0U) {
        /* As with Square2, DEC changes memory only: LoadEnvelopeData indexes
         * with the pre-decrement Y value. */
        envelope = game->ram[MYSMB_RAM_SQUARE1_ENVELOPE];
        if (envelope != 0U)
            game->ram[MYSMB_RAM_SQUARE1_ENVELOPE]--;
        mysmb_audio_write_apu(game, 0U,
            mysmb_audio_load_music_envelope(game, envelope));
    }
    /* DeathMAltReg / DoAltLoad run both after a normal envelope load and on
     * the death/D4 branch. */
    control_y = game->ram[MYSMB_RAM_ALT_REGISTER_CONTENT];
    if (control_y == 0U) control_y = 0x7fU;
    mysmb_audio_write_apu(game, 1U, control_y);
}
/* ROM HandleNoiseMusic through ExitMusicHandler.  The AlternateLengthHandler
 * call is an S8-owned dependency; its source-visible A/Y result is retained
 * here because NoiseBeatHandler immediately consumes it. */
static void mysmb_audio_step_noise_music(struct mysmb_game *game)
{
    mysmb_u16 music_data;
    mysmb_u8 data;
    mysmb_u8 beat;
    mysmb_u8 table_index;
    mysmb_u8 x;
    mysmb_u8 y;

    if ((game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] & 0xf3U) == 0U) return;
    game->ram[MYSMB_RAM_NOISE_BEAT_COUNTER]--;
    if (game->ram[MYSMB_RAM_NOISE_BEAT_COUNTER] != 0U) return;

    music_data = (mysmb_u16)(((mysmb_u16)game->ram[0x00f6U] << 8U) |
                              game->ram[0x00f5U]);
    for (;;) {
        data = mysmb_audio_read_cpu(game, (mysmb_u16)(music_data +
            game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE]));
        game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE]++;
        if (data != 0U) break;
        game->ram[MYSMB_RAM_MUSIC_OFFSET_NOISE] =
            game->ram[MYSMB_RAM_NOISE_LOOPBACK_OFFSET];
    }

    /* AlternateLengthHandler preserves the original byte in X, rotates bits
     * 0/7/6 into A, and ProcessLengthData leaves the lookup index in Y. */
    x = data;
    table_index = (mysmb_u8)(((data & 1U) << 2U) |
        ((data & 0x80U) >> 6U) | ((data & 0x40U) >> 6U));
    y = (mysmb_u8)(table_index + game->ram[MYSMB_RAM_MUSIC_LENGTH_OFFSET] +
        game->ram[MYSMB_RAM_NOTE_LENGTH_TABLE_ADDER]);
    game->ram[MYSMB_RAM_NOISE_BEAT_COUNTER] =
        mysmb_audio_read_cpu(game, (mysmb_u16)(0xff66UL + y));

    beat = (mysmb_u8)(x & 0x3eU);
    if (beat == 0U) {
        mysmb_audio_write_apu(game, 12U, 0x10U);
        mysmb_audio_write_apu(game, 14U, x);
        mysmb_audio_write_apu(game, 15U, y);
        return;
    }
    if (beat == 0x30U) {
        mysmb_audio_write_apu(game, 12U, 0x1cU);
        mysmb_audio_write_apu(game, 14U, 0x03U);
        mysmb_audio_write_apu(game, 15U, 0x58U);
        return;
    }
    if (beat == 0x20U) {
        mysmb_audio_write_apu(game, 12U, 0x1cU);
        mysmb_audio_write_apu(game, 14U, 0x0cU);
        mysmb_audio_write_apu(game, 15U, 0x18U);
        return;
    }
    if ((beat & 0x10U) == 0U) {
        mysmb_audio_write_apu(game, 12U, 0x10U);
        mysmb_audio_write_apu(game, 14U, x);
        mysmb_audio_write_apu(game, 15U, y);
        return;
    }
    mysmb_audio_write_apu(game, 12U, 0x1cU);
    mysmb_audio_write_apu(game, 14U, 0x03U);
    mysmb_audio_write_apu(game, 15U, 0x18U);
}
/* ROM ContinueMusic is an unconditional jump to HandleSquare2Music.  Keeping
 * this entry explicit prevents queue/header work from being mistaken for the
 * already-active music-stream handoff. */
static mysmb_u8 mysmb_audio_continue_music(struct mysmb_game *game)
{
    return mysmb_audio_step_square2_music(game);
}

/* ROM StopSquare1Sfx and StopSquare2Sfx.  The first owns Square1's buffer;
 * the second only cycles the master control register. */
static void mysmb_audio_stop_square1_sfx(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SQUARE1_BUFFER] = 0U;
    mysmb_audio_write_apu(game, 21U, 0x0eU);
    mysmb_audio_write_apu(game, 21U, 0x0fU);
}

static void mysmb_audio_stop_square2_sfx(struct mysmb_game *game)
{
    mysmb_audio_write_apu(game, 21U, 0x0dU);
    mysmb_audio_write_apu(game, 21U, 0x0fU);
}

/* ROM GMLoopB -> HandleAreaMusicLoopB.  The loop counter is itself the
 * LoadHeader selector for ground music. */
static void mysmb_audio_handle_area_music_loop(struct mysmb_game *game,
                                                mysmb_u8 area)
{
    game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = 0U;
    game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = area;
    if (area != 1U) {
        /* FindAreaMusicHeader's residual store precedes the shared bit scan.
         * LoadHeader subsequently initializes the offset back to zero. */
        game->ram[MYSMB_RAM_MUSIC_OFFSET_SQUARE2] = 8U;
        (void)mysmb_audio_load_music_header(game,
            mysmb_audio_find_header_selector(area, 8U));
        return;
    }
    game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET]++;
    if (game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] == 0x32U)
        game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] = 0x11U;
    (void)mysmb_audio_load_music_header(game,
        game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET]);
}

/* ROM LoadEventMusic -> NoStopSfx -> FindEventMusicHeader -> LoadHeader. */
static void mysmb_audio_load_event_music(struct mysmb_game *game,
                                         mysmb_u8 event)
{
    game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] = event;
    if (event == MYSMB_EVENT_DEATH_MUSIC) {
        mysmb_audio_stop_square1_sfx(game);
        mysmb_audio_stop_square2_sfx(game);
    }
    game->ram[MYSMB_RAM_AREA_MUSIC_ALT] =
        game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER];
    game->ram[MYSMB_RAM_NOTE_LENGTH_TABLE_ADDER] =
        event == 0x40U ? 8U : 0U;
    game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] = 0U;
    (void)mysmb_audio_load_music_header(game,
        mysmb_audio_find_header_selector(event, 0U));
}

/* ROM LoadAreaMusic -> NoStop1 -> GMLoopB. */
static void mysmb_audio_load_area_music(struct mysmb_game *game,
                                        mysmb_u8 area)
{
    if (area == 4U) mysmb_audio_stop_square1_sfx(game);
    game->ram[MYSMB_RAM_GROUND_MUSIC_HEADER_OFFSET] = 0x10U;
    mysmb_audio_handle_area_music_loop(game, area);
}

void mysmb_audio_select_music(struct mysmb_game *game)
{
    mysmb_u8 event;
    mysmb_u8 area;

    event = game->ram[MYSMB_RAM_EVENT_MUSIC_QUEUE];
    area = game->ram[MYSMB_RAM_AREA_MUSIC_QUEUE];
    if (event != 0U) {
        mysmb_audio_load_event_music(game, event);
    }
    else if (area != 0U) {
        mysmb_audio_load_area_music(game, area);
    }
}

static void mysmb_audio_step_music(struct mysmb_game *game)
{
    mysmb_audio_select_music(game);
    /* SoundEngine leaves the music-channel tasks once both queues and both
     * active music buffers are clear.  This also retains final envelopes. */
    if (game->ram[MYSMB_RAM_EVENT_MUSIC_BUFFER] == 0U &&
        game->ram[MYSMB_RAM_AREA_MUSIC_BUFFER] == 0U) return;
    if (mysmb_audio_continue_music(game) != 0U) return;
    mysmb_audio_step_square1_music(game);
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

/* A frequency-table fetch is a CPU address operation, including the 16-bit
 * wrap if a caller supplies Y=$ff. The normal table resides at $ff00. */
static mysmb_u8 mysmb_audio_read_cpu(const struct mysmb_game *game,
                                     mysmb_u16 address)
{
    mysmb_u16 offset;

    if (address < 0x0800U) return game->ram[address];
    if (address < 0x8000U || game->area_prg == 0) return 0U;
    offset = (mysmb_u16)(address - 0x8000U);
    if (offset >= game->area_prg_size) return 0U;
    return game->area_prg[offset];
}

/* ROM Dump_Squ1_Regs: Y is written before X. */
void mysmb_audio_dump_squ1_regs(struct mysmb_game *game, mysmb_u8 x,
                                 mysmb_u8 y)
{
    mysmb_audio_write_apu(game, 1U, y);
    mysmb_audio_write_apu(game, 0U, x);
}

/* ROM Dump_Freq_Regs, including NoTone's zero-LSB return. */
mysmb_u8 mysmb_audio_dump_freq_regs(struct mysmb_game *game, mysmb_u8 a,
                                 mysmb_u8 x)
{
    mysmb_u8 low;
    mysmb_u8 high;
    mysmb_u16 address;

    address = (mysmb_u16)(0xff01UL + a);
    low = mysmb_audio_read_cpu(game, address);
    if (low == 0U) return 0U;
    mysmb_audio_write_apu(game, (mysmb_u8)(x + 2U), low);
    address = (mysmb_u16)(0xff00UL + a);
    high = (mysmb_u8)(mysmb_audio_read_cpu(game, address) | 8U);
    mysmb_audio_write_apu(game, (mysmb_u8)(x + 3U), high);
    return high;
}

mysmb_u8 mysmb_audio_set_freq_squ1(struct mysmb_game *game, mysmb_u8 a)
{
    return mysmb_audio_dump_freq_regs(game, a, 0U);
}

mysmb_u8 mysmb_audio_play_squ1_sfx(struct mysmb_game *game, mysmb_u8 a,
                                mysmb_u8 x, mysmb_u8 y)
{
    mysmb_audio_dump_squ1_regs(game, x, y);
    return mysmb_audio_set_freq_squ1(game, a);
}

/* ROM Dump_Sq2_Regs reverses the square-one write order. */
void mysmb_audio_dump_sq2_regs(struct mysmb_game *game, mysmb_u8 x,
                                mysmb_u8 y)
{
    mysmb_audio_write_apu(game, 4U, x);
    mysmb_audio_write_apu(game, 5U, y);
}

mysmb_u8 mysmb_audio_set_freq_sq2(struct mysmb_game *game, mysmb_u8 a)
{
    return mysmb_audio_dump_freq_regs(game, a, 4U);
}

mysmb_u8 mysmb_audio_play_sq2_sfx(struct mysmb_game *game, mysmb_u8 a,
                               mysmb_u8 x, mysmb_u8 y)
{
    mysmb_audio_dump_sq2_regs(game, x, y);
    return mysmb_audio_set_freq_sq2(game, a);
}

mysmb_u8 mysmb_audio_set_freq_tri(struct mysmb_game *game, mysmb_u8 a)
{
    return mysmb_audio_dump_freq_regs(game, a, 8U);
}

/* ROM SwimStompEnvelopeData-1,Y, where Y is the remaining effect length.
 * S4's ContinueSwimStomp will consume this owner-ROM binding. */
mysmb_u8 mysmb_audio_swim_stomp_envelope(const struct mysmb_game *game,
                                          mysmb_u8 length)
{
    return mysmb_audio_read_cpu(game,
        (mysmb_u16)(0xf3b0UL + length));
}

/* ROM PlayFlagpoleSlide -> FPS2nd -> DmpJpFPS. */
void mysmb_audio_square1_play_flagpole(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SQUARE1_LENGTH] = 0x40U;
    (void)mysmb_audio_set_freq_squ1(game, 0x62U);
    mysmb_audio_dump_squ1_regs(game, 0x99U, 0xbcU);
}

/* ROM PlaySmallJump/PlayBigJump -> JumpRegContents. The original then
 * falls through ContinueSndJump and S4's decrement tail in this frame. */
void mysmb_audio_square1_play_jump(struct mysmb_game *game, mysmb_u8 small)
{
    (void)mysmb_audio_play_squ1_sfx(game,
        small != 0U ? 0x26U : 0x18U, 0x82U, 0xa7U);
    game->ram[MYSMB_RAM_SQUARE1_LENGTH] = 0x28U;
}

/* ROM ContinueSndJump -> N2Prt, with FPS2nd's shared third phase. */
void mysmb_audio_square1_continue_jump(struct mysmb_game *game)
{
    mysmb_u8 length;

    length = game->ram[MYSMB_RAM_SQUARE1_LENGTH];
    if (length == 0x25U)
        mysmb_audio_dump_squ1_regs(game, 0x5fU, 0xf6U);
    else if (length == 0x20U)
        mysmb_audio_dump_squ1_regs(game, 0x48U, 0xbcU);
}

/* ROM PlayFireballThrow/PlayBump -> Fthrow. Both share frequency $0c. */
void mysmb_audio_square1_play_throw(struct mysmb_game *game,
                                     mysmb_u8 fireball)
{
    game->ram[MYSMB_RAM_SQUARE1_LENGTH] =
        fireball != 0U ? 0x05U : 0x0aU;
    (void)mysmb_audio_play_squ1_sfx(game, 0x0cU, 0x9eU,
                                     fireball != 0U ? 0x99U : 0x93U);
}

/* ROM ContinueBumpThrow -> DecJpFPS. The S4 tail decrements afterward. */
void mysmb_audio_square1_continue_throw(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_SQUARE1_LENGTH] == 0x06U)
        mysmb_audio_write_apu(game, 1U, 0xbbU);
}

/* S5 table accessors preserve the source's table-1,Y addressing.  The
 * owner ROM remains the only source of the frequency bytes. */
mysmb_u8 mysmb_audio_square2_extra_life_freq(const struct mysmb_game *game,
                                               mysmb_u8 index)
{
    return mysmb_audio_read_cpu(game, (mysmb_u16)(0xf4d3UL + index));
}

mysmb_u8 mysmb_audio_square2_power_up_freq(const struct mysmb_game *game,
                                            mysmb_u8 index)
{
    return mysmb_audio_read_cpu(game, (mysmb_u16)(0xf4d9UL + index));
}

mysmb_u8 mysmb_audio_square2_grow_vine_freq(const struct mysmb_game *game,
                                             mysmb_u8 index)
{
    return mysmb_audio_read_cpu(game, (mysmb_u16)(0xf4f8UL + index));
}

/* ROM JumpToDecLength2 is the unconditional entry into this shared tail. */
static void mysmb_audio_square2_jump_to_decrement(struct mysmb_game *game)
{
    mysmb_audio_square2_decrement(game);
}

/* ROM PBFRegs -> EL_LRegs -> LoadSqu2Regs.  Bowser fall and the earlier
 * blast path share the same control-register load; this entry supplies the
 * Bowser-specific A/Y pair and preserves LoadSqu2Regs' decrement fallthrough. */
static void mysmb_audio_square2_load_bowser_regs(struct mysmb_game *game,
                                                  mysmb_u8 frequency,
                                                  mysmb_u8 control)
{
    (void)mysmb_audio_play_sq2_sfx(game, frequency, 0x9fU, control);
    mysmb_audio_square2_decrement(game);
}

/* ROM PlayBowserFall -> BlstSJp -> PBFRegs -> EL_LRegs. */
static void mysmb_audio_square2_play_bowser_fall(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SQUARE2_LENGTH] = 0x38U;
    mysmb_audio_square2_load_bowser_regs(game, 0x18U, 0xc4U);
}

/* ROM ContinueBowserFall changes its tone only at remaining length $08. */
static void mysmb_audio_square2_continue_bowser_fall(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_SQUARE2_LENGTH] != 0x08U) {
        mysmb_audio_square2_jump_to_decrement(game);
        return;
    }
    mysmb_audio_square2_load_bowser_regs(game, 0x5aU, 0xa4U);
}

/* ROM PlayExtraLife -> ContinueExtraLife -> DivLLoop.  Three logical shifts
 * determine whether the remaining length is divisible by eight.  Any set bit
 * takes JumpToDecLength2; otherwise table-1,Y is loaded before the shared
 * LoadSqu2Regs/decrement tail. */
static void mysmb_audio_square2_continue_extra_life(struct mysmb_game *game)
{
    mysmb_u8 length;
    mysmb_u8 index;

    length = game->ram[MYSMB_RAM_SQUARE2_LENGTH];
    if ((length & 7U) != 0U) {
        mysmb_audio_square2_jump_to_decrement(game);
        return;
    }
    index = (mysmb_u8)(length >> 3U);
    (void)mysmb_audio_play_sq2_sfx(game,
        mysmb_audio_square2_extra_life_freq(game, index), 0x82U, 0x7fU);
    mysmb_audio_square2_decrement(game);
}

static void mysmb_audio_square2_play_extra_life(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SQUARE2_LENGTH] = 0x30U;
    mysmb_audio_square2_continue_extra_life(game);
}

/* ROM PlayGrowPowerUp/PlayGrowVine -> GrowItemRegs. */
static void mysmb_audio_square2_play_grow_item(struct mysmb_game *game,
                                                mysmb_u8 length)
{
    game->ram[MYSMB_RAM_SQUARE2_LENGTH] = length;
    mysmb_audio_write_apu(game, 5U, 0x7fU);
    game->ram[MYSMB_RAM_SFX_SECONDARY] = 0U;
    mysmb_audio_square2_continue_grow_item(game);
}

/* ROM ContinueGrowItems uses its separate counter: it never decrements the
 * usual length.  Equality jumps to EmptySfx2Buffer; otherwise it writes the
 * control register directly and calls SetFreq_Squ2 with PUp_VGrow_FreqData,Y. */
static void mysmb_audio_square2_continue_grow_item(struct mysmb_game *game)
{
    mysmb_u8 index;

    game->ram[MYSMB_RAM_SFX_SECONDARY]++;
    index = (mysmb_u8)(game->ram[MYSMB_RAM_SFX_SECONDARY] >> 1U);
    if (index == game->ram[MYSMB_RAM_SQUARE2_LENGTH]) {
        game->ram[MYSMB_RAM_SQUARE2_BUFFER] = 0U;
        mysmb_audio_write_apu(game, 21U, 0x0dU);
        mysmb_audio_write_apu(game, 21U, 0x0fU);
        return;
    }
    mysmb_audio_write_apu(game, 4U, 0x9dU);
    (void)mysmb_audio_set_freq_sq2(game,
        mysmb_audio_square2_grow_vine_freq(game, index));
}

/* ROM PlayCoinGrab/PlayTimerTick -> CGrab_TTickRegL. */
static void mysmb_audio_square2_play_coin_timer(struct mysmb_game *game,
                                                  mysmb_u8 timer)
{
    game->ram[MYSMB_RAM_SQUARE2_LENGTH] = timer != 0U ? 0x06U : 0x35U;
    (void)mysmb_audio_play_sq2_sfx(game, 0x42U,
        timer != 0U ? 0x98U : 0x8dU, 0x7fU);
}

/* ROM ContinueCGrabTTick -> N2Tone -> DecrementSfx2Length. */
static void mysmb_audio_square2_continue_coin_timer(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_SQUARE2_LENGTH] == 0x30U)
        mysmb_audio_write_apu(game, 6U, 0x54U);
    mysmb_audio_square2_decrement(game);
}

/* ROM PlayBlast -> SBlasJ -> BlstSJp. */
static void mysmb_audio_square2_play_blast(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SQUARE2_LENGTH] = 0x20U;
    (void)mysmb_audio_play_sq2_sfx(game, 0x5eU, 0x9fU, 0x94U);
}

/* ROM ContinueBlast selects its second tone only at length $18. */
static void mysmb_audio_square2_continue_blast(struct mysmb_game *game)
{
    if (game->ram[MYSMB_RAM_SQUARE2_LENGTH] == 0x18U)
        (void)mysmb_audio_play_sq2_sfx(game, 0x18U, 0x9fU, 0x93U);
    mysmb_audio_square2_decrement(game);
}

/* ROM PlayPowerUpGrab falls through ContinuePowerUpGrab. */
static void mysmb_audio_square2_play_power_up(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SQUARE2_LENGTH] = 0x36U;
}

/* ROM ContinuePowerUpGrab changes pitch on even remaining lengths only. */
static void mysmb_audio_square2_continue_power_up(struct mysmb_game *game)
{
    mysmb_u8 length;
    mysmb_u8 index;

    length = game->ram[MYSMB_RAM_SQUARE2_LENGTH];
    if ((length & 1U) == 0U) {
        index = (mysmb_u8)(length >> 1U);
        (void)mysmb_audio_play_sq2_sfx(game,
            mysmb_audio_square2_power_up_freq(game, index), 0x5dU, 0x7fU);
    }
    mysmb_audio_square2_decrement(game);
}

/* ROM DecrementSfx2Length -> EmptySfx2Buffer -> StopSquare2Sfx. */
static void mysmb_audio_square2_decrement(struct mysmb_game *game)
{
    game->ram[MYSMB_RAM_SQUARE2_LENGTH]--;
    if (game->ram[MYSMB_RAM_SQUARE2_LENGTH] != 0U) return;
    game->ram[MYSMB_RAM_SQUARE2_BUFFER] = 0U;
    mysmb_audio_write_apu(game, 21U, 0x0dU);
    mysmb_audio_write_apu(game, 21U, 0x0fU);
}

static void mysmb_audio_pause_tone(struct mysmb_game *game, mysmb_u8 tone)
{

    mysmb_audio_play_squ1_sfx(game, tone, 0x84U, 0x7fU);
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
