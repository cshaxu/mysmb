#ifndef MYSMB_APP_GAME_SNAPSHOT_H
#define MYSMB_APP_GAME_SNAPSHOT_H
#include "core/game.h"
#include "io/snapshot.h"
void mysmb_game_snapshot_fingerprint(const struct mysmb_game *game,
    mysmb_io_u8 *fingerprint);
int mysmb_game_snapshot_capture(const struct mysmb_game *game,
    struct mysmb_io_snapshot *snapshot,const mysmb_io_u8 *fingerprint);
int mysmb_game_snapshot_restore(struct mysmb_game *game,
    const struct mysmb_io_snapshot *snapshot);
int mysmb_game_snapshot_valid(const struct mysmb_game *game,
    const struct mysmb_io_snapshot *snapshot);
mysmb_io_u8 mysmb_game_snapshot_running(const struct mysmb_game *game,
    const struct mysmb_frame *frame);
/* A paused gameplay boundary is also a valid current-state snapshot. */
mysmb_io_u8 mysmb_game_snapshot_available(const struct mysmb_game *game,
    const struct mysmb_frame *frame);
void mysmb_game_snapshot_resume_frame(const struct mysmb_game *game,struct mysmb_frame *frame);
#endif
