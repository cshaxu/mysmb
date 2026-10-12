#include "platform/win32/audio_snapshot_real.h"
#include <float.h>
#include <math.h>
#include <string.h>

int mysmb_snapshot_put_real(mysmb_io_u8 *bytes, double value)
{
    mysmb_io_u8 encoded[MYSMB_SNAPSHOT_REAL_BYTES];
    double fraction, high_part;
    unsigned long high,low;
    int exponent;
    unsigned int i;
    if (value!=value || value>DBL_MAX || value< -DBL_MAX) return 0;
    memset(encoded,0,sizeof(encoded));
    if (value!=0.0) {
        encoded[0]=(mysmb_io_u8)(value<0.0);
        fraction=frexp(value<0.0 ? -value:value,&exponent);
        if (exponent< -1073 || exponent>1024) return 0;
        fraction=ldexp(fraction,53);
        high_part=floor(fraction/4294967296.0);
        high=(unsigned long)high_part;
        low=(unsigned long)(fraction-high_part*4294967296.0);
        mysmb_snapshot_put16(encoded+1,(mysmb_io_u16)(exponent+1074));
        mysmb_snapshot_put32(encoded+3,low);
        for (i=0U;i<3U;++i) {encoded[7U+i]=(mysmb_io_u8)high;high>>=8U;}
    }
    memcpy(bytes,encoded,sizeof(encoded));
    return 1;
}
int mysmb_snapshot_get_real(const mysmb_io_u8 *bytes, double *value)
{
    mysmb_io_u8 check[MYSMB_SNAPSHOT_REAL_BYTES];
    unsigned long high,low;
    mysmb_io_u16 exponent;
    double decoded;
    if (bytes[0]>1U) return 0;
    exponent=mysmb_snapshot_get16(bytes+1);
    low=mysmb_snapshot_get32(bytes+3);
    high=(unsigned long)bytes[7]|((unsigned long)bytes[8]<<8U)|
        ((unsigned long)bytes[9]<<16U);
    if (exponent==0U) {
        if (bytes[0]!=0U || high!=0UL || low!=0UL) return 0;
        decoded=0.0;
    }
    else {
        if (exponent>2098U || high<0x100000UL || high>0x1fffffUL) return 0;
        decoded=ldexp((double)high*4294967296.0+(double)low,
            (int)exponent-1074-53);
        if (bytes[0]!=0U) decoded= -decoded;
        if (!mysmb_snapshot_put_real(check,decoded) ||
            memcmp(check,bytes,sizeof(check))!=0) return 0;
    }
    *value=decoded;
    return 1;
}
