/*
 *
 *    ControlCurvePainter.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTROLCURVEPAINTER_H
#define CONTROLCURVEPAINTER_H

#include <QColor>
#include "AbstractControlPainter.h"

namespace vsq
{
class BPList;
}
class AbstractGridView;

/*!
 *  @brief コントロールカーブの描画を担当するクラスです．
 */
class ControlCurvePainter : public AbstractControlPainter
{
public:
    explicit ControlCurvePainter(const vsq::BPList *control, const AbstractGridView *parent);
    // @Override
    virtual void paint(const QRect &rect, QPainter *painter);

private:
    const vsq::BPList *_control;
    const AbstractGridView *_parent;
};

#endif // CONTROLCURVEPAINTER_H
