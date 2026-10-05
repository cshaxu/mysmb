#include "app/game_io.h"
#include "core/area.h"
#include "game/audio.h"
#include "core/game.h"
#include "platform/win32/audio_renderer.h"
#include "smb1_local_rom.h"

static unsigned int average_level(const short *samples)
{
    unsigned int sample;
    unsigned long total;
    int value;

    total = 0UL;
    for (sample = 0U; sample < 735U; ++sample) {
        value = samples[sample];
        total += (unsigned long)(value < 0 ? -value : value);
    }
    return (unsigned int)(total / 735UL);
}

int main(void)
{
    struct mysmb_game game;
    struct mysmb_io_audio_frame audio;
    struct mysmb_win32_audio_renderer renderer;
    short samples[735];
    unsigned int frame;
    unsigned int level;

    mysmb_game_initialize(&game);
    mysmb_game_bind_area_source(&game, mysmb_local_prg,
                                MYSMB_LOCAL_PRG_SIZE);
    game.ram[0x0770U] = 1U;
    game.ram[0x00fcU] = 1U;
    mysmb_win32_audio_renderer_initialize(&renderer);
    for (frame = 0U; frame < 180U; ++frame) {
        mysmb_audio_step(&game);
        if (game.apu_write_count >= MYSMB_APU_WRITE_CAPACITY) return 1;
        mysmb_game_io_audio(&game, &audio);
        mysmb_win32_audio_render(&renderer, &audio, samples, 735U, 44100U);
        level = average_level(samples);
        if (frame == 0U && level < 500U) return 2;
        if (frame == 25U && level > 10U) return 3;
        if (frame == 40U && level < 500U) return 4;
        if (frame == 175U && level > 10U) return 5;
    }
    return 0;
}
