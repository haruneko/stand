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

#include "AbstractSequenceView.h"

AbstractSequenceView::AbstractSequenceView(int trackId, int beatWidth, int noteHeight, const vsq::Sequence *sequence, QWidget *parent) :
    QObject(parent)
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
    _beatWidth = w;
}

void AbstractSequenceView::noteHeightChanged(int h)
{
    _noteHeight = h;
}

void AbstractSequenceView::paint(const QRegion &region, QPainter *painter)
{
    QVector<QRect> rects = region.rects();
    foreach(const QRect &r , rects)
    {
        paint(r, painter);
    }
}
