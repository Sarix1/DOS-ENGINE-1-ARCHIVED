#include "TYPES.H"
#include "VIDEO.H"
#include "MATH.H"
#include "GFX_BASIC.H"

// CAUTION: no boundary checking in below functions!

// Write a pixel to off-screen buffer or VGA buffer, depending where drawTarget points
void setPixel(int x, int y, int color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		drawTarget[(y<<8) + (y<<6) + x] = color;
}

// Fill the screen
void setPixelsAll(int color)
{
	_fmemset(drawTarget, color, SCREEN_SIZE);
}

// Horizontal line
void setPixelsHorizontally(int x, int y, int len, int color)
{
	byte far* p = drawTarget + (y<<8) + (y<<6) + x;
	// this is a boundary check! move elsewhere?
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		// this is a crop! move elsewhere?
		if (x+len >= SCREEN_WIDTH)
			len -= (x+len - SCREEN_WIDTH);
		
		_fmemset(p, color, len);
	}
}

// Vertical line
void setPixelsVertically(int x, int y, int len, int color)
{
	byte far* p = drawTarget + (y<<8) + (y<<6) + x;
	// this is a boundary check! move elsewhere?
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		// this is a crop! move elsewhere?
		if (y+len >= SCREEN_HEIGHT)
			len -= (y+len - SCREEN_HEIGHT);
		
		while (len--)
		{
			*p = color;
			p += SCREEN_WIDTH;
		}
	}
}

// 45 degree line
void setPixelsDiagonally(int x, int y, int len, int dir, int color)
{
	int offset = SCREEN_WIDTH;
	byte far* p = drawTarget + (y<<8) + (y<<6) + x;
	
	// is the slope downwards...
	if (len > 0) 
	{		
		offset += dir;
		while (len--)	// draw loop
		{
			*p = color;
			p += offset;
		}
	}
	// ...or downwards?
	else
	{
		offset -= dir;
		while (len++)	// draw loop
		{
			*p = color;
			p -= offset;
		}
	}
}

// Unorthodox line
void setPixelsSlope(int ax, int ay, int bx, int by, int color)
{
	int i, x, y, px, py, dx, dy, dx_abs, dy_abs, x_sign, y_sign;
	
	dx = bx - ax;
	dy = by - ay;
	x_sign = sign(dx);
	y_sign = sign(dy);
	dx_abs = abs(dx);
	dy_abs = abs(dy);
	x = dy_abs >> 1;
	y = dx_abs >> 1;
	
	// Starting point
	px = ax;
	py = ay;
	
	// Use the specific functions for vertical, horizontal, and diagonal lines
	// if the coordinates suggest the line is at a right or diagonal angle instead
	// This should probably be in drawLine() instead
	if		(!dx_abs)			setPixelsVertically(ax, (ay < by ? ay : by), dy_abs+1, color);
	else if (!dy_abs)			setPixelsHorizontally((ax < bx ? ax : bx), ay, dx_abs+1, color);
	else if (dx_abs == dy_abs)	setPixelsDiagonally(ax, ay, dy+y_sign, x_sign, color);
	else
	{	
		if (dx_abs > dy_abs)
		{
			for (i = 0; i <= dx_abs; i++)
			{
				setPixel(px, py, color);
				y += dy_abs;
				
				if (y >= dx_abs)
				{
					y -= dx_abs;
					py += y_sign;
				}
				
				px += x_sign;
			}
		}
		else
		{
			for (i = 0; i <= dy_abs; i++)
			{
				setPixel(px, py, color);
				x += dx_abs;
				
				if (x >= dy_abs)
				{
					x -= dy_abs;
					px += x_sign;
				}
				
				py += y_sign;
			}
		}
	}
}

// Put a single pixel
void drawPixel(int x, int y, int color)
{
	// boundary check
	setPixel(x, y, color);
}

// Fill the screen
void drawFill(int color)
{
	setPixelsAll(color);
}

// Draw a line between two points
void drawLine(struct Point2D* p1, struct Point2D* p2, int color)
{
	// optimize
	setPixelsSlope(p1->x, p1->y, p2->x, p2->y, color);
}

// Draw multiple lines between points
void drawLines(struct Point2D* points[], int color)
{
	int i = 0;
	while (points[++i] != NULL)
	{
		drawLine(points[i-1], points[i], color);
	}
}

// Draw a box
void drawBoxFill(int x, int y, int w, int h, int color)
{
	// Needs boundary checking here
	while (h--)
		setPixelsHorizontally(x, y++, w, color);
}

