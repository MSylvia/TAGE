//
//  fp2d.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-08.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "fp2d.h"

fp2d::fp2d()
{
	
}

fp2d::fp2d( const fp2d& _o )
{
	x = _o.x;
	y = _o.y;
}

void fp2d::operator += ( const fp2d& _o )
{
	x += _o.x;
	y += _o.y;
}

void fp2d::operator *= ( const FixedPoint& _o )
{
	x *=_o;
	y *=_o;
}
