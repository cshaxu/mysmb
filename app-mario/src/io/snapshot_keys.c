#include "io/snapshot_keys.h"
void mysmb_snapshot_keys_reset(struct mysmb_snapshot_keys *keys)
{
    keys->held=0U;
}
mygames_kvm_u8 mysmb_snapshot_keys_transition(struct mysmb_snapshot_keys *keys,
    mygames_kvm_u8 request,mygames_kvm_u8 pressed,mygames_kvm_u8 focused)
{
    mygames_kvm_u8 fresh;
    request=(mygames_kvm_u8)(request&(MYSMB_IO_REQUEST_SAVE|MYSMB_IO_REQUEST_LOAD));
    if (focused==0U) {keys->held=0U;return 0U;}
    if (pressed==0U) {keys->held=(mygames_kvm_u8)(keys->held&~request);return 0U;}
    fresh=(mygames_kvm_u8)(request&~keys->held);
    keys->held=(mygames_kvm_u8)(keys->held|request);
    return fresh;
}