// Draw a box centered at x and y
void drawBoxFillCenter(int x, int y, int w, int h, int color)
{
	drawBoxFill((x+1 - w/2 - w%2), (y+1 - h/2 - h%2), w, h, color);
}

// Draw a rectangular frame
void drawBoxFrame(int x, int y, int w, int h, int color)
{
	// Needs boundary checking here
	setPixelsHorizontally	(x,		y,		w,	color);
	setPixelsHorizontally	(x,		y+h-1,	w,	color);
	setPixelsVertically		(x,		y,		h,	color);
	setPixelsVertically		(x+w-1,	y,		h,	color);
}

// Draw a rectangular frame centered at x and y
void drawBoxFrameCenter(int x, int y, int w, int h, int color)
{
	drawBoxFrame((x+1 - w/2 - w%2), (y+1 - h/2 - h%2), w, h, color);
}

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

// Sort points vertically first top to bottom, then horizontally left to right
void sortPair(struct Point2D *a, struct Point2D *b)
{
    if ((a->y > b->y) || (a->y == b->y && a->x > b->x))
	{
    	struct Point2D tmp = *a;
    	*a = *b;
    	*b = tmp;
    }
}

// Check which side of a line a point falls on
int orient2D(struct Point2D* p1, struct Point2D* p2, struct Point2D* p3)
{
	return (p2->x - p1->x) * (p3->y - p1->y) - (p2->y - p1->y) * (p3->x - p1->x);
}

// Plot a slope and store its x coordinates on an array of y coordinates
// The slope must run downwards, i.e. ay < by
void makeSlope(struct Edge* slope, struct Point2D* p1, struct Point2D* p2, int y_offset)
{
	int x, y, px, dx, dy, x_sign;
	
	dy = p2->y - p1->y;
	dx = abs(p2->x - p1->x);
	x_sign = sign(p2->x - p1->x);
	x = dy >> 1;
	
	// Out of bounds check - this should never happen
	if (dy + y_offset > slope->bottom - slope->top)
		dy = 0; // too lazy to truncate, just don't draw it at all
	
	// Starting point
	px = p1->x;
	
	for (y = 0; y <= dy; y++)
	{
		slope->points[y + y_offset] = px;
		x += dx;
		
		if (x >= dy)
		{
			x -= dy;
			px += x_sign;
		}
	}
}

void drawTriangleFill(struct Point2D p1, struct Point2D p2, struct Point2D p3, int color)
{
	int i, y, long_edge;
	struct Edge edges[2];
	
	sortPair(&p1, &p2);
	sortPair(&p1, &p3);
	sortPair(&p2, &p3);
	
	if (p1.y == p3.y)
		return;
	
	for (i = 0; i < 2; i++)
	{
		edges[i].top = p1.y;
		edges[i].bottom = p3.y;
		edges[i].points = malloc(sizeof(int) * ((p3.y - p1.y) + 1));
	}
	
	if (orient2D(&p1, &p2, &p3) > 0)
		long_edge = LEFT;
	else
		long_edge = RIGHT;
	
	// Calculate slope for the long edge
	makeSlope(&(edges[long_edge]), &p1, &p3, 0);
	
	i = 0;
	
	// The following two blocks should be a single inline function
	
	// Calculate slope for upper short edge and draw scanlines
	if (p1.y < p2.y)
	{
		makeSlope(&(edges[long_edge^1]), &p1, &p2, 0);
		
		for (y = p1.y; y < p2.y; y++, i++)
			setPixelsHorizontally(edges[0].points[i], y, (edges[1].points[i] - edges[0].points[i]), color);
	}
	
	// Calculate slope for lower short edge and draw scanlines
	if (p2.y < p3.y)
	{
		makeSlope(&(edges[long_edge^1]), &p2, &p3, (p2.y - p1.y));
		
		for (y = p2.y; y < p3.y; y++, i++)
			setPixelsHorizontally(edges[0].points[i], y, (edges[1].points[i] - edges[0].points[i]), color);
	}
	
	// Free the allocated memory
	free(edges[0].points);
	free(edges[1].points);
}

// Draw a polygon outline
void drawPolygonFrame(struct Point2D* points[], int color)
{
	int i = 0;
	while (points[++i] != NULL)
	{
		drawLine(points[i-1], points[i], color);
	}
	drawLine(points[i-1], points[0], color);
}

// Draw a filled polygon
void drawPolygonFill(struct Point2D* points[], int color)
{
	int i = 1;
	while (points[i+1] != NULL)
	{
		drawTriangleFill(*points[0], *points[i], *points[i+1], color);
		i++;
	}
}