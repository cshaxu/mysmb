#ifndef MYSMB_PLATFORM_DOS16_ROOT_H
#define MYSMB_PLATFORM_DOS16_ROOT_H
#include "app/game_io.h"
#include "io/control.h"
#include "app/game_snapshot.h"
#include "io/snapshot_store.h"
#include "text/scene.h"
/* Composition root: device consumers receive only neutral IO views. */
struct mysmb_dos16_hooks {
    void *context;
    void (*read_input)(void *context, struct mysmb_io_input *input);
    void (*present_video)(void *context, const struct mysmb_io_video_frame *frame);
    mysmb_io_u8 (*submit_audio)(void *context, const struct mysmb_io_audio_frame *frame);
};
struct mysmb_dos16_root {
    struct mysmb_io_control control;
    struct mysmb_game game;
    struct mysmb_frame game_frame;
    struct mysmb_ppu_frame ppu_frame;
    struct mysmb_ppu_frame_workspace ppu_workspace;
    struct mysmb_ppu_frame_view ppu_view;
    struct mysmb_io_palette_pairs *ppu_pairs;
    mysmb_io_u8 ppu_cache_attempted;
    mysmb_io_u8 ppu_cache_near;
    struct mysmb_dos16_hooks hooks;
    struct mysmb_io_audio_frame audio_frame;
    mysmb_io_u8 audio_available;
    mysmb_io_u8 initialized;
    struct mysmb_snapshot_store *snapshot_store;
    mysmb_io_u8 snapshot_fingerprint[16];
    void (*reset_output)(void *context);
    void *reset_context;
    void (*resume_clock)(void *);
    struct mysmb_text_scene_workspace MYSMB_IO_FAR *text_workspace;
    struct mysmb_io_text_frame MYSMB_IO_FAR *text_frame;
    int (*set_mode)(void *,mysmb_io_u8);
    void (*present_text)(void *,const struct mysmb_io_text_frame MYSMB_IO_FAR *);
    mysmb_io_u8 text_mode;
    mysmb_io_u16 video_storage_bytes;
    int (*present_rows)(void *,const struct mysmb_io_video_source *);
    int (*present_palette_rows)(void *,const struct mysmb_io_palette_video_source *);
    int (*present_retained)(void *,const struct mysmb_ppu_frame_view *,
        const mysmb_io_u8 MYSMB_IO_FAR *);
    mysmb_io_u8 video_palette[MYSMB_IO_VIDEO_PALETTE_COLORS];
};
int mysmb_dos16_root_initialize(struct mysmb_dos16_root *root,
                                const struct mysmb_dos16_hooks *hooks);
/* Explicit opt-in;legacy hook layout/full-frame initialization stay valid.
 * storage_bytes must also fit any text view bound by the composition owner. */
int mysmb_dos16_root_initialize_rows(struct mysmb_dos16_root *root,
    const struct mysmb_dos16_hooks *hooks,mysmb_io_u16 storage_bytes,
    int (*present_rows)(void *,const struct mysmb_io_video_source *));
int mysmb_dos16_root_initialize_palette_rows(struct mysmb_dos16_root *root,
    const struct mysmb_dos16_hooks *hooks,mysmb_io_u16 storage_bytes,
    int (*present)(void *,const struct mysmb_io_palette_video_source *));
/* Optional DOS-only physical presenter. It receives a neutral PPU view and
 * palette only; returning false selects the normal neutral row presenter. */
void mysmb_dos16_root_bind_retained(struct mysmb_dos16_root *root,
    int (*present)(void *,const struct mysmb_ppu_frame_view *,
        const mysmb_io_u8 MYSMB_IO_FAR *));
void mysmb_dos16_root_step(struct mysmb_dos16_root *root);
void mysmb_dos16_root_bind_clock(struct mysmb_dos16_root *root,void (*resume)(void *));
void mysmb_dos16_root_shutdown(struct mysmb_dos16_root *root);
void mysmb_dos16_root_bind_snapshot(struct mysmb_dos16_root *root,
    struct mysmb_snapshot_store *store,void (*reset_output)(void *),void *context);
void mysmb_dos16_root_bind_text(struct mysmb_dos16_root *root,
    struct mysmb_text_scene_workspace MYSMB_IO_FAR *workspace,
    struct mysmb_io_text_frame MYSMB_IO_FAR *frame,
    int (*set_mode)(void *,mysmb_io_u8),
    void (*present_text)(void *,const struct mysmb_io_text_frame MYSMB_IO_FAR *));
#endif
