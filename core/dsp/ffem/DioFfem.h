/*
 *
 *    DioFfem.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/08
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef DIOFFEM_H
#define DIOFFEM_H

#include "FfemInterface.h"

/*!
 *  @brief  DIO による基本周波数推定の実装．
 *  @author HAL@shurabaP
 */
class DioFfem : public FfemInterface
{
public:
    bool estimate(Envelope *dst, const double *x, int length, int samplingFrequency, double msFramePeriod);
};

#endif // DIOFFEM_H
