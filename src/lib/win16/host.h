#ifndef MYGAMES_WIN16_HOST_H
#define MYGAMES_WIN16_HOST_H
#include <windows.h>
#include "win16/application.h"
/* Rebase host time after a synchronous app-owned file transaction. */
void mygames_win16_rebase_clock(void);
int mygames_win16_run(HINSTANCE instance,HINSTANCE previous,int show,
    const struct mygames_win16_application *application);
#endif
