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

#include "../models/SequenceModel.h"

#include "AbstractSequenceView.h"

AbstractSequenceView::AbstractSequenceView(SequenceModel *model, QWidget *parent) :
    QWidget(parent)
{
    _model = model;
    _parent = parent;
}

void AbstractSequenceView::trackChanged(int /*id*/)
{
}

void AbstractSequenceView::setModel(SequenceModel *model)
{
    _model = model;
    modelChanged();
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

SequenceModel *AbstractSequenceView::model()
{
    return _model;
}

const SequenceModel *AbstractSequenceView::model() const
{
    return _model;
}
