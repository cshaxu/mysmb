#ifndef MYSMB_IO_SNAPSHOT_KEYS_H
#define MYSMB_IO_SNAPSHOT_KEYS_H
#include "io/input.h"
struct mysmb_snapshot_keys {mygames_kvm_u8 held;};
void mysmb_snapshot_keys_reset(struct mysmb_snapshot_keys *keys);
mygames_kvm_u8 mysmb_snapshot_keys_transition(struct mysmb_snapshot_keys *keys,
    mygames_kvm_u8 request,mygames_kvm_u8 pressed,mygames_kvm_u8 focused);
#endif
