/*
 *
 *    AbstractSteadyOscillator.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/05
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <iostream>
#include "AbstractSteadyOscillator.h"

AbstractSteadyOscillator::AbstractSteadyOscillator(double frequency)
{
    _frequency = 0.0;
    setFrequency(frequency);
}

void AbstractSteadyOscillator::setFrequency(double frequency)
{
    _frequency = std::max(frequency, 0.0);
}

double AbstractSteadyOscillator::frequency() const
{
    return _frequency;
}

double AbstractSteadyOscillator::normalizedPositionAt(double ms, double frequency)
{
    double T = 1 / frequency * 1000.0;
    double theta = ms / T;
    return theta;
}
