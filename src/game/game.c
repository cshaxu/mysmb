#include "game/game.h"

struct mysmb_game {
    unsigned char reserved;
};

void mysmb_game_initialize(mysmb_game *game)
{
    game->reserved = 0u;
}
