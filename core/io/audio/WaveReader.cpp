/*
 *
 *    WaveReader.cpp
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
#include <QFileInfo>

#include "../../dsp/AudioBuffer.h"
#include "../RiffFile.h"
#include "helper/AudioHelper.h"

#include "WaveReader.h"

bool WaveReader::read(AudioBuffer *dst, const QString &path) const
{
    RiffFile f;
    if(!f.read(path.toLocal8Bit().data()))
    {
        qDebug("WaveReader::read(%s); // file read error.", path.toUtf8().data());
        return false;
    }

    if(!f.is("WAVE"))
    {
        qDebug(" WaveReader::read(%s); // This is not WAVE file", path.toUtf8().data());
        return false;
    }

    const RiffChunk *c;
    if((c = f.chunk("fmt ")) == NULL)
    {
        qDebug(" WaveReader::read(%s); // fmt not fount", path.toUtf8().data());
        return false;
    }
    QAudioFormat format;
    WaveHeaderToAudioFormat(c, format);
    qint64 samplesLength = (f.size() - 36) / (format.channelCount() * format.sampleSize() / 8);
    dst->set(samplesLength, format);

    if((c = f.chunk("data")) == NULL)
    {
        qDebug(" WaveBuffer::read(%s); // data not found", path.toUtf8().data());
        return false;
    }

    return _set(dst, c);
}

bool WaveReader::_set(AudioBuffer *dst, const RiffChunk *c)
{
    int j = 0;
    switch(dst->format().sampleSize())
    {
    case 8:
        {
            for(int i = 0; i < dst->length(); i++)
            {
                for(int ch = 0; ch < dst->format().channelCount(); ch++)
                {
                    dst->data()[ch][i] = (c->data()[j] - 128) / 128.0;
                    j++;
                }
            }
        }
        break;
    case 16:
        {
            const qint16 *p = (qint16 *)(c->data());
            for(int i = 0; i < dst->length(); i++)
            {
                for(int ch = 0; ch < dst->format().channelCount(); ch++)
                {
                    dst->data()[ch][i] = p[j] / (double)(1 << 15);
                    j++;
                }
            }
        }
        break;
    case 24:
        {
            for(int i = 0; i < dst->length(); i++)
            {
                for(int ch = 0; ch < dst->format().channelCount(); ch++)
                {
                    qint32 val = 0;
                    char *p = (char *)(&val);
                    p[3] = c->data()[j + 2];
                    p[2] = c->data()[j + 1];
                    p[1] = c->data()[j + 0];
                    dst->data()[ch][i] = val / (double)(1 << 23);
                    j += 3;
                }
            }
        }
        break;
    case 32:
        {
            const qint32 *p = (qint32 *)(c->data());
            for(int i = 0; i < dst->length(); i++)
            {
                for(int ch = 0; ch < dst->format().channelCount(); ch++)
                {
                    dst->data()[ch][i] = p[j] / (double)(1 << 15);
                    j++;
                }
            }
        }
        break;
    default:
        qWarning("WaveReader::read(); // non supported bit rate; %d", dst->format().sampleSize());
        return false;
    }
    return true;
}
