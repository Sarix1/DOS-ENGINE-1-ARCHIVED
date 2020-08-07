#include "TEXT.H"
#include "VIDEO.H"
#include "GFX_BASIC.H"

int main()
{
	// Hello
	resetText();
	putText("Hello", FG+BLUE, BG+BLACK, 0, 0);
	putText("World", FG+RED, BG+BLACK, 2, 1);
	setTextColor(0, 0);
	
	// Initialize video
	initVideo();
	// initArrays();
	drawTarget = offScreen;
	
	// Test draw
	drawBoxCenter(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 50, 50, 4);
	updateBuffer();
	
	// Wait for user before exit
	getch();
	
	// Exit
	setVideo(TEXT_MODE);
	return 0;
}
