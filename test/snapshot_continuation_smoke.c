#include <stdio.h>
#include <string.h>
#include "app/game_snapshot.h"
#include "app/game_io.h"
#include "platform/win32/audio_snapshot.h"
#include "game/area.h"
#include "smb1_local_rom.h"
#include "smb1_local_title.h"
static struct mysmb_game live,restored;
static struct mysmb_win32_audio_renderer sound1,sound2;
static struct mysmb_io_snapshot saved,current,other;
static struct mysmb_ppu_frame pixels1,pixels2;
static struct mysmb_io_audio_frame audio1,audio2;
static unsigned char wire[MYSMB_SNAPSHOT_FILE_BYTES];
static short pcm1[735],pcm2[735];
static void bind(struct mysmb_game *game)
{
    mysmb_game_power_on(game);
    mysmb_game_bind_area_source(game,mysmb_local_prg,MYSMB_LOCAL_PRG_SIZE);
    mysmb_game_bind_chr_source(game,mysmb_local_chr,MYSMB_LOCAL_CHR_SIZE);
    mysmb_game_bind_title_source(game,mysmb_local_title_data,MYSMB_LOCAL_TITLE_DATA_SIZE,
        mysmb_local_title_icon_data,MYSMB_LOCAL_TITLE_ICON_DATA_SIZE);
}
static unsigned long digest(unsigned long hash,const void *bytes,unsigned int size)
{
    const unsigned char *p=(const unsigned char *)bytes;
    unsigned int i;
    for(i=0U;i<size;++i)hash=((hash^p[i])*16777619UL)&0xffffffffUL;
    return hash;
}
int main(int argc,char **argv)
{
    struct mysmb_input input;
    struct mysmb_frame frame1,frame2;
    unsigned char fingerprint[16];
    unsigned int i,running,nonzero;
    unsigned long hash,core_hash,pixel_hash,pcm_hash,audio_hash;
    FILE *file,*audio_records,*stream;
    char audio_path[512];
    if(argc!=4)return 1;
    bind(&live);bind(&restored);
    mysmb_win32_audio_renderer_initialize(&sound1);
    mysmb_game_snapshot_fingerprint(&live,fingerprint);
    input.buttons2=0U;running=0U;nonzero=0U;
    if(!strcmp(argv[1],"capture")){
        for(i=0U;i<1400U && running<32U;++i){
            if(!mysmb_game_startup_step(&live,1U))continue;
            input.buttons=i==100U?MYSMB_BUTTON_START:0U;
            mysmb_game_tick(&live,&input,&frame1);
            mysmb_game_io_audio(&live,&audio1);
            mysmb_win32_audio_render(&sound1,&audio1,pcm1,735U,44100U);
            if(mysmb_game_snapshot_running(&live,&frame1))++running;
        }
        if(running!=32U)return 2;
        mysmb_game_snapshot_capture(&live,&saved,fingerprint);
        if(!mysmb_win32_audio_capture(&sound1,saved.payload+MYSMB_SNAPSHOT_CORE_BYTES) ||
            mysmb_snapshot_encode(&saved,wire,sizeof(wire))!=MYSMB_SNAPSHOT_OK)return 3;
        file=fopen(argv[2],"wb");if(!file)return 4;
        i=(unsigned int)fwrite(wire,1,sizeof(wire),file);
        if(fclose(file) || i!=sizeof(wire))return 5;
    }else if(!strcmp(argv[1],"verify")){
        file=fopen(argv[2],"rb");if(!file)return 6;
        i=(unsigned int)fread(wire,1,sizeof(wire),file);fclose(file);
        if(i!=sizeof(wire) || mysmb_snapshot_decode(wire,sizeof(wire),fingerprint,&saved) ||
            !mysmb_game_snapshot_restore(&live,&saved) ||
            !mysmb_win32_audio_restore(&sound1,saved.payload+MYSMB_SNAPSHOT_CORE_BYTES))return 7;
    }else return 8;
    /* For capture mode live is uninterrupted. Restored always starts from
     * an independent constructor and crosses the explicit wire codec. */
    if(mysmb_snapshot_decode(wire,sizeof(wire),fingerprint,&saved) ||
        !mysmb_game_snapshot_restore(&restored,&saved) ||
        !mysmb_win32_audio_restore(&sound2,saved.payload+MYSMB_SNAPSHOT_CORE_BYTES))return 9;
    mysmb_game_snapshot_capture(&restored,&other,fingerprint);
    if(memcmp(saved.payload,other.payload,MYSMB_SNAPSHOT_CORE_BYTES))return 10;
    hash=2166136261UL;
    core_hash=pixel_hash=pcm_hash=audio_hash=hash;
    if(strlen(argv[3])+7U>=sizeof(audio_path))return 16;
    sprintf(audio_path,"%s.audio",argv[3]);audio_records=fopen(audio_path,"wb");
    if(!audio_records)return 17;
    sprintf(audio_path,"%s.stream",argv[3]);stream=fopen(audio_path,"wb");
    if(!stream)return 20;
    for(i=0U;i<240U;++i){
        input.buttons=i<120U?(MYSMB_BUTTON_RIGHT|MYSMB_BUTTON_B):0U;
        if(i==60U || i==170U)input.buttons|=MYSMB_BUTTON_A;
        mysmb_game_tick(&live,&input,&frame1);mysmb_game_tick(&restored,&input,&frame2);
        mysmb_game_io_audio(&live,&audio1);mysmb_game_io_audio(&restored,&audio2);
        mysmb_win32_audio_render(&sound1,&audio1,pcm1,735U,44100U);
        mysmb_win32_audio_render(&sound2,&audio2,pcm2,735U,44100U);
        mysmb_game_snapshot_capture(&live,&current,fingerprint);
        mysmb_game_snapshot_capture(&restored,&other,fingerprint);
        mysmb_win32_audio_capture(&sound1,current.payload+MYSMB_SNAPSHOT_CORE_BYTES);
        mysmb_win32_audio_capture(&sound2,other.payload+MYSMB_SNAPSHOT_CORE_BYTES);
        if(memcmp(current.payload,other.payload,sizeof(current.payload)) ||
            memcmp(pcm1,pcm2,sizeof(pcm1)))return 11;
        mysmb_ppu_frame_build(&live.ppu,&pixels1);mysmb_ppu_frame_build(&restored.ppu,&pixels2);
        if(memcmp(pixels1.pixels,pixels2.pixels,sizeof(pixels1.pixels)))return 12;
        hash=digest(hash,current.payload,sizeof(current.payload));
        hash=digest(hash,pixels1.pixels,sizeof(pixels1.pixels));
        hash=digest(hash,pcm1,sizeof(pcm1));
        core_hash=digest(core_hash,current.payload,MYSMB_SNAPSHOT_CORE_BYTES);
        audio_hash=digest(audio_hash,current.payload+MYSMB_SNAPSHOT_CORE_BYTES,MYSMB_SNAPSHOT_AUDIO_BYTES);
        if(fwrite(current.payload+MYSMB_SNAPSHOT_CORE_BYTES,1,MYSMB_SNAPSHOT_AUDIO_BYTES,
            audio_records)!=MYSMB_SNAPSHOT_AUDIO_BYTES)return 18;
        pixel_hash=digest(pixel_hash,pixels1.pixels,sizeof(pixels1.pixels));
        pcm_hash=digest(pcm_hash,pcm1,sizeof(pcm1));
        /* A bounded 16.3MB local stream permits direct cross-width comparison
         * of every game byte,pixel,integer synthesis field and PCM sample.
         * Six host floating values have a separate numerical receipt. */
        if(fwrite(current.payload,1,MYSMB_SNAPSHOT_CORE_BYTES,stream)!=MYSMB_SNAPSHOT_CORE_BYTES ||
            fwrite(current.payload+MYSMB_SNAPSHOT_CORE_BYTES,1,64U,stream)!=64U ||
            fwrite(pixels1.pixels,1,sizeof(pixels1.pixels),stream)!=sizeof(pixels1.pixels) ||
            fwrite(pcm1,1,sizeof(pcm1),stream)!=sizeof(pcm1))return 21;
        if(pcm1[400]!=0)++nonzero;
    }
    if(saved.payload[MYSMB_SNAPSHOT_CORE_BYTES] && !nonzero)return 13;
    if(fclose(audio_records))return 19;
    if(fclose(stream))return 22;
    file=fopen(argv[3],"w");if(!file)return 14;
    fprintf(file,"frames=240 samples=176400 differences=0 digest=%08lx audioPresent=%u\n",
        hash,(unsigned int)saved.payload[MYSMB_SNAPSHOT_CORE_BYTES]);
    fprintf(file,"core=%08lx pixels=%08lx pcm=%08lx audioState=%08lx\n",
        core_hash,pixel_hash,pcm_hash,audio_hash);
    if(fclose(file))return 15;
    return 0;
}
