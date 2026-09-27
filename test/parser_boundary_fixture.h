#ifndef MYSMB_PARSER_BOUNDARY_FIXTURE_H
#define MYSMB_PARSER_BOUNDARY_FIXTURE_H

/* Pointer+255 and pointer+0 select immutable bytes; pointer+1 is $fd.
 * Six original data-region positions x fresh / resident 0 / 1 / 127.
 * This changes source RAM only, not the ROM or CPU entry/return state. */
static void mysmb_parser_boundary_fixture(unsigned char *ram, unsigned char scenario)
{
    static const unsigned short pointers[6] = {
        0xa20eU, 0xa4ccU, 0xa68cU, 0xa9ccU, 0xaebeU, 0xa6f1U
    };
    static const unsigned char columns[6] = {8U, 7U, 6U, 0U, 12U, 0U};
    static const unsigned char page_bits[6] = {1U, 0U, 0U, 1U, 0U, 0U};
    static const unsigned char states[4] = {0xffU, 0U, 1U, 127U};
    unsigned char shape, variant, i, slot;
    shape = (unsigned char)(scenario / 4U);
    variant = (unsigned char)(scenario % 4U);
    slot = variant == 0U ? 2U : (unsigned char)(variant - 1U);
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
    ram[0x72aU] = (variant == 0U && page_bits[shape]) ? 0U : 1U;
    ram[0x72bU] = 0U;
    ram[0x72cU] = variant == 0U ? 255U : 1U;
    for (i = 0U; i < 3U; ++i) {
        ram[0x72dU + i] = 0U;
        ram[0x730U + i] = 0xffU;
    }
    ram[0x72dU + slot] = 255U;
    ram[0x730U + slot] = states[variant];
    ram[0x73fU] = 0U;
    ram[0xe7U] = (unsigned char)pointers[shape];
    ram[0xe8U] = (unsigned char)(pointers[shape] >> 8U);
    ram[0x74eU] = 1U;
}

static int mysmb_parser_boundary_argument(const char *text)
{
    static const char prefix[] = "--fixture=t30-parser-boundary=";
    unsigned int i, value;
    for (i = 0U; prefix[i] != '\0'; ++i)
        if (text[i] != prefix[i]) return 0;
    if (text[i] < '0' || text[i] > '9') return 0;
    value = (unsigned int)(text[i++] - '0');
    if (text[i] >= '0' && text[i] <= '9')
        value = value * 10U + (unsigned int)(text[i++] - '0');
    if (text[i] != '\0' || value > 23U) return 0;
    return (int)value + 1;
}
#endif
