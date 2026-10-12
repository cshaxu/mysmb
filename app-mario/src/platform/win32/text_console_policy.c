#include "platform/win32/text_console_policy.h"

unsigned short mysmb_win32_console_rows(unsigned short rows)
{
    return rows==25U?25U:50U;
}

size_t mysmb_win32_console_vt_capacity(unsigned short rows)
{
    /* Reset plus one cursor sequence per row and a conservative 48 WCHAR
     * colour/glyph bound per visible cell. */
    return 10U+(size_t)mysmb_win32_console_rows(rows)*(8U+80U*48U);
}

unsigned char mysmb_win32_console_use_vt(unsigned char indexed_carrier,
    unsigned char output_mode_read,unsigned char output_mode_set)
{
    return (unsigned char)(!indexed_carrier && output_mode_read && output_mode_set);
}

int mysmb_win32_console_write_result(DWORD error,unsigned short failures)
{
    if(error==ERROR_INVALID_HANDLE || error==ERROR_ACCESS_DENIED)
        return MYSMB_WIN32_CONSOLE_LOST;
    if(error==ERROR_INVALID_PARAMETER || error==ERROR_NOT_READY)
        return MYSMB_WIN32_CONSOLE_DEFER;
    return failures>=120U?MYSMB_WIN32_CONSOLE_LOST:MYSMB_WIN32_CONSOLE_DEFER;
}
