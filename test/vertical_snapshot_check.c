#include "game/player.h"
#include "game/enemy/movement.h"
#include "game/world/world.h"
#include <stdio.h>
#include <string.h>

static unsigned int failures;
static void compare(const unsigned char *actual, const unsigned char *expected)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) {
        /* Hardware stack is not portable RAM; persistent score bytes are. */
        if (i >= 0x100U && i < 0x200U && (i < 0x133U || i > 0x139U)) continue;
        if (actual[i] != expected[i]) {
            printf("%04x original=%02x native=%02x\n", i,
                   (unsigned int)expected[i], (unsigned int)actual[i]);
            ++failures;
        }
    }
}

#ifdef MYSMB_CALLER_CHECK
static unsigned char records[1][4098];
static unsigned int count, calls, kind;
static void child(struct mysmb_game *g, mysmb_u8 id, mysmb_u8 offset)
{
    unsigned char *r;
    if (calls >= count) { ++failures; return; }
    r = records[calls++];
    if (r[0] != id || r[1] != offset) ++failures;
    compare(g->ram, r + 2U);
    memcpy(g->ram, r + 2050U, 2048U);
}
void mysmb_world_impose_gravity_spr_object(struct mysmb_game *g,
    mysmb_u8 offset, mysmb_u8 force, mysmb_u8 maximum)
{
    if (force != g->ram[0U] || maximum !=
        (kind == 0U ? 4U : (kind == 5U || kind == 6U ? 2U : 3U))) ++failures;
    child(g, 1U, offset);
}
void mysmb_world_red_gravity(struct mysmb_game *g, mysmb_u8 offset,
                            mysmb_u8 direction)
{
    if (direction != (kind == 4U ? 1U : 0U)) ++failures;
    child(g, 2U, offset);
}
void mysmb_world_impose_gravity_block(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; (void)slot; ++failures; }
void mysmb_world_impose_gravity_misc(struct mysmb_game *g, mysmb_u8 slot,
                                    mysmb_u8 force, mysmb_u8 maximum)
{ (void)g; (void)slot; (void)force; (void)maximum; ++failures; }
#endif

int main(int argc, char **argv)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned char header[8];
    FILE *f;
#ifdef MYSMB_CALLER_CHECK
    if (argc != 3) return 64;
    f = fopen(argv[2], "rb"); if (f == NULL) return 65;
    if (fread(header, 1, 8, f) != 8 || memcmp(header, "MSVC\1", 5) != 0 ||
        header[5] > 1U) return 66;
    count = header[5];
    if (count && fread(records[0], 1, 4098, f) != 4098) return 66;
    if (fgetc(f) != EOF) return 66;
    fclose(f);
#else
    if (argc != 2) return 64;
#endif
    f = fopen(argv[1], "rb"); if (f == NULL) return 65;
    if (fread(header, 1, 8, f) != 8 || memcmp(header, "MSVP\1", 5) != 0) return 66;
    memset(&g, 0, sizeof(g));
    if (fread(g.ram, 1, 2048, f) != 2048 ||
        fread(expected, 1, 2048, f) != 2048 || fgetc(f) != EOF) return 66;
    fclose(f);
#ifdef MYSMB_CALLER_CHECK
    kind = header[5];
#endif
    switch (header[5]) {
    case 0U: mysmb_player_move_vertically(&g); break;
    case 1U: mysmb_enemy_move_d_vertically(&g, header[6]); break;
    case 2U: mysmb_enemy_move_falling_platform(&g, header[6]); break;
    case 3U: mysmb_enemy_move_red_down(&g, header[6]); break;
    case 4U: mysmb_enemy_move_red_up(&g, header[6]); break;
    case 5U: mysmb_enemy_move_drop_platform(&g, header[6]); break;
    case 6U: mysmb_enemy_move_slow_vertically(&g, header[6]); break;
    case 7U: mysmb_enemy_move_j_vertically(&g, header[6]); break;
    default: return 66;
    }
    compare(g.ram, expected);
#ifdef MYSMB_CALLER_CHECK
    if (calls != count) ++failures;
#endif
    return failures ? 1 : 0;
}
