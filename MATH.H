#include "TYPES.H"

// Math constants
// #ifndef M_PI
#define M_PI				3.14159265358979323846264338327950288
// #endif
#define DEGREES				360
#define ANGLES				1024
// Precision of trigonometric calculations
#define TRIG_PRECISION		10
#define TRIGONOMETRY		(1<<TRIG_PRECISION) 		// 1024
#define FRACTION			14							// 16384
// Magnitude difference between TRIGONOMETRY and (1<<FRACTION)
#define FRAC_TO_TRIG		(FRACTION - TRIG_PRECISION)	// 4

// Macros
#define min(a,b)			((a < b) ? (a) : (b))
#define max(a,b)			((a > b) ? (a) : (b))
#define min3(a,b,c)			(min(min((a), (b)), (c)))
#define max3(a,b,c)			(max(max((a), (b)), (c)))
#define sign(x)				(((x) < 0) ? -1 : (((x) > 0) ? 1 : 0))
#define sameSigns(a,b)		(((long) ((unsigned long)a ^ (unsigned long)b)) >= 0)
#define angToDeg(x)			((double)(x) * DEGREES / ANGLES)
#define degToAng(x)			((double)(x) * ANGLES / DEGREES)

// Enums
enum direction
{
	LEFT	= 0,
	RIGHT	= 1,
	UP		= 2,
	DOWN	= 3
};

enum align
{
	TOP		= 0,
	BOTTOM	= 1
};

enum intersect
{
	DONT_INTERSECT	= 0,
	DO_INTERSECT	= 1,
	COLLINEAR		= 2
};

// Structs
struct Point2D		{long x, y;		};
struct Point3D		{long x, y, z;	};
struct Vertex2D 	{long x, y;		byte color;	};
struct Vertex3D 	{long x, y, z;	byte color;	};
struct Triangle2D	{struct Point2D* point[3];	byte color;};
struct Triangle3D	{struct Point3D* point[3];	byte color;};
struct Polygon2D	{struct Point2D* point;		byte color;};
struct Polygon3D	{struct Point3D* point;		byte color;};

// Tables
long		SinCosTable[ANGLES + ANGLES/4];
long*		SinTable = SinCosTable;
long*		CosTable = &(SinCosTable[ANGLES/4]);
unsigned	SinAcosTable[TRIGONOMETRY];

// Math functions
void initTrigTables	();
int sinAngle		(int value, int angle);
int cosAngle		(int value, int angle);
long dot2D			(const struct Point2D* p1, const struct Point2D* p2);
long cross2D		(const struct Point2D* p1, const struct Point2D* p2);
void sub2D			(const struct Point2D* p1, const struct Point2D* p2, struct Point2D* result);
long dot3D			(const struct Point3D* p1, const struct Point3D* p2);
void sub3D			(const struct Point3D* p1, const struct Point3D* p2, struct Point3D* result);
void sortPair		(struct Point2D** p1, struct Point2D** p2);
int orient2D		(const struct Point2D* p1, const struct Point2D* p2, const struct Point2D* p3);
int lineSegIntersect(const struct Point2D* p1, const struct Point2D* p2,
					 const struct Point2D* p3, const struct Point2D* p4, struct Point2D* intersection);

// New structs
struct Point2D*		newPoint2D		(long x, long y);
struct Point3D*		newPoint3D		(long x, long y, long z);
struct Vertex2D*	newVertex2D		(long x, long y, byte color);
struct Vertex3D*	newVertex3D		(long x, long y, long z, byte color);
struct Triangle2D*	newTriangle2D	(long ax, long ay, long bx, long by, long cx, long cy, byte color);
struct Triangle2D*	newTriangle2D_P	(const struct Point2D* p1, const struct Point2D* p2, const struct Point2D* p3, byte color);
struct Triangle3D*	newTriangle3D	(long ax, long ay, long az, long bx, long by, long bz, long cx, long cy, long cz, byte color);
struct Triangle3D*	newTriangle3D_P	(const struct Point3D* p1, const struct Point3D* p2, const struct Point3D* p3, byte color);