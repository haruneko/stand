/*
 *
 *    AbstractControlPainter.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef PAINTABLE_H
#define PAINTABLE_H

#include <QColor>

class QRect;
class QPainter;

/**
 *  @brief コントロールトラックの描画を担当するクラスのインターフェースです．
 */
class AbstractControlPainter
{
public:
    /*!
     *  @brief 描画を行います． QWidget のサブクラスの paintEvent からの呼び出しを想定しています．
     *  @param[in] rect 描画範囲
     *  @param[in] painter 呼び出し元で作成した QPainter クラスへのポインタ．ペンなどの状態はもとに戻すのが望ましいです．
     */
    virtual void paint(const QRect &rect, QPainter *painter) = 0;

    /** @brief 表示色 */
    QColor color;
};

#endif // PAINTABLE_H
