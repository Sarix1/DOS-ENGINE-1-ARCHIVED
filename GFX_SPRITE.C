#include "VIDEO.H"

//Draw a sprite with transparency
void blitSprite(struct sprite* sprite, int x, int y)
{
	int i, j;
	
	// Draw the sprite with transparency
	for (i = 0; i < sprite->height; i++)
	{
		for (j = 0; j < sprite->width; j++)
		{
			if (sprite->data[i * sprite->width + j] != 0)
				drawTarget[(y+i) * SCREEN_WIDTH + x+j] = sprite->data[i * sprite->width + j];
		}
	}
}