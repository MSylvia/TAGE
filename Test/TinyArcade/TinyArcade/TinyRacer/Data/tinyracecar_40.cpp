#include "Image.h"

unsigned short tinyracecar_40_pixels[] =
{
	0x0000,0x0000,0x0000,0xf986,0xf965,0x0000,0x0000,
	0x0000,0x0000,0x1800,0x4882,0xf986,0xf986,0x0000,
	0x0000,0x0000,0xf966,0x3861,0x2841,0xf165,0x0000,
	0x0000,0xf965,0xf966,0xf986,0x58a2,0x1000,0x0000,
	0x0000,0xf966,0xf986,0xf986,0xf986,0x80a2,0x0000,
	0x0000,0xf924,0xf965,0xf966,0xf800,0x0000,0x0000,
	0x0000,0x0000,0x0000,0xf965,0x0000,0x0000,0x0000,
};

unsigned char tinyracecar_40_alpha[] =
{
	0x00,0x00,0x00,0x0a,0x26,0x00,0x00,
	0x00,0x00,0x19,0xa7,0xf2,0x4e,0x00,
	0x00,0x00,0x8a,0xff,0xff,0xff,0x00,
	0x00,0x76,0xea,0xff,0xff,0x83,0x00,
	0x00,0xdd,0xff,0xff,0xad,0x19,0x00,
	0x00,0x0e,0xbb,0xb4,0x02,0x00,0x00,
	0x00,0x00,0x00,0x3b,0x00,0x00,0x00,
};

Image tinyracecar_40 =
{
	7,7,
	(unsigned short*)&tinyracecar_40_pixels,
	(unsigned char*)&tinyracecar_40_alpha,
};