#ifndef MYGAMES_WIN16_HOST_H
#define MYGAMES_WIN16_HOST_H
#include <windows.h>
#include "win16/application.h"
int mygames_win16_run(HINSTANCE instance,HINSTANCE previous,int show,
    const struct mygames_win16_application *application);
#endif
