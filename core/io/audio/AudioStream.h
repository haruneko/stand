/*
 *
 *    AudioStream.h
 *                                    (c) HAL 2012
 *
 *  This class provides I/O functions for AudioDevice.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef AUDIOSTREAM_H
#define AUDIOSTREAM_H

#include <QAudioOutput>
#include <QAudioFormat>
#include <QObject>

namespace stand
{
namespace io
{
namespace audio
{

/*!
 *  @brief 波形のストリーム再生用のクラスです．
 *         このクラスは requireBuffer シグナルを通してバッファのやり取りを行います．
 *  @author HAL@shurabaP
 */
class AudioStream : public QObject
{
    Q_OBJECT
public:
    static const qint64 MsMinimumBufferLength = 512;
public:
    /*!
     *  @brief コンストラクタではフォーマットを指定します．
     */
    explicit AudioStream(const QAudioFormat &format, QObject *parent = 0);
    virtual ~AudioStream();

    inline qint64 msBufferLength() const
    {
        return _msBufferLength;
    }

    inline QAudio::State state() const
    {
        return (_output ? _output->state() : QAudio::StoppedState);
    }

    /*!
     *  @brief フォーマットを指定します．再生中には実行できません．
     *  @param[in] format 指定するフォーマット．
     */
    void setFormat(const QAudioFormat &format);

    /*!
     *  @brief バッファの長さを指定します．再生中には実行できません．
     *  @param[in] msBufferLength バッファ長[msec]．
     */
    void setBufferLength(qint64 msBufferLength);

public slots:
    /*!
     *  @brief 再生が可能な場合再生を開始します．
     */
    void start();

    /*!
     *  @brief 停止が可能な場合再生を停止します．
     */
    void stop();

    /*!
     *  @brief 再生位置を変更します．
     *  @attention 既にバッファに書き込み済みのデータは再生されることに注意してください．
     *  @param[in] position 変更したい再生位置[samples]．
     */
    void seek(qint64 position);

signals:
    /*!
     *  @brief バッファを要求するシグナルです．
     *  @attention バッファはゼロクリアしてシグナルを発生させますが，どの順番で書き込まれるかは不明なので，バッファには加算を行なってください．
     *  @param[out] buffer 書き込むべきバッファ．
     *  @param[in] format オーディオ出力のフォーマット．
     *  @param[in] position 書き込むバッファの開始時刻[samples]．
     *  @param[in] length 書き込むサンプル長．
     */
    void requireBuffer(double **buffer, const QAudioFormat &format, qint64 position, qint64 length);

private slots:
    void _notified();
    void _outputStateChanged(QAudio::State);

private:
    void _create();
    void _destroy();
    void _writeBuffer(qint64 length);

    void _writeBuffer8(qint64 length);
    void _writeBuffer16(qint64 length);
    void _writeBuffer32(qint64 length);

private:
    QAudioFormat _format;
    QAudioOutput *_output;
    QIODevice *_device;

    qint64 _msBufferLength;
    qint64 _samplesBufferLength;
    qint64 _samplesPosition;

    double **_buffer;
};

}
}
}

#endif // AUDIOSTREAM_H
