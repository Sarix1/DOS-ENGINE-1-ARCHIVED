#include "TYPES.H"

struct Sprite
{
	word width, height;
	byte* data;
};

void blitSprite(struct Sprite* sprite, int x, int y);