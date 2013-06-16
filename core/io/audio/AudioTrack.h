/*
 *
 *    AudioTrack.h
 *                                    (c) HAL 2012
 *
 *  This class provides track class for AudioStream class.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef STAND_AUDIOTRACK_H
#define STAND_AUDIOTRACK_H

#include <QAudio>
#include <QAudioFormat>
#include <QObject>

/*!
 *  @brief オーディオ出力の一単位分のクラスです．
 */
class AudioTrack : public QObject
{
    Q_OBJECT
public:
    explicit AudioTrack(QObject *parent = 0);

    inline double volume() const
    {
        return _volume;
    }

    inline double pan() const
    {
        return _pan;
    }

public slots:
    inline void setVolume(double volume)
    {
        _volume = qMax(0.0, volume);
    }

    inline void setPan(double pan)
    {
        pan = qMax(-1.0, qMin(1.0, pan));
    }

protected slots:
    /*!
     *  @brief ミキサーから要求された位置，長さの信号を書き込むスロット．
     *  @param[out] dst 書きこみ対象のバッファ．
     *  @param[in] format オーディオデバイスのフォーマット．
     *  @param[in] position サンプルの位置．
     *  @param[in] length 書き込むサンプル長．
     */
    virtual void bufferRequired(double** dst, const QAudioFormat &format, qint64 position, qint64 length) = 0;

private:
    double _volume;
    double _pan;
};

#endif // STAND_AUDIOTRACK_H
