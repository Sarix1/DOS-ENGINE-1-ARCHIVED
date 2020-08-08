#include "TEXT.H"
#include "VIDEO.H"
#include "MATH.H"
#include "GFX_BASIC.H"
#include "GFX_TRIG.H"

int main()
{
	// Hello
	resetText();
	putText("Hello", FG+BLUE, BG+BLACK, 0, 0);
	putText("World", FG+RED, BG+BLACK, 2, 1);
	setTextColor(0, 0);
	
	// Initialize video
	initVideo();
	initTrigTables();
	drawTarget = offScreen;
	
	// Test draw
	drawBoxCenter(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 200, 200, 4);
	drawCircle(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 200, 12);
	drawBoxCenter(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 15, 15, 3);
	drawCircle(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 15, 11);
	drawCircle(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 2, 15);
	updateBuffer();
	
	// Wait for user before exit
	getch();
	
	// Exit
	setVideo(TEXT_MODE);
	return 0;
}
