/*
 *
 *    ResidualExtractor.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/09
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef RESIDUALEXTRACTOR_H
#define RESIDUALEXTRACTOR_H

#include "fft.h"

class Specgram;

/*!
 *  @brief  励起信号スペクトル列を励起信号波形列へ変換するクラスです．
 *  @note   WORLD の流儀に従ってここは関数で実装したほうがそれっぽいかしら？？
 *  @author HAL@shurabaP
 */
class ResidualExtractor
{
public:
    /*!
     *  @brief 励起信号スペクトル列から励起信号波形列を計算します．
     *  @param[out] dst 波形の格納には Specgram クラスを使用します．
     *                  スペクトログラムの周波数軸は該当フレームにおける励起信号のローカルな時間軸を表します．
     *  @param[in]  src PLATINUM により計算された励起信号スペクトル列
     */
    static void extract(Specgram *dst, const Specgram *src);

    /*!
     *  @brief 励起信号スペクトルを励起信号波形に変換します．
     *  @param[out] dst 出力信号波形
     *  @param[in] residual PLATINUM の励起信号スペクトル．実装は WORLD API 群に同じ．
     *  @param[in] fftLength FFT 長．
     */
    static void extractOneFrame(double *dst, const double *residual, int fftLength);

    /*!
     *  @brief WORLD 形式の励起信号スペクトルを FFTW や FFTSG で使用できる形式に変更します
     *  @param[out] dst 変換後
     *  @param[in] src PLATINUM の励起信号スペクトル．実装は WORLD API 群に同じ．
     *  @param[in] fftLength FFT 長．
     */
    static void convertToComplex(fft_complex *dst, const double *src, int fftLength);
};

#endif // RESIDUALEXTRACTOR_H
