#include "app/game_io.h"

void mysmb_game_io_input(const struct mysmb_io_input *source,
                         struct mysmb_input *input)
{
    input->buttons = source->buttons;
    input->buttons2 = source->buttons2;
}

void mysmb_game_io_video(const struct mysmb_ppu_frame *source,
                         struct mysmb_io_video_frame *frame)
{
    frame->pixels = source->pixels;
}

void mysmb_game_io_audio(const struct mysmb_game *source,
                         struct mysmb_io_audio_frame *frame)
{
    unsigned int index;

    for (index = 0U; index < MYSMB_IO_AUDIO_REGISTER_COUNT; ++index)
        frame->registers[index] = source->apu_registers[index];
    frame->delta_counter_load = source->apu_delta_counter_load;
    frame->channel_enable = source->apu_channel_enable;
    frame->frame_counter = source->apu_frame_counter;
    frame->write_count = source->apu_write_count;
    for (index = 0U; index < MYSMB_IO_AUDIO_WRITE_CAPACITY; ++index) {
        if (index < source->apu_write_count) {
            frame->writes[index].index = source->apu_writes[index].index;
            frame->writes[index].value = source->apu_writes[index].value;
        } else {
            frame->writes[index].index = 0U;
            frame->writes[index].value = 0U;
        }
    }
}
