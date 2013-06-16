/*
 *
 *    WaveReader.h
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides one stream unit for AudioStream.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef WAVEREADER_H
#define WAVEREADER_H

#include "AudioBufferReader.h"

class RiffChunk;

/*!
 *  @brief WAVE ファイルを AudioBuffer に読み込むクラスです
 *  @author HAL@shurabaP
 */
class WaveReader : public AudioBufferReader
{
public:
    bool read(AudioBuffer *dst, const QString &path) const;

private:
    static bool _set(AudioBuffer *dst, const RiffChunk *c);
};

#endif // WAVEREADER_H
