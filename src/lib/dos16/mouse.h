#ifndef MYGAMES_DOS16_MOUSE_H
#define MYGAMES_DOS16_MOUSE_H
#include "kvm/pointer.h"
struct mygames_dos16_mouse_registers {unsigned short ax,bx,cx,dx;};
struct mygames_dos16_mouse_bus {
    int (*present)(void *);
    void (*call)(void *,struct mygames_dos16_mouse_registers *,void MYGAMES_KVM_FAR *);
};
struct mygames_dos16_mouse {
    const struct mygames_dos16_mouse_bus *bus;
    void *context;
    void MYGAMES_KVM_FAR *saved;
    struct mygames_kvm_pointer pointer;
    struct mygames_kvm_input_event events[MYGAMES_KVM_POINTER_EVENTS];
    unsigned short bytes,max_x,max_y,div_x,div_y,pending,count;
    unsigned char opened,visible,space,configured;
};
/* Query/save never reset the caller's driver. Unsupported save-state or absent
 * drivers return0. Zero-initialize the owner before open. Caller storage stays
 * valid until close restores it; configure range before position/poll. */
unsigned short mygames_dos16_mouse_storage(const struct mygames_dos16_mouse_bus *bus,void *context);
int mygames_dos16_mouse_open(struct mygames_dos16_mouse *mouse,
    const struct mygames_dos16_mouse_bus *bus,void *context,
    void MYGAMES_KVM_FAR *saved,unsigned short capacity);
int mygames_dos16_mouse_range(struct mygames_dos16_mouse *mouse,
    unsigned short max_x,unsigned short max_y,unsigned short div_x,unsigned short div_y,
    unsigned char coordinate_space);
void mygames_dos16_mouse_visible(struct mygames_dos16_mouse *mouse,unsigned char visible);
int mygames_dos16_mouse_position(struct mygames_dos16_mouse *mouse,unsigned short x,unsigned short y);
int mygames_dos16_mouse_poll(struct mygames_dos16_mouse *mouse,struct mygames_kvm_input_event *event);
void mygames_dos16_mouse_close(struct mygames_dos16_mouse *mouse);
extern const struct mygames_dos16_mouse_bus mygames_dos16_mouse_native_bus;
#endif
