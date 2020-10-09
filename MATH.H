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
#define min(a, b)			((a < b) ? (a) : (b))
#define max(a, b)			((a > b) ? (a) : (b))
#define min3(a, b, c)		(min(min((a), (b)), (c)))
#define max3(a, b, c)		(max(max((a), (b)), (c)))
#define sign(x)				(((x) < 0) ? -1 : (((x) > 0) ? 1 : 0))
#define angToDeg(x)			((double)(x) * DEGREES / ANGLES)
#define degToAng(x)			((double)(x) * ANGLES / DEGREES)

struct Point2D	{int x, y;};
struct Point3D	{int x, y, z;};
struct Vector2D	{long x, y;};
struct Vector3D	{long x, y, z;};
struct Vertex2D {int x, y, color;};
struct Vertex3D {int x, y, z, color;};

// Tables
long			SinCosTable[ANGLES + ANGLES/4];
long*			SinTable = SinCosTable;
long*			CosTable = &(SinCosTable[ANGLES/4]);
unsigned int	SinAcosTable[TRIGONOMETRY];

// Math functions
void initTrigTables();
int sinAngle(int value, int angle);
int cosAngle(int value, int angle);