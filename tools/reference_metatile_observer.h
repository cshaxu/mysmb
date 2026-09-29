#ifndef MYSMB_REFERENCE_METATILE_OBSERVER_H
#define MYSMB_REFERENCE_METATILE_OBSERVER_H

/* Passive original-entry observer. No machine state is modified. */
static unsigned char metatile_records[64][4112];
static unsigned short metatile_returns[64];
static unsigned int metatile_pending[64], metatile_count, metatile_depth;

static int metatile_observe(const unsigned char *ram, unsigned short pc,
    unsigned char a, unsigned char x, unsigned char y, unsigned char p,
    unsigned char stack)
{
    unsigned int index;
    unsigned char *record;
    if (metatile_depth) {
        index = metatile_pending[metatile_depth - 1U];
        record = metatile_records[index];
        if (pc == metatile_returns[index] &&
            stack == (unsigned char)(record[10] + 2U)) {
            record[6] = a; record[7] = x; record[8] = y; record[9] = p;
            memcpy(record + 2064U, ram, 2048U);
            --metatile_depth;
        }
    }
    if (pc != 0xdf8fU && pc != 0xdf9aU && pc != 0xdfa1U && pc != 0xdfb0U)
        return 1;
    if (metatile_count >= 64U || metatile_depth >= 64U) return 0;
    index = metatile_count++;
    record = metatile_records[index];
    record[0] = (unsigned char)pc; record[1] = (unsigned char)(pc >> 8U);
    record[2] = a; record[3] = x; record[4] = y; record[5] = p;
    record[10] = stack;
    memcpy(record + 16U, ram, 2048U);
    metatile_returns[index] = (unsigned short)(1U +
        ram[0x100U + (unsigned char)(stack + 1U)] +
        256U * ram[0x100U + (unsigned char)(stack + 2U)]);
    metatile_pending[metatile_depth++] = index;
    return 1;
}
static int metatile_write(const char *path)
{
    unsigned char header[8] = { 'M', 'S', 'M', 'C', 1U, 0U, 0U, 0U };
    FILE *file;
    int good;
    if (metatile_depth) return 0;
    header[5] = (unsigned char)metatile_count;
    file = fopen(path, "wb");
    if (!file) return 0;
    good = fwrite(header, 1U, 8U, file) == 8U &&
        fwrite(metatile_records, 4112U, metatile_count, file) == metatile_count;
    if (fclose(file)) good = 0;
    return good;
}
#endif
