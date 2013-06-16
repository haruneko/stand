/*
 *
 *    PlatinumSeem.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/08
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef PLATINUMSEEM_H
#define PLATINUMSEEM_H

#include "SeemInterface.h"

class Envelope;

/*!
 *  @brief 励起信号抽出法 PLATINUM によるスペクトログラム推定の実装です．
 *  @author HAL@shurabaP
 */
class PlatinumSeem : public SeemInterface
{
public:
    /*!
     *  @brief 基本周波数とパワースペクトル列を与えて初期化します．
     *  @param[in] f0 基本周波数列
     *  @param[in] power パワースペクトル列
     */
    PlatinumSeem(Envelope *f0 = 0, Specgram *power = 0);
    ~PlatinumSeem();

    /*!
     *  @brief 分析用の F0 列を与えます．
     *  @param[in] f0 基本周波数列
     *  @param[in] autodelete オブジェクト破棄時，基本周波数列を解放するかフラグ
     */
    void setF0(Envelope *f0);

    /*!
     *  @brief 分析用のパワースペクトル列を与えます．
     *  @param[in] power パワースペクトル列
     */
    void setPower(Specgram *power);

    /*!
     *  @Override
     */
    bool estimate(Specgram *dst, const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod);

private:
    bool _prepare(const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod);

    Envelope *_f0;
    bool _deletableF0;
    Specgram *_power;
    bool _deletablePower;
};

#endif // PLATINUMSEEM_H
