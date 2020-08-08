// Math constants
// #ifndef M_PI
#define M_PI				3.14159265358979323846264338327950288
// #endif
#define DEGREES				360
#define ANGLES				1024//4096
// Precision of trigonometric calculations
#define TRIGONOMETRY		1024//4096
#define FRACTION			14
// Magnitude difference between TRIGONOMETRY and (1<<FRACTION)
#define FRAC_TO_TRIG		4

// Macros
#define sign(x)				(((x) < 0) ? -1 : (((x) > 0) ? 1 : 0))
#define angToDeg(x)			((double)(x) * DEGREES / ANGLES)
#define degToAng(x)			((double)(x) * ANGLES / DEGREES)

// Tables
long			SinCosTable[ANGLES + ANGLES/4];
long*			SinTable = SinCosTable;
long*			CosTable = &(SinCosTable[ANGLES/4]);
unsigned int	SinAcosTable[TRIGONOMETRY];

// Math functions
void initTrigTables();
int sinAngle(int value, int angle);
int cosAngle(int value, int angle);