/*
 *
 *    WindowFunctions.h
 *                                    (c) HAL@shurabaP
 *                                        2013/03/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef WINDOWFUNCTIONS_H
#define WINDOWFUNCTIONS_H

/*!
 *  @brief 窓関数を集めたファイルです。
 *  @attention これらの関数は範囲 [0, 1.0] において値を返す関数として設計されます。
 *  @author HAL@shurabaP
 */

/*!
 *  @brief ハン窓
 */
double han(double t);

/*!
 *  @brief ハミング窓
 */
double hamming(double t);

/*!
 *  @brief 矩形窓
 */
double squareWindow(double t);

#endif // WINDOWFUNCTIONS_H
