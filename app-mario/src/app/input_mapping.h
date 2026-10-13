#ifndef MYSMB_APP_INPUT_MAPPING_H
#define MYSMB_APP_INPUT_MAPPING_H

#include "io/input.h"
#include "kvm/input_event.h"

struct mysmb_app_input_mapping {
    mygames_kvm_u8 down[MYGAMES_KVM_PHYSICAL_KEY_COUNT];
};

void mysmb_app_input_mapping_initialize(struct mysmb_app_input_mapping *mapping);
void mysmb_app_input_mapping_event(struct mysmb_app_input_mapping *mapping,
    const struct mygames_kvm_input_event *event, struct mysmb_io_input *input);

#endif
