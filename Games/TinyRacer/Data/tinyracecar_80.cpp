#include "Types.h"
#include "Image.h"

uint16 tinyracecar_80_pixels[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xf986,0xf986,0xd145,0x1000,0xf986,0x0000,
	0x0000,0xf966,0xf986,0xf986,0x0000,0xf986,0x0000,
	0x0000,0xf966,0xf966,0xf986,0x1000,0xd145,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

uint8 tinyracecar_80_alpha[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xff,0xf3,0xf3,0xf8,0xc9,0x00,
	0x00,0xf6,0xff,0xff,0xff,0xfc,0x00,
	0x00,0xc4,0xf9,0xf3,0xf3,0xff,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

Image tinyracecar_80 =
{
	7,7,
	(uint16*)&tinyracecar_80_pixels,
	(uint8*)&tinyracecar_80_alpha,
	(uint8*)"tinyracecar_80",
};
