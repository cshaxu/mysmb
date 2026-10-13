#include <string.h>

#include "dos16/raw_keyboard.h"
#include "dos16/text_cells.h"

int main(void)
{
    struct mygames_dos16_set1_keyboard keyboard;
    struct mygames_dos16_key_transition transition;
    static struct mygames_kvm_text_cell frame_cells[4000];
    static unsigned long frame_colors[16];
    static struct mygames_kvm_text_frame frame={frame_cells,80U,50U,80U,4000U,0U,frame_colors};
    mygames_kvm_u16 cells[4000U+1U];
    unsigned short i;
    mygames_dos16_set1_keyboard_initialize(&keyboard);
    if(mygames_dos16_set1_keyboard_scan(&keyboard,0xe0U,&transition)!=0)return 1;
    if(!mygames_dos16_set1_keyboard_scan(&keyboard,0x4bU,&transition) ||
        !transition.extended || !transition.down || transition.repeat)return 2;
    if(mygames_dos16_set1_keyboard_scan(&keyboard,0xe0U,&transition)!=0 ||
        !mygames_dos16_set1_keyboard_scan(&keyboard,0xcbU,&transition) ||
        !transition.extended || transition.down)return 3;
    if(mygames_dos16_set1_keyboard_scan(&keyboard,0xe1U,&transition)!=0 ||
        mygames_dos16_set1_keyboard_scan(&keyboard,0x1dU,&transition)!=0)return 4;
    for(i=0U;i<4U;++i)
        if(mygames_dos16_set1_keyboard_scan(&keyboard,0x45U,&transition))return 8;
    if(!mygames_dos16_set1_keyboard_scan(&keyboard,0x1eU,&transition) ||
        transition.extended || transition.repeat || !keyboard.down[0x1eU])return 9;
    if(!mygames_dos16_set1_keyboard_scan(&keyboard,0x1eU,&transition) ||
        !transition.repeat)return 10;
    if(!mygames_dos16_set1_keyboard_scan(&keyboard,0x9eU,&transition) ||
        transition.down || transition.repeat || keyboard.down[0x1eU])return 11;
    memset(&frame,0,sizeof(frame));frame.cells=frame_cells;frame.colors=frame_colors;
    frame.columns=frame.stride=80U;frame.capacity=4000U;
    frame.rows=25U;frame_cells[0].character='A';frame_cells[0].foreground=15U;
    frame_cells[0].background=1U;frame_colors[15U]=0xffffffUL;frame_colors[1U]=0x0000aaUL;
    frame.source_colors=1U;
    cells[2000U]=0x1234U;
    mygames_dos16_text_cells(&frame,cells);
    if(cells[0]!=0x1f41U || cells[2000U]!=0x1234U)return 6;
    frame.rows=50U;
    frame.source_colors=0U;
    frame_cells[3999U].character='Z';
    frame_cells[3999U].foreground=4U;
    frame_cells[3999U].background=2U;
    cells[4000U]=0x5678U;
    mygames_dos16_text_cells(&frame,cells);
    if(cells[3999U]!=0x245aU || cells[4000U]!=0x5678U)return 7;
    mygames_dos16_text_cells(0,cells);
    mygames_dos16_text_cells(&frame,0);
    if(cells[4000U]!=0x5678U)return 12;
    return 0;
}
