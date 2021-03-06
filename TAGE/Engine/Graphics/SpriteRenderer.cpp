//
//  SpriteRenderer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-26.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "Engine/Graphics/SpriteRenderer.h"
#include "Engine/Graphics/Screen.h"
#include "Engine/Graphics/Image.h"
#include "Engine/BitHelpers.h"
#include "Engine/Debug.h"

SpriteRenderer spriteRenderer;

SpriteRenderer::SpriteRenderer()
{
	Reboot();
}

void SpriteRenderer::Reboot()
{
	int i = 0;
	for( i=0; i<MAX_SPRITES; i++ )
		m_sprite[ i ].Reboot();

	for( i=0; i<MAX_SPRITES+1; i++ )
		m_sortedSprites[ i ] = NULL;
}

Sprite* SpriteRenderer::AllocateSprite( const Image* _image )
{
	//printf("Allocating sprite from image \"%s\"\n", _image->DEBUG_name );
	
	int i = 0;
	for( i=0; i<MAX_SPRITES; i++ )
	{
		Sprite* sprite = &m_sprite[ i ];
		if( sprite->image == NULL )
		{
			sprite->image = _image;
			SetBit( sprite->flags, SPRITE_FLAG_ENABLED );
			sprite->rendererIndex = i;
			//printf("using index %i\n", i );
			
			AddSpriteToSortList( sprite );
			SortAllSprites();
			return sprite;
		}
	}
	
	debugLog("Out of sprites, gangstah!\n");

	return NULL;
}

void SpriteRenderer::AddSpriteToSortList( Sprite* _pSprite )
{
	int i;
	for( i=0; i<MAX_SPRITES; i++ )
	{
		if( m_sortedSprites[ i ] == NULL )
		{
			m_sortedSprites[ i ] = _pSprite;
			return;
		}
	}
}

void SpriteRenderer::FreeSprite( Sprite* _spriteInstance )
{
	//printf("freeing sprite from image %s\n", _spriteInstance->image->DEBUG_name );
	_spriteInstance->image = NULL;
	_spriteInstance->owner = NULL;
	_spriteInstance->rendererIndex = INVALID_SPRITE_RENDERER_INDEX;
	ClrBit( _spriteInstance->flags, SPRITE_FLAG_ENABLED );
}

Sprite* SpriteRenderer::GetSprite( int _spriteRendererIndex )
{
	return &m_sprite[ _spriteRendererIndex ];
}

void SpriteRenderer::FrameStart()
{
	m_currentScanline = 0;
	
	int i;
	for( i=0; i<MAX_SPRITES+1; i++ )
	{
		m_potentialSprites[ i ] = NULL;
		m_scanlineSprites[ i ] = NULL;
	}
	
	int iPot = 0;
	int iCurr = 0;
	for( i=0; i<MAX_SPRITES; i++ )
	{
		Sprite* sprite = m_sortedSprites[ i ]; //&m_sprite[ i ];
		if( sprite == NULL )
			break;
		
		//printf("Sprite index %i. Image=0x%016llx\n", i, sprite->image );
		if( HasBit( sprite->flags, SPRITE_FLAG_ENABLED ) && (sprite->image != NULL))
		{
			// Refresh sprite bounds and other render related flags
			sprite->PreRender();

			//
			if( sprite->boundsTop > 0 )
			{
				m_potentialSprites[ iPot ] = sprite;
				sprite->FrameStart();
				iPot++;
			} else if( sprite->boundsBottom > 0 )
			{
				m_scanlineSprites[ iCurr ] = sprite;
				sprite->FrameStart();
				iCurr++;
			}
		}
	}
	
	/*
	// NULL terminated lists
	m_potentialSprites[ iPot ] = NULL;
	m_scanlineSprites[ iCurr ] = NULL;
	 */
}

