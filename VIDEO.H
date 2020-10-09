#include <stdio.h>
#include "TYPES.H"

// Interrupts and addresses
#define VIDEO_INT           0x10 	// BIOS video interrupt	
#define SET_MODE            0x00 	// BIOS video mode 	
#define TEXT_MODE           0x03 	// 80x25 text mode	
#define VGA_256_MODE		0x13 	// VGA 256-color mode
#define VGA					0xa000	// VGA memory address
#define PALETTE_INDEX		0x03c8
#define PALETTE_DATA		0x03c9
#define INPUT_STATUS		0x3da	// VGA v-retrace index state
#define VRETRACE            0x08	// Vertical retrace
#define PLOT_PIXEL			0x0C

// Mode 13 graphics constants
#define SCREEN_WIDTH		320
#define SCREEN_HEIGHT		200
#define SCREEN_SIZE			((size_t)SCREEN_WIDTH*(size_t)SCREEN_HEIGHT)
#define NUM_COLORS			256

// Far pointers
byte far* screen;
byte far* offScreen;
byte far* drawTarget;

void setVideo(byte mode);
void initVideo();
void updateBuffer();
void setPixelInt86(int x, int y, byte color);

// CAUTION: use of (y<<8)+(y<<6) in graphics code assumes a 320x200 resolution;
// Replace with y*SCREEN_WIDTH otherwise, but lose the optimization benefit