#include <time.h>
#include "WATCOM.H"
#include "TEXT.H"
#include "TYPES.H"
#include "MATH.H"
#include "VIDEO.H"
#include "GFX.H"
#include "BITMAP.H"

int main()
{
	// Test variables
	int i, j, k;
	
	struct Bitmap bmp;
	struct Point2D a, b, box_a, box_b, box_c, box_d, tri_a, tri_b, tri_c;
	struct Point2D* boxPoints[5];
	struct Triangle2D* arrow = newTriangle2D_P(&tri_a, &tri_b, &tri_c, 15);
	
	clock_t start_t, end_t, run_t;
	
	// Initialize video
	initVideo();
	initTrigTables();
	drawTarget = offScreen;
	
	// Load bitmap
	loadBitmap("PIC.BMP", &bmp, 0);
	setPalette(bmp.palette);
	
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
		if (++i >= 360)
			i = 0;
		k = degToAng(i);
		
		b.x = a.x + cosAngle(80, k);
		b.y = a.y - sinAngle(80, k);
		
		arrow->point[0]->x = b.x + cosAngle(15, k); 
		arrow->point[0]->y = b.y - sinAngle(15, k);
		arrow->point[1]->x = b.x - sinAngle(-5, k);
		arrow->point[1]->y = b.y + cosAngle(5, k);
		arrow->point[2]->x = b.x - sinAngle(5, k);
		arrow->point[2]->y = b.y + cosAngle(-5, k);
		arrow->color = i / 2;
		
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
		drawPolyFill_P(boxPoints, 5);

		// Box frame
		drawPolyFrame_P(boxPoints, 7);
		
		// Box corners
		drawPixel(box_a.x, box_a.y, 12);
		drawPixel(box_b.x, box_b.y, 13);
		drawPixel(box_c.x, box_c.y, 14);
		drawPixel(box_d.x, box_d.y, 15);
		
		// Circles in the middle
		drawCircleThick(a.x, a.y, 15+i%45, 10, 12);
		drawCircleFill(a.x, a.y, (i%45)/2, 9);
		
		// Draw bitmap image
		setPixelsFromBitmap(&bmp, box_a.x-(bmp.width/2), box_a.y-(bmp.height/2));
		
		// Pointer arrow stuff
		drawLine(&a, &b, 15);
		drawTriangleFill(arrow);
		drawCircleFrame(b.x, b.y, 15+i%15, 10);
				
		// Update buffer
		updateBuffer();
	}
	
	// Debug information
	printf("%d\n", orient2D(&a, &box_a, &box_b));
	
	// Wait for user before exit
	getch();
	
	// Exit
	free(bmp.data);
	setVideo(TEXT_MODE);
	
	return 0;
}
