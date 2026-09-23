#ifndef MYSMB_GAME_AUDIO_H
#define MYSMB_GAME_AUDIO_H

#include "game/game.h"

/* ROM SoundEngine ($f1-$ff, $07b1-$07c6).  This core preserves the sound
 * command queues and their ownership; an adapter may consume the buffers to
 * produce host audio later. */
void mysmb_audio_step(struct mysmb_game *game);

#endif
