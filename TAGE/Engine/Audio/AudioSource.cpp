//
//  AudioSource.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "AudioSource.h"

void AudioSource::Reset()
{
	isPlaying = false;
	pAudioData = NULL;
	playbackPosition = 0;
}

void AudioSource::SetData( const AudioData *_pData )
{
	pAudioData = _pData;
}

void AudioSource::PlayFromBeginning()
{
	playbackPosition = 0;
	isPlaying = true;
}
