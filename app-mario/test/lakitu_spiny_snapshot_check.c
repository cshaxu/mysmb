#include "core/enemy/frenzy.h"
#include "core/enemy/init_targets.h"
#include <stdio.h>
#include <string.h>

/* Host-only GCC instrumentation observes the production caller's child
 * entries. Recorded original child returns are substituted explicitly.
 * This proves the caller boundary only; enemy_loop_actual_check retains
 * every failure from executing the actual, unmodified native children. */
static struct mysmb_game game;
static unsigned char children[4][4098], expected[2048];
static unsigned int count, next_child, active, failed;
static void *active_function;

static int portable(unsigned int i)
{
    return i < 0x100U || i >= 0x200U || (i >= 0x109U && i <= 0x139U);
}

static unsigned int child_id(void *function)
{
    void (*entries[4])(void);
    void *address;
    unsigned int i;
    entries[0] = (void (*)(void))mysmb_enemy_setup_lakitu;
    entries[1] = (void (*)(void))mysmb_enemy_put_at_right_extent;
    entries[2] = (void (*)(void))mysmb_enemy_player_lakitu_difference;
    entries[3] = (void (*)(void))mysmb_enemy_init_small_box;
    if (sizeof(address) != sizeof(entries[0])) return 0U;
    for (i = 0U; i < 4U; ++i) {
        memcpy(&address, &entries[i], sizeof(address));
        if (function == address) return i + 1U;
    }
    return 0U;
}

void __cyg_profile_func_enter(void *function, void *caller)
{
    unsigned int id, i;
    (void)caller;
    if (active) return;
    id = child_id(function);
    if (id == 0U) return;
    if (next_child >= count || children[next_child][0] != id) {
        printf("unexpected child %u at index %u\n", id, next_child);
        failed = 1U;
        return;
    }
    for (i = 0U; i < 2048U; ++i) if (portable(i) &&
        game.ram[i] != children[next_child][2U + i]) {
        printf("child=%u incoming RAM=%04x original=%02x native=%02x\n",
            id, i, (unsigned int)children[next_child][2U + i],
            (unsigned int)game.ram[i]);
        failed = 1U;
    }
    active = 1U;
    active_function = function;
}

void __cyg_profile_func_exit(void *function, void *caller)
{
    unsigned int i;
    (void)caller;
    if (!active || function != active_function) return;
    for (i = 0U; i < 2048U; ++i)
        if (portable(i)) game.ram[i] = children[next_child][2050U + i];
    ++next_child;
    active = 0U;
}

int main(int argc, char **argv)
{
    FILE *file;
    unsigned char header[8];
    unsigned int slot, i;
    if (argc != 3) return 64;
    file = fopen(argv[1], "rb");
    if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MSAP\1", 5)) return 66;
    slot = header[6];
    if (fread(game.ram, 1, 2048, file) != 2048 ||
        fread(expected, 1, 2048, file) != 2048 || fgetc(file) != EOF) return 66;
    fclose(file);
    file = fopen(argv[2], "rb");
    if (!file) return 65;
    if (fread(header, 1, 8, file) != 8 || memcmp(header, "MSAC\1", 5)) return 66;
    count = header[5];
    if (count > 4U) return 66;
    for (i = 0U; i < count; ++i)
        if (fread(children[i], 1, 4098, file) != 4098) return 66;
    if (fgetc(file) != EOF) return 66;
    fclose(file);
    mysmb_enemy_init_lakitu_spiny_frenzy(&game, (mysmb_u8)slot);
    if (next_child != count || active) failed = 1U;
    for (i = 0U; i < 2048U; ++i) if (portable(i) && game.ram[i] != expected[i]) {
        printf("return RAM=%04x original=%02x native=%02x\n", i,
            (unsigned int)expected[i], (unsigned int)game.ram[i]);
        failed = 1U;
    }
    return failed ? 1 : 0;
}
