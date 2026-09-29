#ifndef MYSMB_REFERENCE_ENEMY_BACKGROUND_OBSERVER_H
#define MYSMB_REFERENCE_ENEMY_BACKGROUND_OBSERVER_H

/* Root and immediate original child captures. These helpers only read CPU
 * state; all fixture input control is separate and also runs without them. */
static unsigned char background_records[65][4112];
static unsigned short background_return, background_child_return;
static unsigned int background_phase, background_child_active, background_count;

static void background_record_entry(unsigned char *out, const unsigned char *ram,
    unsigned short pc, unsigned char a, unsigned char x, unsigned char y,
    unsigned char p, unsigned char stack)
{
    out[0] = (unsigned char)pc; out[1] = (unsigned char)(pc >> 8U);
    out[2] = a; out[3] = x; out[4] = y; out[5] = p; out[10] = stack;
    memcpy(out + 16U, ram, 2048U);
}
static void background_record_exit(unsigned char *out, const unsigned char *ram,
    unsigned char a, unsigned char x, unsigned char y, unsigned char p)
{
    out[6] = a; out[7] = x; out[8] = y; out[9] = p;
    memcpy(out + 2064U, ram, 2048U);
}
static unsigned short background_return_pc(const unsigned char *r, unsigned char s)
{
    return (unsigned short)(1U + r[0x100U + (unsigned char)(s + 1U)] +
        256U * r[0x100U + (unsigned char)(s + 2U)]);
}
static int background_is_child(unsigned short pc)
{
    return pc == 0xe1aeU || pc == 0xe1b5U || pc == 0xe0e2U ||
        pc == 0xe067U || pc == 0xe18eU || pc == 0xda11U ||
        pc == 0xe143U || pc == 0xe163U || pc == 0xe185U;
}
static int background_observe(const unsigned char *ram, unsigned short pc,
    unsigned char a, unsigned char x, unsigned char y, unsigned char p,
    unsigned char stack, unsigned int n)
{
    unsigned char *record;
    unsigned short entry;
    entry = n < 1024U ? 0xdfc1U : 0xdffaU;
    if (!background_phase && pc == entry && x == ((n & 1U) ? 5U : 0U)) {
        background_record_entry(background_records[0], ram, pc, a, x, y, p, stack);
        background_return = background_return_pc(ram, stack);
        background_phase = 1U;
    }
    if (background_phase != 1U) return 1;
    if (background_child_active) {
        record = background_records[background_count];
        if (pc == background_child_return && stack == (unsigned char)(record[10] + 2U)) {
            background_record_exit(record, ram, a, x, y, p);
            background_child_active = 0U;
        }
    }
    if (pc == background_return &&
        stack == (unsigned char)(background_records[0][10] + 2U)) {
        if (background_child_active) return 0;
        background_record_exit(background_records[0], ram, a, x, y, p);
        background_phase = 2U;
        return 1;
    }
    if (!background_child_active && background_is_child(pc)) {
        if (background_count >= 64U) return 0;
        record = background_records[++background_count];
        background_record_entry(record, ram, pc, a, x, y, p, stack);
        background_child_return = background_return_pc(ram, stack);
        background_child_active = 1U;
    }
    return 1;
}
static int background_write(const char *path)
{
    unsigned char header[8] = { 'M', 'S', '!', 'B', 1U, 0U, 0U, 0U };
    FILE *file;
    int good;
    if (background_phase != 2U || background_child_active) return 0;
    header[5] = (unsigned char)background_count;
    file = fopen(path, "wb"); if (!file) return 0;
    good = fwrite(header, 1U, 8U, file) == 8U &&
        fwrite(background_records, 4112U, background_count + 1U, file) == background_count + 1U;
    if (fclose(file)) good = 0;
    return good;
}
#endif
