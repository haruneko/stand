/*
 *
 *    ChunkReader.h
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides the interface to write AudioChunk data into file.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef AUDIO_CHUNKWRITER_H
#define AUDIO_CHUNKWRITER_H

class QString;

class AudioBuffer;

/*!
 *  @brief AudioBuffer からファイルへの書き込みを行うインターフェースです
 *  @author HAL@shurabaP
 */
class AudioBufferWriter
{
public:
    /*!
     *  @brief ファイルから読みAudioBuffer に読み込む純粋仮想関数です
     *  @param[out] dst 書き込む対象
     *  @param[in] path ファイルパス
     */
    virtual bool write(const AudioBuffer *src, const QString &path) const = 0;
};

#endif // AUDIO_CHUNKWRITER_H
