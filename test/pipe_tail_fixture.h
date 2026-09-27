#ifndef MYSMB_PIPE_TAIL_FIXTURE_H
#define MYSMB_PIPE_TAIL_FIXTURE_H

/* Immutable data-region pairs consumed by the original parser. Source RAM
 * selects one resident pipe and a real terminal marker for the current
 * stream. Sixteen height/usage pairs x left/right column. No code/PC edits. */
static void mysmb_pipe_tail_fixture(unsigned char *ram, unsigned char scenario)
{
    static const unsigned short pointers[16] = {
        0xa9f9U, 0xa82aU, 0xac2aU, 0xa611U, 0xa42aU, 0xa682U, 0xad62U, 0xa67cU, 0xa4bcU, 0xabc7U, 0xa9f6U, 0xa454U, 0xad63U, 0xae41U, 0xa447U, 0xabd3U
    };
    static const unsigned char terminals[16] = {
        0x5U, 0x7U, 0xaU, 0x7U, 0x40U, 0xbU, 0x16U, 0x11U, 0x11U, 0xfU, 0x8U, 0x16U, 0x15U, 0x3U, 0x23U, 0x3U
    };
    static const unsigned char columns[16] = {
        0x6U, 0x6U, 0x9U, 0x6U, 0xeU, 0x6U, 0x4U, 0xaU, 0x9U, 0x0U, 0xaU, 0xaU, 0xfU, 0xcU, 0x4U, 0xcU
    };
    unsigned char shape, side, i;
    shape = (unsigned char)(scenario / 2U);
    side = (unsigned char)(scenario % 2U);
    ram[0x722U] = 0U;
    ram[0x770U] = 1U;
    ram[0x772U] = 1U;
    ram[0x73cU] = 8U;
    ram[0x71eU] = 0U;
    ram[0x00eU] = 8U;
    ram[0x773U] = 0U;
    ram[0x71fU] = 8U;
    ram[0x725U] = 1U;
    ram[0x726U] = columns[shape];
    ram[0x728U] = 0U;
    ram[0x72aU] = 1U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = terminals[shape];
    for (i = 0U; i < 3U; ++i) {
        ram[0x72dU+i] = 0U;
        ram[0x730U+i] = 0xffU;
    }
    ram[0x732U] = side == 0U ? 1U : 0U;
    ram[0x73fU] = 0U;
    ram[0xe7U] = (unsigned char)pointers[shape];
    ram[0xe8U] = (unsigned char)(pointers[shape] >> 8U);
    ram[0x74eU] = 1U;
    ram[0x760U] = 0U;
    ram[0x75fU] = 0U;
}

static int mysmb_pipe_tail_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-pipe-tail=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 31U) return 0;
    return (int)value + 1;
}
#endif
