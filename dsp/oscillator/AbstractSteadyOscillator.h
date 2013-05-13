/*
 *
 *    AbstractSteadyOscillator.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/05
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef ABSTRACTSTEADYOSCILLATOR_H
#define ABSTRACTSTEADYOSCILLATOR_H

#include "OscillatorInterface.h"

/*!
 *  @brief 振動数が固定の発振器を表す抽象クラス型です．
 *  @author HAL@shurabaP
 */
class AbstractSteadyOscillator : public OscillatorInterface
{
public:
    /*!
     *  @brief 周波数を初期化します．
     *  @param[in] frequency 周波数 [Hz]
     */
    explicit AbstractSteadyOscillator(double frequency);

    /*!
     *  @brief signalAt メソッドは派生クラスで実装される必要があります．
     */
    virtual double signalAt(double ms) = 0;

    void setFrequency(double frequency);
    double frequency() const;

protected:
    /*!
     *  @brief  時刻に対応する正規化した位置を返します．
     *          戻り値は必ず [0, 1) の範囲に正規化されます．
     *  @param[in]  ms  時刻（ミリ秒）
     *  @param[in]  frequency   周波数(Hz)
     */
    static double normalizedPositionAt(double ms, double frequency);

private:
    double _frequency;
};

#endif // ABSTRACTSTEADYOSCILLATOR_H
