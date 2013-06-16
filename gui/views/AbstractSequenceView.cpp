/*
 *
 *    AbstractSequenceView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPaintEvent>
#include <QPainter>

#include <Sequence.hpp>

#include "AbstractSequenceView.h"

AbstractSequenceView::AbstractSequenceView(int trackId, int beatWidth, int noteHeight, const vsq::Sequence *sequence, QWidget *parent) :
    QWidget(parent)
{
    _trackId = trackId;
    _beatWidth = beatWidth;
    _noteHeight = noteHeight;
    _sequence = sequence;
    _parent = parent;
}

void AbstractSequenceView::dataChanged(int /*tickBegin*/, int /*tickEnd*/)
{
}

void AbstractSequenceView::beatWidthChanged(int w)
{
    _beatWidth = qMax(0, w);
    update();
}

void AbstractSequenceView::noteHeightChanged(int h)
{
    _noteHeight = qMax(0, h);
    update();
}

void AbstractSequenceView::trackChanged(int id)
{
    // 範囲外の場合何もしない．
    if(id < 0 || _sequence->tracks()->size() <= id)
    {
        return;
    }
    _trackId = id;
    update();
}

void AbstractSequenceView::paint(const QRegion &region, QPainter *painter)
{
    QVector<QRect> rects = region.rects();
    foreach(const QRect &r , rects)
    {
        paint(r, painter);
    }
}

void AbstractSequenceView::paintEvent(QPaintEvent *e)
{
    paint(e->region(), &(QPainter(this)));
}
