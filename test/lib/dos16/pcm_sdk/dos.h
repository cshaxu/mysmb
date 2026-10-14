#ifndef TEST_DOS_PCM_DOS_H
#define TEST_DOS_PCM_DOS_H
#define far
#define interrupt
unsigned _dos_allocmem(unsigned paragraphs,unsigned short *segment);
unsigned _dos_freemem(unsigned segment);
void (*_dos_getvect(unsigned vector))(void);
void _dos_setvect(unsigned vector,void (*handler)(void));
#endif
