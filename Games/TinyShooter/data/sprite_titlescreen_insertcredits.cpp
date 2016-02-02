#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_titlescreen_insertcredits_pixels[] =
{
	0xff7a,0xff7a,0xff7a,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xff7a,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xff7a,0x0000,0x0000,0xff7a,0xff7a,0xff7a,0xff5a,0x0000,0xff5a,0xff7a,0xff7a,0x0000,0xff5a,0xff7a,0xff7a,0xff5a,0x0000,0xff5a,0xff7a,0xff7a,0x0000,0xff7a,0xff7a,0xff7a,0x0000,0x0000,0xff5a,0xff7a,0xff7a,0x0000,0xff5a,0xff7a,0xff7a,0x0000,0xff5a,0xff7a,0xff7a,0xff5a,0x0000,0xff5a,0xff7a,0xff7a,0xff7a,0x0000,0x0000,0x0000,0xff7a,0xff7a,0xff7a,0x0000,0xff5a,0xff7a,0xff7a,
	0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0xff7a,0xff7a,0x0000,0x0000,0xff7a,0xff7a,0xff7a,0xff7a,0x0000,0xff7a,0x0000,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff7a,0xff7a,0xff7a,0xff7a,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0x0000,0xff7a,0xff7a,0x0000,
	0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0x0000,0xff7a,0xff7a,0x0000,0xff7a,0x0000,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff7a,0xff7a,
	0xff7a,0xff7a,0xff7a,0x0000,0xff7a,0x0000,0x0000,0xff7a,0x0000,0xff7a,0xff7a,0xff5a,0x0000,0xff5a,0xff7a,0xff7a,0xff5a,0x0000,0xff7a,0x0000,0x0000,0x0000,0x0000,0xff5a,0xff7a,0x0000,0x0000,0xff5a,0xff7a,0xff7a,0x0000,0xff7a,0x0000,0x0000,0x0000,0xff5a,0xff7a,0xff7a,0xff5a,0x0000,0xff5a,0xff7a,0xff7a,0xff7a,0x0000,0xff7a,0x0000,0x0000,0xff5a,0xff7a,0x0000,0xff7a,0xff7a,0xff5a,
};

const uint8 sprite_titlescreen_insertcredits_alpha[] =
{
	0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,
	0x00,0xff,0x00,0x00,0xff,0xff,0xff,0x66,0x00,0x66,0xff,0xff,0x00,0x66,0xff,0xff,0x66,0x00,0x66,0xff,0xff,0x00,0xff,0xff,0xff,0x00,0x00,0x66,0xff,0xff,0x00,0x66,0xff,0xff,0x00,0x66,0xff,0xff,0x66,0x00,0x66,0xff,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x66,0xff,0xff,
	0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0xff,0x00,
	0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xff,
	0xff,0xff,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0xff,0x66,0x00,0x66,0xff,0xff,0x66,0x00,0xff,0x00,0x00,0x00,0x00,0x66,0xff,0x00,0x00,0x66,0xff,0xff,0x00,0xff,0x00,0x00,0x00,0x66,0xff,0xff,0x66,0x00,0x66,0xff,0xff,0xff,0x00,0xff,0x00,0x00,0x66,0xff,0x00,0xff,0xff,0x66,
};

extern "C" const Image sprite_titlescreen_insertcredits;
const Image sprite_titlescreen_insertcredits =
{
	54,5,
	(uint16*)&sprite_titlescreen_insertcredits_pixels,
	(uint8*)&sprite_titlescreen_insertcredits_alpha,
	(uint8*)"sprite_titlescreen_insertcredits",
};
