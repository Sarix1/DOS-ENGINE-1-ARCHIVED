#include "TYPES.H"
#include "VIDEO.H"
#include "MATH.H"

// CAUTION: no boundary checking in below functions!

// Write a pixel to off-screen buffer or VGA buffer, depending where drawTarget points
void setPixel(int x, int y, int color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		drawTarget[(y<<8) + (y<<6) + x] = color;
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
	px = ax;
	py = ay;
	
	// Use the specific functions for vertical, horizontal, and diagonal lines
	// if the coordinates suggest the line is at a right or diagonal angle instead
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

// Fill the screen
void drawFill(int color)
{
	_fmemset(drawTarget, color, SCREEN_SIZE);
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
