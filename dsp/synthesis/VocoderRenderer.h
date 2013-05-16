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
class VocoderInterface;
class PitchGeneratorInterface;
class SpectrumGeneratorInterface;

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
     *  @param[in]  msBegin     合成開始時刻.
     *  @param[in]  msEnd       合成時間.
     *  @param[in]  fftLength   1 フレーム辺りの長さ．
     *  @param[in]  vocoder     合成に用いる Vocoder．
     *  @param[in]  pitch       F0 生成器
     *  @param[in]  specgram    スペクトル生成器
     *  @param[in]  residual    非周期性指標/励起信号生成器
     *  @return 合成成否．
     */
    virtual bool render(AudioBuffer *dst,
                        int samplingFrequency,
                        double msBegin,
                        double msEnd,
                        int fftLength,
                        VocoderInterface *vocoder,
                        PitchGeneratorInterface *pitch,
                        SpectrumGeneratorInterface *specgram,
                        SpectrumGeneratorInterface *residual);

private:
    void _prepareBuffer(AudioBuffer *dst, int samplingFrequency, double msLength);
    void _render(AudioBuffer *dst,
                double msBegin,
                double msEnd,
                int fftLength,
                VocoderInterface *vocoder,
                PitchGeneratorInterface *pitch,
                SpectrumGeneratorInterface *specgram, SpectrumGeneratorInterface *residual);
};

#endif // VOCODERRENDERER_H
