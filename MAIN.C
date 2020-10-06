#include <time.h>
#include "TEXT.H"
#include "TYPES.H"
#include "MATH.H"
#include "VIDEO.H"
#include "GFX_BASIC.H"
#include "GFX_BITMAP.H"

int main()
{
	// Test variables
	int i, j, k;
	struct bitmap bmp;
	struct Point2D a, b, c, d, e, box_a, box_b, box_c, box_d;
	struct Point2D* boxPoints[5];
	clock_t start_t, end_t, run_t;
	
	// Initialize video
	initVideo();
	initTrigTables();
	drawTarget = offScreen;
	
	// Load bitmap
	/*
	loadBitmap("PIC.BMP", &bmp, 0);
	setPalette(bmp.palette);
	*/
	
	// Set variables
	i = 0;
	j = degToAng(45);
	k = 0;
	a.x = SCREEN_WIDTH/2-1;
	a.y = SCREEN_HEIGHT/2-1;
	
	boxPoints[0] = &box_a;
	boxPoints[1] = &box_b;
	boxPoints[2] = &box_c;
	boxPoints[3] = &box_d;
	boxPoints[4] = NULL;
	
	while (1)
	{
		if (kbhit())
		{
			getch();
			break;
		}	

		// Logic
		i++; if (i >= 360) i = 0;
		k = degToAng(i);
		
		b.x = a.x + cosAngle(80, k);
		b.y = a.y - sinAngle(80, k);
		c.x = b.x + cosAngle(15, k); 
		c.y = b.y - sinAngle(15, k);
		d.x = b.x - sinAngle(-5, k);
		d.y = b.y + cosAngle(5, k);
		e.x = b.x - sinAngle(5, k);
		e.y = b.y + cosAngle(-5, k);
		
		box_a.x = a.x + cosAngle(60, k+j);
		box_a.y = a.y - sinAngle(60, k+j);
		box_b.x = a.x + sinAngle(60, k+j);
		box_b.y = a.y + cosAngle(60, k+j);
		box_c.x = a.x - cosAngle(60, k+j);
		box_c.y = a.y + sinAngle(60, k+j);
		box_d.x = a.x - sinAngle(60, k+j);
		box_d.y = a.y - cosAngle(60, k+j);

		// Draw
		drawFill(0);
		
		// Box fill
		drawPolygonFill(boxPoints, 5);
		
		// Box frame
		drawPolygonFrame(boxPoints, 7);
		
		// Box corners
		setPixel(box_a.x, box_a.y, 12);
		setPixel(box_b.x, box_b.y, 12);
		setPixel(box_c.x, box_c.y, 12);
		setPixel(box_d.x, box_d.y, 12);
		
		// Circles in the middle
		drawCircleThick(a.x, a.y, 15+i%45, 10, 12);
		drawCircleFill(a.x, a.y, (i%45)/2, 9);
		
		// Draw bitmap image
		// setPixelsFromBitmap(&bmp, b.x-(bmp.width/2), b.y-(bmp.height/2));
		
		// Pointer arrow
		drawLine(&a, &b, 15);
		drawTriangleFill(c, d, e, 14);
		drawCircleFrame(b.x, b.y, 15+i%15, 10);
				
		// Update buffer
		updateBuffer();
	}
	
	// Wait for user before exit
	getch();
	
	// Exit
	free(bmp.data);
	setVideo(TEXT_MODE);
	
	return 0;
}
