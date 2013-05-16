/*
 *
 *    ExcitationColorPalette.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "ExcitationColorPalette.h"

uint ExcitationColorPalette::bgColor() const
{
    return 0xff000000;
}

uint ExcitationColorPalette::color(double value, double maxValue, double minValue) const
{
    double midValue = (maxValue + minValue) / 2.0;
    value = (value - midValue) * 2 / (maxValue - minValue + DBL_MIN);
    uint c = 0xff0000ff;
    if(value < 0)
    {
        c += (uint)(-value * 255) * 0x000100;
    }
    else
    {
        c += (uint)(value * 255) * 0x010000;
    }
    return c;
}
