/*
 *
 *    AudioHelper.cpp
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides one stream unit for AudioStream.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include <QAudioFormat>
#include "../../RiffChunk.h"

#include "AudioHelper.h"

void WaveHeaderToAudioFormat(const RiffChunk *chunk, QAudioFormat &format)
{
    // 名前チェック！
    if(strcmp(chunk->header(), "fmt ") != 0)
    {
        format.setChannelCount(-1);
        return;
    }
    // サイズチェック！！
    if(chunk->length() < sizeof(FormatChunk))
    {
        return;
    }

    FormatChunk data;
    memcpy(&data, chunk->data(), sizeof(FormatChunk));

    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setChannelCount(data.channelCount);
    format.setCodec("audio/pcm");
    format.setSampleRate(data.sampleRate);
    format.setSampleSize(data.sampleSize);
    format.setSampleType(QAudioFormat::SignedInt);

    switch(data.sampleSize)
    {
    case 8:
        format.setSampleType(QAudioFormat::UnSignedInt);
        break;
    case 32:
        // 32 bit の仕様よくわからん．
        break;
    }
}

void AudioFormatToFormatChunk(FormatChunk *chunk, const QAudioFormat &format)
{
    chunk->blockSize = format.channelCount() * format.sampleSize() / 8;
    chunk->bytesPerSecond = format.sampleRate() * chunk->blockSize;
    chunk->channelCount = format.channelCount();
    chunk->formatTag = (format.codec() == "audio/pcm") ? 1 : 0; // 生波形以外はしらん．
    chunk->sampleRate = format.sampleRate();
    chunk->sampleSize = format.sampleSize();
}

int SamplesAtMsec(double msec, const QAudioFormat &format)
{
    return (int)((double)format.sampleRate() * msec / 1000.0);
}
