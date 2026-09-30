#ifndef MYSMB_GAME_AUDIO_H
#define MYSMB_GAME_AUDIO_H

#include "game/game.h"

/* ROM SoundEngine ($f1-$ff, $07b1-$07c6).  This core preserves the sound
 * command queues and their ownership; an adapter may consume the buffers to
 * produce host audio later. */
void mysmb_audio_step(struct mysmb_game *game);

/* ROM MusicHandler's queue-selection prefix ($f694-$f733).  This leaves the
 * game at the HandleSquare2Music entry state; SoundEngine then continues the
 * channel handlers through mysmb_audio_step(). */
void mysmb_audio_select_music(struct mysmb_game *game);

/* ROM LoadHeader ($f6f5).  The selector is the source Y value after the
 * event/area bit scan or ground-layout loop.  The header bytes are always
 * read through the owner-local PRG binding. */
mysmb_u8 mysmb_audio_load_music_header(struct mysmb_game *game,
                                       mysmb_u8 selector);

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

/* ROM square-one effect phases before Square1SfxHandler's S4 dispatch and
 * decrement tail.  A nonzero selector chooses the indicated start phase. */
void mysmb_audio_square1_play_flagpole(struct mysmb_game *game);
void mysmb_audio_square1_play_jump(struct mysmb_game *game, mysmb_u8 small);
void mysmb_audio_square1_continue_jump(struct mysmb_game *game);
void mysmb_audio_square1_play_throw(struct mysmb_game *game,
                                     mysmb_u8 fireball);
void mysmb_audio_square1_continue_throw(struct mysmb_game *game);
mysmb_u8 mysmb_audio_swim_stomp_envelope(const struct mysmb_game *game,
                                          mysmb_u8 length);

/* ROM square-two S5 table bindings; table bytes stay in the owner ROM. */
mysmb_u8 mysmb_audio_square2_extra_life_freq(const struct mysmb_game *game,
                                               mysmb_u8 index);
mysmb_u8 mysmb_audio_square2_power_up_freq(const struct mysmb_game *game,
                                            mysmb_u8 index);
mysmb_u8 mysmb_audio_square2_grow_vine_freq(const struct mysmb_game *game,
                                             mysmb_u8 index);

#endif
