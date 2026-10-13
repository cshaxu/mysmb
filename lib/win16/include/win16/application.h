#ifndef MYGAMES_WIN16_APPLICATION_H
#define MYGAMES_WIN16_APPLICATION_H

#include "kvm/input_event.h"
#include "kvm/video.h"

/* The USER/GDI host implementation owns devices;
 * the app owns every input meaning, view decision and frame producer. */
#define MYGAMES_WIN16_VIEW_GRAPHICS 1U
#define MYGAMES_WIN16_VIEW_TEXT 2U

struct mygames_win16_application {
    void *context;
    const char *title;
    mygames_kvm_u8 available_views;
    void (*input)(void *,const struct mygames_kvm_input_event *);
    void (*tick)(void *);
    mygames_kvm_u8 (*presentation)(void *);
    mygames_kvm_u8 (*exit_requested)(void *);
    const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *(*text)(void *);
    int (*graphics)(void *,struct mygames_kvm_video_band *);
};

/* The graphical runtime entry is declared in win16/host.h. */
#endif
