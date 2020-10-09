#include "TYPES.H"

// ANSI escape color codes
enum color
{
	BLACK	= 0,
	RED		= 1,
	GREEN	= 2,
	YELLOW	= 3,
	BLUE	= 4,
	PURPLE	= 5,
	CYAN	= 6,
	WHITE	= 7,
	FG		= 30,
	BG		= 40,
	LIGHT	= 60
};

void setTextPosition(int x, int y);
void setTextColor(byte fg, byte bg);
void putText(char* string, byte fg, byte bg, int x, int y);
void resetText();
