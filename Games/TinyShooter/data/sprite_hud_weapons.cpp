#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_hud_weapons_pixels[] =
{
	0x0000,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x0000,
	0xffff,0xffff,0x7bef,0x0000,0x0000,0x0000,0x7bef,0xffff,0x7bef,0x0000,0x0000,0x0000,0x7bef,0xffff,0xffff,
	0xffff,0x7bef,0x0000,0x0000,0x0000,0x0000,0x0000,0x7bef,0x0000,0x0000,0x0000,0x0000,0x0000,0x7bef,0xffff,
	0xffff,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xffff,
	0xffff,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xffff,
	0xffff,0x7bef,0x0000,0x0000,0x0000,0x0000,0x0000,0x7bef,0x0000,0x0000,0x0000,0x0000,0x0000,0x7bef,0xffff,
};

const uint8 sprite_hud_weapons_alpha[] =
{
	0x00,0x80,0xff,0xff,0xff,0xff,0xff,0x80,0xff,0xff,0xff,0xff,0xff,0x80,0x00,
	0x80,0xff,0xb3,0xb3,0xb3,0xb3,0xb3,0xff,0xb3,0xb3,0xb3,0xb3,0xb3,0xff,0x80,
	0xff,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xff,
	0xff,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xff,
	0xff,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xff,
	0xff,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xb3,0xff,
};

extern "C" const Image sprite_hud_weapons;
const Image sprite_hud_weapons =
{
	15,6,
	(uint16*)&sprite_hud_weapons_pixels,
	(uint8*)&sprite_hud_weapons_alpha,
	(uint8*)"sprite_hud_weapons",
};
