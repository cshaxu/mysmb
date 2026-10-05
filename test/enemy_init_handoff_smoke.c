#include "core/enemy/init.h"
#include "core/enemy/init_targets.h"
#include "core/enemy/frenzy.h"
#include "core/objects.h"
#include <string.h>

/* Original $C26C checkpoint and $C282 vector boundary, not child proof. */
static mysmb_u8 before_child[2048];
static unsigned int calls;
static unsigned int selected;
static unsigned int selected_slot;
static unsigned int selected_y;

static void capture(struct mysmb_game *game, unsigned int target,
                    unsigned int slot, unsigned int y)
{
    ++calls;
    selected = target;
    selected_slot = slot;
    selected_y = y;
    memcpy(before_child, game->ram, sizeof(before_child));
    game->ram[0x0600U] = 0xa7U;
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
TARGET_STUB(piranha_plant, 0xc787U)
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

int main(void)
{
    static struct mysmb_game game;
    static mysmb_u8 expected[2048];
    static const mysmb_u8 ids[55] = {
        0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U,
        0x08U, 0x09U, 0x0aU, 0x0bU, 0x0cU, 0x0dU, 0x0eU, 0x0fU,
        0x10U, 0x11U, 0x12U, 0x13U, 0x14U, 0x15U, 0x16U, 0x17U,
        0x18U, 0x19U, 0x1aU, 0x1bU, 0x1cU, 0x1dU, 0x1eU, 0x1fU,
        0x20U, 0x21U, 0x22U, 0x23U, 0x24U, 0x25U, 0x26U, 0x27U,
        0x28U, 0x29U, 0x2aU, 0x2bU, 0x2cU, 0x2dU, 0x2eU, 0x2fU,
        0x30U, 0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U
    };
    static const mysmb_u16 targets[55] = {
        0xc30eU, 0xc30eU, 0xc30eU, 0xc31eU, 0xc2f0U, 0xc328U, 0xc2f1U, 0xc342U,
        0xc36bU, 0xc2f0U, 0xc375U, 0xc375U, 0xc2f7U, 0xc787U, 0xc7d1U, 0xc34aU,
        0xc33dU, 0xc385U, 0xc7a0U, 0xc2f0U, 0xc7a0U, 0xc7a0U, 0xc7a0U, 0xc7a0U,
        0xc7b8U, 0xc2f0U, 0xc2f0U, 0xc45cU, 0xc45cU, 0xc45cU, 0xc45cU, 0xc459U,
        0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc7dfU, 0xc812U, 0xc83fU, 0xc845U,
        0xc80bU, 0xc803U, 0xc80bU, 0xc84bU, 0xc857U, 0xc549U, 0xbc60U, 0xb91eU,
        0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc2f0U, 0xc307U, 0xc881U
    };
    unsigned int i, slot, y;
    for (i = 0U; i < 55U; ++i) {
        for (slot = 0U; slot < 6U; ++slot) {
            for (y = 0U; y < 256U; ++y) {
                memset(&game, 0, sizeof(game));
                memset(game.ram, 0x5a, sizeof(game.ram));
                game.ram[0x16U + slot] = ids[i];
                game.ram[0xcfU + slot] = (mysmb_u8)y;
                memcpy(expected, game.ram, sizeof(expected));
                if (ids[i] < 0x15U) {
                    expected[0xcfU + slot] = (mysmb_u8)(y + 8U);
                    expected[0x3d8U + slot] = 1U;
                }
                expected[4U] = 0x81U;
                expected[5U] = 0xc2U;
                expected[6U] = (mysmb_u8)targets[i];
                expected[7U] = (mysmb_u8)(targets[i] >> 8U);
                calls = 0U;
                mysmb_enemy_checkpoint_loaded(&game, (mysmb_u8)slot);
                if (targets[i] == 0xc2f0U || targets[i] == 0xc881U) {
                    if (calls != 0U) return 1;
                } else {
                    if (calls != 1U || selected != targets[i]) return 2;
                    if (selected_slot != (ids[i] == 0x2eU ? 0U : slot))
                        return 3;
                    if (selected_y != (ids[i] == 0x2fU ? 0x60U : 0U))
                        return 4;
                    if (memcmp(before_child, expected, sizeof(expected)))
                        return 5;
                    expected[0x0600U] = 0xa7U;
                }
                if (memcmp(game.ram, expected, sizeof(expected))) return 6;
            }
        }
    }
    return 0;
}
