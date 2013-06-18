/*
 *
 *    AbstractControlView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <Sequence.hpp>

#include "AbstractControlView.h"

AbstractControlView::AbstractControlView(int beatWidth, const vsq::Sequence *sequence, int trackId, QWidget *parent ) :
    AbstractSequenceView(sequence, trackId, parent)
{
    beatWidthChanged(beatWidth);
}

void AbstractControlView::dataChanged(int tickBegin, int tickEnd)
{
    update(xAt(tickBegin), 0, xAt(tickEnd) + 1, height());
}

vsq::tick_t AbstractControlView::tickAt(int x) const
{
    vsq::tick_t ret = x * sequence()->getTickPerQuarter() / _beatWidth - sequence()->getPreMeasureClocks();
    return ret;
}

int AbstractControlView::xAt(vsq::tick_t tick) const
{
    int ret = (sequence()->getPreMeasureClocks() + tick) * _beatWidth / sequence()->getTickPerQuarter();
    return ret;
}

void AbstractControlView::beatWidthChanged(int w)
{
    _beatWidth = qMax(0, w);
    int width = w * sequence()->getTotalClocks();
    setMinimumWidth(width);
    update();
}

void AbstractControlView::noteHeightChanged(int /* h */)
{
}
