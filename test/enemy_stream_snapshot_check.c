#include "game/enemy/stream.h"
#include "game/enemy/init.h"
#include "game/enemy/loop.h"
#include "game/enemy/group.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <string.h>

static unsigned char records[8][4098];
static unsigned int count,calls,failures;
static void compare(const unsigned char *actual,const unsigned char *expected)
{
    unsigned int i;
    for(i=0U;i<2048U;++i) {
        if(i>=0x100U && i<0x200U && (i<0x133U || i>0x139U)) continue;
        if(actual[i]!=expected[i]) {
            printf("%04x original=%02x native=%02x\n",i,
                (unsigned int)expected[i],(unsigned int)actual[i]);
            ++failures;
        }
    }
}
static void child(struct mysmb_game *game,mysmb_u8 id,mysmb_u8 argument)
{
    unsigned char *record;
    if(calls>=count) { ++failures;return; }
    record=records[calls++];
    if(record[0]!=id || record[1]!=argument) ++failures;
    compare(game->ram,record+2U);
    memcpy(game->ram,record+2050U,2048U);
}
void mysmb_enemy_checkpoint_loaded(struct mysmb_game *game,mysmb_u8 slot)
{ child(game,1U,slot); }
void mysmb_enemy_process_loop_command(struct mysmb_game *game,
    const struct mysmb_area_source *source,mysmb_u8 slot)
{ (void)source;child(game,2U,slot); }
void mysmb_enemy_stream_handle_group(struct mysmb_game *game,mysmb_u8 id)
{ child(game,3U,id); }

int main(int argc,char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    struct mysmb_area_source source;
    unsigned char header[8];
    FILE *file;
    if(argc!=3) return 64;
    file=fopen(argv[2],"rb");if(file==NULL) return 65;
    if(fread(header,1,8,file)!=8 || memcmp(header,"MSSC\1",5)!=0 || header[5]>8U) return 66;
    count=header[5];
    if(fread(records,4098,count,file)!=count || fgetc(file)!=EOF) return 66;
    fclose(file);
    file=fopen(argv[1],"rb");if(file==NULL) return 65;
    if(fread(header,1,8,file)!=8 || memcmp(header,"MSSP\1",5)!=0) return 66;
    if(fread(game.ram,1,2048,file)!=2048 || fread(expected,1,2048,file)!=2048 ||
        fgetc(file)!=EOF) return 66;
    fclose(file);
    source.prg=mysmb_local_prg;source.prg_size=MYSMB_LOCAL_PRG_SIZE;
    (void)mysmb_enemy_stream_process_current(&game,&source,header[6]);
    compare(game.ram,expected);
    if(calls!=count) ++failures;
    return failures?1:0;
}
