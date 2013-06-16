/*
 *
 *    SineOscillator.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/05
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

// For VC++
#define _USE_MATH_DEFINES
#include <cmath>

#include "SineOscillator.h"

SineOscillator::SineOscillator(double frequency) :
    AbstractSteadyOscillator(frequency)
{
}

double SineOscillator::signalAt(double ms)
{
    // sin(2 * pi * t / T) : t[sec], T[sec]
    double phase = 2.0 * M_PI * normalizedPositionAt(ms, frequency());
    return sin(phase);
}
