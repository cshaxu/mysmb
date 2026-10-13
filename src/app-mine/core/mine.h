#ifndef MYGAMES_MINE_CORE_H
#define MYGAMES_MINE_CORE_H

/* Independent rules implementation. Tile constants are presentation IDs,
 * never a packed cell representation or an imported program ABI. */
#define MINE_CAPACITY 600
#define MINE_CLOSED 15
#define MINE_FLAG 14
#define MINE_QUESTION 13
#define MINE_EXPLODED 12
#define MINE_WRONG 11
#define MINE_SHOWN 10
#define MINE_PLAYING 0
#define MINE_WON 1
#define MINE_LOST 2
#define MINE_COVERED 0
#define MINE_OPEN 1
#define MINE_MARKED 2
#define MINE_UNCERTAIN 3

typedef struct Mine {
    unsigned char hazard[MINE_CAPACITY];
    unsigned char cover[MINE_CAPACITY];
    int width,height,mines,flags,opened,state,seconds,started,questions;
    int exploded;
    unsigned long random;
} Mine;

int mine_inside(const Mine *game,int x,int y);
void mine_new(Mine *game,int width,int height,int bombs,unsigned long seed);
void mine_mark(Mine *game,int x,int y);
void mine_reveal(Mine *game,int x,int y);
void mine_chord(Mine *game,int x,int y);
void mine_second(Mine *game);
int mine_count_bombs(const Mine *game,int x,int y);
int mine_sprite(const Mine *game,int x,int y);
#endif
