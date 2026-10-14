#ifndef MYGAMES_WIN16_HOST_H
#define MYGAMES_WIN16_HOST_H
#include <windows.h>
#include "win16/application.h"
/* Called by the app during update, before menu-dependent window sizing.
 * Detach/reattach the host-owned menu without destroying its contents.
 * Returns zero on failure; clients without a menu need no operation. */
int mygames_win16_menu_visible(HWND window,int visible);
/* Optional lifecycle extension leaves existing clients' ABI unchanged.
 * started follows initial paint. close: 1=allow,0=pending,-1=cancel.
 * Host errors supply a nonzero reason; no device policy lives in this host. */
struct mygames_win16_lifecycle {
    void (*started)(void *);
    int (*close)(void *,int reason);
};
int mygames_win16_run_lifecycle(HINSTANCE instance,HINSTANCE previous,int show,
    const struct mygames_win16_application *application,
    const struct mygames_win16_lifecycle *lifecycle);
int mygames_win16_run(HINSTANCE instance,HINSTANCE previous,int show,
    const struct mygames_win16_application *application);
#endif
