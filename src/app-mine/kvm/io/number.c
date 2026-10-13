#include "number.h"
char *mine_number(char *out,int value,int minimum)
{
    char digits[6];
    unsigned int magnitude;
    int count=0;
    if(value<0){*out++='-';--minimum;magnitude=(unsigned int)(-(value+1))+1U;}
    else magnitude=(unsigned int)value;
    do {digits[count++]=(char)('0'+magnitude%10U);magnitude/=10U;}while(magnitude);
    while(minimum>count){*out++='0';--minimum;}
    while(count)*out++=digits[--count];
    *out=0;return out;
}
