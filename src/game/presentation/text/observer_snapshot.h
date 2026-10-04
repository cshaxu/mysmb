#ifndef MYSMB_TEXT_OBSERVER_SNAPSHOT_H
#define MYSMB_TEXT_OBSERVER_SNAPSHOT_H

/* Explicit wire bytes, not a native struct image or immutable resource data. */
#define MYSMB_TEXT_OBSERVER_SNAPSHOT_BYTES 5253U
struct mysmb_game;
int mysmb_text_observer_snapshot_valid(const unsigned char *bytes);
int mysmb_text_observer_snapshot_capture(const struct mysmb_game *game,
    unsigned char *bytes);
/* Caller validates before restoring any original program state. */
void mysmb_text_observer_snapshot_restore(struct mysmb_game *game,
    const unsigned char *bytes);
#endif
