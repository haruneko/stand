/*
 *
 *    SpectrumGeneratorInterface.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SPECTRUMGENERATORINTERFACE_H
#define SPECTRUMGENERATORINTERFACE_H

/*!
 *  @brief  VocoderRenderer にスペクトルを提供するインタフェースです.
 *  @author HAL@shurabaP
 */
class SpectrumGeneratorInterface
{
public:
    /*!
     *  @brief  該当時刻のスペクトルを返します.
     *  @param[in] 時刻(ミリ秒)
     *  @return スペクトルへのポインタ.
     */
    virtual const double *generate(double ms) const = 0;

    /*!
     *  @brief  周波数方向へのバッファ長を返します.
     *  @return スペクトルの長さ.
     */
    virtual int fftLength() const = 0;

    /*!
     *  @brief  時刻方向への長さを返します.
     *  @return 時間長
     */
    virtual double msTimeLength() const = 0;
};

#endif // SPECTRUMGENERATORINTERFACE_H
