#include "io/snapshot_keys.h"
void mysmb_snapshot_keys_reset(struct mysmb_snapshot_keys *keys)
{
    keys->held=0U;
}
mysmb_io_u8 mysmb_snapshot_keys_transition(struct mysmb_snapshot_keys *keys,
    mysmb_io_u8 request,mysmb_io_u8 pressed,mysmb_io_u8 focused)
{
    mysmb_io_u8 fresh;
    request=(mysmb_io_u8)(request&(MYSMB_IO_REQUEST_SAVE|MYSMB_IO_REQUEST_LOAD));
    if (focused==0U) {keys->held=0U;return 0U;}
    if (pressed==0U) {keys->held=(mysmb_io_u8)(keys->held&~request);return 0U;}
    fresh=(mysmb_io_u8)(request&~keys->held);
    keys->held=(mysmb_io_u8)(keys->held|request);
    return fresh;
}
