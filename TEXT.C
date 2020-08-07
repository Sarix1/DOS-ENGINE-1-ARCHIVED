#include <stdio.h>
#include <conio.h>
#include "TEXT.H"

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
	system("cls");
	putText("", 0, 0, 0, 0);
}