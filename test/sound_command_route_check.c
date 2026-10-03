#include "game/audio.h"
#include "game/blocks/head.h"
#include "game/blocks/chunks.h"
#include "game/enemy/core.h"
#include "game/enemy/loop.h"
#include "game/enemy/stream.h"
#include "game/enemy/init.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/dispatcher.h"
#include "game/status.h"
#include "game/score.h"
#include "game/frame_root.h"
#include "game/area.h"
#include "game/player.h"
#include "game/terminal_modes.h"
#include "game/fireball/fireball.h"
#include <stdio.h>
#include <string.h>
#define RECORD_BYTES 4290U
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768],record[RECORD_BYTES];
    static unsigned int ram_failures[2048];
    struct mysmb_area_source source;
    unsigned char h[16];FILE *f;unsigned int count,n,i,pc,failures=0U;mysmb_u8 a;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(!f||fread(h,1U,16U,f)!=16U||memcmp(h,"NES\032",4U)||h[4]!=2U||fread(prg,1U,32768U,f)!=32768U)return 65;fclose(f);
    f=fopen(argv[1],"rb");if(!f||fread(h,1U,16U,f)!=16U||memcmp(h,"MSCM\1",5U))return 65;
    count=h[8]|((unsigned int)h[9]<<8U);if(!count||count>1024U)return 66;
    for(n=0U;n<count;++n){
        if(fread(record,1U,sizeof(record),f)!=sizeof(record))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+16U,2048U);memcpy(game.apu_registers,record+2064U,24U);
        game.area_prg=prg;game.area_prg_size=32768U;source.prg=prg;source.prg_size=32768U;
        /* These bootstrap bindings are presence-only preconditions here.
         * InitializeGame does not read title/icon bytes; all actual data
         * reads use the unchanged full owner PRG above. */
        game.title_data=prg;game.title_data_size=0x013aU;
        game.title_icon_data=prg;game.title_icon_data_size=1U;
        a=record[2];pc=record[0]|((unsigned int)record[1]<<8U);
        switch(pc){
        case 0xc385U:mysmb_enemy_init_lakitu(&game,record[3]);break;
        case 0xc3a4U:mysmb_enemy_init_lakitu_spiny_frenzy(&game,record[3]);break;
        case 0xc459U:mysmb_enemy_init_firebar_entry(&game,record[3],1U);break;
        case 0xc45cU:mysmb_enemy_init_firebar_entry(&game,record[3],0U);break;
        case 0xc4a8U:mysmb_enemy_init_flying_cheep_frenzy(&game,record[3]);break;
        case 0xc9b0U:mysmb_objects_step_podoboos_slot(&game,record[3]);break;
        case 0xc34aU:mysmb_enemy_init_red_ptroopa(&game,record[3]);break;
        case 0xc375U:mysmb_enemy_init_cheep_cheep(&game,record[3]);break;
        case 0xc26cU:mysmb_enemy_checkpoint_loaded(&game,record[3]);break;
        case 0xc047U:mysmb_enemy_core_step_slot(&game,&source,record[3]);break;
        case 0xc0ccU:mysmb_enemy_process_loop_command(&game,&source,record[3]);break;
        case 0xc144U:(void)mysmb_enemy_stream_process_current(&game,&source,record[3]);break;
        case 0xbe02U:mysmb_blocks_shatter(&game,record[3]);break;
        case 0xbe41U:mysmb_blocks_spawn_chunks(&game,record[3]);break;
        case 0xbc85U:mysmb_objects_step_power_up(&game);break;
        case 0xbcedU:mysmb_blocks_head_collision(&game,record[2]);break;
        case 0xbe70U:mysmb_objects_step_block(&game,record[3]);break;
        case 0xbed4U:mysmb_area_apply_block_replacements(&game);break;
        case 0xbf4dU:mysmb_player_move_vertically(&game);break;
        case 0xbac3U:mysmb_objects_step_hammer(&game,record[3]);break;
        case 0xbb96U:mysmb_objects_step_misc(&game);break;
        case 0xbb38U:mysmb_objects_coin_block(&game,record[3],record[7]);break;
        case 0xbb51U:mysmb_objects_setup_jump_coin(&game,record[3]);break;
        case 0xbbfeU:mysmb_objects_give_one_coin(&game);break;
        case 0xbc27U:(void)mysmb_score_add(&game);break;
        case 0xb94bU:mysmb_objects_step_vine(&game,record[3]);break;
        case 0xba33U:mysmb_game_handle_cannon_bullet(&game,record[3]);break;
        case 0xb9bcU:mysmb_game_process_cannons(&game);break;
        case 0xb689U:mysmb_fireball_step_object(&game,record[3]);break;
        case 0xb6f9U:mysmb_fireball_check_bubble(&game,record[3]);break;
        case 0xb70bU:mysmb_fireball_setup_bubble(&game,record[3]);break;
        case 0xb450U:mysmb_player_physics_sub(&game);break;
        case 0xb3cfU:mysmb_player_climb(&game);break;
        case 0xb58fU:mysmb_player_update_animation_speed(&game,game.ram[0x06fcU]);break;
        case 0x9508U:(void)mysmb_area_process_object_state(&game);break;
        case 0x8808U:(void)mysmb_area_queue_game_text(&game,a);break;
        case 0x91cdU:mysmb_game_lose_life(&game);break;
        case 0x9218U:mysmb_game_step_game_over(&game);break;
        case 0x9131U:mysmb_player_initialize_entrance(&game);break;
        case 0x90edU:mysmb_game_get_area_music(&game);break;
        case 0x90ccU:mysmb_game_initialize_memory(&game,record[4]);break;
        case 0x9071U:mysmb_game_secondary_setup(&game);break;
        case 0x9061U:mysmb_game_primary_setup(&game);break;
        case 0x8fe4U:mysmb_area_initialize(&game);break;
        case 0x8fcfU:(void)mysmb_game_begin_title_bootstrap(&game);break;
        case 0x8f06U:(void)mysmb_status_print_numbers(&game,a);break;
        case 0x8f5fU:mysmb_status_apply_digit_modifier(&game,record[4]);break;
        case 0x8f97U:mysmb_frame_root_update_top_score(&game);break;
        case 0xf2d0U:mysmb_audio_step(&game);break;
        case 0xf6f5U:(void)mysmb_audio_load_music_header(&game,record[4]);break;
        case 0xf8cbU:a=mysmb_audio_process_music_length(&game,a);break;
        case 0xf8f4U:a=mysmb_audio_load_music_envelope(&game,record[4]);break;
        case 0xf381U:mysmb_audio_dump_squ1_regs(&game,record[3],record[4]);break;
        case 0xf388U:a=mysmb_audio_play_squ1_sfx(&game,a,record[3],record[4]);break;
        case 0xf38bU:a=mysmb_audio_set_freq_squ1(&game,a);break;
        case 0xf38dU:a=mysmb_audio_dump_freq_regs(&game,a,record[3]);break;
        case 0xf39eU:break;
        case 0xf39fU:mysmb_audio_dump_sq2_regs(&game,record[3],record[4]);break;
        case 0xf3a6U:a=mysmb_audio_play_sq2_sfx(&game,a,record[3],record[4]);break;
        case 0xf3a9U:a=mysmb_audio_set_freq_sq2(&game,a);break;
        case 0xf3adU:a=mysmb_audio_set_freq_tri(&game,a);break;
        default:return 66;
        }
        if(record[8]) {
            if(pc==0xbe41U)mysmb_objects_step_block(&game,record[3]);
            else if(pc==0xbe02U||pc==0xbe70U)mysmb_area_apply_block_replacements(&game);
            else if(record[8]==2U&&pc==0xc34aU)mysmb_objects_step_red_paratroopas_slot(&game,record[3]);
            else if(record[8]==2U&&pc==0xc375U)mysmb_objects_step_swimming_cheep_cheeps_slot(&game,record[3]);
            else return 66;
        }
        if(pc!=0xf2d0U&&pc!=0xf6f5U&&pc!=0x8f06U&&pc!=0x8f5fU&&pc!=0x8f97U&&pc!=0x90ccU&&pc!=0x9071U&&pc!=0x9061U&&pc!=0x8fe4U&&pc!=0x8fcfU&&pc!=0x90edU&&pc!=0x9131U&&pc!=0x91cdU&&pc!=0x9218U&&pc!=0x8808U&&pc!=0x9508U&&pc!=0xb450U&&pc!=0xb3cfU&&pc!=0xb58fU&&pc!=0xb689U&&pc!=0xb6f9U&&pc!=0xb70bU&&pc!=0xb94bU&&pc!=0xba33U&&pc!=0xb9bcU&&pc!=0xbac3U&&pc!=0xbb96U&&pc!=0xbb38U&&pc!=0xbb51U&&pc!=0xbbfeU&&pc!=0xbc27U&&pc!=0xbc85U&&pc!=0xbcedU&&pc!=0xbe70U&&pc!=0xbed4U&&pc!=0xbf4dU&&pc!=0xbe02U&&pc!=0xbe41U&&pc!=0xc26cU&&pc!=0xc047U&&pc!=0xc0ccU&&pc!=0xc144U&&pc!=0xc385U&&pc!=0xc3a4U&&pc!=0xc459U&&pc!=0xc45cU&&pc!=0xc4a8U&&pc!=0xc9b0U&&pc!=0xc34aU&&pc!=0xc375U&&a!=record[5]){if(failures<10U)printf("root=%u A ROM=%02x C=%02x\n",n,record[5],a);++failures;}
        for(i=0U;i<2048U;++i){
            if(pc==0x90ccU||pc==0x9071U||pc==0x9061U||pc==0x8fe4U||pc==0x8fcfU||pc==0x90edU||pc==0x9131U||pc==0x91cdU||pc==0x9218U||pc==0x8808U||pc==0x9508U||pc==0xb450U||pc==0xb3cfU||pc==0xb58fU||pc==0xb689U||pc==0xb6f9U||pc==0xb70bU||pc==0xb94bU||pc==0xba33U||pc==0xb9bcU||pc==0xbac3U||pc==0xbb96U||pc==0xbb38U||pc==0xbb51U||pc==0xbbfeU||pc==0xbc27U||pc==0xbc85U||pc==0xbcedU||pc==0xbe70U||pc==0xbed4U||pc==0xbf4dU||pc==0xbe02U||pc==0xbe41U||pc==0xc26cU||pc==0xc047U||pc==0xc0ccU||pc==0xc144U||pc==0xc385U||pc==0xc3a4U||pc==0xc459U||pc==0xc45cU||pc==0xc4a8U||pc==0xc9b0U||pc==0xc34aU||pc==0xc375U){
                if(i>=0x1f0U&&i<=0x1ffU)continue;
            }else if((i>=0x100U&&i<=0x108U)||(i>=0x13aU&&i<=0x1ffU))continue;
            if(game.ram[i]!=record[2088U+i]){++ram_failures[i];if(failures<10U)printf("root=%u RAM=%04x ROM=%02x C=%02x\n",n,i,record[2088U+i],game.ram[i]);++failures;}
        }
        for(i=0U;i<24U;++i)if(game.apu_registers[i]!=record[4136U+i]){if(failures<10U)printf("root=%u APU=%u ROM=%02x C=%02x\n",n,i,record[4136U+i],game.apu_registers[i]);++failures;}
        if(game.apu_write_count!=record[6]){if(failures<10U)printf("root=%u writes ROM=%u C=%u\n",n,record[6],game.apu_write_count);++failures;}
        for(i=0U;i<game.apu_write_count&&i<record[6];++i)if(game.apu_writes[i].index!=record[4160U+2U*i]||game.apu_writes[i].value!=record[4161U+2U*i]){
            if(failures<10U)printf("root=%u write=%u ROM=%u:%02x C=%u:%02x\n",n,i,record[4160U+2U*i],record[4161U+2U*i],game.apu_writes[i].index,game.apu_writes[i].value);++failures;
        }
    }
    for(i=0U;i<2048U;++i)if(ram_failures[i])printf("ram-difference-address=%04x count=%u\n",i,ram_failures[i]);
    if(fgetc(f)!=EOF)return 66;fclose(f);printf("roots=%u differences=%u\n",count,failures);return failures?1:0;
}
