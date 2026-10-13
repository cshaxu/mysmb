#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "win32/text_console_policy.h"
#include "win32/text_console_presentation.h"

#define CHECK(value) do { \
    if (!(value)) { \
        printf("failed line %d\n", __LINE__); \
        return 1; \
    } \
} while (0)

int main(void)
{
    size_t compact;
    size_t retained;
    size_t count;
    WCHAR output[256];
    static const WCHAR source_expected[]=L"\x1b[0m\x1b[?25l\x1b[1;1H\x1b[38;2;17;34;51;48;2;68;85;102mA";
    static const WCHAR canonical_expected[]=L"\x1b[0m\x1b[?25l\x1b[1;1H\x1b[38;2;255;255;85;48;2;0;0;170mB";
    static struct mygames_kvm_text_cell frame_cells[4000];
    static unsigned long frame_colors[16];
    static struct mygames_kvm_text_frame frame={frame_cells,80U,50U,80U,4000U,0U,frame_colors};

    CHECK(mygames_win32_console_rows(25U)==25U);
    CHECK(mygames_win32_console_rows(50U)==50U);
    CHECK(mygames_win32_console_rows(0U)==50U);

    compact=mygames_win32_console_vt_capacity(25U);
    retained=mygames_win32_console_vt_capacity(50U);
    CHECK(compact==10U+25U*(8U+80U*48U));
    CHECK(retained==10U+50U*(8U+80U*48U));
    CHECK(compact<retained);

    CHECK(mygames_win32_console_use_vt(0U,1U,1U));
    CHECK(!mygames_win32_console_use_vt(1U,1U,1U));
    CHECK(!mygames_win32_console_use_vt(0U,0U,1U));
    CHECK(!mygames_win32_console_use_vt(0U,1U,0U));

    CHECK(mygames_win32_console_write_result(ERROR_INVALID_HANDLE,1U)==MYGAMES_WIN32_CONSOLE_LOST);
    CHECK(mygames_win32_console_write_result(ERROR_ACCESS_DENIED,1U)==MYGAMES_WIN32_CONSOLE_LOST);
    CHECK(mygames_win32_console_write_result(ERROR_INVALID_PARAMETER,1U)==MYGAMES_WIN32_CONSOLE_DEFER);
    CHECK(mygames_win32_console_write_result(ERROR_NOT_READY,1U)==MYGAMES_WIN32_CONSOLE_DEFER);
    CHECK(mygames_win32_console_write_result(1UL,119U)==MYGAMES_WIN32_CONSOLE_DEFER);
    CHECK(mygames_win32_console_write_result(1UL,120U)==MYGAMES_WIN32_CONSOLE_LOST);

    ZeroMemory(&frame,sizeof(frame));frame.cells=frame_cells;frame.colors=frame_colors;
    frame.columns=frame.stride=80U;frame.capacity=4000U;frame.rows=25U;frame.source_colors=1U;
    frame_colors[1]=0x112233UL;frame_colors[2]=0x445566UL;
    frame_cells[0].character='A';frame_cells[0].foreground=1U;frame_cells[0].background=2U;
    count=mygames_win32_console_vt_encode(&frame,1U,1U,output,256U);
    CHECK(count==wcslen(source_expected));
    CHECK(!memcmp(output,source_expected,count*sizeof(WCHAR)));
    CHECK(mygames_win32_console_vt_encode(&frame,1U,1U,output,count-1U)==0U);
    CHECK(mygames_win32_console_vt_encode(&frame,0U,1U,output,256U)==0U);
    frame.source_colors=0U;frame_cells[0].character='B';frame_cells[0].foreground=14U;frame_cells[0].background=1U;
    count=mygames_win32_console_vt_encode(&frame,1U,1U,output,256U);
    CHECK(count==wcslen(canonical_expected));
    CHECK(!memcmp(output,canonical_expected,count*sizeof(WCHAR)));
    frame_cells[0].character=0x80U;
    CHECK(mygames_win32_console_vt_encode(&frame,1U,1U,output,256U)>0U);
    puts("console policy and VT presentation branches passed");
    return 0;
}
