#ifndef MYSMB_PLATFORM_STARTUP_TIMING_H
#define MYSMB_PLATFORM_STARTUP_TIMING_H

/* ROM Start waits for VBlank1 and VBlank2 before the first NMI-owned game
 * frame.  This is a host scheduler contract only: it must never be stored in
 * or inferred from translated game state. */
#define MYSMB_PLATFORM_STARTUP_VBLANK_COUNT 2U

#endif