void SpriteRenderer::NextScanline( bool _debugPrint )
{
	m_currentScanline++;
	
	
	//
	// First we iterate the sprites from the last scanline to see if we can remove any
	//
	Sprite** renderSpriteList = m_scanlineSprites;
	Sprite* sprite = *renderSpriteList;
	while( sprite != NULL )
	{
		if( sprite->boundsBottom == m_currentScanline )
		{
			// This sprite has been passed and should no longer be considered for rendering. Remove it from list and check the next sprite.
			Sprite** removeList = renderSpriteList;
			while( *removeList != NULL )
			{
				*removeList = *(removeList+1);
				removeList++;
			}
		} else
		{
			sprite->NextScanLine();
			
			// Next sprite in list
			renderSpriteList++;
		}
		
		// Pick the next sprite
		sprite = *renderSpriteList;
	}

	//
	// Then we iterate the potential sprites and add them to the list of scanline sprites
	//
	bool sortSprites = false;
	Sprite** potentialSpriteList = m_potentialSprites;
	sprite = *potentialSpriteList;
	while( sprite != NULL )
	{
		if( sprite->boundsTop == m_currentScanline )
		{
			// This sprite should be added to the list of rendered sprites
			*renderSpriteList = sprite;
			renderSpriteList++;
			sortSprites = true;
			
			// Also remove this sprite from the list of potential sprites
			Sprite** removeList = potentialSpriteList;
			while( *removeList != NULL )
			{
				*removeList = *(removeList+1);
				removeList++;
			}
		} else
		{
			// If we added a sprite to the render list we also remove that sprite from the list of
			// potential sprites. And if we've removed a sprite from the list of potential sprites
			// then we should not go to the next element in that list. So that is why we only go to
			// the next element of the list when we have not removed an entry from the list.
			potentialSpriteList++;
		}
		
		// Next sprite in the potential sprite list
		sprite = *potentialSpriteList;
	}
	
	if( sortSprites )
		SortScanlineSprites();
	
	//
	if( _debugPrint )
	{
		debugLog( "\n------------[ Scanline: %i\n", m_currentScanline );
		
		debugLog( "Current sprites: \n" );
		renderSpriteList = m_scanlineSprites;
		sprite = *renderSpriteList;
		while( sprite != NULL )
		{
			debugLog( "  Image x=%i, y=%i, w=%i, h=%i, left=%i, top=%i, right=%i, bottom=%i, data=0x%016llx\n", sprite->x, sprite->y, sprite->image->w, sprite->image->h, sprite->boundsLeft, sprite->boundsTop, sprite->boundsRight, sprite->boundsBottom, sprite->image->pixels );
			renderSpriteList++;
			sprite = *renderSpriteList;
		}
		
		debugLog( "Upcoming sprites: \n" );
		renderSpriteList = m_potentialSprites;
		sprite = *renderSpriteList;
		while( sprite != NULL )
		{
			debugLog( "  Image x=%i, y=%i, w=%i, h=%i, left=%i, top=%i, right=%i, bottom=%i, data=0x%016llx\n", sprite->x, sprite->y, sprite->image->w, sprite->image->h, sprite->boundsLeft, sprite->boundsTop, sprite->boundsRight, sprite->boundsBottom, sprite->image->pixels );
			renderSpriteList++;
			sprite = *renderSpriteList;
		}
	}
}

/*Sprite** SpriteRenderer::GetScanlineSprites()
{
	return m_scanlineSprites;
}*/

