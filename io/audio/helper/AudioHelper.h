/*
 *
 *    AudioHelper.h
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides one stream unit for AudioStream.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <QtGlobal>

class QAudioFormat;
class RiffChunk;

typedef struct
{
    qint16 formatTag;
    qint16 channelCount;
    qint32 sampleRate;
    qint32 bytesPerSecond;
    qint16 blockSize;
    qint16 sampleSize;
} FormatChunk;

void WaveHeaderToAudioFormat(const RiffChunk *chunk, QAudioFormat &format);
void AudioFormatToFormatChunk(FormatChunk *chunk, const QAudioFormat &format);
int SamplesAtMsec(double msec, const QAudioFormat &format);


#endif // AUDIO_HELPER_H
