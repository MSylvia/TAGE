#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_sparrow_02_pixels[] =
{
	0x0000,0xe923,0xe923,
	0xea23,0xe923,0x0000,
	0x0000,0xe923,0xe923,
};

const uint8 sprite_enemy_sparrow_02_alpha[] =
{
	0x00,0xff,0xff,
	0xff,0xff,0x00,
	0x00,0xff,0xff,
};

extern "C" const Image sprite_enemy_sparrow_02;
const Image sprite_enemy_sparrow_02 =
{
	3,3,
	(uint16*)&sprite_enemy_sparrow_02_pixels,
	(uint8*)&sprite_enemy_sparrow_02_alpha,
	(uint8*)"sprite_enemy_sparrow_02",
};
