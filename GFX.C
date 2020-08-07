#include <stdio.h>
#include <conio.h>

// ANSI escape color codes
enum color
{
	BLACK	= 0,
	RED		= 1,
	GREEN	= 2,
	YELLOW	= 3,
	BLUE	= 4,
	MAGENTA	= 5,
	CYAN	= 6,
	WHITE	= 7,
	FG		= 30,
	BG		= 40,
	LIGHT	= 60
};

void setTextPosition(int x, int y)
{
	// Escape code to set the cursor position
	printf("%c[%d;%df", 0x1B, y+1, x+1);
}

void setTextColor(int fg, int bg)
{
	// Escape code to set fore/background colours
	printf("%c[1;%d;%dm", 0x1B, fg, bg);
}

// Write text to a specific position with foreground and background colours
void putText(char* string, int fg, int bg, int x, int y)
{
	setTextPosition(x, y);
	setTextColor(fg, bg);
	printf("%s", string);
}

void resetText()
{
	putText("", 0, 0, 0, 0);
}

int main()
{
	system("cls");
	putText("Hello", FG+BLUE, BG+BLACK, 0, 0);
	putText("World", FG+RED, BG+BLACK, 2, 1);
	setTextColor(0, 0);
	
	return 0;
}