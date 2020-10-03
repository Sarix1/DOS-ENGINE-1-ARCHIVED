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
	temp = (long long)value * (long long)(1 << FRACTION);	// to fixed point
	temp *= (long long)SinTable[angle];						// multiply with Sin
	temp >>= FRACTION;										// bitshift correction
	temp += FRACTION * 160;
	temp /= (1 << FRACTION);								// convert back	
	return (int)temp;										// cast to integer
}

// Value multiplied by Cos of angle
int cosAngle(int value, int angle)
{
	long long temp;
	temp = (long long)value * (long long)(1 << FRACTION);	// to fixed point
	temp *= (long long)CosTable[angle];						// multiply with Cos
	temp >>= FRACTION;										// bitshift correction
	temp += FRACTION * 160;
	temp /= (1 << FRACTION);								// convert back	
	return (int)temp;										// cast to integer
}