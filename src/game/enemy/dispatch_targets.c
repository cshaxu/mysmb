#include "game/enemy/core.h"
#include "game/enemy/actor_slots.h"
#include "game/objects.h"
#include "game/oam/oam.h"

/* ROM $C8D7 RunRetainerObj: three original child calls in source order. */
void mysmb_objects_draw_retainer(struct mysmb_game *game, mysmb_u8 slot)
{
    mysmb_oam_get_enemy_offscreen_bits(game, slot);
    mysmb_oam_relative_enemy_position(game, slot);
    (void)mysmb_objects_draw_normal_enemy_graphics(game, slot);
}