bool SpriteRenderer::RenderPixel( int _x, uint16* _pOutPixel, uint8* _pOutCollisionMask )
{
	// Clear collision mask
	*_pOutCollisionMask = 0;
	
	bool didRender = false;

	Sprite** sprites = m_scanlineSprites;
	Sprite* sprite = *sprites;

	while( sprite != NULL )
	{
		if((sprite->boundsLeft <= _x) && (_x < sprite->boundsRight))
		{
			/*
			int ofsx = _x - sprite->x;
			int ofsy = m_currentScanline - sprite->y;
			int ofs = sprite->GetOffset( ofsx, ofsy );
			 */
			
			uint8 alpha = 255;
			if( sprite->pAlphaData )
			{
				alpha = *sprite->pAlphaData;
				sprite->pAlphaData++;
			}
			/*
			if( sprite->image->alpha != NULL )
				alpha = sprite->image->alpha[ ofs ];*/
			
			/*
			uint16 rgb = sprite->image->pixels[ ofs ];
			if( sprite->flags & SPRITE_FLAG_DRAWWHITE )
				rgb = 0xffff;
			 */
			
			uint16 rgb = *sprite->pPixelData;
			sprite->pPixelData++;
			
			if( alpha == 0 )
			{
				// Skip
			} else if( alpha == 255 )
			{
				// Full overdraw
				*_pOutPixel = rgb;
				*_pOutCollisionMask |= (1<<sprite->collisionIndex);
				m_collisionSprites[ sprite->collisionIndex ] = sprite;
				didRender = true;
			}
			else
			{
				uint16 srccol = rgb;
				
				uint32 srcr = (srccol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 srcg = (srccol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 srcb = (srccol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				uint32 dsta = 255-alpha;
				uint16 dstcol = *_pOutPixel;
				uint32 dstr = (dstcol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 dstg = (dstcol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 dstb = (dstcol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				// Multiply
				uint32 outr = (((srcr*alpha)+(dstr*dsta)) >> 8) & COLORWIDTH_16_R;
				uint32 outg = (((srcg*alpha)+(dstg*dsta)) >> 8) & COLORWIDTH_16_G;
				uint32 outb = (((srcb*alpha)+(dstb*dsta)) >> 8) & COLORWIDTH_16_B;
				
				/*
				 // Additive
				 uint32 outr = ((srcr*srca)+(dstr<<8)) >> 8;
				 uint32 outg = ((srcg*srca)+(dstg<<8)) >> 8;
				 uint32 outb = ((srcb*srca)+(dstb<<8)) >> 8;
				 if( outr > COLORWIDTH_16_R ) outr = COLORWIDTH_16_R;
				 if( outg > COLORWIDTH_16_G ) outg = COLORWIDTH_16_G;
				 if( outb > COLORWIDTH_16_B ) outb = COLORWIDTH_16_B;
				 */
				
				uint16 out = (outr<<COLORSHIFT_16_R) + (outg<<COLORSHIFT_16_G) + (outb<<COLORSHIFT_16_B);
				
				*_pOutPixel = out;
			}
		}
		
		sprites++;
		sprite = *sprites;
	}
	
	//
	return didRender;
}

void SpriteRenderer::RenderScanline( uint16* _targetBuffer, uint8* _collisionBits, uint8* _collisionIndices )
{
	Sprite** sprites = m_scanlineSprites;
	Sprite* sprite = *sprites;
	
	while( sprite != NULL )
	{
		const Image* image = sprite->image;

		int drawLength = image->w;

		const uint16* color = &image->pixels[ sprite->readY ];
		const uint8* alphaData = NULL;
		if( image->alpha != NULL )
			alphaData = &image->alpha[ sprite->readY ];
		
		int drawx = sprite->boundsLeft;
		if( drawx < 0 )
		{
			int skip = -drawx;
			drawx = 0;
			color += skip;
			if( alphaData != NULL )
				alphaData += skip;
			drawLength -= skip;
		}
		
		int apa = drawx + drawLength;
		if( apa >= SCREEN_WIDTH )
		{
			drawLength -= (apa - SCREEN_WIDTH);
		}
		
		uint16* outBuffer = &_targetBuffer[ drawx ];
		uint8* collisionBits = &_collisionBits[ drawx ];
		uint8* collisionIndices = &_collisionIndices[ drawx << 3 ];
		
		while( drawLength > 0 )
		{
			drawLength--;
			
			
			uint8 alpha = 255;
			if( alphaData != NULL )
			{
				alpha = *alphaData;
				alphaData++;
			}
			/*
			 if( sprite->image->alpha != NULL )
				alpha = sprite->image->alpha[ ofs ];*/
			
			/*
			uint16 rgb = *sprite->pPixelData;
			sprite->pPixelData++;
			 */

			uint16 rgb = *color;
			color++;

			if( sprite->flags & SPRITE_FLAG_DRAWWHITE )
				rgb = 0xffff;
			
			if( alpha == 0 )
			{
				// Skip
				outBuffer++;
				collisionBits++;
				collisionIndices += 8;
			} else if( alpha == 255 )
			{
				// Full overdraw
				*outBuffer = rgb;
				outBuffer++;

				if( sprite->collisionIndex != 0 )
					*collisionBits |= (1<<sprite->collisionIndex);
				
				collisionBits++;
				
				collisionIndices[ sprite->collisionIndex ] = sprite->rendererIndex;
				collisionIndices += 8;

				/*
				*_pOutPixel = rgb;
				*_pOutCollisionMask |= (1<<sprite->collisionIndex);
				m_collisionSprites[ sprite->collisionIndex ] = sprite;
				didRender = true;
				 */
			}
			else
			{
				uint16 srccol = ((rgb&0x00ff)<<8) + ((rgb&0xff00)>>8);
				
				uint32 srcr = (srccol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 srcg = (srccol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 srcb = (srccol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				uint32 dsta = 255-alpha;
				uint16 dstcol2 = *outBuffer;
				uint16 dstcol = ((dstcol2&0x00ff)<<8) + ((dstcol2&0xff00)>>8);
				
				uint32 dstr = (dstcol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 dstg = (dstcol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 dstb = (dstcol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				// Multiply
				uint32 outr = (((srcr*alpha)+(dstr*dsta)) >> 8) & COLORWIDTH_16_R;
				uint32 outg = (((srcg*alpha)+(dstg*dsta)) >> 8) & COLORWIDTH_16_G;
				uint32 outb = (((srcb*alpha)+(dstb*dsta)) >> 8) & COLORWIDTH_16_B;
				
				/*
				 // Additive
				 uint32 outr = ((srcr*srca)+(dstr<<8)) >> 8;
				 uint32 outg = ((srcg*srca)+(dstg<<8)) >> 8;
				 uint32 outb = ((srcb*srca)+(dstb<<8)) >> 8;
				 if( outr > COLORWIDTH_16_R ) outr = COLORWIDTH_16_R;
				 if( outg > COLORWIDTH_16_G ) outg = COLORWIDTH_16_G;
				 if( outb > COLORWIDTH_16_B ) outb = COLORWIDTH_16_B;
				 */
				
				uint16 out = (outr<<COLORSHIFT_16_R) + (outg<<COLORSHIFT_16_G) + (outb<<COLORSHIFT_16_B);
				uint16 out2 = ((out&0x00ff)<<8) + ((out&0xff00)>>8);
				
				*outBuffer = out2;
				outBuffer++;

				/*
				*collisionBits |= (1<<sprite->collisionIndex);
				collisionBits++;
				
				collisionIndices[ sprite->collisionIndex ] = sprite->rendererIndex;
				collisionIndices += 8;
				*/
			}
		}
		sprites++;
		sprite = *sprites;
	}
}

void SpriteRenderer::SortAllSprites()
{
	SortSprites( m_sortedSprites );
}

void SpriteRenderer::SortScanlineSprites()
{
	SortSprites( m_scanlineSprites );
}

void SpriteRenderer::SortSprites( Sprite** _apSprites )
{
	// Bubble sort, woop!
	bool sortAgain = false;

	do
	{
		sortAgain = false;
		int i;
		for( i=MAX_SPRITES-2; i>=0; i-- )
		{
			Sprite* pSprA = _apSprites[ i+0 ];
			Sprite* pSprB = _apSprites[ i+1 ];
			if((pSprA != NULL) && (pSprB != NULL))
			{
				if( pSprA->sort > pSprB->sort )
				{
					// Sprites in the wrong order. Sort!
					_apSprites[ i+0 ] = pSprB;
					_apSprites[ i+1 ] = pSprA;
					sortAgain = true;
				}
			}
		}
	} while( sortAgain );
}

extern const char* stringFromBool( bool );

void SpriteRenderer::debugPrintStats()
{
	debugLog( "----------[ SpriteRenderer ]----------\n" );
	int numUsed = 0;
	int i;
	for( i=0; i<MAX_SPRITES; i++ )
	{
		Sprite* sprite = &m_sprite[ i ];
		debugLog("Sprite object %-3i -", i );
		debugLog(" Used: %-3s", stringFromBool( sprite->image != NULL ));
		if( sprite->image != NULL )
		{
			numUsed++;
			debugLog(" - Image: %s", sprite->image->DEBUG_name );
		}
		debugLog("\n");
	}

	debugLog("Sorted sprites:\n");
	for( i=0; i<MAX_SPRITES; i++ )
	{
		Sprite* sprite = m_sortedSprites[ i ];
		if( sprite == NULL )
			break;
		debugLog("Sprite instance=%i sort=%i\n", sprite->rendererIndex, sprite->sort );
	}
	
	debugLog("Num sprites used: %i / %i\n", numUsed, MAX_SPRITES );
}
