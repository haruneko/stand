/*
 *
 *    SeemInterface.h
 *                                    (c) HAL@shurabaP
 *                                        2013/04/30
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SEEMINTERFACE_H
#define SEEMINTERFACE_H

class Specgram;

/*!
 *  @brief SEEM インタフェースはスペクトル推定法用インタフェースです．
 *  @author HAL@shurabaP
 */
class SeemInterface
{
public:
    /*!
     *  @brief  SEEM インタフェースが提供するスペクトログラム計算メソッド．
     *          SEEM インタフェースを実装するクラスはこのメソッドを実装してください．
     *  @param[out] dst 計算結果が格納されるスペクトログラム
     *  @param[in] src スペクトルを計算したい信号を格納した配列．
     *  @param[in] length src の配列長．
     *  @param[in] fftLength FFT 長．
     *  @param[in] samplingFrequency 標本化周波数．
     *  @param[in] msFramePeriod 計算結果のスペクトログラム 1 フレームあたりの時間長（ミリ秒）．
     *  @return 分析成否．
     */
    virtual bool estimate(Specgram *dst, const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod) = 0;
};

#endif // SEEMINTERFACE_H
