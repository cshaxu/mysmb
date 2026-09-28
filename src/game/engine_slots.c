#include "game/dispatcher.h"
#include "game/enemy/core.h"
#include "game/fireball/fireball.h"
#include "game/objects.h"

/* ROM $aefe-$af0f: ProcFireball_Bubble followed by ProcELoop. The caller
 * owns X=0..5 and the ObjectOffset store before each enemy/floatey pair. */
void mysmb_game_engine_actors(struct mysmb_game *game,
                               const struct mysmb_area_source *source)
{
    mysmb_u8 slot;

    mysmb_fireball_step(game);
    for (slot = 0U; slot < 6U; ++slot) {
        game->ram[0x0008U] = slot;
        mysmb_enemy_core_step_slot(game, source, slot);
        mysmb_objects_step_floatey_number(game, slot);
    }
}

/* ROM GameEngine's two explicit BlockObjectsCore calls. Even an inactive
 * block receives its caller's ObjectOffset write before returning. */
void mysmb_game_engine_blocks(struct mysmb_game *game)
{
    game->ram[0x0008U] = 1U;
    mysmb_objects_step_block(game, 1U);
    game->ram[0x0008U] = 0U;
    mysmb_objects_step_block(game, 0U);
}
