/*
 *
 *    AudioChunk.cpp
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides one stream unit for AudioStream.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "../io/audio/AudioBufferReader.h"
#include "../io/audio/AudioBufferWriter.h"

#include <QtGlobal>

#include "AudioBuffer.h"

WaveWriter AudioBuffer::DefaultWriter;
WaveReader AudioBuffer::DefaultReader;

AudioBuffer::AudioBuffer(int samplesLength, const QAudioFormat &format)
{
    _format = format;
    _samplesLength = samplesLength;

    _data = NULL;
    setFormat(format);
}

AudioBuffer::~AudioBuffer()
{
    _destroy();
}

void AudioBuffer::_create()
{
    _destroy();
    if(!_format.isValid() || _samplesLength <= 0)
    {
        return;
    }
    _data = new double*[_format.channelCount()];
    _data[0] = new double[_format.channelCount() * _samplesLength];
    for(int i = 1; i < _format.channelCount(); i++)
    {
        _data[i] = _data[0] + i * _samplesLength;
    }
}

void AudioBuffer::_destroy()
{
    if(_data)
    {
        delete[] _data[0];
    }
    delete[] _data;
    _data = NULL;
}

void AudioBuffer::set(int samplesLength, const QAudioFormat &format)
{
    if(format.isValid())
    {
        _samplesLength = samplesLength;
        _format.setChannelCount(-1);
        setFormat(format);
    }
}

void AudioBuffer::setFormat(const QAudioFormat &format)
{
    if(!format.isValid())
    {
        return;
    }

/*    // チャンネル数同じならバッファはいじらない．
    if(_format.isValid() && format.channelCount() == _format.channelCount())
    {
        return;
    }*/

    _format = format;
    _create();
}

void AudioBuffer::setLength(int samplesLength)
{
    if(_samplesLength == samplesLength)
    {
        return;
    }
    _samplesLength = samplesLength;
    if(_format.isValid())
    {
        _create();
    }
}

bool AudioBuffer::read(const QString &path, const AudioBufferReader &reader)
{
    return reader.read(this, path);
}

bool AudioBuffer::write(const QString &path, const AudioBufferWriter &writer) const
{
    return writer.write(this, path);
}

void AudioBuffer::clearBufferToZero()
{
    if(!_data || !_data[0])
    {
        return;
    }

    for(int ch = 0; ch < _format.channelCount(); ch++)
    {
        for(int i = 0; i < _samplesLength; i++)
        {
            _data[ch][i] = 0.0;
        }
    }
}
