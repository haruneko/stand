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

#include "AbstractSequenceView.h"

AbstractSequenceView::AbstractSequenceView(const vsq::Sequence *sequence, QWidget *parent) :
    QWidget(parent)
{
    _sequence = sequence;
    _parent = parent;
}

void AbstractSequenceView::trackChanged(int /*id*/)
{
}

void AbstractSequenceView::dataChanged(int /*tickBegin*/, int /*tickEnd*/)
{
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

void AbstractSequenceView::selectionChanged(const Selection &/*current*/, const Selection &/*previous*/)
{
}
