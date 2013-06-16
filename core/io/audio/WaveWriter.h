/*
 *
 *    WaveWriter.h
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
#ifndef WAVEWRITER_H
#define WAVEWRITER_H

#include "AudioBufferWriter.h"

/*!
 *  @brief AudioChunk から WAVE ファイルを保存するクラスです
 */
class WaveWriter : public AudioBufferWriter
{
public:
    virtual bool write(const AudioBuffer *src, const QString &path) const;
};

#endif // WAVEWRITER_H
