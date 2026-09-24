#include "platform/dos16/dos16_root.h"

#ifdef MYSMB_DOS16_TARGET
#include <bios.h>
#define MYSMB_DOS16_FAR __far
#define MYSMB_DOS16_VGA_MEMORY ((mysmb_u8 __far *)0xa0000000L)
#define MYSMB_DOS16_TEXT_MEMORY ((mysmb_u8 __far *)0xb8000000L)
#else
#define MYSMB_DOS16_FAR
#endif

static struct mysmb_dos16_root mysmb_dos16_root;
struct mysmb_dos16_host {
    mysmb_u8 text_mode;
};
static struct mysmb_dos16_host mysmb_dos16_host;
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page0[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page1[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page2[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page3[MYSMB_VGA_PAGE_SIZE];

static mysmb_u8 mysmb_dos16_read_buttons(void *context)
{
#ifdef MYSMB_DOS16_TARGET
    unsigned key;
    struct mysmb_dos16_host *host;

    host = (struct mysmb_dos16_host *)context;
    if (_bios_keybrd(_KEYBRD_READY) == 0U) return 0U;
    key = _bios_keybrd(_KEYBRD_READ);
    switch ((key >> 8U) & 0xffU) {
    case 0x3bU: host->text_mode = host->text_mode == 0U ? 1U : 0U; return 0U;
    case 0x4bU: return MYSMB_BUTTON_LEFT;
    case 0x4dU: return MYSMB_BUTTON_RIGHT;
    case 0x48U: return MYSMB_BUTTON_UP;
    case 0x50U: return MYSMB_BUTTON_DOWN;
    case 0x1cU: return MYSMB_BUTTON_START;
    case 0x2cU: return MYSMB_BUTTON_A;
    case 0x2dU: return MYSMB_BUTTON_B;
    default: return 0U;
    }
#else
    (void)context;
    return 0U;
#endif
}

static void mysmb_dos16_present_vga(void *context, const struct mysmb_vga_frame *frame)
{
#ifdef MYSMB_DOS16_TARGET
    union REGS registers;
    mysmb_u16 page;
    mysmb_u16 offset;
    mysmb_u8 __far *video;

    if (((struct mysmb_dos16_host *)context)->text_mode != 0U) return;
    registers.h.ah = 0U;
    registers.h.al = 0x13U;
    int86(0x10, &registers, &registers);
    video = MYSMB_DOS16_VGA_MEMORY;
    for (page = 0U; page < MYSMB_VGA_PAGE_COUNT; ++page) {
        for (offset = 0U; offset < MYSMB_VGA_PAGE_SIZE; ++offset) {
            video[page * MYSMB_VGA_PAGE_SIZE + offset] = frame->pages[page][offset];
        }
    }
#else
    (void)context;
    (void)frame;
#endif
}

static void mysmb_dos16_present_text(void *context, const struct mysmb_text_frame *frame)
{
#ifdef MYSMB_DOS16_TARGET
    union REGS registers;
    mysmb_u16 index;
    mysmb_u8 __far *video;

    if (((struct mysmb_dos16_host *)context)->text_mode == 0U) return;
    registers.h.ah = 0U;
    registers.h.al = 3U;
    int86(0x10, &registers, &registers);
    video = MYSMB_DOS16_TEXT_MEMORY;
    for (index = 0U; index < MYSMB_TEXT_ROWS * MYSMB_TEXT_COLUMNS; ++index) {
        video[index * 2U] = frame->cells[index].character;
        video[index * 2U + 1U] = frame->cells[index].color;
    }
#else
    (void)context;
    (void)frame;
#endif
}

#ifdef MYSMB_DOS16_TARGET
static void mysmb_dos16_wait_frame(void)
{
    union REGS registers;

    registers.h.ah = 0x86U;
    registers.x.cx = 0U;
    registers.x.dx = 16667U;
    int86(0x15, &registers, &registers);
}
#endif

int main(void)
{
    struct mysmb_dos16_hooks hooks;

    mysmb_dos16_host.text_mode = 0U;
    hooks.context = &mysmb_dos16_host;
    hooks.read_buttons = mysmb_dos16_read_buttons;
    hooks.present_vga = mysmb_dos16_present_vga;
    hooks.present_text = mysmb_dos16_present_text;
    mysmb_dos16_root_initialize(&mysmb_dos16_root, &hooks, mysmb_dos16_page0,
        mysmb_dos16_page1, mysmb_dos16_page2, mysmb_dos16_page3);
#ifdef MYSMB_DOS16_TARGET
    for (;;) {
        mysmb_dos16_root_step(&mysmb_dos16_root);
        mysmb_dos16_wait_frame();
    }
#else
    mysmb_dos16_root_step(&mysmb_dos16_root);
    return 0;
#endif
}
