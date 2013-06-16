/*
 *
 *    DioFfem.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/08
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "../Envelope.h"
#include "../world/dio.h"

#include "DioFfem.h"

bool DioFfem::estimate(Envelope *dst, const double *x, int length, int samplingFrequency, double msFramePeriod)
{
    if(!dst || !x || length <= 0 || samplingFrequency <= 0 || msFramePeriod <= 0)
    {
        return false;
    }

    int timeLength = GetSamplesForDIO(samplingFrequency, length, msFramePeriod);
    double *f0 = new double[timeLength];
    double *t = new double[timeLength];
    dst->set(f0, timeLength, msFramePeriod, true);
    Dio(x, length, samplingFrequency, msFramePeriod, t, f0);
    delete[] t;

    return true;
}
