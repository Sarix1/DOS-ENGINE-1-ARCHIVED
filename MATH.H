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
struct Triangle2D	{struct Point2D point[3];	};
struct Triangle3D	{struct Point3D point[3];	};
struct Polygon2D	{struct Point2D* point;		};
struct Polygon3D	{struct Point3D* point;		};

// Tables
long		SinCosTable[ANGLES + ANGLES/4];
long*		SinTable = SinCosTable;
long*		CosTable = &(SinCosTable[ANGLES/4]);
unsigned	SinAcosTable[TRIGONOMETRY];

// Math functions
void initTrigTables	();
int sinAngle		(int value, int angle);
int cosAngle		(int value, int angle);
long dot2D			(struct Point2D* p1, struct Point2D* p2);
long cross2D		(struct Point2D* p1, struct Point2D* p2);
void sub2D			(struct Point2D* p1, struct Point2D* p2, struct Point2D* result);
long dot3D			(struct Point3D* p1, struct Point3D* p2);
void sub3D			(struct Point3D* p1, struct Point3D* p2, struct Point3D* result);
void sortPair		(struct Point2D* p1, struct Point2D* p2);
int orient2D		(struct Point2D* p1, struct Point2D* p2, struct Point2D* p3);
int lineSegIntersect(struct Point2D* p1, struct Point2D* p2,
					 struct Point2D* p3, struct Point2D* p4, struct Point2D* intersection);
