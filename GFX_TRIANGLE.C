#include "TYPES.H"
#include "VIDEO.H"
#include "MATH.H"
#include "GFX_BASIC.H"
#include "GFX_TRIANGLE.H"

int orient2D(struct Point2D* a, struct Point2D* b, struct Point2D* c)
{
	return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

void drawTriangle(struct Point2D* v0, struct Point2D* v1, struct Point2D* v2, int color)
{
    // Variable declarations
    int w0, w1, w2;
    struct Point2D p;
    
    // Calculate triangle bounding box
    int minX = min3(v0->x, v1->x, v2->x);
    int minY = min3(v0->y, v1->y, v2->y);
    int maxX = max3(v0->x, v1->x, v2->x);
    int maxY = max3(v0->y, v1->y, v2->y);
    
    // Clip bounding box coordinates to screen
    minX = max(minX, 0);
    minY = max(minY, 0);
    maxX = min(maxX, SCREEN_WIDTH - 1);
    maxY = min(maxY, SCREEN_HEIGHT - 1);
    
    // Rasterize triangle
    for (p.y = minY; p.y <= maxY; p.y++)
    {
        for (p.x = minX; p.x <= maxX; p.x++)
        {
            // Calculate barycentric coordinates
            w0 = orient2D(v1, v2, &p);
            w1 = orient2D(v2, v0, &p);
            w2 = orient2D(v0, v1, &p);
            
            if (w0 >= 0 && w1 >= 0 && w2 >= 0)
                setPixel(p.x, p.y, color);
        }
    }
}