#include <math.h>
#include "MATH.H"

// Initialize tables and arrays
void initTrigTables()
{
	int i;
	long double x, real;
	
	// Init SinCosTable
	for (i = 0; i < ANGLES + ANGLES/4; i++)
	{
		real = sin((i * 2 * M_PI) / ANGLES);
		SinCosTable[i] = real * (1 << FRACTION);
	}

	// Init Sin(aCos(x)) table
	for (i = 0; i < TRIGONOMETRY-1; i++)
	{
		x = (long double)i / TRIGONOMETRY;
		real = sqrt(1 - x*x);
		// real = sin(acos((double)i / TRIGONOMETRY));
		SinAcosTable[i] = real * (1 << FRACTION) + 0.5;
	}
}

// Value multiplied by Sin of angle
int sinAngle(int value, int angle)
{
	long long temp;
	
	while (angle < 0)
		angle += ANGLES;
	while (angle >= ANGLES)
		angle -= ANGLES;
	
	temp = (long long)value * (long long)(1 << FRACTION);	// to fixed point
	temp *= (long long)SinTable[angle];						// multiply with Sin
	temp >>= FRACTION;										// bitshift correction
	temp /= (1 << FRACTION);								// convert back	
	
	return (int)temp;										// cast to integer
}

// Value multiplied by Cos of angle
int cosAngle(int value, int angle)
{
	long long temp;
	
	while (angle < 0)
		angle += ANGLES;
	while (angle >= ANGLES)
		angle -= ANGLES;
	
	temp = (long long)value * (long long)(1 << FRACTION);	// to fixed point
	temp *= (long long)CosTable[angle];						// multiply with Cos
	temp >>= FRACTION;										// bitshift correction
	temp /= (1 << FRACTION);								// convert back	
	
	return (int)temp;										// cast to integer
}

// 2D dot product
long dot2D(const struct Point2D* p1, const struct Point2D* p2)
{
	return (p1->x * p2->x) + (p1->y * p2->y);
}

// 2D cross product
long cross2D(const struct Point2D* p1, const struct Point2D* p2)
{
	return (p1->x * p2->y) + (p1->y * p2->x);
}

// Subtract positions between 2D points
void sub2D(const struct Point2D* p1, const struct Point2D* p2, struct Point2D* result)
{
	result->x = p1->x - p2->x;
	result->x = p1->y - p2->y;
}

// 3D dot product
long dot3D(const struct Point3D* p1, const struct Point3D* p2)
{
	return (p1->x * p2->x) + (p1->y * p2->y) + (p1->z * p2->z);
}

// Subtract positions between 3D points
void sub3D(const struct Point3D* p1, const struct Point3D* p2, struct Point3D* result)
{
	result->x = p1->x - p2->x;
	result->x = p1->y - p2->y;
	result->z = p1->z - p2->z;
}

// Sort 2D points vertically first top to bottom, then horizontally left to right
void sortPair(struct Point2D** p1, struct Point2D** p2)
{
    if (((*p1)->y > (*p2)->y) || ((*p1)->y == (*p2)->y && (*p1)->x > (*p2)->x))
	{
    	struct Point2D* tmp = *p1;
    	*p1 = *p2;
    	*p2 = tmp;
    }
}

// Check which side of a line (p2 to p3) a 2D point (p1) falls on
int orient2D(const struct Point2D* p1, const struct Point2D* p2, const struct Point2D* p3)
{
	return ((p2->x - p1->x) * (p3->y - p1->y)) - ((p2->y - p1->y) * (p3->x - p1->x));
}

// Test if two line segments intersect
int lineSegIntersect(const struct Point2D* p1, const struct Point2D* p2, // 1st line
					 const struct Point2D* p3, const struct Point2D* p4, // 2nd line
					 struct Point2D* intersection)
{
	long a1, a2, b1, b2, c1, c2;	
	long r1, r2, r3, r4;			
	long denom, offset, num;
	
	// Coefficients of line equations
	// a1 x + b1 x + c1 == 0
	a1 = p2->y - p1->y;
	b1 = p1->x - p2->x;
	c1 = cross2D(p2, p1);
	
