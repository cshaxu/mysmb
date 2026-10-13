#include "core/objects.h"
#include "core/area.h"
#include "core/enemy/loop.h"
#include "core/enemy/movement.h"
#include "core/enemy/init_targets.h"
#include "core/enemy/actor_slots.h"
#include <stdio.h>
#include <string.h>
static unsigned char records[8][4098];
static unsigned int count, calls, failures;
static void compare(const unsigned char *a, const unsigned char *z)
{
    unsigned int i;
    for (i = 0U; i < 2048U; ++i) {
        if (i >= 0x100U && i < 0x200U && (i < 0x109U || i > 0x139U)) continue;
        if (a[i] != z[i]) {
            printf("%04x original=%02x native=%02x\n",i,(unsigned int)z[i],(unsigned int)a[i]);
            ++failures;
        }
    }
}
static void child(struct mysmb_game *g, unsigned int id, unsigned int arg)
{
    unsigned char *r;
    if (calls >= count) { ++failures; return; }
    r = records[calls++];
    if (r[0] != id || (id != 1U && r[1] != arg)) ++failures;
    compare(g->ram, r + 2U);
    memcpy(g->ram, r + 2050U, 2048U);
}
void mysmb_enemy_kill_all(struct mysmb_game *g) { child(g, 1U, 0U); }
void mysmb_enemy_move_slow_vertically(struct mysmb_game *g, mysmb_u8 s)
{ child(g, 2U, s); }
void mysmb_objects_draw_bowsers_slot(struct mysmb_game *g, mysmb_u8 s)
{ child(g, 3U, s); }
void mysmb_area_rem_bridge(struct mysmb_game *g, mysmb_u8 graphics,
    mysmb_u8 y, mysmb_u8 low, mysmb_u8 high)
{
    if (graphics != 12U || g->ram[4U] != low || g->ram[5U] != high) ++failures;
    child(g, 4U, y);
}
void mysmb_area_move_v_offset(struct mysmb_game *g, mysmb_u8 y)
{ child(g, 5U, y); }
void mysmb_enemy_init_vertical_state(struct mysmb_game *g, mysmb_u8 s)
{ child(g, 6U, s); }
static int run_case(const char *snapshot_path, const char *calls_path)
{
    static struct mysmb_game g;
    static unsigned char expected[2048];
    unsigned char h[8]; FILE *f;
    count = calls = failures = 0U;
    f = fopen(calls_path, "rb"); if (!f) return 65;
    if (fread(h,1,8,f) != 8 || memcmp(h,"MSkC\1",5) || h[5] > 8U) return 66;
    count = h[5];
    if (fread(records,4098,count,f) != count || fgetc(f) != EOF) return 66;
    fclose(f); f = fopen(snapshot_path,"rb"); if (!f) return 65;
    if (fread(h,1,8,f) != 8 || memcmp(h,"MSkP\1",5) ||
        fread(g.ram,1,2048,f) != 2048 || fread(expected,1,2048,f) != 2048 ||
        fgetc(f) != EOF) return 66;
    fclose(f); (void)mysmb_objects_step_bridge_collapse(&g);
    compare(g.ram, expected); if (calls != count) ++failures;
    return failures ? 1 : 0;
}

int main(int argc, char **argv)
{
    FILE *manifest;
    char line[1024], *separator;
    unsigned int cases, failed;
    int result;
    if (argc == 3 && strcmp(argv[1], "--manifest") != 0)
        return run_case(argv[1], argv[2]);
    if (argc != 3 || strcmp(argv[1], "--manifest") != 0) return 64;
    manifest = fopen(argv[2], "r"); if (!manifest) return 65;
    cases = failed = 0U;
    while (fgets(line, sizeof(line), manifest) != 0) {
        separator = strchr(line, '\t');
        if (separator == 0) { fclose(manifest); return 66; }
        *separator++ = '\0';
        separator[strcspn(separator, "\r\n")] = '\0';
        if (line[0] == '\0' || separator[0] == '\0') {
            fclose(manifest); return 66;
        }
        result = run_case(line, separator);
        ++cases;
        if (result != 0) {
            ++failed;
            printf("case %u failed (%d)\n", cases - 1U, result);
        }
    }
    fclose(manifest);
    printf("bridge collapse manifest: %u cases, %u failures\n", cases, failed);
    return failed == 0U ? 0 : 1;
}
