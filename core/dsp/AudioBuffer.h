/*
 *
 *    AudioBuffer.h
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides one stream unit for AudioStream.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <QAudioFormat>

#include "../io/audio/WaveWriter.h"
#include "../io/audio/WaveReader.h"
#include "../io/audio/helper/AudioHelper.h"

class ChunkReader;
class AudioBufferWriter;

/*!
 *  @brief  AudioChunk クラスは波形を保持するクラスです．
 *          また，波形管理のためのメタデータも保持します．
 *  @author HAL@shurabaP
 */
class AudioBuffer
{
public:
    /*!
     *  @brief バッファの作成に必要な情報を与えます．
     *  @param[in] samplesLength チャンクの長さ[samples]．
     *  @param[in] format チャンクのフォーマット．
     */
    explicit AudioBuffer(int samplesLength = 0, const QAudioFormat &format = QAudioFormat());
    virtual ~AudioBuffer();

    /*!
     * @brief バッファへのポインタを返します．
     * @attention buffer()[channel][index] でアクセス可能です．
     *            ただし， 0 <= channel < channelCount かつ
     *             0 <= index < samples の範囲でアクセスすること．
     */
    inline double **data()
    {
        return _data;
    }

    /*!
     *  @brief 指定したチャンネルのバッファを返します．
     *  @param[in] channel 指定するチャンネル．
     */
    inline const double *data(int channel) const
    {
        return _data[channel];
    }

    /*!
     *  @brief バッファをゼロクリアします．
     */
    void clearBufferToZero();

    /*!
     *  @brief  バッファのサンプル長を返します．
     */
    inline int length() const
    {
        return _samplesLength;
    }

    inline const QAudioFormat &format() const
    {
        return _format;
    }

    inline bool isEmpty() const
    {
        return (_samplesLength == 0) || !_data;
    }

    void set(int length, const QAudioFormat &format);
    void setLength(int length);
    void setFormat(const QAudioFormat &format);

    bool read(const QString &path, const AudioBufferReader &reader = DefaultReader);
    bool write(const QString &path, const AudioBufferWriter &writer = DefaultWriter) const;

    /*!
     *  @brief  与えられた時刻(ミリ秒)が何サンプル目かを返します．
     *  @param[in] msec サンプル数を知りたい時刻(ミリ秒)
     *  @return 該当時刻のサンプル位置．
     */
    inline int samplesAtMsec(double msec) const
    {
        return SamplesAtMsec(msec, _format);
    }

    /*!
     *  @brief  バッファの長さをミリ秒で返します．
     *  @return バッファの長さ(ミリ秒)
     */
    inline double msLength() const
    {
        return (double)_samplesLength / (double)_format.sampleRate() * 1000.0;
    }

    /*!
     *  @brief  バッファの長さをミリ秒で指定します．
     */
    inline void setMsLength(double ms)
    {
        setLength(samplesAtMsec(ms));
    }

private:
    static WaveWriter DefaultWriter;
    static WaveReader DefaultReader;

    void _create();
    void _destroy();
    double **_data;
    int _samplesLength;

    QAudioFormat _format;
};


#endif // AUDIOBUFFER_H
