/*
 *
 *    AudioBufferReader.h
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides the interface to read AudioChunk data.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef AUDIO_BUFFERREADER_H
#define AUDIO_BUFFERREADER_H

class QString;

class AudioBuffer;

/*!
 *  @brief AudioBuffer にファイルから読み込みを行うインターフェースです
 *  @author HAL@shurabaP
 */
class AudioBufferReader
{
public:
    /*!
     *  @brief ファイルから AudioBuffer に読み込む純粋仮想関数です
     *  @param[out] dst 書き込む対象
     *  @param[in] path ファイルパス
     */
    virtual bool read(AudioBuffer *dst, const QString &path) const = 0;
};

#endif // AUDIO_BUFFERREADER_H
