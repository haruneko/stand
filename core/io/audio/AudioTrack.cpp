/*
 *
 *    AudioTrack.cpp
 *                                    (c) HAL 2012
 *
 *  This class provides track class for AudioStream class.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "AudioTrack.h"

AudioTrack::AudioTrack(QObject *parent) :
    QObject(parent)
{
    _volume = 1.0;
    _pan = 0.0;
}

