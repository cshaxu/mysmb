#include "game/enemy/loop.h"
#include "game/enemy/stream.h"
#include "game/enemy/init.h"
#include "game/objects.h"

/* ROM $C06B-$C08B and $9BF8: reverse-indexed castle-loop records. */
static const mysmb_u8 loop_world[11] = {3U,3U,6U,6U,6U,6U,6U,6U,7U,7U,7U};
static const mysmb_u8 loop_page[11] = {5U,9U,4U,5U,6U,8U,9U,10U,6U,11U,16U};
static const mysmb_u8 loop_y[11] = {0x40U,0xb0U,0xb0U,0x80U,0x40U,0x40U,
    0x80U,0x40U,0xf0U,0xf0U,0xf0U};
static const mysmb_u8 loop_offset[11] = {0x12U,0x36U,0x0eU,0x0eU,0x0eU,
    0x32U,0x32U,0x32U,0x0aU,0x26U,0x40U};

/* ROM $C08C ExecGameLoopback; no coordinate or scroll reconstruction. */
void mysmb_enemy_exec_loopback(struct mysmb_game *game, mysmb_u8 index)
{
    game->ram[0x006dU] = (mysmb_u8)(game->ram[0x006dU] - 4U);
    game->ram[0x0725U] = (mysmb_u8)(game->ram[0x0725U] - 4U);
    game->ram[0x071aU] = (mysmb_u8)(game->ram[0x071aU] - 4U);
    game->ram[0x071bU] = (mysmb_u8)(game->ram[0x071bU] - 4U);
    game->ram[0x072aU] = (mysmb_u8)(game->ram[0x072aU] - 4U);
    game->ram[0x073bU] = 0U;
    game->ram[0x072bU] = 0U;
    game->ram[0x0739U] = 0U;
    game->ram[0x073aU] = 0U;
    game->ram[0x072cU] = loop_offset[index];
}

/* ROM $D071 KillAllEnemies / KillLoop; EraseEnemyObject returns A zero. */
void mysmb_enemy_kill_all(struct mysmb_game *game)
{
    mysmb_u8 slot;
    slot = 4U;
    do {
        mysmb_objects_erase_enemy(game, slot);
        --slot;
    } while (slot < 0x80U);
    game->ram[0x06cbU] = 0U;
}

/* ROM $C0CC ProcLoopCommand through ChkEnemyFrenzy. The parser and
 * initializer remain separately owned successors of this caller chain. */
void mysmb_enemy_process_loop_command(struct mysmb_game *game,
    const struct mysmb_area_source *source, mysmb_u8 slot)
{
    mysmb_u8 index;
    if (game->ram[0x0745U] == 0U || game->ram[0x0726U] != 0U) goto frenzy;
    index = 11U;
find_loop:
    --index;
    if ((index & 0x80U) != 0U) goto frenzy;
    if (game->ram[0x075fU] != loop_world[index] ||
        game->ram[0x0725U] != loop_page[index]) goto find_loop;
    if (game->ram[0x00ceU] != loop_y[index] || game->ram[0x001dU] != 0U)
        goto wrong;
    if (game->ram[0x075fU] != 6U) goto init_multi;
    ++game->ram[0x06d9U];
inc_multi:
    ++game->ram[0x06daU];
    if (game->ram[0x06daU] != 3U) goto init_command;
    if (game->ram[0x06d9U] == 3U) goto init_multi;
    goto loopback;
wrong:
    if (game->ram[0x075fU] == 6U) goto inc_multi;
loopback:
    mysmb_enemy_exec_loopback(game, index);
    mysmb_enemy_kill_all(game);
    slot = game->ram[8U];
init_multi:
    game->ram[0x06daU] = 0U;
    game->ram[0x06d9U] = 0U;
init_command:
    game->ram[0x0745U] = 0U;
frenzy:
    if (game->ram[0x06cdU] != 0U) {
        game->ram[0x0016U + slot] = game->ram[0x06cdU];
        game->ram[0x000fU + slot] = 1U;
        game->ram[0x001eU + slot] = 0U;
        game->ram[0x06cdU] = 0U;
        /* Existing InitEnemyObject tail is state-zero then checkpoint. */
        mysmb_enemy_checkpoint_loaded(game, slot);
        return;
    }
    (void)mysmb_enemy_stream_process_current(game, source, slot);
}
