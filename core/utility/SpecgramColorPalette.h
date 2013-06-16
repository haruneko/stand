/*
 *
 *    SpecgramColorPalette.h
 *                                    (c) HAL@shurabaP
 *                                        2013/03/20
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SPECGRAMCOLORPALETTE_H
#define SPECGRAMCOLORPALETTE_H

#include <QtGlobal>

/*!
 *  @brief ToImage が行う、スペクトログラムのビジュアライズを視覚化する際のパレットを表します。
 *  @author HAL@shurabaP
 */
class SpecgramColorPalette
{
public:
    /*!
     *  @brief 与えられた値と最大値最小値から対応する色情報を返します。
     *  @param[in] value 値
     *  @param[in] maxValue 最大値
     *  @param[in] minValue 最小値
     */
    virtual uint color(double value, double maxValue, double minValue) const = 0;

    /*!
     *  @brief グラフの背景色を返します。
     */
    virtual uint bgColor() const = 0;
};

#endif // SPECGRAMCOLORPALETTE_H
