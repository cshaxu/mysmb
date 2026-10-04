/* Diagnostic composition entry,not linked into the product.
 * Reuse the complete product entry;observe public input/pause contracts only.
 * Bounded transition logging cannot certify the uninstrumented runtime. */
#include "platform/dos16/devices.h"
static void observed_input(struct mysmb_io_input *input);
#define mysmb_dos16_devices_input observed_input
#include "../src/platform/dos16/main_dos16.c"
#undef mysmb_dos16_devices_input

static void observed_input(struct mysmb_io_input *input)
{
    static unsigned count;
    static unsigned char previous[5];
    unsigned char current[5];
    unsigned i;
    int changed;
    FILE *log;
    mysmb_dos16_devices_input(input);
    current[0]=input->buttons;
    current[1]=input->requests;
    current[2]=mysmb_game_is_paused(&root.game);
    current[3]=mysmb_game_pause_input_state(&root.game);
    current[4]=root.text_mode;
    changed=count==0U;
    for(i=0U;i<5U;++i) {
        if(current[i]!=previous[i])changed=1;
        previous[i]=current[i];
    }
    if(!changed || count>=128U)return;
    ++count;
    log=fopen("input.log","a");
    if(!log)return;
    fprintf(log,"frame=%lu buttons=%u requests=%u paused=%u permission=%u text=%u\n",
        root.game.frame_number,(unsigned)current[0],(unsigned)current[1],
        (unsigned)current[2],(unsigned)current[3],(unsigned)current[4]);
    fclose(log);
}
