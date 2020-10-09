#include <stdio.h>
#include "TYPES.H"

struct bitmap
{
    word width;
    word height;
    byte palette[256*3];
    byte near* data;
};

void fskip(FILE* fp, int bytes);
void loadBitmap(char* file, struct bitmap* b, int palette_only);
void setPixelsFromBitmap(struct bitmap* bmp, int x, int y);
void setPalette(byte* palette);
