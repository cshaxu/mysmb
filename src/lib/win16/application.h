#ifndef MYGAMES_WIN16_APPLICATION_H
#define MYGAMES_WIN16_APPLICATION_H

#include "kvm/input_event.h"
#include "kvm/video.h"

/* The USER/GDI host implementation owns devices;
 * the app owns every input meaning, view decision and frame producer. */
#define MYGAMES_WIN16_VIEW_GRAPHICS 1U
#define MYGAMES_WIN16_VIEW_TEXT 2U

/* update runs after input or a requested wake. dirty requests composition;
 * wake_ms is a one-shot delay (0 means wait for input indefinitely).
 * Host paint never calls update or graphics. Timers may wake later than asked. */
struct mygames_win16_update {mygames_kvm_u16 wake_ms;mygames_kvm_u8 dirty;};
/* Two-level menus: contents/IDs and mutable checked/enabled state belong to
 * the app. A null item label denotes a separator; command0 is not delivered. */
struct mygames_win16_menu_item {const char *label;mygames_kvm_u16 command;mygames_kvm_u8 checked,disabled;};
struct mygames_win16_menu {const char *label;const struct mygames_win16_menu_item *items;mygames_kvm_u16 count;};
struct mygames_win16_application {
    void *context;
    const char *title;
    mygames_kvm_u8 available_views;
    void (*input)(void *,const struct mygames_kvm_input_event *);
    void (*update)(void *,unsigned long,struct mygames_win16_update *);
    mygames_kvm_u8 (*presentation)(void *);
    mygames_kvm_u8 (*exit_requested)(void *);
    const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *(*text)(void *);
    int (*graphics)(void *,struct mygames_kvm_video_band *);
    /* Geometry/palette can change during update; set dirty to publish them.
     * Menu labels/counts remain fixed during run; flags may change in update. */
    const unsigned long MYGAMES_KVM_FAR *palette;
    mygames_kvm_u16 palette_count;
    mygames_kvm_u16 width,height;
    const struct mygames_win16_menu *menus;
    mygames_kvm_u16 menu_count;
};

/* The graphical runtime entry is declared in win16/host.h. */
#endif
