/*
 *
 *    WorldSynthesis.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef WORLDSYNTHESIS_H
#define WORLDSYNTHESIS_H

#include "../world/fft.h"
#include "VocoderInterface.h"

struct MinimumPhaseAnalysis;

/*!
 *  @brief  WORLD による VocoderInterface の実装です.
 *          内部に作業用バッファを持つためスレッドセーフではありません.
 *          マルチスレッダイズ時には必ずインスタンスを複数生成してください.
 *  @author HAL@shurabaP
 */
class WorldSynthesis : public VocoderInterface
{
public:
    WorldSynthesis(int fftLength = 0);
    ~WorldSynthesis();

    /*!
     *  @Override
     */
    void synthesize(double *dst, int frameLength, const double *spectrum, const double *residual);

    /*!
     *  @Override
     */
    double msForUnvoicedFrame() const;

private:
    void _destroy();
    void _setFftLength(int fftLength);
    int _fftLength;
    fft_plan _plan;
    MinimumPhaseAnalysis *_minimumPhase; //! @brief 最小位相用
    fft_complex *_residual;             //! @brief 励起信号展開用
    fft_complex *_spectrum;             //! @brief インパルスのスペクトル
    double *_impulse;                   //! @brief 実際の波形
};

#endif // WORLDSYNTHESIS_H
