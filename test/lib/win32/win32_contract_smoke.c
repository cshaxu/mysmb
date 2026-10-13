#include "win32/frame_wait.h"
#include "win32/launch.h"
#include "win32/text_console_policy.h"

int main(void)
{
    if (mygames_win32_frame_wait_timeout(600, 60) != 1000U) return 1;
    if (mygames_win32_console_rows(25U) != 25U) return 2;
    if (mygames_win32_console_rows(80U) != 50U) return 3;
    /* Parent-console probing is a host query: this test asserts only that it
     * is callable, never that a specific launcher owns a console. */
    (void)mygames_win32_parent_console_available();
    return 0;
}
