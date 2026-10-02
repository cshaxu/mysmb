#include "game/audio.h"
#include "game/status.h"
#include "game/frame_root.h"
#include "game/area.h"
#include "game/player.h"
#include "game/terminal_modes.h"
#include <stdio.h>
#include <string.h>
#define RECORD_BYTES 4290U
int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char prg[32768],record[RECORD_BYTES];
    unsigned char h[16];FILE *f;unsigned int count,n,i,pc,failures=0U;mysmb_u8 a;
    if(argc!=3)return 64;
    f=fopen(argv[2],"rb");if(!f||fread(h,1U,16U,f)!=16U||memcmp(h,"NES\032",4U)||h[4]!=2U||fread(prg,1U,32768U,f)!=32768U)return 65;fclose(f);
    f=fopen(argv[1],"rb");if(!f||fread(h,1U,16U,f)!=16U||memcmp(h,"MSCM\1",5U))return 65;
    count=h[8]|((unsigned int)h[9]<<8U);if(!count||count>1024U)return 66;
    for(n=0U;n<count;++n){
        if(fread(record,1U,sizeof(record),f)!=sizeof(record))return 66;
        memset(&game,0,sizeof(game));memcpy(game.ram,record+16U,2048U);memcpy(game.apu_registers,record+2064U,24U);
        game.area_prg=prg;game.area_prg_size=32768U;
        /* These bootstrap bindings are presence-only preconditions here.
         * InitializeGame does not read title/icon bytes; all actual data
         * reads use the unchanged full owner PRG above. */
        game.title_data=prg;game.title_data_size=0x013aU;
        game.title_icon_data=prg;game.title_icon_data_size=1U;
        a=record[2];pc=record[0]|((unsigned int)record[1]<<8U);
        switch(pc){
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
        if(pc!=0xf2d0U&&pc!=0xf6f5U&&pc!=0x8f06U&&pc!=0x8f5fU&&pc!=0x8f97U&&pc!=0x90ccU&&pc!=0x9071U&&pc!=0x9061U&&pc!=0x8fe4U&&pc!=0x8fcfU&&pc!=0x90edU&&pc!=0x9131U&&pc!=0x91cdU&&pc!=0x9218U&&a!=record[5]){if(failures<10U)printf("root=%u A ROM=%02x C=%02x\n",n,record[5],a);++failures;}
        for(i=0U;i<2048U;++i){
            if(pc==0x90ccU||pc==0x9071U||pc==0x9061U||pc==0x8fe4U||pc==0x8fcfU||pc==0x90edU||pc==0x9131U||pc==0x91cdU||pc==0x9218U){
                if(i>=0x1f0U&&i<=0x1ffU)continue;
            }else if((i>=0x100U&&i<=0x108U)||(i>=0x13aU&&i<=0x1ffU))continue;
            if(game.ram[i]!=record[2088U+i]){if(failures<10U)printf("root=%u RAM=%04x ROM=%02x C=%02x\n",n,i,record[2088U+i],game.ram[i]);++failures;}
        }
        for(i=0U;i<24U;++i)if(game.apu_registers[i]!=record[4136U+i]){if(failures<10U)printf("root=%u APU=%u ROM=%02x C=%02x\n",n,i,record[4136U+i],game.apu_registers[i]);++failures;}
        if(game.apu_write_count!=record[6]){if(failures<10U)printf("root=%u writes ROM=%u C=%u\n",n,record[6],game.apu_write_count);++failures;}
        for(i=0U;i<game.apu_write_count&&i<record[6];++i)if(game.apu_writes[i].index!=record[4160U+2U*i]||game.apu_writes[i].value!=record[4161U+2U*i]){
            if(failures<10U)printf("root=%u write=%u ROM=%u:%02x C=%u:%02x\n",n,i,record[4160U+2U*i],record[4161U+2U*i],game.apu_writes[i].index,game.apu_writes[i].value);++failures;
        }
    }
    if(fgetc(f)!=EOF)return 66;fclose(f);printf("roots=%u differences=%u\n",count,failures);return failures?1:0;
}
