/*
 *
 *    StarSeem.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/04
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef STARSEEM_H
#define STARSEEM_H

#include "../Envelope.h"

#include "SeemInterface.h"

/*!
 *  @brief  STAR による SEEM の実装クラス。
 *  @author HAL@shurabaP
 */
class StarSeem : public SeemInterface
{
public:
    /*!
     *  @brief F0 列を与えて初期化します。 NULL が与えられた場合推定時に F0 推定を行います。
     *  @param[in] e F0 列。
     */
    explicit StarSeem(Envelope *e = 0);
    virtual ~StarSeem();

    /*!
     *  @Override
     */
    virtual bool estimate(Specgram *dst, const double *src, int length, int fftLength, int samplingFrequency, double msFramePeriod);

private:
    void _destroy();
    void _setPitch(Envelope *e);

    Envelope *_pitch;
    bool _autodelete;
};

#endif // STARSEEM_H
