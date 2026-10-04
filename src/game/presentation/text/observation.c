#include "game/game.h"
#include "game/presentation/text/observation.h"
#include <string.h>

void mysmb_text_observer_enable(struct mysmb_game *game, unsigned char enabled)
{
    memset(&game->text_observer, 0, sizeof(game->text_observer));
    game->text_observer.enabled = enabled != 0U ? 1U : 0U;
}

void mysmb_text_observer_invalidate(struct mysmb_game *game)
{
    unsigned char enabled;
    enabled = game->text_observer.enabled;
    memset(&game->text_observer, 0, sizeof(game->text_observer));
    game->text_observer.enabled = enabled == 1U ? 1U : 0U;
}

void mysmb_text_observer_clear_producer(struct mysmb_game *game)
{
    if (game->text_observer.enabled != 1U) return;
    memset(&game->text_observer.producer, 0,
        sizeof(game->text_observer.producer));
}

void mysmb_text_observer_commit(struct mysmb_game *game)
{
    if (game->text_observer.enabled != 1U) return;
    game->text_observer.visible = game->text_observer.producer;
}

void mysmb_text_observer_record(struct mysmb_game *game,
    unsigned char family, unsigned char identity, unsigned char slot,
    unsigned char graphics, unsigned char facing, unsigned char oam,
    unsigned char sprites, unsigned char source_size)
{
    struct mysmb_text_observation_buffer *buffer;
    struct mysmb_text_observation *item;
    unsigned short i;
    unsigned short bytes;
    unsigned short record_index;
    unsigned short candidate;
    unsigned short owner;

    if (game->text_observer.enabled != 1U) return;
    buffer = &game->text_observer.producer;
    bytes = (unsigned short)(sprites * 4U);
    if (sprites == 0U || sprites > 8U || (oam & 3U) != 0U ||
        (unsigned short)(oam + bytes) > 256U ||
        buffer->count > MYSMB_TEXT_OBSERVATION_CAPACITY) {
        buffer->overflow = 1U;
        return;
    }
    /* These source entries have already been written by the caller. Release
     * their old receipts before searching for a reusable metadata slot. */
    for (i = 0U; i < sprites; ++i) buffer->owners[oam / 4U + i] = 0U;
    for (i = 0U; i < buffer->count; ++i)
        if (buffer->items[i].family == family &&
            buffer->items[i].slot == slot && buffer->items[i].oam == oam) break;
    if (i == buffer->count) {
        /* Reuse receipts whose entries were wholly superseded by a later
         * typed draw. At most 64 receipts can still own a sprite entry. */
        for (candidate = 0U; candidate < buffer->count; ++candidate) {
            for (owner = 0U; owner < 64U; ++owner)
                if (buffer->owners[owner] == candidate + 1U) break;
            if (owner == 64U) { i = candidate; break; }
        }
    }
    if (i == buffer->count) {
        if (i == MYSMB_TEXT_OBSERVATION_CAPACITY) {
            buffer->overflow = 1U;
            return;
        }
        buffer->count++;
    }
    item = &buffer->items[i];
    record_index = i;
    /* A repeated owner may shrink its span. Old entries outside the new
     * draw must not keep pointing at the replacement receipt. */
    for(owner=0U;owner<64U;++owner)
        if(buffer->owners[owner]==record_index+1U)buffer->owners[owner]=0U;
    memset(item, 0, sizeof(*item));
    item->family = family; item->identity = identity; item->slot = slot;
    item->graphics = graphics; item->facing = facing; item->oam = oam;
    item->sprites = sprites; item->source_size = source_size;
    for (i = 0U; i < bytes; ++i)
        item->entries[i] = game->ram[0x0200U + oam + i];
    for (i = 0U; i < sprites; ++i)
        buffer->owners[oam / 4U + i] = (unsigned char)(record_index + 1U);
}

unsigned char mysmb_text_observer_visible_mask(const struct mysmb_game *game,
    unsigned char index)
{
    const struct mysmb_text_observation *item;
    unsigned short i;
    unsigned short offset;
    unsigned char mask;

    if (game->text_observer.enabled != 1U ||
        index >= game->text_observer.visible.count ||
        index >= MYSMB_TEXT_OBSERVATION_CAPACITY) return 0U;
    item = &game->text_observer.visible.items[index];
    if (item->sprites > 8U ||
        (unsigned short)(item->oam + item->sprites * 4U) > 256U) return 0U;
    mask = 0U;
    for (i = 0U; i < item->sprites; ++i) {
        offset = (unsigned short)(i * 4U);
        if (game->text_observer.visible.owners[item->oam / 4U + i] !=
            (unsigned char)(index + 1U)) continue;
        if (item->entries[offset] >= 239U ||
            item->entries[offset + 1U] == 0xfcU) continue;
        if (memcmp(item->entries + offset,
            game->visible_oam + item->oam + offset, 4U) == 0)
            mask |= (unsigned char)(1U << i);
    }
    return mask;
}
