#include "io/snapshot.h"
#include <string.h>

static const mysmb_io_u8 snapshot_magic[8] = {
    'M', 'Y', 'S', 'M', 'B', 'S', 'A', 'V'
};

void mysmb_snapshot_put16(mysmb_io_u8 *bytes, mysmb_io_u16 value)
{
    bytes[0]=(mysmb_io_u8)value;
    bytes[1]=(mysmb_io_u8)(value>>8U);
}
mysmb_io_u16 mysmb_snapshot_get16(const mysmb_io_u8 *bytes)
{
    return (mysmb_io_u16)(bytes[0]|((mysmb_io_u16)bytes[1]<<8U));
}
void mysmb_snapshot_put32(mysmb_io_u8 *bytes, unsigned long value)
{
    unsigned int i;
    for (i=0U;i<4U;++i) {bytes[i]=(mysmb_io_u8)value;value>>=8U;}
}
unsigned long mysmb_snapshot_get32(const mysmb_io_u8 *bytes)
{
    unsigned long value;
    int i;
    value=0UL;
    for (i=3;i>=0;--i) value=(value<<8U)|bytes[i];
    return value;
}
static unsigned long crc_add(unsigned long crc, mysmb_io_u8 value)
{
    unsigned int bit;
    crc^=value;
    for (bit=0U;bit<8U;++bit)
        crc=(crc>>1U)^((crc&1UL)!=0UL ? 0xedb88320UL:0UL);
    return crc;
}
unsigned long mysmb_snapshot_crc(const mysmb_io_u8 *bytes, mysmb_io_u16 size)
{
    unsigned long crc;
    mysmb_io_u16 i;
    crc=0xffffffffUL;
    for (i=0U;i<size;++i) crc=crc_add(crc,bytes[i]);
    return crc^0xffffffffUL;
}
static unsigned long parts_crc(const mysmb_io_u8 *header,
    const mysmb_io_u8 *payload,mysmb_io_u16 size)
{
    unsigned long crc;
    mysmb_io_u16 i;
    crc=0xffffffffUL;
    for (i=0U;i<32U;++i) crc=crc_add(crc,header[i]);
    for (i=0U;i<size;++i) crc=crc_add(crc,payload[i]);
    return crc^0xffffffffUL;
}
int mysmb_snapshot_real_valid(const mysmb_io_u8 *bytes)
{
    mysmb_io_u16 exponent;
    unsigned int i,bits;
    if (bytes[0]>1U) return 0;
    exponent=mysmb_snapshot_get16(bytes+1);
    if (exponent==0U) {
        for (i=0U;i<MYSMB_SNAPSHOT_REAL_BYTES;++i)
            if (bytes[i]!=0U) return 0;
        return 1;
    }
    if (exponent>2098U || bytes[9]<0x10U || bytes[9]>0x1fU) return 0;
    /* Subnormal values must be exact multiples of the minimum quantum. */
    bits=exponent<53U ? 53U-exponent:0U;
    for (i=0U;i<bits;++i)
        if ((bytes[3U+i/8U]&(1U<<(i%8U)))!=0U) return 0;
    return 1;
}
static int payload_valid(const mysmb_io_u8 *payload)
{
    const mysmb_io_u8 *audio;
    unsigned int i;
    audio=payload+MYSMB_SNAPSHOT_CORE_BYTES;
    if (audio[0]>1U) return 0;
    if (audio[0]==0U) {
        for (i=1U;i<MYSMB_SNAPSHOT_AUDIO_BYTES;++i)
            if (audio[i]!=0U) return 0;
    }
    else for (i=0U;i<6U;++i)
        if (!mysmb_snapshot_real_valid(audio+MYSMB_SNAPSHOT_AUDIO_REAL_OFFSET+
            i*MYSMB_SNAPSHOT_REAL_BYTES)) return 0;
    return 1;
}
int mysmb_snapshot_encode_header(const struct mysmb_io_snapshot *snapshot,
    mysmb_io_u8 *file)
{
    if (!payload_valid(snapshot->payload))
        return MYSMB_SNAPSHOT_INVALID;
    memcpy(file,snapshot_magic,8U);
    mysmb_snapshot_put16(file+8,2U);
    mysmb_snapshot_put16(file+10,2U);
    mysmb_snapshot_put32(file+12,MYSMB_SNAPSHOT_PAYLOAD_BYTES);
    memcpy(file+16,snapshot->fingerprint,16U);
    mysmb_snapshot_put32(file+32,parts_crc(file,snapshot->payload,
        MYSMB_SNAPSHOT_PAYLOAD_BYTES));
    return MYSMB_SNAPSHOT_OK;
}
mysmb_io_u16 mysmb_snapshot_header_payload(const mysmb_io_u8 *file)
{
    mysmb_io_u16 version,payload;
    version=mysmb_snapshot_get16(file+8);
    if(version!=1U && version!=2U)return 0U;
    payload=version==2U?MYSMB_SNAPSHOT_PAYLOAD_BYTES:MYSMB_SNAPSHOT_PRESENTATION_OFFSET;
    if(memcmp(file,snapshot_magic,8U)!=0 ||
        mysmb_snapshot_get16(file+10)!=version ||
        mysmb_snapshot_get32(file+12)!=payload)return 0U;
    return payload;
}
int mysmb_snapshot_check_parts(const mysmb_io_u8 *file,
    const mysmb_io_u8 *payload,mysmb_io_u16 size,const mysmb_io_u8 *fingerprint)
{
    if(!size || mysmb_snapshot_header_payload(file)!=size)return MYSMB_SNAPSHOT_INVALID;
    if(parts_crc(file,payload,size)!=mysmb_snapshot_get32(file+32))return MYSMB_SNAPSHOT_INTEGRITY;
    if(memcmp(file+16,fingerprint,16U)!=0)return MYSMB_SNAPSHOT_RESOURCE;
    if(!payload_valid(payload))return MYSMB_SNAPSHOT_INVALID;
    return MYSMB_SNAPSHOT_OK;
}
int mysmb_snapshot_encode(const struct mysmb_io_snapshot *snapshot,
    mysmb_io_u8 *file, mysmb_io_u16 size)
{
    int result;
    if(size!=MYSMB_SNAPSHOT_FILE_BYTES)return MYSMB_SNAPSHOT_INVALID;
    result=mysmb_snapshot_encode_header(snapshot,file);
    if(result!=MYSMB_SNAPSHOT_OK)return result;
    memcpy(file+MYSMB_SNAPSHOT_HEADER_BYTES,snapshot->payload,MYSMB_SNAPSHOT_PAYLOAD_BYTES);
    return MYSMB_SNAPSHOT_OK;
}
int mysmb_snapshot_decode(const mysmb_io_u8 *file, mysmb_io_u16 size,
    const mysmb_io_u8 *fingerprint, struct mysmb_io_snapshot *snapshot)
{
    mysmb_io_u16 payload,version;
    int result;
    if (size!=MYSMB_SNAPSHOT_FILE_BYTES && size!=MYSMB_SNAPSHOT_LEGACY_FILE_BYTES)
        return MYSMB_SNAPSHOT_INVALID;
    version=size==MYSMB_SNAPSHOT_FILE_BYTES?2U:1U;
    payload=(mysmb_io_u16)(size-MYSMB_SNAPSHOT_HEADER_BYTES);
    result=mysmb_snapshot_check_parts(file,file+MYSMB_SNAPSHOT_HEADER_BYTES,payload,fingerprint);
    if(result!=MYSMB_SNAPSHOT_OK)return result;
    memcpy(snapshot->fingerprint,file+16,16U);
    memcpy(snapshot->payload,file+MYSMB_SNAPSHOT_HEADER_BYTES,
        payload);
    if(version==1U)memset(snapshot->payload+MYSMB_SNAPSHOT_PRESENTATION_OFFSET,
        0,MYSMB_SNAPSHOT_PRESENTATION_BYTES);
    return MYSMB_SNAPSHOT_OK;
}
void mysmb_snapshot_cache_initialize(struct mysmb_io_snapshot_cache *cache)
{
    cache->valid=0U;cache->published=0;
}
struct mysmb_io_snapshot *mysmb_snapshot_cache_staging(struct mysmb_io_snapshot_cache *cache,
    struct mysmb_io_snapshot *spare)
{
    return cache->published==spare?&cache->last_running:spare;
}
void mysmb_snapshot_cache_publish(struct mysmb_io_snapshot_cache *cache,
    struct mysmb_io_snapshot *completed)
{
    cache->published=completed;cache->valid=1U;
}
void mysmb_snapshot_cache_update(struct mysmb_io_snapshot_cache *cache,
    const struct mysmb_io_snapshot *snapshot, mysmb_io_u8 running_boundary)
{
    if (running_boundary!=0U) {
        cache->last_running=*snapshot;
        cache->published=0;
        cache->valid=1U;
    }
}
const struct mysmb_io_snapshot *mysmb_snapshot_cache_current(
    const struct mysmb_io_snapshot_cache *cache)
{
    return cache->valid!=0U ? (cache->published?cache->published:&cache->last_running):0;
}
