#include "core/game.h"
#include "game/presentation/text/observer_snapshot.h"
#include <string.h>

#define BUFFER_BYTES 2626U
#define RECORD_BYTES 40U

static void write_buffer(const struct mysmb_text_observation_buffer *buffer,
    unsigned char *out)
{
    unsigned short i;
    const struct mysmb_text_observation *item;
    out[0]=buffer->count;out[1]=buffer->overflow;
    memcpy(out+2,buffer->owners,64U);out+=66U;
    for(i=0U;i<buffer->count;++i,out+=RECORD_BYTES) {
        item=&buffer->items[i];
        out[0]=item->family;out[1]=item->identity;out[2]=item->slot;
        out[3]=item->graphics;out[4]=item->facing;out[5]=item->oam;
        out[6]=item->sprites;out[7]=item->source_size;
        memcpy(out+8,item->entries,32U);
    }
}

static int buffer_valid(const unsigned char *in)
{
    unsigned short i,owner,start;
    const unsigned char *item;
    if(in[0]>64U || in[1]>1U)return 0;
    for(i=0U;i<64U;++i) {
        item=in+66U+i*RECORD_BYTES;
        if(i>=in[0]) {
            for(owner=0U;owner<RECORD_BYTES;++owner)
                if(item[owner]!=0U)return 0;
        } else if(item[0]<MYSMB_TEXT_OBSERVE_PLAYER ||
            item[0]>MYSMB_TEXT_OBSERVE_STAR_FLAG || (item[5]&3U)!=0U ||
            item[6]==0U || item[6]>8U || item[5]+item[6]*4U>256U)return 0;
    }
    for(i=0U;i<64U;++i) {
        owner=in[2U+i];
        if(owner==0U)continue;
        if(owner>in[0])return 0;
        item=in+66U+(owner-1U)*RECORD_BYTES;start=item[5]/4U;
        if(i<start || i>=start+item[6])return 0;
    }
    return 1;
}

int mysmb_text_observer_snapshot_valid(const unsigned char *bytes)
{
    unsigned short i;
    if(bytes[0]==0U) {
        for(i=1U;i<MYSMB_TEXT_OBSERVER_SNAPSHOT_BYTES;++i)
            if(bytes[i]!=0U)return 0;
        return 1;
    }
    return bytes[0]==1U && buffer_valid(bytes+1) &&
        buffer_valid(bytes+1U+BUFFER_BYTES);
}

int mysmb_text_observer_snapshot_capture(const struct mysmb_game *game,
    unsigned char *bytes)
{
    if(game->text_observer.enabled==1U &&
        (game->text_observer.producer.count>64U ||
         game->text_observer.visible.count>64U))return 0;
    memset(bytes,0,MYSMB_TEXT_OBSERVER_SNAPSHOT_BYTES);
    if(game->text_observer.enabled!=1U)return 1;
    bytes[0]=1U;
    write_buffer(&game->text_observer.producer,bytes+1);
    write_buffer(&game->text_observer.visible,bytes+1U+BUFFER_BYTES);
    return mysmb_text_observer_snapshot_valid(bytes);
}

static void read_buffer(struct mysmb_text_observation_buffer *buffer,
    const unsigned char *in)
{
    unsigned short i;
    struct mysmb_text_observation *item;
    buffer->count=in[0];buffer->overflow=in[1];
    memcpy(buffer->owners,in+2,64U);in+=66U;
    for(i=0U;i<buffer->count;++i,in+=RECORD_BYTES) {
        item=&buffer->items[i];
        item->family=in[0];item->identity=in[1];item->slot=in[2];
        item->graphics=in[3];item->facing=in[4];item->oam=in[5];
        item->sprites=in[6];item->source_size=in[7];
        memcpy(item->entries,in+8,32U);
    }
}

void mysmb_text_observer_snapshot_restore(struct mysmb_game *game,
    const unsigned char *bytes)
{
    /* Absent/legacy receipts retain the destination's observation preference. */
    mysmb_text_observer_invalidate(game);
    if(bytes[0]==0U)return;
    game->text_observer.enabled=1U;
    read_buffer(&game->text_observer.producer,bytes+1);
    read_buffer(&game->text_observer.visible,bytes+1U+BUFFER_BYTES);
}
