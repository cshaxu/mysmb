#include "game/frame_snapshot.h"

enum {
    MYSMB_SNAPSHOT_OAM_RAM = 0x0200U,
    MYSMB_SNAPSHOT_AUDIO_SQUARE1 = 0x00f1U,
    MYSMB_SNAPSHOT_AUDIO_SQUARE2 = 0x00f2U,
    MYSMB_SNAPSHOT_AUDIO_NOISE = 0x00f3U,
    MYSMB_SNAPSHOT_AUDIO_AREA = 0x00f4U,
    MYSMB_SNAPSHOT_AUDIO_EVENT = 0x07b1U,
    MYSMB_SNAPSHOT_AUDIO_PAUSE = 0x07b2U,
    MYSMB_SNAPSHOT_AUDIO_SQUARE1_LENGTH = 0x07bbU,
    MYSMB_SNAPSHOT_AUDIO_SQUARE2_LENGTH = 0x07bdU,
    MYSMB_SNAPSHOT_AUDIO_SECONDARY = 0x07beU,
    MYSMB_SNAPSHOT_AUDIO_NOISE_LENGTH = 0x07bfU,
    MYSMB_SNAPSHOT_AUDIO_AREA_ALT = 0x07c5U,
    MYSMB_SNAPSHOT_AUDIO_PAUSE_MODE = 0x07c6U,
    MYSMB_SNAPSHOT_AUDIO_SQUARE1_QUEUE = 0x00ffU,
    MYSMB_SNAPSHOT_AUDIO_EVENT_QUEUE = 0x00fcU
};

static void mysmb_frame_snapshot_copy(mysmb_u8 *destination,
                                      const mysmb_u8 *source,
                                      mysmb_u16 count)
{
    mysmb_u16 index;

    for (index = 0U; index < count; ++index) destination[index] = source[index];
}

void mysmb_frame_snapshot_capture(const struct mysmb_game *game,
                                  struct mysmb_frame_snapshot *snapshot)
{
    static const mysmb_u16 audio_offsets[MYSMB_FRAME_SNAPSHOT_AUDIO_BYTES] = {
        MYSMB_SNAPSHOT_AUDIO_SQUARE1, MYSMB_SNAPSHOT_AUDIO_SQUARE2,
        MYSMB_SNAPSHOT_AUDIO_NOISE, MYSMB_SNAPSHOT_AUDIO_AREA,
        MYSMB_SNAPSHOT_AUDIO_EVENT, MYSMB_SNAPSHOT_AUDIO_PAUSE,
        MYSMB_SNAPSHOT_AUDIO_SQUARE1_LENGTH, MYSMB_SNAPSHOT_AUDIO_SQUARE2_LENGTH,
        MYSMB_SNAPSHOT_AUDIO_SECONDARY, MYSMB_SNAPSHOT_AUDIO_NOISE_LENGTH,
        MYSMB_SNAPSHOT_AUDIO_AREA_ALT, MYSMB_SNAPSHOT_AUDIO_PAUSE_MODE,
        MYSMB_SNAPSHOT_AUDIO_SQUARE1_QUEUE, MYSMB_SNAPSHOT_AUDIO_EVENT_QUEUE
    };
    mysmb_u8 index;

    snapshot->sequence = game->frame_number;
    snapshot->verified_fields = 0U;
    mysmb_frame_snapshot_copy(snapshot->cpu_ram, game->ram, 0x0800U);
    mysmb_frame_snapshot_copy(snapshot->name_table[0], game->name_table[0], 0x0400U);
    mysmb_frame_snapshot_copy(snapshot->name_table[1], game->name_table[1], 0x0400U);
    mysmb_frame_snapshot_copy(snapshot->oam,
                              &game->ram[MYSMB_SNAPSHOT_OAM_RAM], 0x0100U);
    for (index = 0U; index < MYSMB_FRAME_SNAPSHOT_AUDIO_BYTES; ++index) {
        snapshot->audio[index] = game->ram[audio_offsets[index]];
    }
    snapshot->captured_fields = (mysmb_u16)(MYSMB_FRAME_SNAPSHOT_CPU_RAM |
        MYSMB_FRAME_SNAPSHOT_NAME_TABLES | MYSMB_FRAME_SNAPSHOT_OAM |
        MYSMB_FRAME_SNAPSHOT_AUDIO);
}

mysmb_u8 mysmb_frame_snapshot_is_complete(
    const struct mysmb_frame_snapshot *snapshot)
{
    return (mysmb_u8)(snapshot->captured_fields == MYSMB_FRAME_SNAPSHOT_REQUIRED &&
        snapshot->verified_fields == MYSMB_FRAME_SNAPSHOT_REQUIRED);
}
