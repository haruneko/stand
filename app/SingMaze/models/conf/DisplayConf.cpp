/*
 *
 *    DisplayConf.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "DisplayConf.h"

DisplayConf::DisplayConf(double pixelPerSecond, QObject *parent) :
    QObject(parent)
{
    setPixelPerSecond(pixelPerSecond);
}

double DisplayConf::pixelPerSecond() const
{
    return _pixelPerSecond;
}

void DisplayConf::setPixelPerSecond(double pixelPerSecond)
{
    if(_pixelPerSecond != pixelPerSecond)
    {
        _pixelPerSecond = pixelPerSecond;
        emit widthChanged(pixelPerSecond);
    }
}
