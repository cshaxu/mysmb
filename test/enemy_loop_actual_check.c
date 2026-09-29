#include "game/world/world.h"
#include "game/enemy/core.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/platform.h"
#include "game/enemy/actor_slots.h"
#include "game/enemy/movement.h"
#include "game/enemy/x_counter.h"
#include "game/enemy/stream.h"
#include "game/enemy/init.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/frenzy.h"
#include "game/enemy/loop.h"
#include "game/enemy/group.h"
#include "game/objects.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

/* Integrated diagnostic: no child substitutions or scratch-byte masking. */
static int check_one(const char *path)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    struct mysmb_area_source source;
    unsigned char header[8];
    unsigned int i,failures,register_failure;
    FILE *file;
    memset(&game,0,sizeof(game));
    file=fopen(path,"rb");if(file==NULL) return 65;
    if(fread(header,1,8,file)!=8 || (memcmp(header,"MSEP\1",5)!=0 &&
        memcmp(header,"MSSP\1",5)!=0 && memcmp(header,"MSZP\1",5)!=0 &&
        memcmp(header,"MSAP\1",5)!=0 && memcmp(header,"MSYP\1",5)!=0 &&
        memcmp(header,"MSOP\1",5)!=0 && memcmp(header,"MS2P\1",5)!=0 &&
        memcmp(header,"MS3P\1",5)!=0 && memcmp(header,"MS4P\1",5)!=0 && memcmp(header,"MS5P\1",5)!=0 && memcmp(header,"MS6P\1",5)!=0 && memcmp(header,"MS7P\1",5)!=0 && memcmp(header,"MS8P\1",5)!=0 && memcmp(header,"MS9P\1",5)!=0 && memcmp(header,"MSaP\1",5)!=0 && memcmp(header,"MSbP\1",5)!=0 && memcmp(header,"MScP\1",5)!=0 && memcmp(header,"MSdP\1",5)!=0 && memcmp(header,"MSeP\1",5)!=0 && memcmp(header,"MSfP\1",5)!=0 && memcmp(header,"MSgP\1",5)!=0 && memcmp(header,"MShP\1",5)!=0 && memcmp(header,"MSiP\1",5)!=0 && memcmp(header,"MSjP\1",5)!=0 && memcmp(header,"MSkP\1",5)!=0 && memcmp(header,"MSlP\1",5)!=0 && memcmp(header,"MSmP\1",5)!=0 && memcmp(header,"MSnP\1",5)!=0 && memcmp(header,"MSoP\1",5)!=0 && memcmp(header,"MSpP\1",5)!=0 && memcmp(header,"MSqP\1",5)!=0 && memcmp(header,"MSrP\1",5)!=0 && memcmp(header,"MSsP\1",5)!=0 && memcmp(header,"MStP\1",5)!=0 && memcmp(header,"MSuP\1",5)!=0 && memcmp(header,"MSvP\1",5)!=0 && memcmp(header,"MSwP\1",5)!=0 && memcmp(header,"MSxP\1",5)!=0 && memcmp(header,"MSyP\1",5)!=0 && memcmp(header,"MSzP\1",5)!=0)) return 66;
    if(fread(game.ram,1,2048,file)!=2048 || fread(expected,1,2048,file)!=2048 ||
        fgetc(file)!=EOF) return 66;
    fclose(file);
    register_failure=0U;
    game.area_prg=mysmb_local_prg;game.area_prg_size=MYSMB_LOCAL_PRG_SIZE;
    game.ppu_control_0=game.ram[0x778U];
    source.prg=mysmb_local_prg;source.prg_size=MYSMB_LOCAL_PRG_SIZE;
    if(header[2]=='z') mysmb_objects_collect_power_up(&game,header[6]);
    else if(header[2]=='y') mysmb_objects_check_hammer_collision(&game,header[6]);
    else if(header[2]=='x') mysmb_world_handle_fireball_enemy_hit(&game,header[6]);
    else if(header[2]=='w') mysmb_world_fireball_enemy_collision(&game,header[6]);
    else if(header[2]=='v') mysmb_objects_check_enemy_offscreen_bounds(&game,header[6]);
    else if(header[2]=='u') {
        if(game.ram[0x16U+header[6]]<43U)mysmb_platform_move_large_lift(&game,header[6]);
        else mysmb_platform_move_small(&game,header[6]);
    }
    else if(header[2]=='t') {
        if(game.ram[0x16U+header[6]]==40U)mysmb_platform_move_x(&game,header[6]);
        else if(game.ram[0x16U+header[6]]==41U)mysmb_platform_move_drop(&game,header[6]);
        else mysmb_platform_move_right(&game,header[6]);
    }
    else if(header[2]=='s') mysmb_platform_move_y(&game,header[6]);
    else if(header[2]=='r') mysmb_platform_move_balance(&game,header[6]);
    else if(header[2]=='q') mysmb_objects_step_piranha_plants_slot(&game,header[6]);
    else if(header[2]=='p') mysmb_objects_step_star_flags_slot(&game,header[6]);
    else if(header[2]=='o') mysmb_objects_step_fireworks_slot(&game,header[6]);
    else if(header[2]=='n') mysmb_enemy_proc_bowser_flame(&game,header[6]);
    else if(header[2]=='m') mysmb_objects_draw_bowsers_slot(&game,header[6]);
    else if(header[2]=='l') mysmb_enemy_run_bowser(&game,header[6]);
    else if(header[2]=='k') (void)mysmb_objects_step_bridge_collapse(&game);
    else if(header[2]=='j') {
        if(header[5]==1U) mysmb_enemy_step_lakitus_slot(&game,header[6]);
        else if(mysmb_enemy_player_lakitu_difference(&game,header[6])!=header[7]) {
            puts("return A mismatch"); register_failure=1U;
        }
    }
    else if(header[2]=='i') mysmb_objects_step_flying_cheep_cheeps_slot(&game,header[6]);
    else if(header[2]=='h') (void)mysmb_enemy_proc_firebar(&game,header[6]);
    else if(header[2]=='g') mysmb_objects_step_swimming_cheep_cheeps_slot(&game,header[6]);
    else if(header[2]=='f') mysmb_objects_step_bullet_bills_slot(&game,header[6]);
    else if(header[2]=='e') mysmb_objects_step_bloobers_slot(&game,header[6]);
    else if(header[2]=='d') {
        if(header[5]==1U) mysmb_objects_step_flying_green_paratroopas_slot(&game,header[6]);
        else mysmb_enemy_x_counter_platform(&game,header[6],header[7]);
    }
    else if(header[7]==0U && header[2]=='c') {
        if(header[5]==1U) mysmb_enemy_move_jumping(&game,header[6]);
        else mysmb_objects_step_red_paratroopas_slot(&game,header[6]);
    }
    else if(header[7]==0U && header[2]=='b') {
        if(header[5]==1U) mysmb_objects_step_hammer_bros_slot(&game,header[6]);
        else mysmb_enemy_move_normal(&game,header[6]);
    }
    else if(header[7]==0U && header[2]=='a')
        mysmb_objects_step_podoboos_slot(&game,header[6]);
    else if(header[7]==0U && header[2]=='9') {
        switch(header[5]) {
        case 1U: mysmb_objects_step_bowser_flames_slot(&game,header[6]);break;
        case 2U: (void)mysmb_objects_step_firebars_slot(&game,header[6]);break;
        case 3U: mysmb_enemy_run_small_platform(&game,header[6]);break;
        case 4U: mysmb_enemy_run_large_platform(&game,header[6]);break;
        case 5U: mysmb_platform_movement_dispatch(&game,header[6]);break;
        case 6U: mysmb_objects_erase_enemy(&game,header[6]);break;
        default:return 66;
        }
    }
    else if(header[7]==0U && header[2]=='8') {
        if(header[5]==1U) mysmb_objects_step_normal_enemy(&game,header[6]);
        else if(header[5]==2U) mysmb_enemy_movement_dispatch(&game,header[6]);
        else return 66;
    }
    else if(header[7]==0U && header[2]=='7') {
        if(header[5]==1U) mysmb_enemy_run_objects(&game);
        else if(header[5]==2U) mysmb_objects_draw_retainer(&game,header[6]);
        else return 66;
    }
    else if(header[7]==0U && header[2]=='6') {
        switch(header[5]) {
        case 36U: mysmb_enemy_init_balance_platform(&game,header[6]);break;
        case 37U: mysmb_enemy_init_vertical_platform(&game,header[6]);break;
        case 38U: mysmb_enemy_init_large_lift_up(&game,header[6]);break;
        case 39U: mysmb_enemy_init_large_lift_down(&game,header[6]);break;
        case 40U: case 42U: mysmb_enemy_init_horizontal_platform(&game,header[6]);break;
        case 41U: mysmb_enemy_init_drop_platform(&game,header[6]);break;
        case 43U: mysmb_enemy_init_small_lift_up(&game,header[6]);break;
        case 44U: mysmb_enemy_init_small_lift_down(&game,header[6]);break;
        case 54U: break; /* EndOfEnemyInitCode: empty return. */
        default:return 66;
        }
    }
    else if(header[7]==0U && header[2]=='5') {
        switch(header[5]) {
        case 1U: mysmb_enemy_init_piranha_plant(&game,header[6]);break;
        case 2U: mysmb_enemy_init_jump_green_ptroopa(&game,header[6]);break;
        case 3U: mysmb_enemy_end_frenzy(&game,header[6]);break;
        case 4U: mysmb_enemy_init_frenzy(&game,header[6]);break;
        default:return 66;
        }
    }
    else if(header[7]==0U && header[2]=='4')
        mysmb_enemy_stream_handle_group(&game,header[6]);
    else if(header[7]==0U && header[2]=='3')
        mysmb_enemy_step_bullet_bill_cheep_frenzy(&game,header[6]);
    else if(header[7]==0U && header[2]=='2')
        mysmb_enemy_init_fireworks_frenzy(&game,header[6]);
    else if(header[7]==0U && header[2]=='O') {
        if(header[5]==1U) mysmb_enemy_init_bowser(&game,header[6]);
        else if(header[5]==2U) mysmb_enemy_init_bowser_flame_frenzy(&game,header[6]);
        else return 66;
    }
    else if(header[7]==0U && header[2]=='Y')
        mysmb_enemy_init_flying_cheep_frenzy(&game,header[6]);
    else if(header[7]==0U && header[2]=='A')
        mysmb_enemy_init_lakitu_spiny_frenzy(&game,header[6]);
    else if(header[7]==0U && header[2]=='Z')
        mysmb_enemy_checkpoint_loaded(&game,header[6]);
    else if(header[7]==0U && header[2]=='S')
        (void)mysmb_enemy_stream_process_current(&game,&source,header[6]);
    else if(header[7]==0U) mysmb_enemy_core_step_slot(&game,&source,header[6]);
    else if(header[7]==1U) {
        switch(header[5]) {
        case 1U: (void)mysmb_enemy_stream_process_current(&game,&source,header[6]);break;
        case 2U: mysmb_enemy_checkpoint_loaded(&game,header[6]);break;
        case 3U: mysmb_enemy_run_objects(&game);break;
        default:return 66;
        }
    } else if(header[7]==2U) {
        switch(header[5]) {
        case 1U: mysmb_enemy_checkpoint_loaded(&game,header[6]);break;
        case 2U: mysmb_enemy_process_loop_command(&game,&source,header[6]);break;
        case 3U: mysmb_enemy_stream_handle_group(&game,header[6]);break;
        default:return 66;
        }
    } else return 66;
    failures=register_failure;
    for(i=0U;i<2048U;++i) {
        /* Original game variables include floatey numbers and shell chains,
         * not only DigitModifier. Retain their whole $0109-$0139 region. */
        if(i>=0x100U && i<0x200U && (i<0x109U || i>0x139U)) continue;
        if(game.ram[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)game.ram[i]);
            ++failures;
        }
    }
    return failures?1:0;
}

int main(int argc, char **argv)
{
    char path[1024];
    size_t length;
    unsigned int n;
    int result, bad;
    if (argc != 2) return 64;
    if (strcmp(argv[1], "--batch") != 0) return check_one(argv[1]);
    n = 0U; bad = 0;
    while (fgets(path, sizeof(path), stdin) != NULL) {
        length = strlen(path);
        while (length && (path[length - 1U] == '\n' || path[length - 1U] == '\r')) path[--length] = '\0';
        if (!length) return 64;
        printf("BEGIN %u\n", n);
        result = check_one(path);
        printf("END %u %d\n", n++, result);
        if (result != 0 && result != 1) bad = 1;
    }
    return bad;
}
