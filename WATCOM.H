// Watcom vs Borland specific libraries and functions
#ifdef __WATCOMC__
#include <malloc.h>
#define outportb outp
#define inportb inp
#define disable _disable
#define enable _enable
#define getvect _dos_getvect
#define setvect _dos_setvect
#define farmalloc _fmalloc
#else
#include <alloc.h>
#endif