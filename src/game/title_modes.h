#ifndef MYSMB_GAME_TITLE_MODES_H
#define MYSMB_GAME_TITLE_MODES_H

/* DrawTitleScreen copies this many bytes into CPU RAM $0300-$0439. */
#define MYSMB_TITLE_BUFFER_SIZE 0x013aU
#define MYSMB_TITLE_ICON_BUFFER_OFFSET 0x0301U

void mysmb_game_draw_mushroom_icon(struct mysmb_game *game);

#endif