	// Check sign values
	r3 = (a1 * p3->x) + (b1 * p3->y) + c1;
	r4 = (a1 * p4->x) + (b1 * p4->y) + c1;
	
	// If p3 and p4 are on the same side of 1st line, no intersection
	if (r3 != 0 && r4 != 0 && sameSigns(r3, r4))
		return DONT_INTERSECT;
	
	// Coefficients of line equations
	a2 = p4->y - p3->y;
	b2 = p3->x - p4->x;
	c2 = cross2D(p4, p3);
	
	// Check sign values
	r1 = (a2 * p1->x) + (b2 * p1->y) + c2;
	r2 = (a2 * p2->x) + (b2 * p2->y) + c2;
	
	// If p3 and p4 are on the same side of 2nd line, no intersection
	if (r1 != 0 && r2 != 0 && sameSigns(r1, r2))
		return DONT_INTERSECT;
	
	// Else, find intersection point
	denom = (a1 * b2) - (a2 * b1);
	
	// Equal coefficients indicate collinear lines
	if (denom == 0)
		return COLLINEAR;
	
	// Round the number instead of truncating: denom/2
	offset = denom < 0 ? -denom/2 : denom/2;
	
	num = (b1 * c2) - (b2 * c1);
	intersection->x = (num < 0 ? num - offset : num + offset) / denom;
	
	num = (a2 * c1) - (a1 * c2);
	intersection->y = (num < 0 ? num - offset : num + offset) / denom;
	
	return DO_INTERSECT;
}

struct Point2D* newPoint2D(long x, long y)
{
	struct Point2D* new = (struct Point2D*)malloc(sizeof(struct Point2D));
	
	new->x = x;
	new->y = y;
	
	return new;
}

struct Point3D* newPoint3D(long x, long y, long z)
{
	struct Point3D* new = (struct Point3D*)malloc(sizeof(struct Point3D));
	
	new->x = x;
	new->y = y;
	new->z = z;
	
	return new;
}

struct Vertex2D* newVertex2D(long x, long y, byte color)
{
	struct Vertex2D* new = (struct Vertex2D*)malloc(sizeof(struct Vertex2D));
	
	new->x = x;
	new->y = y;
	new->color = color;
	
	return new;
}

struct Vertex3D* newVertex3D(long x, long y, long z, byte color)
{
	struct Vertex3D* new = (struct Vertex3D*)malloc(sizeof(struct Vertex3D));
	
	new->x = x;
	new->y = y;
	new->z = z;
	new->color = color;
	
	return new;
}

struct Triangle2D* newTriangle2D(long ax, long ay, long bx, long by, long cx, long cy, byte color)
{
	struct Triangle2D* new = (struct Triangle2D*)malloc(sizeof(struct Triangle2D));
	
	new->point[0] = newPoint2D(ax, ay);
	new->point[1] = newPoint2D(bx, by);
	new->point[2] = newPoint2D(cx, cy);
	new->color = color;
	
	return new;
}

struct Triangle2D* newTriangle2D_P(const struct Point2D* p1, const struct Point2D* p2, const struct Point2D* p3, byte color)
{
	struct Triangle2D* new = (struct Triangle2D*)malloc(sizeof(struct Triangle2D));
	
	new->point[0] = p1;
	new->point[1] = p2;
	new->point[2] = p3;
	new->color = color;
	
	return new;
}

struct Triangle3D* newTriangle3D(long ax, long ay, long az, long bx, long by, long bz, long cx, long cy, long cz, byte color)
{
	struct Triangle3D* new = (struct Triangle3D*)malloc(sizeof(struct Triangle3D));
	
	new->point[0] = newPoint3D(ax, ay, az);
	new->point[1] = newPoint3D(bx, by, bz);
	new->point[2] = newPoint3D(cx, cy, cz);
	new->color = color;
	
	return new;
}

struct Triangle3D* newTriangle3D_P(const struct Point3D* p1, const struct Point3D* p2, const struct Point3D* p3, byte color)
{
	struct Triangle3D* new = (struct Triangle3D*)malloc(sizeof(struct Triangle3D));
	
	new->point[0] = p1;
	new->point[1] = p2;
	new->point[2] = p3;
	new->color = color;
	
	return new;
}