#ifndef MYSMB_GAME_TEXT_OBSERVATION_H
#define MYSMB_GAME_TEXT_OBSERVATION_H

/* Source-decision receipts, independent of IO, templates and host devices. */
#define MYSMB_TEXT_OBSERVATION_CAPACITY 16U
#define MYSMB_TEXT_OBSERVE_PLAYER 1U
#define MYSMB_TEXT_OBSERVE_ENEMY 2U
#define MYSMB_TEXT_OBSERVE_POWERUP 3U

struct mysmb_text_observation {
    unsigned char family;
    unsigned char identity;
    unsigned char slot;
    unsigned char graphics;
    unsigned char facing;
    unsigned char oam;
    unsigned char sprites;
    unsigned char source_size;
    /* Completed draw entries, including clipping and attribute overrides. */
    unsigned char entries[32];
};

struct mysmb_text_observation_buffer {
    unsigned char count;
    unsigned char overflow;
    unsigned char owners[64];
    struct mysmb_text_observation items[MYSMB_TEXT_OBSERVATION_CAPACITY];
};

struct mysmb_text_observer {
    unsigned char enabled;
    struct mysmb_text_observation_buffer producer;
    struct mysmb_text_observation_buffer visible;
};

struct mysmb_game;
void mysmb_text_observer_enable(struct mysmb_game *game, unsigned char enabled);
void mysmb_text_observer_invalidate(struct mysmb_game *game);
void mysmb_text_observer_clear_producer(struct mysmb_game *game);
void mysmb_text_observer_commit(struct mysmb_game *game);
void mysmb_text_observer_record(struct mysmb_game *game,
    unsigned char family, unsigned char identity, unsigned char slot,
    unsigned char graphics, unsigned char facing, unsigned char oam,
    unsigned char sprites, unsigned char source_size);
/* Mask bits follow the source's OAM entry order. Unmatched/blank/hidden
 * entries are excluded; callers must not replace these with live RAM. */
unsigned char mysmb_text_observer_visible_mask(const struct mysmb_game *game,
    unsigned char index);

#endif
