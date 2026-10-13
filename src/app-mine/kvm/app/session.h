#ifndef MINE_SESSION_H
#define MINE_SESSION_H
#include "app.h"
#include "kvm/input_event.h"
#include "kvm/video.h"
typedef struct MineSession {
    MineApp app;
    unsigned char text_mode,clock_ready,tab_down;
    unsigned long last_second;
    struct mygames_kvm_text_cell cells[2000];
    struct mygames_kvm_text_frame text;
} MineSession;
void mine_session_init(MineSession *session,unsigned long seed,int text_mode);
void mine_session_event(MineSession *session,const struct mygames_kvm_input_event *event);
void mine_session_update(MineSession *session,unsigned long now);
const struct mygames_kvm_text_frame *mine_session_text(MineSession *session);
#endif
