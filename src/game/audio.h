#ifndef MYSMB_GAME_AUDIO_H
#define MYSMB_GAME_AUDIO_H

#include "game/game.h"

/* ROM SoundEngine ($f1-$ff, $07b1-$07c6).  This core preserves the sound
 * command queues and their ownership; an adapter may consume the buffers to
 * produce host audio later. */
void mysmb_audio_step(struct mysmb_game *game);

/* ROM Dump_Squ1_Regs through SetFreq_Tri. The input bytes are the
 * original A/X/Y values at each entry; all writes stay in shared output. */
void mysmb_audio_dump_squ1_regs(struct mysmb_game *game, mysmb_u8 x,
                                 mysmb_u8 y);
mysmb_u8 mysmb_audio_play_squ1_sfx(struct mysmb_game *game, mysmb_u8 a,
                                mysmb_u8 x, mysmb_u8 y);
mysmb_u8 mysmb_audio_set_freq_squ1(struct mysmb_game *game, mysmb_u8 a);
mysmb_u8 mysmb_audio_dump_freq_regs(struct mysmb_game *game, mysmb_u8 a,
                                 mysmb_u8 x);
void mysmb_audio_dump_sq2_regs(struct mysmb_game *game, mysmb_u8 x,
                                mysmb_u8 y);
mysmb_u8 mysmb_audio_play_sq2_sfx(struct mysmb_game *game, mysmb_u8 a,
                               mysmb_u8 x, mysmb_u8 y);
mysmb_u8 mysmb_audio_set_freq_sq2(struct mysmb_game *game, mysmb_u8 a);
mysmb_u8 mysmb_audio_set_freq_tri(struct mysmb_game *game, mysmb_u8 a);

#endif
