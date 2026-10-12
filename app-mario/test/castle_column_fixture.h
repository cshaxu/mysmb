#ifndef MYSMB_CASTLE_COLUMN_FIXTURE_H
#define MYSMB_CASTLE_COLUMN_FIXTURE_H

/* Controlled source-RAM preconditions at the ordinary NMI boundary.
 * Offsets select existing L_CastleArea1 records in the owner ROM:
 * axe $a209, chain $a203, bridge $a201, empty block $a1bf.
 * No program bytes, CPU registers, PC or stack are replaced. */
static void mysmb_castle_column_fixture(unsigned char *ram, unsigned char kind)
{
    static const unsigned char offsets[4] = { 0x5aU, 0x54U, 0x52U, 0x10U };
    static const unsigned char columns[4] = { 13U, 12U, 0U, 7U };
    unsigned char entry;
    entry = kind < 4U ? kind : 2U;
    ram[0x0722U] = 0U;
    ram[0x0770U] = 1U;
    ram[0x0772U] = 3U;
    ram[0x000eU] = 8U;
    ram[0x0773U] = 0U;
    ram[0x071fU] = 8U;
    ram[0x0725U] = 1U;
    ram[0x0726U] = columns[entry];
    ram[0x0728U] = 0U;
    ram[0x072aU] = entry == 2U ? 0U : 1U;
    ram[0x072bU] = 0U;
    ram[0x072cU] = offsets[entry];
    ram[0x072dU] = 0U;
    ram[0x072eU] = 0U;
    ram[0x072fU] = 0U;
    ram[0x0730U] = 0xffU;
    ram[0x0731U] = 0xffU;
    ram[0x0732U] = 0xffU;
    ram[0x073fU] = 0U;
    ram[0x00e7U] = 0xafU;
    ram[0x00e8U] = 0xa1U;
    /* Already resident bridge: exercise the fixed-length helper's BPL
     * branch and the final column without reinitializing its length. */
    if (kind >= 4U) {
        ram[0x0726U] = kind == 4U ? 7U : 12U;
        ram[0x072aU] = 1U;
        ram[0x072bU] = 1U;
        ram[0x072cU] = 0x54U;
        ram[0x072fU] = 0x52U;
        ram[0x0732U] = kind == 4U ? 5U : 0U;
    }
}

#endif
