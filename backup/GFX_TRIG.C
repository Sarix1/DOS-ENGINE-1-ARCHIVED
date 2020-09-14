#include "MATH.H"
#include "GFX_BASIC.H"

// Circle drawing
void drawCircle(int x, int y, int diameter, int color)
{
	// r is for inverse of remainder
	const int radius			= diameter / 2;
	const long inverseRadius	= ((1 / (float)radius) * (1 << FRACTIONAL_PART));
	const int r					= (diameter % 2) ^ 1;
	
	int px			= 0;
	int py			= radius;
	long distance	= 0;
	
	while (px <= py)
	{
		setPixel(x+px,		y-py+r,		color);
		setPixel(x+px,		y+py,		color);
		setPixel(x-px+r,	y-py+r,		color);
		setPixel(x-px+r,	y+py,		color);
		setPixel(x+py,		y-px+r,		color);
		setPixel(x+py,		y+px,		color);
		setPixel(x-py+r,	y-px+r,		color);
		setPixel(x-py+r,	y+px,		color);

		px++;
		distance += inverseRadius;
		py = (int)(((radius * (long)(SinAcosTable[distance >> 2])) >> FRACTIONAL_PART) + 1);
	}
}