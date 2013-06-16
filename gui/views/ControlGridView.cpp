/*
 *
 *    ControlGridView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>

#include <MeasureLineIterator.hpp>

#include "ControlGridView.h"

ControlGridView::ControlGridView(int divCount, int beatWidth, const vsq::Sequence *sequence, int trackId, QWidget *parent) :
    AbstractControlView(beatWidth, sequence, trackId, parent)
{
    setDivCount(divCount);
}

void ControlGridView::setColor(const QColor &color)
{
    _color = color;
    _weakColor = QColor(color.red(), color.green(), color.blue(), color.alpha() * 3 / 4);
    update();
}

void ControlGridView::setDivCount(int divCount)
{
    int old = _divCount;
    _divCount = divCount;
    if(old != divCount)
    {
        update();
    }
}

void ControlGridView::paint(const QRect &rect, QPainter *painter)
{
    QPen old(painter->pen());
    vsq::tick_t assistStep = sequence()->getTickPerQuarter() / _divCount;    // 補助線の間隔
    vsq::tick_t beginTick = tickAt(rect.left());
    vsq::tick_t endTick = tickAt(rect.right() + 1);

    vsq::MeasureLineIterator it(&(sequence()->timesigList), assistStep);
    vsq::MeasureLine ml = it.next();
    for(; ml.tick < beginTick && it.hasNext(); ml = it.next());
    for(; ml.tick < endTick && it.hasNext(); ml = it.next())
    {
        // 小節線
        if(ml.isBorder)
        {
            _drawBarLine(ml.tick, painter);
        }
        // 補助線
        else
        {
            _drawAssistLine(ml.tick, painter);
        }
    }

    // 真ん中の横線
    painter->setPen(_color);
    painter->drawLine(rect.left(), height() / 2, rect.right() + 1, height() / 2);
    // 1/4, 3/4 の横線
    painter->setPen(_weakColor);
    painter->drawLine(rect.left(), height() / 4, rect.right() + 1, height() / 4);
    painter->drawLine(rect.left(), height() * 3 / 4, rect.right() + 1, height() * 3 / 4);

    painter->setPen(old);
}

void ControlGridView::_drawBarLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(_color);
    painter->drawLine(x, 0, x, height());
}

void ControlGridView::_drawAssistLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(_weakColor);
    int h = height();
    painter->drawLine(x, 0, x, h / 8);
    painter->drawLine(x, h * 3 / 8, x, h * 5 / 8);
    painter->drawLine(x, h * 7 / 8, x, h);
}
