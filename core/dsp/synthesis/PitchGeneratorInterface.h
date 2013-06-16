/*
 *
 *    PitchGeneratorInterface.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef PITCHGENERATORINTERFACE_H
#define PITCHGENERATORINTERFACE_H

/*!
 *  @brief  VocoderRenderer に基本周波数を提供するインタフェースです.
 *  @author HAL@shurabaP
 */
class PitchGeneratorInterface
{
public:
    /*!
     *  @brief  該当時刻の基本周波数を返します.
     *          該当時刻が無声音であるときは必ず 0.0 を返すようにして下さい.
     *  @param[in] 時刻(ミリ秒)
     *  @return 該当時刻での基本周波数.
     *  @retval 0.0 該当時刻は無声音である.
     */
    virtual double generate(double ms) = 0;

    /*!
     *  @brief 時間方向への長さを返します.
     *  @return 時間長
     */
    virtual double msTimeLength() const = 0;
};

#endif // PITCHGENERATORINTERFACE_H
