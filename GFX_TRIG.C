#include "MATH.H"
#include "GFX_BASIC.H"

// Circle drawing
void drawCircleFrame(const int x, const int y, const int diameter, const int color)
{
	// r is for inverse of remainder
	// where FRACTION is involved, fixed point values are used
	const int	radius			= diameter / 2;
	const long	inverseRadius	= ((1 / (float)radius) * (1 << FRACTION)) + 0.5;
	const int	r				= (diameter % 2) ^ 1;
	
	int py				= radius;
	int px				= 0;
	long distance		= 0;
	long heightRatio;
	
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

		distance		+= inverseRadius;
		heightRatio		 = SinAcosTable[distance >> FRAC_TO_TRIG];
		py = (int)(((radius * (long long)heightRatio) >> FRACTION)) + 1;
		px++;
	}
}

// Filled circle
void drawCircleFill(int x, int y, int diameter, int color)
{
	// r is for inverse of remainder
	// where FRACTION is involved, fixed point values are used
	const int	radius			= diameter / 2;
	const long	inverseRadius	= ((1 / (float)radius) * (1 << FRACTION)) + 0.5;
	const int	r				= (diameter % 2) ^ 1;

	int w;
	int py				= 1;
	int px				= radius;
	long distance		= 0x1F;
	long widthRatio;
	
	if (!r)
		setPixelsHorizontally(x-px,	y,	diameter,	color);
	
	while (py <= radius)
	{
		w = px * 2 + (r ^ 1);
		setPixelsHorizontally(x-px+r,	y-py+r,	w,	color);
		setPixelsHorizontally(x-px+r,	y+py,	w,	color);
		
		distance		+= inverseRadius;
		widthRatio		 = SinAcosTable[distance >> FRAC_TO_TRIG];
		px = (int)(((radius * (long long)widthRatio) >> FRACTION) + 1);
		py++;
	}
}

// Thick circle
void drawCircleThick(int x, int y, int diameter, int thickness, int color)
{
	// r is for inverse of remainder
	// 2 suffix is for the inner circle
	// where FRACTION is involved, fixed point values are used
	const int	radius				= diameter / 2;
	const int	radius2				= radius - thickness;
	const long	inverseRadius		= ((1 / (float)radius) * (1 << FRACTION)) + 0.5;
	const long	inverseRadius2		= ((1 / (float)radius2) * (1 << FRACTION)) + 0.5;
	const int	r					= (diameter % 2) ^ 1;
	
	int w;
	int py				= 1;
	int px				= radius;
	int px2				= radius2;
	long distance		= 0x1F;
	long distance2		= 0x1F;
	long widthRatio;
	
	if (!r)
	{
		setPixelsHorizontally(x-px,			y,	thickness,	color);
		setPixelsHorizontally(x+px2+r+1,	y,	thickness,	color);
	}
	
	while (py <= radius2)
	{
		w = px - px2;
		setPixelsHorizontally(x-px+r,	y-py+r,	w,	color);
		setPixelsHorizontally(x-px+r,	y+py,	w,	color);
		setPixelsHorizontally(x+px2+1,	y-py+r,	w,	color);
		setPixelsHorizontally(x+px2+1,	y+py,	w,	color);
		
		distance	+= inverseRadius;
		distance2	+= inverseRadius2;
		widthRatio	 = SinAcosTable[distance >> FRAC_TO_TRIG];
		px			 = (int)(((radius * (long long)widthRatio) >> FRACTION) + 1);
		widthRatio	 = SinAcosTable[distance2 >> FRAC_TO_TRIG];
		px2			 = (int)(((radius2 * (long long)widthRatio) >> FRACTION) + 1);
		py++;
	}
	
	while (py <= radius)
	{
		w = px*2 + (r^1);
		setPixelsHorizontally(x-px+r,	y-py+r,	w,	color);
		setPixelsHorizontally(x-px+r,	y+py,	w,	color);
		
		distance	+= inverseRadius;
		widthRatio	 = (SinAcosTable[distance >> FRAC_TO_TRIG]);
		px			 = (int)(((radius * (long long)widthRatio) >> FRACTION) + 1);
		py++;
	}
}