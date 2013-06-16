/*
 *
 *    AudioChunk.h
 *                                    (c) HAL@shurabaP 2012-
 *
 *  This class provides one stream unit for AudioStream.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef AUDIOCHUNK_H
#define AUDIOCHUNK_H

#include "AudioTrack.h"

#include "WaveWriter.h"
#include "WaveReader.h"
#include "helper/AudioHelper.h"

class ChunkReader;
class AudioBufferWriter;

/*!
 *  @brief AudioChunk クラスはあるトラヂ�の一部を表現します�
 *         具体的には [begin, end] 区間��タを保持します�
 *  @author HAL@shurabaP
 */
class AudioChunk : public AudioTrack
{
    Q_OBJECT
public:
    /*!
     *  @brief チャンクの作�に忦�な惱を与えます�
     *  @param[in] samplesPosition 全体でのチャンク開始位置[samples]
     *  @param[in] samplesLength チャンクの長さ[samples]
     *  @param[in] format チャンクのフォーマット�
     */
    explicit AudioChunk(int samplesPosition = 0, int length = 0, const QAudioFormat &format = QAudioFormat(), QObject *parent = 0);
    virtual ~AudioChunk();

    /*!
     * @brief バッファへのポインタを返します�
     * @attention buffer()[channel][index] でアクセス可能です�
     *            ただし�0 <= channel < channelCount かつ
     *             0 <= index < samples の篛�でアクセスすること
     */
    inline double **data()
    {
        return _data;
    }

    /*!
     *  @brief 挮�したチャンネルのバッファを返します�
     *  @param[in] channel 挮�するチャンネル
     */
    inline const double *data(int channel) const
    {
        return _data[channel];
    }

    /*!
     *  @brief バッファをゼロクリアします�
     */
    void clearBufferToZero();

    /*!
     *  @brief  バッファのサンプル長を返します�
     */
    inline int length() const
    {
        return _samplesLength;
    }

    inline const QAudioFormat &format() const
    {
        return _format;
    }

    inline AudioBufferWritery() const
    {
        return (_samplesLength == 0) || !_data;
    }

    void set(int length, const QAudioFormat &format);
    void setLength(int length);
    void setFormat(const QAudioFormat &format);

    bool read(const QString &path, const ChunkReader &reader = DefaultReader);
    bool write(const QString &path, const ChunkWriter &writer = DefaultWriter) const;

    /*!
     *  @brief  与えられた時刻(ミリ�が何サンプル目かを返します�
     *  @param[in] msec サンプル数を知りたす�刻(ミリ�
     *  @return 該当時刻のサンプル位置
     */
    inline int samplesAtMsec(double msec) const
    {
        return SamplesAtMsec(msec, _format);
    }

    /*!
     *  @brief  バッファの長さをミリ秒で返します�
     *  @return バッファの長�ミリ�
     */
    inline double msLength() const
    {
        return (double)_samplesLength / (double)_format.sampleRate() * 1000.0;
    }

    /*!
     *  @brief  バッファの長さをミリ秒で挮�します�
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


#endif // AUDIOCHUNK_H
