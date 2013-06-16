/*
 *
 *    AbstractControlView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef ABSTRACTCONTROLVIEW_H
#define ABSTRACTCONTROLVIEW_H

#include "AbstractSequenceView.h"

/**
 *  @brief コントロールトラックに表示するクラスの基底クラス．
 */
class AbstractControlView : public AbstractSequenceView
{
public:
    Q_OBJECT
    explicit AbstractControlView(
            int trackId,
            int beatWidth,
            int noteHeight,
            const vsq::Sequence *sequence,
            QWidget *parent
            );
public slots:
    // @Override
    virtual void dataChanged(int tickBegin, int tickEnd);

    virtual void paint(const QRect &rect, QPainter *painter) = 0;
};

#endif // ABSTRACTCONTROLVIEW_H
