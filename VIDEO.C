#include <dos.h>
#include "WATCOM.H"
#include "TYPES.H"
#include "TEXT.H"
#include "VIDEO.H"

// Set video mode with interrupts
void setVideo(byte mode)
{
	union REGS regs;
	regs.h.ah = SET_MODE;
	regs.h.al = mode;
	int86(VIDEO_INT, &regs, &regs);
}

// Go to VGA mode 13 and initialize memory for VGA and off-screen buffer
void initVideo()
{
	int i;
	offScreen = farmalloc(SCREEN_SIZE);
	
	if (offScreen)
	{
		screen = MK_FP(VGA, 0);
		setVideo(VGA_256_MODE);
		_fmemset(offScreen, 0, SCREEN_SIZE);
	}
	else
	{
		setVideo(TEXT_MODE);
		putText("Failed to allocate memory for off-screen buffer\n", 0, 0, FG+RED, BG+PURPLE);
	}
}

// Copy off-screen buffer to VGA buffer, wait for vertical retrace
void updateBuffer()
{
	while (inportb(INPUT_STATUS) & VRETRACE);
	while (!(inportb(INPUT_STATUS) & VRETRACE));
	_fmemcpy(screen, offScreen, SCREEN_SIZE);
}

// Manual interrupt to set pixel in VGA memory
void setPixelInt86(int x, int y, byte color)
{
	union REGS regs;
	regs.h.ah = PLOT_PIXEL;
	regs.h.al = color;
	regs.w.cx = x;
	regs.w.dx = y;
	int86(VIDEO_INT, &regs, &regs);
}
