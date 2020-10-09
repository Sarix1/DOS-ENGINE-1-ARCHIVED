#include <stdio.h>
#include "TYPES.H"

struct Bitmap
{
    word width;
    word height;
    byte palette[256*3];
    byte near* data;
};

void fskip              (FILE* fp, int bytes);
void loadBitmap         (char* file, struct Bitmap* b, int palette_only);
void setPixelsFromBitmap(struct Bitmap* bmp, int x, int y);
void setPalette         (byte* palette);
