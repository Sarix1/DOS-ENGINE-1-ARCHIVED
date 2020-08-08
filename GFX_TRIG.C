#include "MATH.H"
#include "GFX_BASIC.H"

// Circle drawing
void drawCircle(const int x, const int y, const int diameter, const int color)
{
	// r is for inverse of remainder
	const int	radius			= diameter / 2;
	const long	inverseRadius	= ((1 / (float)radius) * (1 << FRACTION)) + 0.5;
	const int	r				= (diameter % 2) ^ 1;
	
	int px				= 0;
	int py				= radius;
	long distance		= 0;
	// long distanceRatio	= 0;
	
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
		
		// distanceRatio = distance >> 
		
		py = (int)(((radius * (long long)(SinAcosTable[distance >> FRAC_TO_TRIG])) >> FRACTION)) + 1;
	}
}