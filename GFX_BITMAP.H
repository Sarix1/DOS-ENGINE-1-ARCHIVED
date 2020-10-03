#include <stdio.h>
#include "TYPES.H"

struct BITMAP
{
    word width;
    word height;
    byte palette[256*3];
    byte far* data;
};

void fskip(FILE* fp, int bytes);
void loadBitmap(char* file, struct BITMAP* b);
void setPixelsBitmap(struct BITMAP* bmp, int x, int y);
void setPalette(byte* palette);
