#include "win32/text_console_geometry.h"
#include "win32/text_console_policy.h"

/* Only an actual visible host window may be shown or geometrically managed.
 * A notification HWND is not a window capability;no class-name policy. */
unsigned char mygames_win32_console_window(HWND window)
{
    RECT rect;
    return (unsigned char)(window && IsWindowVisible(window) &&
        GetWindowRect(window,&rect) && rect.right>rect.left && rect.bottom>rect.top);
}
/* NTVWM's hidden Console carries its captured text grid with a 2x4 font and
 * no usable host window. It accepts the VT mode bit for compatibility but
 * does not expose a terminal RGB presentation surface. This is a measured
 * device capability, not a process, launcher or title classification. */
unsigned char mygames_win32_console_indexed_carrier(struct mygames_win32_text_console *console)
{
    CONSOLE_FONT_INFOEX font;
    if(console->window_usable)return 0U;
    ZeroMemory(&font,sizeof(font));font.cbSize=sizeof(font);
    if(!GetCurrentConsoleFontEx(console->output,FALSE,&font))return 0U;
    return (unsigned char)(font.dwFontSize.X==2 && font.dwFontSize.Y==4);
}
void mygames_win32_console_fit(struct mygames_win32_text_console *console,
    unsigned char initial)
{
    CONSOLE_FONT_INFOEX font;
    CONSOLE_SCREEN_BUFFER_INFO info;
    RECT client;
    COORD maximum;
    unsigned int target=8U;
    /* NTVWM's hidden Console deliberately supplies a 2x4 carrier font so
     * its logical grid can be captured. Changing that invisible carrier
     * makes its viewport temporarily unrepresentable while it is sampled.
     * Font fitting is only meaningful for a visible host HWND. */
    if(!console->window_usable)return;
    console->rows=mygames_win32_console_rows(console->rows);
    if(!initial && console->window_usable && GetClientRect(console->window,&client)) {
        unsigned int x=(unsigned int)(client.right-client.left)/80U;
        unsigned int y=(unsigned int)(client.bottom-client.top)/(console->rows*(console->rows==25U?2U:1U));
        if(x<target)target=x;
        if(y<target)target=y;
        if(target<4U)target=4U;
    }
    ZeroMemory(&font,sizeof(font));font.cbSize=sizeof(font);
    font.FontWeight=FW_NORMAL;lstrcpyW(font.FaceName,L"Consolas");
    for(;;) {
        font.dwFontSize.X=(SHORT)target;font.dwFontSize.Y=(SHORT)(target*(console->rows==25U?2U:1U));
        if(SetCurrentConsoleFontEx(console->output,FALSE,&font))console->font_changed=1U;
        maximum=GetLargestConsoleWindowSize(console->output);
        if((maximum.X>=80 && maximum.Y>=console->rows) || target==4U)break;
        --target;
    }
    ZeroMemory(&console->effective_font,sizeof(console->effective_font));
    console->effective_font.cbSize=sizeof(console->effective_font);
    (void)GetCurrentConsoleFontEx(console->output,FALSE,&console->effective_font);
    if(GetConsoleScreenBufferInfo(console->output,&info)) {
        console->observed_view.X=(SHORT)(info.srWindow.Right-info.srWindow.Left+1);
        console->observed_view.Y=(SHORT)(info.srWindow.Bottom-info.srWindow.Top+1);
    }
    console->fit_changed_at=GetTickCount();
}
/* Probe device operations themselves,not the availability of a host HWND.
 * One optional entry attempt restores the former80x50contract on ConPTY too.
 * Never repeat this sequence per frame on a non-window host. */
unsigned char mygames_win32_console_size(struct mygames_win32_text_console *console,
    COORD size,const SMALL_RECT *view)
{
    SMALL_RECT tiny={0,0,0,0};
    CONSOLE_SCREEN_BUFFER_INFO before,info;
    /* A non-window Console may be a hidden NTVWM carrier or a terminal
     * viewport. Its geometry is host-owned; a temporary 1x1 rectangle is
     * observable to concurrent capture and is therefore not a safe probe. */
    if(!console->window_usable)return 0U;
    if(!GetConsoleScreenBufferInfo(console->output,&before))return 0U;
    {
        unsigned int attempt;
        /* A settled host can race one optional request. Retry once only. */
        for(attempt=0U;attempt<2U;++attempt) {
            if(SetConsoleWindowInfo(console->output,TRUE,&tiny) &&
                SetConsoleScreenBufferSize(console->output,size) &&
                SetConsoleWindowInfo(console->output,TRUE,view) &&
                GetConsoleScreenBufferInfo(console->output,&info) &&
                info.dwSize.X==size.X && info.dwSize.Y==size.Y &&
                info.srWindow.Left==view->Left && info.srWindow.Top==view->Top &&
                info.srWindow.Right==view->Right && info.srWindow.Bottom==view->Bottom) {
                console->observed_view.X=(SHORT)(info.srWindow.Right-info.srWindow.Left+1);
                console->observed_view.Y=(SHORT)(info.srWindow.Bottom-info.srWindow.Top+1);
                return 1U;
            }
            /* Optional partial failure must not leave the temporary1x1view. */
            (void)SetConsoleWindowInfo(console->output,TRUE,&tiny);
            (void)SetConsoleScreenBufferSize(console->output,before.dwSize);
            (void)SetConsoleWindowInfo(console->output,TRUE,&before.srWindow);
        }
    }
    return 0U;
}

/* Resize is an optional geometry operation,never a device-loss signal.
 * Apply font/geometry only after a settled change,not on every video frame. */
int mygames_win32_console_geometry(struct mygames_win32_text_console *console)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    COORD size,visible;
    SMALL_RECT view={0,0,79,49};
    DWORD now=GetTickCount();
    console->rows=mygames_win32_console_rows(console->rows);
    view.Bottom=(SHORT)(console->rows-1U);
    if(!GetConsoleScreenBufferInfo(console->output,&info))return MYGAMES_WIN32_CONSOLE_DEFER;
    if(console->window_usable && IsIconic(console->window))return MYGAMES_WIN32_CONSOLE_DEFER;
    visible.X=(SHORT)(info.srWindow.Right-info.srWindow.Left+1);
    visible.Y=(SHORT)(info.srWindow.Bottom-info.srWindow.Top+1);
    if(visible.X!=console->observed_view.X || visible.Y!=console->observed_view.Y) {
        console->observed_view=visible;console->fit_changed_at=now;
        console->geometry_pending=1U;
    }
    if(console->geometry_pending && now-console->fit_changed_at>=150U) {
        console->geometry_pending=0U;
        mygames_win32_console_fit(console,0U);
        if(console->window_usable && !IsZoomed(console->window)) {
            size.X=80;size.Y=(SHORT)console->rows;
            if(mygames_win32_console_size(console,size,&view))console->geometry_usable=1U;
        }
    }
    return MYGAMES_WIN32_CONSOLE_READY;
}
