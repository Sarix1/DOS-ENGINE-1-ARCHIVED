#include "TEXT.H"
#include "MATH.H"
#include "VIDEO.H"
#include "GFX_BASIC.H"
#include "GFX_BITMAP.H"
#include "GFX_TRIANGLE.H"

int main()
{
	// Test variables
	struct Point2D a, b, c;
	struct bitmap bmp;
	
	// Initialize video
	initVideo();
	initTrigTables();
	drawTarget = offScreen;
	
	// Test draw shapes
	drawBoxFillCenter(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 200, 200, 4);
	drawCircleFrame(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 200, 12);
	drawCircleFill(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 196, 3);
	drawCircleThick(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 180, 10, 14);
	drawBoxFrameCenter(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 200, 200, 15);
	drawBoxFillCenter(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 15, 15, 3);
	drawCircleFrame(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 15, 11);
	drawBoxFrameCenter(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 15, 15, 15);
	setPixelsSlope(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, 5);
	drawCircleFrame(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2-1, 2, 15);
	
	// Test draw triangle
	a.x = 100;
	a.y = 100;
	b.x = 200;
	b.y = 80;
	c.x = 150;
	c.y = 150;
	drawTriangle(&a, &b, &c, 12);
	
	// Test draw bitmap
	loadBitmap("PIC.BMP", &bmp, 0);
	setPalette(bmp.palette);
	setPixelsFromBitmap(&bmp, 50, 50);
	
	// Update buffer
	updateBuffer();
	
	// Wait for user before exit
	getch();
	
	// Exit
	free(bmp.data);
	setVideo(TEXT_MODE);
	return 0;
}
