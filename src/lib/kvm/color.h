#ifndef MYGAMES_KVM_COLOR_H
#define MYGAMES_KVM_COLOR_H

#include "kvm/types.h"

/* Canonical RGB for the neutral sixteen-color text attributes. */
unsigned long mygames_kvm_color_text_rgb(mygames_kvm_u8 index);
/* Device fallback for an arbitrary neutral RGB text palette. */
mygames_kvm_u8 mygames_kvm_color_text_nearest(unsigned long rgb);
/* Project the neutral sixteen text slots onto fixed hardware/API attributes.
 * Source RGB slots are reduced once; canonical slots retain their identity. */
void mygames_kvm_color_text_attributes(const unsigned long *colors,
    mygames_kvm_u8 source_colors,mygames_kvm_u8 attributes[16]);

/* Black/white ink chosen for a canonical text background. */
mygames_kvm_u8 mygames_kvm_color_text_contrast(mygames_kvm_u8 background);

#endif
