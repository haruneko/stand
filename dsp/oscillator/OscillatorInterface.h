/*
 *
 *    OscillatorInterface.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/05
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef OSCILLATORINTERFACE_H
#define OSCILLATORINTERFACE_H

/*!
 *  @brief  発振器を表すインターフェースです．
 *          発振器の発する信号は [-1, 1] の範囲であることが期待されます．
 *  @author HAL@shurabaP
 */
class OscillatorInterface
{
public:
    /*!
     *  @brief 該当時刻の信号を返します．
     *  @param[in] 時刻(ミリ秒)
     *  @return ms(msec) での信号値
     */
    virtual double signalAt(double ms) = 0;
};

#endif // OSCILLATORINTERFACE_H
