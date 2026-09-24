#include "platform/dos16/dos16_root.h"

#ifdef MYSMB_DOS16_TARGET
#define MYSMB_DOS16_FAR __far
#else
#define MYSMB_DOS16_FAR
#endif

static struct mysmb_dos16_root mysmb_dos16_root;
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page0[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page1[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page2[MYSMB_VGA_PAGE_SIZE];
static mysmb_u8 MYSMB_DOS16_FAR mysmb_dos16_page3[MYSMB_VGA_PAGE_SIZE];

static mysmb_u8 mysmb_dos16_read_buttons(void *context)
{
    (void)context;
    return 0U;
}

static void mysmb_dos16_present_vga(void *context, const struct mysmb_vga_frame *frame)
{
    (void)context;
    (void)frame;
}

static void mysmb_dos16_present_text(void *context, const struct mysmb_text_frame *frame)
{
    (void)context;
    (void)frame;
}

int main(void)
{
    struct mysmb_dos16_hooks hooks;

    hooks.context = 0;
    hooks.read_buttons = mysmb_dos16_read_buttons;
    hooks.present_vga = mysmb_dos16_present_vga;
    hooks.present_text = mysmb_dos16_present_text;
    mysmb_dos16_root_initialize(&mysmb_dos16_root, &hooks, mysmb_dos16_page0,
        mysmb_dos16_page1, mysmb_dos16_page2, mysmb_dos16_page3);
    mysmb_dos16_root_step(&mysmb_dos16_root);
    return 0;
}
