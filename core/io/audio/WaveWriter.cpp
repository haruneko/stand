/*
 *
 *    WaveWriter.cpp
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides the function to write RIFF Wave file
 * from an AudioChunk class.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "../../dsp/AudioBuffer.h"
#include "../RiffFile.h"
#include "helper/AudioHelper.h"
#include <QFile>

#include "WaveWriter.h"

bool WaveWriter::write(const AudioBuffer *src, const QString &path) const
{
    QFile file(path);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug("WaveWriter::write(%s); // could not open the file.", path.toUtf8().data());
        return false;
    }

    if(!(src->format().sampleSize() == 8 || src->format().sampleSize() == 16))
    {
        qDebug("WaveWriter::write(%s); // %d bit Wave file is not supported.", path.toUtf8().data(), src->format().sampleSize());
        return false;
    }

    // RIFF ヘッダ設定するよ
    char riffHeader[4] = {'R', 'I', 'F' ,'F'};
    char waveHeader[4] = {'W', 'A', 'V', 'E'};
    qint32 waveSize = (src->length()) * src->format().channelCount() * src->format().sampleSize() / 8;
    qint32 fileSize = waveSize + 24 + 12;

    // fmt  チャンク設定するよ
    char fmtHeader[4] = {'f', 'm', 't', ' '};
    qint32 fmtSize = 16;
    FormatChunk chunk;
    AudioFormatToFormatChunk(&chunk, src->format());

    // data チャンク設定するよ
    char dataHeader[4] = {'d', 'a', 't', 'a'};
    char *data = new char[waveSize];

    // if - else の大量セール
    if(src->format().sampleSize() == 8)
    {
        for(int i = 0; i < src->length(); i++)
        {
            for(int c = 0; c < src->format().channelCount(); c++)
            {
                data[i] = 128 + 127 * src->data(c)[i];
            }
        }
    }
    else if(src->format().sampleSize() == 16)
    {
        short *data16 = (short *)data;
        for(int i = 0; i < src->length(); i++)
        {
            for(int c = 0; c < src->format().channelCount(); c++)
            {
                data16[i] = (short)(src->data(c)[i] * 32767);;
            }
        }
    }

    int written = 0;

    //RIFF ヘッダ書くよ
    written += file.write(riffHeader, 4);
    written += file.write((char *)&fileSize, 4);
    written += file.write(waveHeader, 4);

    // fmt  チャンク書くよ
    written += file.write(fmtHeader, 4);
    written += file.write((char *)&fmtSize, 4);
    written += file.write((char *)&chunk, sizeof(FormatChunk));

    // data チャンク書くよ
    written += file.write(dataHeader, 4);
    written += file.write((char *)&waveSize, 4);
    written += file.write(data, waveSize);

    return (written == fileSize + 8);
}
