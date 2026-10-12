#ifndef MYSMB_BOWSER_CONTROL_FIXTURE_H
#define MYSMB_BOWSER_CONTROL_FIXTURE_H
#include "actor_dispatch_fixture.h"
static unsigned char mysmb_bowser_control_slot(unsigned int n)
{ return (unsigned char)((n & 1U) * 5U); }
static void mysmb_bowser_control_fixture(unsigned char *r, unsigned int n)
{ mysmb_actor_dispatch_fixture(r, 90U + (n & 1U)); }
/* Controlled RAM inputs at the naturally reached original RunBowser entry.
 * The same inputs apply with and without observation; no CPU/ROM patches. */
static void mysmb_bowser_control_inputs(unsigned char *r, unsigned int n)
{
    static const unsigned char ys[4] = {0x7f,0x80,0xdf,0xe0};
    static const unsigned char feet[4] = {0,1,2,255};
    static const unsigned char frames[5] = {0,1,3,4,16};
    static const unsigned char timers[4] = {0,1,2,32};
    static const unsigned char xs[6] = {0,0x7f,0x90,0xc7,0xc8,255};
    static const unsigned char origins[4] = {0,0x7f,0x90,0xc8};
    static const unsigned char ranges[4] = {0,0x20,0x40,0x80};
    unsigned char s;
    s = mysmb_bowser_control_slot(n);
    r[0x1eU+s] = (unsigned char)(n < 32U ? 0x20U : 0U);
    r[0xcfU+s] = ys[(n/2U)%4U]; r[0x747U] = (unsigned char)(n%17U == 0U);
    r[0x363U] = (unsigned char)(n%4U < 2U ? 0x80U : 0U);
    r[0x364U] = feet[(n/7U)%4U]; r[9U] = frames[(n/3U)%5U];
    r[0x78aU+s] = timers[(n/5U)%4U];
    r[0x365U] = (unsigned char)(n%3U == 0U ? 255U : n%3U);
    r[0x7a7U+s] = (unsigned char)((n/11U)%4U);
    r[0x87U+s] = xs[(n/13U)%6U]; r[0x366U] = origins[(n/17U)%4U];
    r[0x46U+s] = (unsigned char)(1U+(n/19U)%2U);
    r[0x6dU] = (unsigned char)((n/23U)%3U); r[0x6eU+s] = 1U;
    r[0x86U] = xs[(n/29U)%6U]; r[0x6dcU] = ranges[(n/31U)%4U];
    r[0x75fU] = (unsigned char)((n/37U)%8U);
    r[0x790U] = (unsigned char)(n%3U == 0U ? 1U : 0U);
    r[0x6ccU] = (unsigned char)((n/41U)%2U); r[0x367U] = (unsigned char)(n%8U);
}
static int mysmb_bowser_control_argument(const char *text)
{
    static const char prefix[] = "--fixture=t41-bowser-control=";
    unsigned int i, value, digits;
    for (i=0U;prefix[i]!='\0';++i) if(text[i]!=prefix[i]) return 0;
    value=digits=0U;
    while(text[i]>='0' && text[i]<='9' && digits<4U) {
        value=value*10U+(unsigned int)(text[i++]-'0');++digits;
    }
    if(!digits || text[i]!='\0' || value>=1024U) return 0;
    return (int)value+1;
}
#endif
