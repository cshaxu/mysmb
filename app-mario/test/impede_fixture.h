#ifndef MYSMB_IMPEDE_FIXTURE_H
#define MYSMB_IMPEDE_FIXTURE_H

static void mysmb_impede_inputs(unsigned char *r, unsigned int n)
{
    static const unsigned char speeds[4] = { 0U, 0x80U, 0x81U, 0x7fU };
    r[0U] = n < 512U ? (unsigned char)(1U + n / 256U) : (unsigned char)n;
    r[0x57U] = n < 512U ? (unsigned char)n : speeds[(n / 64U) & 3U];
    r[0x86U] = (n & 1U) ? 255U : 0U;
    r[0x6dU] = (n & 2U) ? 255U : 0U;
    r[0x785U] = 0xa5U; r[0x490U] = (unsigned char)(n / 4U);
    if (n >= 768U) {
        r[0U] = (n & 1U) ? 1U : 2U;
        r[0x57U] = 0U; r[0x86U] = (unsigned char)n;
    }
}
static int mysmb_impede_argument(const char *text)
{
    static const char prefix[] = "--fixture=t43-impede=";
    unsigned int i, value, digits;
    for (i = 0U; prefix[i]; ++i) if (text[i] != prefix[i]) return 0;
    value = digits = 0U;
    while (text[i] >= '0' && text[i] <= '9' && digits < 4U) {
        value = value * 10U + (unsigned int)(text[i++] - '0'); ++digits;
    }
    return digits && !text[i] && value < 1024U ? (int)value + 1 : 0;
}
#endif
