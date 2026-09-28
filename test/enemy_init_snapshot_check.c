#include "game/enemy/init.h"
#include "game/enemy/init_targets.h"
#include "game/enemy/frenzy.h"
#include "game/objects.h"
#include <stdio.h>
#include <string.h>

static unsigned char record[4098];
static unsigned int failures, calls, root_slot, root_id;
static void compare(const unsigned char *actual, const unsigned char *expected)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) {
        /* Hardware stack is not native game RAM; retain mapped $0133-$0139. */
        if (i >= 0x100U && i < 0x200U && (i < 0x133U || i > 0x139U)) continue;
        if (actual[i] != expected[i]) {
            printf("%04x original=%02x native=%02x\n", i,
                   (unsigned int)expected[i], (unsigned int)actual[i]);
            ++failures;
        }
    }
}
static void capture(struct mysmb_game *game, unsigned int target,
                    unsigned int slot, unsigned int y)
{
    unsigned int address;
    ++calls;
    address = (unsigned int)record[8U] + 256U * record[9U];
    if (calls != 1U || target != address || record[0] != root_id + 1U ||
        slot != (root_id == 0x2eU ? 0U : root_slot)) ++failures;
    if (root_id == 0x2fU && y != record[1]) ++failures;
    compare(game->ram, record + 2U);
    /* Explicit caller-only proof: replay the separately observed child return. */
    memcpy(game->ram, record + 2050U, 2048U);
}

void mysmb_enemy_init_frenzy(struct mysmb_game *game, mysmb_u8 slot)
{
    capture(game, 0xc7a0U, slot, 0U);
}

void mysmb_enemy_end_frenzy(struct mysmb_game *game, mysmb_u8 slot)
{
    capture(game, 0xc7b8U, slot, 0U);
}

void mysmb_objects_initialize_power_up(struct mysmb_game *game)
{
    capture(game, 0xbc60U, 0U, 0U);
}

void mysmb_objects_start_vine(struct mysmb_game *game, mysmb_u8 slot,
                              mysmb_u8 block_slot)
{
    capture(game, 0xb91eU, slot, block_slot);
}

/* Each stub represents an original target entry, not its implementation. */
#define TARGET_STUB(name, address) \
    void mysmb_enemy_init_##name(struct mysmb_game *game, mysmb_u8 slot) \
    { capture(game, address, slot, 0U); }

TARGET_STUB(normal, 0xc30eU)
TARGET_STUB(red_koopa, 0xc31eU)
TARGET_STUB(hammer_bro, 0xc328U)
TARGET_STUB(goomba, 0xc2f1U)
TARGET_STUB(bloober, 0xc342U)
TARGET_STUB(bullet_bill, 0xc36bU)
TARGET_STUB(cheep_cheep, 0xc375U)
TARGET_STUB(podoboo, 0xc2f7U)
TARGET_STUB(piranha_entry, 0xc787U)
TARGET_STUB(jump_green_ptroopa, 0xc7d1U)
TARGET_STUB(red_ptroopa, 0xc34aU)
TARGET_STUB(horizontal_fly_swim, 0xc33dU)
TARGET_STUB(lakitu, 0xc385U)
TARGET_STUB(balance_platform, 0xc7dfU)
TARGET_STUB(vertical_platform, 0xc812U)
TARGET_STUB(large_lift_up, 0xc83fU)
TARGET_STUB(large_lift_down, 0xc845U)
TARGET_STUB(horizontal_platform, 0xc80bU)
TARGET_STUB(drop_platform, 0xc803U)
TARGET_STUB(small_lift_up, 0xc84bU)
TARGET_STUB(small_lift_down, 0xc857U)
TARGET_STUB(bowser, 0xc549U)
TARGET_STUB(retainer, 0xc307U)

#undef TARGET_STUB

void mysmb_enemy_init_firebar_entry(struct mysmb_game *game, mysmb_u8 slot,
                                    mysmb_u8 long_entry)
{
    capture(game, long_entry != 0U ? 0xc459U : 0xc45cU, slot, 0U);
}

int main(int argc, char **argv)
{
    static struct mysmb_game game;
    static unsigned char expected[2048];
    unsigned char header[8];
    unsigned int target;
    FILE *file;
    if (argc != 3) return 64;
    file = fopen(argv[2], "rb");
    if (file == NULL) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MSZC\1", 5) ||
        header[5] != 1U || fread(record, 1, 4098, file) != 4098 ||
        fgetc(file) != EOF) return 66;
    fclose(file);
    file = fopen(argv[1], "rb");
    if (file == NULL) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MSZP\1", 5) ||
        fread(game.ram, 1, 2048, file) != 2048 ||
        fread(expected, 1, 2048, file) != 2048 || fgetc(file) != EOF) return 66;
    fclose(file);
    root_slot = header[6];
    if (root_slot >= 6U) return 66;
    root_id = game.ram[0x16U + root_slot];
    if (record[0] != root_id + 1U ||
        record[1] != (unsigned char)(root_id * 2U + 2U)) return 67;
    target = (unsigned int)record[8U] + 256U * record[9U];
    mysmb_enemy_checkpoint_loaded(&game, (mysmb_u8)root_slot);
    if (target == 0xc2f0U || target == 0xc881U) {
        if (calls != 0U) ++failures;
        compare(game.ram, record + 2U);
        compare(record + 2U, record + 2050U);
    } else if (calls != 1U) ++failures;
    compare(game.ram, expected);
    return failures ? 1 : 0;
}
