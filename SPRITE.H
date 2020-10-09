#include "TYPES.H"

struct sprite
{
	word width, height;
	byte* data;
};

void blitSprite(struct sprite* sprite, int x, int y);