#ifndef MYGAMES_KVM_INPUT_EVENT_H
#define MYGAMES_KVM_INPUT_EVENT_H

#include "kvm/types.h"

/* Codes identify a physical input only. KVM never maps one to a controller,
 * menu, save/load, exit, Tab, mouse action or any application command. */
enum mygames_kvm_physical_key {
    MYGAMES_KVM_KEY_NONE = 0,
    MYGAMES_KVM_KEY_A, MYGAMES_KVM_KEY_D, MYGAMES_KVM_KEY_W, MYGAMES_KVM_KEY_S,
    MYGAMES_KVM_KEY_J, MYGAMES_KVM_KEY_K, MYGAMES_KVM_KEY_P, MYGAMES_KVM_KEY_O,
    MYGAMES_KVM_KEY_TAB, MYGAMES_KVM_KEY_ENTER, MYGAMES_KVM_KEY_LEFT_SHIFT,
    MYGAMES_KVM_KEY_RIGHT_SHIFT, MYGAMES_KVM_KEY_ESCAPE,
    MYGAMES_KVM_KEY_LEFT_ARROW, MYGAMES_KVM_KEY_RIGHT_ARROW,
    MYGAMES_KVM_KEY_UP_ARROW, MYGAMES_KVM_KEY_DOWN_ARROW,
    MYGAMES_KVM_KEY_F1, MYGAMES_KVM_KEY_F2,
    MYGAMES_KVM_KEY_1, MYGAMES_KVM_KEY_2, MYGAMES_KVM_KEY_3,
    MYGAMES_KVM_KEY_N, MYGAMES_KVM_KEY_H, MYGAMES_KVM_KEY_M, MYGAMES_KVM_KEY_Q,
    MYGAMES_KVM_PHYSICAL_KEY_COUNT
};

enum mygames_kvm_physical_mouse_button {
    MYGAMES_KVM_MOUSE_NONE = 0,
    MYGAMES_KVM_MOUSE_LEFT, MYGAMES_KVM_MOUSE_RIGHT, MYGAMES_KVM_MOUSE_MIDDLE,
    MYGAMES_KVM_MOUSE_X1, MYGAMES_KVM_MOUSE_X2
};

enum mygames_kvm_input_kind {
    MYGAMES_KVM_INPUT_KEY = 1,
    MYGAMES_KVM_INPUT_MOUSE_BUTTON = 2,
    MYGAMES_KVM_INPUT_MOUSE_MOVE = 3,
    MYGAMES_KVM_INPUT_FOCUS = 4,
    MYGAMES_KVM_INPUT_CANCEL = 5,
    MYGAMES_KVM_INPUT_COMMAND = 6,
    MYGAMES_KVM_INPUT_RESIZE = 7
};

enum mygames_kvm_coordinate_space {
    MYGAMES_KVM_COORD_NONE = 0,
    MYGAMES_KVM_COORD_CLIENT_PIXELS = 1,
    MYGAMES_KVM_COORD_TEXT_CELLS = 2
};
#define MYGAMES_KVM_MOD_SHIFT 1U
#define MYGAMES_KVM_MOD_CONTROL 2U
#define MYGAMES_KVM_MOD_ALT 4U
#define MYGAMES_KVM_MOUSE_LEFT_MASK 1U
#define MYGAMES_KVM_MOUSE_RIGHT_MASK 2U
#define MYGAMES_KVM_MOUSE_MIDDLE_MASK 4U
#define MYGAMES_KVM_MOUSE_X1_MASK 8U
#define MYGAMES_KVM_MOUSE_X2_MASK 16U

struct mygames_kvm_input_event {
    mygames_kvm_u8 kind;
    mygames_kvm_u8 down;
    mygames_kvm_u8 repeat;
    mygames_kvm_u16 physical_code;
    mygames_kvm_u16 native_scan;
    mygames_kvm_u16 modifiers;
    short x;
    short y;
    /* Complete physical state after this event. CANCEL has buttons=0 and
     * ends capture; it never synthesizes a click. Apps interpret gestures.
     * COMMAND uses physical_code as an opaque app-provided menu/control ID.
     * Pointer positions can remain outside the view during capture. */
    mygames_kvm_u16 buttons;
    mygames_kvm_u8 coordinate_space;
};

/* Presentation is an app request, never an input binding owned by KVM. */
enum mygames_kvm_presentation {
    MYGAMES_KVM_PRESENTATION_GRAPHICS = 0,
    MYGAMES_KVM_PRESENTATION_TEXT = 1
};

#endif
