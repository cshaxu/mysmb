#include <stdio.h>
#include <stdlib.h>

#include "game/frame_snapshot.h"
#include "smb1_local_rom.h"

static mysmb_u32 mysmb_summary_hash(const mysmb_u8 *bytes, mysmb_u16 count,
                                    mysmb_u32 value)
{
    mysmb_u16 index;

    for (index = 0U; index < count; ++index) {
        value ^= (mysmb_u32)bytes[index];
        value *= 16777619UL;
    }
    return value;
}

int main(int argument_count, char **arguments)
{
    struct mysmb_game game;
    struct mysmb_input input;
    struct mysmb_frame frame;
    struct mysmb_frame_snapshot snapshot;
    unsigned long frames;
    unsigned long start_frame;
    unsigned long release_frame;
    unsigned long index;
    mysmb_u32 hash;

    if (argument_count != 4) return 64;
    frames = strtoul(arguments[1], 0, 10);
    start_frame = strtoul(arguments[2], 0, 10);
    release_frame = strtoul(arguments[3], 0, 10);
    if (frames == 0UL || frames > 600UL || start_frame >= release_frame ||
        release_frame > frames) return 64;
    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg, MYSMB_LOCAL_PRG_SIZE);
    printf("frame,mode,task,ppu_address,ciram_fnv1a,palette_fnv1a,oam_fnv1a\n");
    for (index = 0UL; index < frames; ++index) {
        /* NES serial Start is bit 3; MySMB's decoded RAM representation is $10. */
        input.buttons = index >= start_frame && index < release_frame ?
            MYSMB_BUTTON_START : 0U;
        mysmb_game_tick(&game, &input, &frame);
        mysmb_frame_snapshot_capture(&game, &snapshot);
        hash = mysmb_summary_hash(snapshot.name_table[0], 0x0400U, 2166136261UL);
        hash = mysmb_summary_hash(snapshot.name_table[1], 0x0400U, hash);
        printf("%lu,%u,%u,%04x,%08lx,", index, (unsigned int)frame.operating_mode,
               (unsigned int)frame.operating_mode_task,
               (unsigned int)snapshot.ppu_address, hash);
        hash = mysmb_summary_hash(snapshot.palette, 0x20U, 2166136261UL);
        printf("%08lx,", hash);
        hash = mysmb_summary_hash(snapshot.oam, 0x0100U, 2166136261UL);
        printf("%08lx\n", hash);
    }
    return 0;
}
