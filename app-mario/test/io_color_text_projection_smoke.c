#include <stdio.h>
#include "io/color.h"

#define CHECK(value) do {if(!(value)){printf("failed line %d\n",__LINE__);return 1;}}while(0)

int main(void)
{
    unsigned long colors[16];
    mysmb_io_u8 attributes[16];
    unsigned short i;

    for(i=0U;i<16U;++i)colors[i]=mysmb_io_color_text_rgb((mysmb_io_u8)i);
    mysmb_io_color_text_attributes(colors,0U,attributes);
    for(i=0U;i<16U;++i)CHECK(attributes[i]==(mysmb_io_u8)i);

    colors[0]=0x001e74UL;colors[1]=0xecb4b0UL;
    colors[2]=0x4cd020UL;colors[3]=0xe454ecUL;
    mysmb_io_color_text_attributes(colors,1U,attributes);
    for(i=0U;i<16U;++i)
        CHECK(attributes[i]==mysmb_io_color_text_nearest(colors[i]));
    puts("text colour projection: canonical and source palettes passed");
    return 0;
}
