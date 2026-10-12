#include "io/snapshot.h"
#include "platform/win32/audio_snapshot_real.h"
#include <float.h>
#include <string.h>
#include <math.h>

static struct mysmb_io_snapshot source,decoded,unchanged;
static struct mysmb_io_snapshot_cache cache;
static mysmb_io_u8 file[MYSMB_SNAPSHOT_FILE_BYTES+1U];
static mysmb_io_u8 legacy_crc[MYSMB_SNAPSHOT_LEGACY_FILE_BYTES-4U];

int main(void)
{
    static const double values[]={0.0,1.0,-1.0,0.125,0.9999999999999999,
        -0.12345678912345678,DBL_MIN,DBL_MAX};
    static const mysmb_io_u8 crc_fixture[]={'1','2','3','4','5','6','7','8','9'};
    mysmb_io_u8 real[10],saved,other_fingerprint[16];
    double result;
    unsigned int i,bit;
    mysmb_io_u16 pos;
    if (MYSMB_SNAPSHOT_FILE_BYTES!=10035U ||
        MYSMB_SNAPSHOT_CORE_BYTES+MYSMB_SNAPSHOT_AUDIO_BYTES+
        MYSMB_SNAPSHOT_PRESENTATION_BYTES!=MYSMB_SNAPSHOT_PAYLOAD_BYTES)
        return 1;
    if (mysmb_snapshot_crc(crc_fixture,9U)!=0xcbf43926UL) return 2;
    mysmb_snapshot_put32(real,0x89abcdefUL);
    if (real[0]!=0xefU || real[3]!=0x89U ||
        mysmb_snapshot_get32(real)!=0x89abcdefUL) return 3;
    for (i=0U;i<sizeof(values)/sizeof(values[0]);++i) {
        if (!mysmb_snapshot_put_real(real,values[i]) ||
            !mysmb_snapshot_get_real(real,&result) || result!=values[i]) return 4;
    }
    result=ldexp(1.0,-1074);
    if (!mysmb_snapshot_put_real(real,result) ||
        !mysmb_snapshot_get_real(real,&result) || result!=ldexp(1.0,-1074)) return 5;
    memset(real,0,sizeof(real));real[0]=2U;result=1.0;
    if (mysmb_snapshot_get_real(real,&result) || result!=1.0) return 6;
    memset(real,0,sizeof(real));real[1]=1U;
    if (mysmb_snapshot_get_real(real,&result)) return 7;
    memset(&source,0,sizeof(source));
    for (pos=0U;pos<MYSMB_SNAPSHOT_CORE_BYTES;++pos)
        source.payload[pos]=(mysmb_io_u8)(pos*37U+11U);
    for (i=0U;i<16U;++i) source.fingerprint[i]=(mysmb_io_u8)(i+1U);
    source.payload[MYSMB_SNAPSHOT_CORE_BYTES]=1U;
    for (i=0U;i<6U;++i)
        if (!mysmb_snapshot_put_real(source.payload+MYSMB_SNAPSHOT_CORE_BYTES+
            MYSMB_SNAPSHOT_AUDIO_REAL_OFFSET+i*10U,values[i])) return 8;
    if (mysmb_snapshot_encode(&source,file,MYSMB_SNAPSHOT_FILE_BYTES)!=0 ||
        memcmp(file,"MYSMBSAV",8U)!=0 || file[8]!=2U || file[9]!=0U ||
        mysmb_snapshot_get32(file+12)!=MYSMB_SNAPSHOT_PAYLOAD_BYTES) return 9;
    if (mysmb_snapshot_decode(file,MYSMB_SNAPSHOT_FILE_BYTES,source.fingerprint,
        &decoded)!=0 || memcmp(&source,&decoded,sizeof(source))!=0) return 10;
    memset(&unchanged,0xa6,sizeof(unchanged));decoded=unchanged;
    for (pos=0U;pos<MYSMB_SNAPSHOT_FILE_BYTES;++pos) {
        saved=file[pos];
        for (bit=0U;bit<(pos<36U ? 8U:1U);++bit) {
            file[pos]=(mysmb_io_u8)(saved^(1U<<(pos<36U ? bit:pos%8U)));
            if (mysmb_snapshot_decode(file,MYSMB_SNAPSHOT_FILE_BYTES,
                source.fingerprint,&decoded)==0 ||
                memcmp(&decoded,&unchanged,sizeof(decoded))!=0) return 11;
        }
        file[pos]=saved;
    }
    for (pos=0U;pos<MYSMB_SNAPSHOT_FILE_BYTES;++pos)
        if (mysmb_snapshot_decode(file,pos,source.fingerprint,&decoded)==0)
            return 12;
    if (mysmb_snapshot_decode(file,MYSMB_SNAPSHOT_FILE_BYTES+1U,
        source.fingerprint,&decoded)==0) return 13;
    memset(other_fingerprint,0,sizeof(other_fingerprint));
    if (mysmb_snapshot_decode(file,MYSMB_SNAPSHOT_FILE_BYTES,other_fingerprint,
        &decoded)!=MYSMB_SNAPSHOT_RESOURCE) return 14;
    /* Independently construct schema1: unchanged core/audio and no receipts. */
    mysmb_snapshot_put16(file+8,1U);mysmb_snapshot_put16(file+10,1U);
    mysmb_snapshot_put32(file+12,MYSMB_SNAPSHOT_PRESENTATION_OFFSET);
    memcpy(legacy_crc,file,32U);
    memcpy(legacy_crc+32,file+36,MYSMB_SNAPSHOT_PRESENTATION_OFFSET);
    mysmb_snapshot_put32(file+32,mysmb_snapshot_crc(legacy_crc,sizeof(legacy_crc)));
    memset(&decoded,0xa6,sizeof(decoded));
    if(mysmb_snapshot_decode(file,MYSMB_SNAPSHOT_LEGACY_FILE_BYTES,
        source.fingerprint,&decoded)!=0 || memcmp(decoded.payload,source.payload,
        MYSMB_SNAPSHOT_PRESENTATION_OFFSET))return 19;
    for(pos=MYSMB_SNAPSHOT_PRESENTATION_OFFSET;pos<MYSMB_SNAPSHOT_PAYLOAD_BYTES;++pos)
        if(decoded.payload[pos]!=0U)return 20;
    if(mysmb_snapshot_decode(file,MYSMB_SNAPSHOT_FILE_BYTES,
        source.fingerprint,&decoded)==0)return 21;
    mysmb_snapshot_cache_initialize(&cache);
    mysmb_snapshot_cache_update(&cache,&source,0U);
    if (mysmb_snapshot_cache_current(&cache)!=0) return 15;
    mysmb_snapshot_cache_update(&cache,&source,1U);
    source.payload[0]^=1U;
    mysmb_snapshot_cache_update(&cache,&source,0U);
    if (mysmb_snapshot_cache_current(&cache)->payload[0]==source.payload[0])
        return 16;
    mysmb_snapshot_cache_update(&cache,&source,1U);
    if (mysmb_snapshot_cache_current(&cache)->payload[0]!=source.payload[0])
        return 17;
    memset(file,0x5c,sizeof(file));source.payload[MYSMB_SNAPSHOT_CORE_BYTES]=2U;
    if (mysmb_snapshot_encode(&source,file,MYSMB_SNAPSHOT_FILE_BYTES)==0 ||
        file[0]!=0x5cU || file[MYSMB_SNAPSHOT_FILE_BYTES-1U]!=0x5cU) return 18;
    return 0;
}
