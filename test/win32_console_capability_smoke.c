#include <stdio.h>
#include "platform/win32/text_console_policy.h"

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

    CHECK(mysmb_win32_console_rows(25U)==25U);
    CHECK(mysmb_win32_console_rows(50U)==50U);
    CHECK(mysmb_win32_console_rows(0U)==50U);

    compact=mysmb_win32_console_vt_capacity(25U);
    retained=mysmb_win32_console_vt_capacity(50U);
    CHECK(compact==10U+25U*(8U+80U*48U));
    CHECK(retained==10U+50U*(8U+80U*48U));
    CHECK(compact<retained);

    CHECK(mysmb_win32_console_use_vt(0U,1U,1U));
    CHECK(!mysmb_win32_console_use_vt(1U,1U,1U));
    CHECK(!mysmb_win32_console_use_vt(0U,0U,1U));
    CHECK(!mysmb_win32_console_use_vt(0U,1U,0U));
    puts("console policy: rows, bounded VT capacity and carrier fallback passed");
    return 0;
}
