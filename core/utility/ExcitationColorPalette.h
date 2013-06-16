/*
 *
 *    ExcitationColorPalette.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef EXCITATIONCOLORPALETTE_H
#define EXCITATIONCOLORPALETTE_H

#include "SpecgramColorPalette.h"

/*!
 *  @brief 励起信号を視覚化するときのパレット
 *  @author HAL@shurabaP
 */
class ExcitationColorPalette : public SpecgramColorPalette
{
public:
    /*!
     *  @Override
     */
    virtual uint color(double value, double maxValue, double minValue) const;

    /*!
     *  @Override
     */
    virtual uint bgColor() const;
};

#endif // EXCITATIONCOLORPALETTE_H
