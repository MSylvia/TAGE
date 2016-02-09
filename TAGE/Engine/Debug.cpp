//
//  Debug.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-02-09.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>
#include "Debug.h"

#ifdef TAGE_TARGET_MACOSX
#else
#include <Arduino.h>
#endif

void debugInit()
{
#ifdef TAGE_TARGET_MACOSX
#else
	Serial.begin( 9600 );
#endif
}

void debugLog( const char* _pszFormat, ... )
{
	const int SIZE = 256;
	char buffer[ SIZE ];
	va_list args;
	va_start( args, _pszFormat );
	
	vsnprintf( buffer, SIZE-1, _pszFormat, args );
#ifdef TAGE_TARGET_MACOSX
	printf( buffer );
#else
	Serial.print( buffer );
#endif
	
	va_end( args );
}
