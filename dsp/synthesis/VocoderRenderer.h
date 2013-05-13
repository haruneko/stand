/*
 *
 *    VocoderRenderer.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/14
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef VOCODERRENDERER_H
#define VOCODERRENDERER_H

class AudioBuffer;
class Envelope;
class Specgram;
class VocoderInterface;

/*!
 *  @brief  Vocoder を用いて音声を合成するクラスです．
 *  @author HAL@shurabaP
 */
class VocoderRenderer
{
public:
    /*!
     *  @brief  AudioBuffer に波形を合成します．
     *  @param[out] dst 合成した波形を保持するバッファ．
     *  @param[in]  samplingFrequency 合成する波形の標本化周波数．
     *  @param[in]  f0  合成波形の基本周波数列．
     *  @param[in]  specgram    合成波形のスペクトログラム．
     *  @param[in]  residual    残差波形や非周期性指標など．
     *  @param[in]  msFramePeriod バッファ群の 1 フレーム辺りの長さ
     *  @param[in]  vocoder     合成に用いる Vocoder．
     *  @return 合成成否．
     */
    virtual bool render(AudioBuffer *dst, int samplingFrequency, const Envelope *f0, const Specgram *specgram, const Specgram *residual, double msFramePeriod, VocoderInterface *vocoder);

private:
    void _prepareBuffer(AudioBuffer *dst, int samplingFrequency, double msLength);
};

#endif // VOCODERRENDERER_H
