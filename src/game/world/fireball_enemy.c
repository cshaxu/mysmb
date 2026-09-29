#include "game/world/world.h"

/* ROM $D6D9-$D735: FireballEnemyCollision through ExitFBallEnemy.
 * The saved fireball box survives both children; $01 and ObjectOffset
 * remain live RAM inputs after a child returns. A hit does not end the scan.
 * Collision geometry and hit response retain their separate owners. */
void mysmb_world_fireball_enemy_collision(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_u8 enemy;
    mysmb_u8 id;
    mysmb_u8 box;
    mysmb_u16 fireball_box;

    if (game->ram[0x0024U + slot] == 0U ||
        (game->ram[0x0024U + slot] & 0x80U) != 0U ||
        (game->ram[0x0009U] & 1U) != 0U) return;

    box = (mysmb_u8)(slot * 4U + 0x1cU);
    fireball_box = (mysmb_u16)(0x04acU + box);
    enemy = 4U;
    do {
        game->ram[0x0001U] = enemy;
        id = game->ram[0x0016U + enemy];
        if ((game->ram[0x001eU + enemy] & 0x20U) == 0U &&
            game->ram[0x000fU + enemy] != 0U &&
            (id < 0x24U || id >= 0x2bU) &&
            (id != 6U || game->ram[0x001eU + enemy] < 2U) &&
            game->ram[0x03d8U + enemy] == 0U) {
            box = (mysmb_u8)(enemy * 4U + 4U);
            if (mysmb_world_boxes_collide(game,
                    (mysmb_u16)(0x04acU + box), fireball_box) != 0U) {
                slot = game->ram[0x0008U];
                game->ram[0x0024U + slot] = 0x80U;
                mysmb_world_handle_fireball_enemy_hit(game, game->ram[0x0001U]);
            }
        }
        enemy = (mysmb_u8)(game->ram[0x0001U] - 1U);
    } while ((enemy & 0x80U) == 0U);
}
