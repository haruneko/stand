/*
 *
 *    SimpleSeem.h
 *                                    (c) HAL@shurabaP
 *                                        2013/04/30
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SIMPLESEEM_H
#define SIMPLESEEM_H

#include "SeemInterface.h"

extern double han(double);

/*!
 *  @brief 短時間フーリエ変換による SEEM の実装です．
 *  @author HAL@shurabaP
 */
class SimpleSeem : public SeemInterface
{
public:
    /*!
     *  @brief コンストラクタでは窓関数を与えて初期化します．
     *  @param[in] window "double window(double t);" で定義される窓関数へのポインタ．
     */
    explicit SimpleSeem(int fftLength = 0, double (*window)(double) = han);

    virtual ~SimpleSeem();

    /*!
     *  @override
     */
    virtual bool estimate(Specgram *dst, const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod);

    inline int fftLength() const
    {
        return _fftLength;
    }

private:
    // ------------------------------------------- private member methods

    static void _setBuffer(double *buf, const double *wave, int frameIndex, int length, int fftLength, double frameShift, double (*window)(double));
    static void _setPowerSpectrum(double *dst, const double *src, int fftLength);

    void _destroy();
    void _resetFftLength(int fftLength);

private:
    // ------------------------------------------- private field

    double (*_window)(double);
    int _fftLength;
    int *_ip;
    double *_w;
};

#endif // SIMPLESEEM_H
