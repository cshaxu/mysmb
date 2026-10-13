#ifndef MYGAMES_WIN16_MEMORY_H
#define MYGAMES_WIN16_MEMORY_H
#include <string.h>
/* Explicit far spans; never truncate GlobalLock pointers in a small model. */
#if defined(MYGAMES_WIN16_TARGET) || defined(MYGAMES_DOS16_TARGET)
#define mygames_win16_copy _fmemcpy
#define mygames_win16_zero _fmemset
#define mygames_win16_compare _fmemcmp
#else
#define mygames_win16_copy memcpy
#define mygames_win16_zero memset
#define mygames_win16_compare memcmp
#endif
#endif
