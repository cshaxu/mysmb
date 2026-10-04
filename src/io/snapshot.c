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
static unsigned long file_crc(const mysmb_io_u8 *file)
{
    unsigned long crc;
    mysmb_io_u16 i;
    crc=0xffffffffUL;
    for (i=0U;i<MYSMB_SNAPSHOT_FILE_BYTES;++i)
        if (i<32U || i>=36U) crc=crc_add(crc,file[i]);
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
int mysmb_snapshot_encode(const struct mysmb_io_snapshot *snapshot,
    mysmb_io_u8 *file, mysmb_io_u16 size)
{
    if (size!=MYSMB_SNAPSHOT_FILE_BYTES || !payload_valid(snapshot->payload))
        return MYSMB_SNAPSHOT_INVALID;
    memcpy(file,snapshot_magic,8U);
    mysmb_snapshot_put16(file+8,1U);
    mysmb_snapshot_put16(file+10,1U);
    mysmb_snapshot_put32(file+12,MYSMB_SNAPSHOT_PAYLOAD_BYTES);
    memcpy(file+16,snapshot->fingerprint,16U);
    memcpy(file+MYSMB_SNAPSHOT_HEADER_BYTES,snapshot->payload,
        MYSMB_SNAPSHOT_PAYLOAD_BYTES);
    mysmb_snapshot_put32(file+32,file_crc(file));
    return MYSMB_SNAPSHOT_OK;
}
int mysmb_snapshot_decode(const mysmb_io_u8 *file, mysmb_io_u16 size,
    const mysmb_io_u8 *fingerprint, struct mysmb_io_snapshot *snapshot)
{
    if (size!=MYSMB_SNAPSHOT_FILE_BYTES || memcmp(file,snapshot_magic,8U)!=0 ||
        mysmb_snapshot_get16(file+8)!=1U || mysmb_snapshot_get16(file+10)!=1U ||
        mysmb_snapshot_get32(file+12)!=MYSMB_SNAPSHOT_PAYLOAD_BYTES)
        return MYSMB_SNAPSHOT_INVALID;
    if (file_crc(file)!=mysmb_snapshot_get32(file+32))
        return MYSMB_SNAPSHOT_INTEGRITY;
    if (memcmp(file+16,fingerprint,16U)!=0) return MYSMB_SNAPSHOT_RESOURCE;
    if (!payload_valid(file+MYSMB_SNAPSHOT_HEADER_BYTES))
        return MYSMB_SNAPSHOT_INVALID;
    memcpy(snapshot->fingerprint,file+16,16U);
    memcpy(snapshot->payload,file+MYSMB_SNAPSHOT_HEADER_BYTES,
        MYSMB_SNAPSHOT_PAYLOAD_BYTES);
    return MYSMB_SNAPSHOT_OK;
}
void mysmb_snapshot_cache_initialize(struct mysmb_io_snapshot_cache *cache)
{
    cache->valid=0U;
}
void mysmb_snapshot_cache_update(struct mysmb_io_snapshot_cache *cache,
    const struct mysmb_io_snapshot *snapshot, mysmb_io_u8 running_boundary)
{
    if (running_boundary!=0U) {
        cache->last_running=*snapshot;
        cache->valid=1U;
    }
}
const struct mysmb_io_snapshot *mysmb_snapshot_cache_current(
    const struct mysmb_io_snapshot_cache *cache)
{
    return cache->valid!=0U ? &cache->last_running:0;
}
