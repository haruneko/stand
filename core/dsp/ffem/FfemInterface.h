/*
 *
 *    FfemInterface.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/08
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef FFEMINTERFACE_H
#define FFEMINTERFACE_H

class Envelope;

/*!
 *  @brief  Ffem; Fundamental frequency estimation method.
 *          基本周波数推定を行うインターフェースです．
 *  @author HAL@shurabaP
 */
class FfemInterface
{
public:
    /*!
     *  @brief  基本周波数の推定を行うメソッド．
     *  @param[out] dst 出力包絡を保持する．
     *  @param[in] x 信号の生データ．
     *  @param[in] length 信号の長さ．
     *  @param[in] msFramePeriod 1 フレーム長(ミリ秒)
     *  @return 推定成否．
     */
    virtual bool estimate(Envelope *dst, const double *x, int length, int samplingFrequency, double msFramePeriod) = 0;
};

#endif // FFEMINTERFACE_H
