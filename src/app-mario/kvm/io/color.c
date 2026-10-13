#include "io/color.h"

const unsigned long mysmb_io_source_colors[64] = {
        0x545454UL,0x001e74UL,0x081090UL,0x300088UL,0x440064UL,0x5c0030UL,0x540400UL,0x3c1800UL,0x202a00UL,0x083a00UL,0x004000UL,0x003c00UL,0x00323cUL,0,0,0,
        0x989698UL,0x084cc4UL,0x3032ecUL,0x5c1ee4UL,0x8814b0UL,0xa01464UL,0x982220UL,0x783c00UL,0x545a00UL,0x287200UL,0x087c00UL,0x007628UL,0x006678UL,0,0,0,
        0xeceeeeUL,0x4c9aecUL,0x787cecUL,0xb062ecUL,0xe454ecUL,0xec58b4UL,0xec6a64UL,0xd48820UL,0xa0aa00UL,0x74c400UL,0x4cd020UL,0x38c06cUL,0x38b4ccUL,0x3c3c3cUL,0,0,
        0xeceeeeUL,0xa8ccecUL,0xbcbcecUL,0xd4b2ecUL,0xecaeecUL,0xecaed4UL,0xecb4b0UL,0xe4c690UL,0xccd278UL,0xb4de78UL,0xa8e290UL,0x98e2b4UL,0xa0d6e4UL,0xa0a2a0UL,0,0
    };
unsigned long mysmb_io_color_rgb(mygames_kvm_u8 index)
{
    return mysmb_io_source_colors[index & 0x3fU];
}

mygames_kvm_u8 mysmb_io_color_text16(mygames_kvm_u8 index)
{
    /* Exact nearest entries for the application source and standard device palettes.
     * The exhaustive IO contract checks aliases and first-entry ties. */
    static const mygames_kvm_u8 choices[64] = {
        8U,1U,1U,1U,8U,4U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,
        7U,1U,9U,9U,5U,5U,4U,6U,8U,2U,2U,2U,3U,0U,0U,0U,
        15U,9U,9U,13U,13U,13U,12U,6U,6U,10U,10U,10U,3U,8U,0U,0U,
        15U,7U,7U,7U,15U,7U,7U,7U,7U,7U,7U,7U,7U,7U,0U,0U
    };
    return choices[index&63U];
}

