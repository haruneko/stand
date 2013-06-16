/*
 *
 *    WindowFunctions.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/03/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#define _USE_MATH_DEFINES
#include <cmath>

#include "WindowFunctions.h"

double han(double t)
{
    return 0.5 - 0.5 * cos(2.0 * M_PI * t);
}

double hamming(double t)
{
    return 0.54 - 0.46 * cos(2.0 * M_PI * t);
}

double squareWindow(double t)
{
    return 1.0;
}
