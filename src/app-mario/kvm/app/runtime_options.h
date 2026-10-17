#ifndef MYSMB_APP_RUNTIME_OPTIONS_H
#define MYSMB_APP_RUNTIME_OPTIONS_H
/* Return 0 for normal, 1 for --turbo, -1 for an invalid command tail. */
int mysmb_app_runtime_options(const char *tail);
#endif
