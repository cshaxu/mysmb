#ifndef MYSMB_GAME_TEXT_OBSERVATION_H
#define MYSMB_GAME_TEXT_OBSERVATION_H

/* Source-decision receipts, independent of IO, templates and host devices. */
#define MYSMB_TEXT_OBSERVATION_CAPACITY 64U
#define MYSMB_TEXT_OBSERVE_PLAYER 1U
#define MYSMB_TEXT_OBSERVE_ENEMY 2U
#define MYSMB_TEXT_OBSERVE_POWERUP 3U
#define MYSMB_TEXT_OBSERVE_FIREBALL 4U
#define MYSMB_TEXT_OBSERVE_FIREBAR 5U
#define MYSMB_TEXT_OBSERVE_EXPLOSION 6U
#define MYSMB_TEXT_OBSERVE_HAMMER 7U
#define MYSMB_TEXT_OBSERVE_BLOCK 8U
#define MYSMB_TEXT_OBSERVE_CHUNKS 9U
#define MYSMB_TEXT_OBSERVE_VINE 10U
#define MYSMB_TEXT_OBSERVE_PLATFORM 11U
#define MYSMB_TEXT_OBSERVE_FLAG 12U
#define MYSMB_TEXT_OBSERVE_BUBBLE 13U
#define MYSMB_TEXT_OBSERVE_FLAME 14U
#define MYSMB_TEXT_OBSERVE_COIN 15U
#define MYSMB_TEXT_OBSERVE_SCORE 16U
#define MYSMB_TEXT_PLAYER_DEATH_FLAG 0x80U
#define MYSMB_TEXT_PLAYER_THROW_FLAG 0x40U
#define MYSMB_TEXT_PLAYER_KICK_FLAG 0x20U
#define MYSMB_TEXT_PLAYER_MIXED_FLAG 0x10U

struct mysmb_text_observation {
    unsigned char family;
    unsigned char identity;
    unsigned char slot; /* Player receipts: source-selected pre-throw graphics. */
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
