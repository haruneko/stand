/*
 *
 *    SineOscillator.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/05
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SINEOSCILLATOR_H
#define SINEOSCILLATOR_H

#include "AbstractSteadyOscillator.h"

class SineOscillator : public AbstractSteadyOscillator
{
public:
    explicit SineOscillator(double frequency);

    /*!
     *  @Override
     */
    double signalAt(double ms);
};

#endif // SINEOSCILLATOR_H
