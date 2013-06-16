#ifndef AUDIORENDERER_H
#define AUDIORENDERER_H

#include "AudioChunk.h"

namespace stand
{
namespace io
{
namespace audio
{

/*!
 *  @brief あるシーケンスをレンダリングするためのクラスです．
 *  @author HAL@shurabaP
 */
class AudioRenderer : public AudioChunk
{
public:
    explicit AudioRenderer(int sampleRate, int samplesLength, const QAudioFormat &format, QObject *parent = 0);
    virtual ~AudioRenderer();

    inline int sampleRate() const
    {
        return _sampleRate;
    }

public slots:
    /*!
     *  @brief 全区間をレンダリングします．
     */
    virtual void render();

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

private:
    int _sampleRate;
};

}
}
}

#endif // AUDIORENDERER_H
