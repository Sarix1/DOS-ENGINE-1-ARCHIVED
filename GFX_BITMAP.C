#include "TEXT.H"
#include "VIDEO.H"
#include "GFX_BITMAP.H"

// Skip bytes in a file
void fskip(FILE* fp, int bytes)
{
    int i;
    for (i = 0; i < bytes; i++)
        fgetc(fp);
}

// Store a bitmap into a struct
void loadBitmap(char* file, struct BITMAP* b)
{
    FILE *fp;
    long index;
    unsigned int x, y;
    unsigned int num_colors;
    
    // Open the file
    if ((fp = fopen(file, "rb")) == NULL)
    {
        setVideo(TEXT_MODE); resetText();
        printf("Could not open file: %s.\n", file);
        exit(1);
    }
    
    // Ensure it is a valid bitmap file
    if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
    {
        fclose(fp);
        setVideo(TEXT_MODE); resetText();
        printf("Not a valid bitmap file: %s.\n", file);
        exit(1);
    }
    
    // Get width and height
    fskip(fp, 16);
    fread(&b->width, sizeof(word), 1, fp);
    fskip(fp, 2);
    fread(&b->height, sizeof(word), 1, fp);
    fskip(fp, 22);
    fread(&num_colors, sizeof(word), 1, fp);
    fskip(fp, 6);
    
    if (num_colors == 0)
        num_colors = 256;
    
    // Allocate memory for bitmap data
    b->data = (byte far*) malloc((word)(b->width * b->height));
    /*
    if ((b->data = (byte*)malloc(b->width * b->height)) == NULL)
    {
        fclose(fp);
        setVideo(TEXT_MODE); resetText();
        printf("Failed to allocate memory for bitmap file: %s.\n", file);
        exit(1);
    } 
    */
    
    /* read the bitmap */
    for (index = (b->height-1) * b->width; index >= 0; index -= b->width)
    {
        for (x = 0; x < b->width; x++)
        {
            b->data[(word)(index+x)] = (byte)fgetc(fp);
        }
    }
    
    // load palette
    for (index = 0; index < num_colors; index++)
    {
        b->palette[(int)(index*3 + 2)] = fgetc(fp) >> 2;
        b->palette[(int)(index*3 + 1)] = fgetc(fp) >> 2;
        b->palette[(int)(index*3 + 0)] = fgetc(fp) >> 2;
        x = fgetc(fp);
    }
    
    fclose(fp);
}

// Copy a bitmap to the screen buffer
void setPixelsBitmap(struct BITMAP* bmp, int x, int y)
{
    int j;
    word offset = 0;
    byte far* p = drawTarget + (y<<8) + (y<<6) + x;
    
    for (j = 0; j < bmp->height; j++)
    {
        memcpy(p, &bmp->data[offset], bmp->width);
        offset += bmp->width;
        p += SCREEN_WIDTH;
    }
}

// Set 256 color palette
void setPalette(byte* palette)
{
    int i;
    outp(PALETTE_INDEX, 0);
    for (i = 0; i < 256 * 3; i++)
        outp(PALETTE_DATA, palette[i]);
}