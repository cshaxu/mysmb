#include "core/enemy/frenzy.h"
#include "core/enemy/actor_slots.h"
#include "core/enemy/init_targets.h"
#include "core/enemy/movement.h"
#include "core/enemy/init.h"
#include "core/world/world.h"
#include <stdio.h>
#include <string.h>

static unsigned int unexpected;
void mysmb_enemy_step_lakitus_slot(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++unexpected; }
void mysmb_enemy_setup_lakitu(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++unexpected; }
mysmb_u8 mysmb_enemy_player_lakitu_difference(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++unexpected;return 0U; }
void mysmb_enemy_init_small_box(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++unexpected; }
void mysmb_enemy_move_downward(struct mysmb_game *g,mysmb_u8 s,mysmb_u8 a,mysmb_u8 b) { (void)g;(void)s;(void)a;(void)b;++unexpected; }
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *g,mysmb_u8 s) { (void)g;(void)s;++unexpected; }
mysmb_u8 mysmb_world_query_enemy_under(struct mysmb_game *g,mysmb_u8 s,struct mysmb_enemy_terrain *t) { (void)g;(void)s;(void)t;++unexpected;return 0U; }

static int check_call(const unsigned char *record)
{
    struct mysmb_game game;
    const unsigned char *before;
    const unsigned char *after;
    unsigned int i;
    mysmb_u8 result;
    before=record+2U; after=record+2050U;
    memcpy(game.ram,before,sizeof(game.ram));
    result=mysmb_enemy_set_flame_timer(&game);
    if(result!=record[1]) return 1;
    for(i=0U;i<sizeof(game.ram);++i)
        if(game.ram[i]!=after[i]) return 1;
    return 0;
}

static int scan_file(const char *path,unsigned int *cases,unsigned int *failures)
{
    unsigned char header[8],record[4098];
    unsigned int i,count;
    FILE *file;
    file=fopen(path,"rb"); if(file==0) return 65;
    if(fread(header,1U,8U,file)!=8U || memcmp(header,"MSlC\1",5U)!=0 || header[5]>16U) { fclose(file);return 66; }
    count=header[5];
    for(i=0U;i<count;++i) {
        if(fread(record,1U,sizeof(record),file)!=sizeof(record)) { fclose(file);return 66; }
        if(record[0]==7U) { ++*cases; if(check_call(record)!=0) ++*failures; }
    }
    if(fgetc(file)!=EOF) { fclose(file);return 66; }
    fclose(file); return 0;
}

int main(int argc,char **argv)
{
    FILE *manifest;
    char line[1024];
    unsigned int cases,failures;
    int result;
    if(argc!=3 || strcmp(argv[1],"--manifest")!=0) return 64;
    manifest=fopen(argv[2],"r"); if(manifest==0) return 65;
    cases=failures=unexpected=0U;
    while(fgets(line,sizeof(line),manifest)!=0) {
        line[strcspn(line,"\r\n")]='\0';
        if(line[0]=='\0') continue;
        result=scan_file(line,&cases,&failures);
        if(result!=0) { fclose(manifest);return result; }
    }
    fclose(manifest);
    printf("flame timer ROM calls: %u cases, %u failures, %u unexpected\n",cases,failures,unexpected);
    return cases!=0U && failures==0U && unexpected==0U ? 0 : 1;
}

