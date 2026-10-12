#include <string.h>
#include "app/game_io.h"

static struct mysmb_game game;
static struct mysmb_game before;
static struct mysmb_ppu_frame ppu;

int main(void)
{
    struct mysmb_io_input decoded;
    struct mysmb_input input;
    struct mysmb_io_video_frame video;
    struct mysmb_io_audio_frame audio;
    unsigned int index;

    decoded.buttons = 0x42U;
    decoded.buttons2 = 0xa0U;
    decoded.requests=MYSMB_IO_REQUEST_EXIT;
    mysmb_game_io_input(&decoded, &input);
    if (input.buttons != decoded.buttons || input.buttons2 != decoded.buttons2)
        return 1;
    ppu.pixels[0] = 0x21U;
    ppu.pixels[61439U] = 0x3fU;
    mysmb_game_io_video(&ppu, &video);
    if (video.pixels != ppu.pixels || video.pixels[61439U] != 0x3fU)
        return 2;

    memset(&game, 0x55, sizeof(game));
    game.apu_write_count = 2U;
    game.apu_writes[0].index = 3U;
    game.apu_writes[0].value = 8U;
    game.apu_writes[1] = game.apu_writes[0];
    memcpy(&before, &game, sizeof(game));
    mysmb_game_io_audio(&game, &audio);
    if (memcmp(&before, &game, sizeof(game)) != 0) return 3;
    if (audio.write_count != 2U || audio.writes[0].index != 3U ||
        audio.writes[1].value != 8U || audio.writes[2].value != 0U)
        return 4;
    for (index = 0U; index < 24U; ++index)
        if (audio.registers[index] != game.apu_registers[index]) return 5;
    if (audio.channel_enable != game.apu_channel_enable ||
        audio.frame_counter != game.apu_frame_counter ||
        audio.delta_counter_load != game.apu_delta_counter_load) return 6;
    game.apu_writes[0].value = 0U;
    if (audio.writes[0].value != 8U) return 7;
    game.apu_write_count = 64U;
    game.apu_writes[63].index = 23U;
    game.apu_writes[63].value = 0x80U;
    mysmb_game_io_audio(&game, &audio);
    if (audio.write_count != 64U || audio.writes[63].value != 0x80U) return 8;
    game.apu_write_count = 0U;
    mysmb_game_io_audio(&game, &audio);
    if (audio.write_count != 0U || audio.writes[63].value != 0U) return 9;
    return 0;
}
