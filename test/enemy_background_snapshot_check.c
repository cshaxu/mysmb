#include "game/enemy/background.h"
#include "game/enemy/distance.h"
#include "game/objects.h"
#include "game/world/world.h"
#include "smb1_local_rom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Original CPU snapshots are ignored local inputs, never tracked fixtures.
 * Caller mode replays immediate children, actual mode executes their C owners. */
static struct mysmb_game game;
static unsigned char records[65][4112];
static unsigned int count, cursor, failures;

static void compare(const unsigned char *expected, const char *where)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
        if (game.ram[i] != expected[i]) {
            if (failures < 16U) printf("%s %04x original=%02x native=%02x\n",
                where, i, (unsigned int)expected[i], (unsigned int)game.ram[i]);
            ++failures;
        }
    }
}
static void terrain_from_ram(struct mysmb_enemy_terrain *terrain, mysmb_u8 a)
{
    terrain->metatile = a;
    terrain->contact_low_nibble = game.ram[4U];
    terrain->block_address_low = game.ram[6U];
    terrain->block_row_offset = game.ram[2U];
    terrain->block_address = (mysmb_u16)(game.ram[6U] +
        256U * game.ram[7U] + game.ram[2U]);
}
#ifndef MYSMB_BACKGROUND_ACTUAL
static unsigned char *child(unsigned int pc, unsigned int slot, int source_a)
{
    unsigned char *r;
    if (++cursor > count) { printf("unexpected child %04x\n", pc); exit(2); }
    r = records[cursor];
    if (r[0] + 256U * r[1] != pc || r[3] != slot ||
        (source_a >= 0 && r[2] != (unsigned int)source_a)) {
        printf("child %u expected=%04x/%u/%02x got=%04x/%u/%02x\n", cursor,
            r[0] + 256U * r[1], (unsigned int)r[3], (unsigned int)r[2],
            pc, slot, (unsigned int)source_a); ++failures;
    }
    compare(r + 16U, "child-entry");
    memcpy(game.ram, r + 2064U, 2048U);
    return r;
}
mysmb_u8 mysmb_world_query_enemy_block(struct mysmb_game *g, mysmb_u8 slot,
    mysmb_u8 adder, mysmb_u8 horizontal, struct mysmb_enemy_terrain *terrain)
{
    unsigned char *r;
    (void)g;
    if (adder != 0x15U || horizontal != 0U) ++failures;
    r = child(0xe1aeU, slot, -1);
    terrain_from_ram(terrain, r[6]);
    return 1U;
}
mysmb_u8 mysmb_objects_is_solid_terrain(mysmb_u8 tile)
{
    unsigned char *r;
    r = child(0xe1b5U, records[0][3], tile);
    return (mysmb_u8)((r[9] & 2U) == 0U);
}
void mysmb_objects_enemy_no_ground(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; (void)child(0xe0e2U, slot, -1); }
void mysmb_objects_enemy_land_from_probe(struct mysmb_game *g, mysmb_u8 slot,
    const struct mysmb_enemy_terrain *terrain)
{ (void)g; (void)child(0xe067U, slot, terrain->metatile); }
void mysmb_objects_kill_enemy_above_block(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; (void)child(0xe18eU, slot, 6); }
void mysmb_objects_step_enemy_jump_terrain(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; (void)child(0xe163U, slot, -1); }
void mysmb_objects_step_hammer_terrain(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; (void)child(0xe185U, slot, -1); }
void mysmb_objects_setup_floatey_from_relative(struct mysmb_game *g,
    mysmb_u8 slot, mysmb_u8 score)
{
    unsigned char *r;
    (void)g; r = child(0xda11U, slot, score);
    if (r[6] != game.ram[0x3aeU]) ++failures;
}
mysmb_u8 mysmb_enemy_player_difference(struct mysmb_game *g, mysmb_u8 slot)
{ (void)g; return child(0xe143U, slot, -1)[6]; }
#endif

int main(int argc, char **argv)
{
    FILE *file;
    unsigned char header[8];
    struct mysmb_enemy_terrain terrain;
    unsigned int entry;
    if (argc != 2) return 64;
    file = fopen(argv[1], "rb"); if (!file) return 65;
    if (fread(header, 1U, 8U, file) != 8U || memcmp(header, "MS!B\1", 5U)) return 66;
    count = header[5];
    if (count > 64U || fread(records, 4112U, count + 1U, file) != count + 1U ||
        fgetc(file) != EOF) return 66;
    fclose(file);
    game.area_prg = mysmb_local_prg; game.area_prg_size = MYSMB_LOCAL_PRG_SIZE;
    memcpy(game.ram, records[0] + 16U, 2048U);
    entry = records[0][0] + 256U * records[0][1];
    if (entry == 0xdfc1U) mysmb_objects_enemy_background_current(&game, records[0][3]);
    else if (entry == 0xdffaU) {
        terrain_from_ram(&terrain, records[0][2]);
        mysmb_enemy_handle_background(&game, records[0][3], &terrain);
    } else return 67;
#ifndef MYSMB_BACKGROUND_ACTUAL
    if (cursor != count) { printf("children %u/%u\n", cursor, count); ++failures; }
#else
    (void)cursor;
#endif
    compare(records[0] + 2064U, "root-exit");
    return failures ? 1 : 0;
}
