#include <stdio.h>
#include "TYPES.H"

// Mode 13 graphics constants
// CAUTION: use of (y<<8)+(y<<6) in graphics code assumes a 320x200 resolution;
// Replace with y*SCREEN_WIDTH otherwise, but lose the optimization benefit
#define SCREEN_WIDTH		320
#define SCREEN_HEIGHT		200
#define SCREEN_SIZE			((size_t)SCREEN_WIDTH*(size_t)SCREEN_HEIGHT)
#define NUM_COLORS			256

// Interrupts and addresses
#define VIDEO_INT           0x10 	// BIOS video interrupt	
#define SET_MODE            0x00 	// BIOS video mode 	
#define TEXT_MODE           0x03 	// 80x25 text mode	
#define VGA_256_MODE		0x13 	// VGA 256-color mode
#define VGA					0xA000	// VGA memory address
#define INPUT_STATUS_0		0x3DA	// VGA index state
#define PLOT_PIXEL			0x0C

// Far pointers
byte far* screen;
byte far* offScreen;
byte far* drawTarget;

void setVideo(byte mode);
void initVideo();
void updateBuffer();
inline void setPixelInt86(int x, int y, int color);