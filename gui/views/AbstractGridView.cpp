/*
 *
 *    AbstractGridView.cpp
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

#include "AbstractGridView.h"

AbstractGridView::AbstractGridView(int divCount, int beatWidth, const vsq::Sequence *sequence, QWidget *parent) :
    AbstractSequenceView(sequence, parent)
{
    _beatWidth = beatWidth;
    setDivCount(divCount);
    gridLineColor = QColor(128, 192, 255);
}

void AbstractGridView::setDivCount(int divCount)
{
    int old = _divCount;
    _divCount = divCount;
    if(old != divCount)
    {
        update();
    }
}

vsq::tick_t AbstractGridView::tickAt(int x) const
{
    vsq::tick_t ret = x * sequence()->getTickPerQuarter() / _beatWidth - sequence()->getPreMeasureClocks();
    return ret;
}

int AbstractGridView::xAt(vsq::tick_t tick) const
{
    int ret = (sequence()->getPreMeasureClocks() + tick) * _beatWidth / sequence()->getTickPerQuarter();
    return ret;
}

void AbstractGridView::beatWidthChanged(int w)
{
    if(_beatWidth == w)
    {
        return;
    }
    _beatWidth = w;
    update();
}

void AbstractGridView::divCountChanged(int divCount)
{
    setDivCount(divCount);
}

void AbstractGridView::paint(const QRect &rect, QPainter *painter)
{
    QPen old(painter->pen());
    paintBefore(rect, painter);

    vsq::tick_t assistStep = sequence()->getTickPerQuarter() / _divCount;    // 補助線の間隔
    vsq::tick_t beginTick = tickAt(rect.left());
    vsq::tick_t endTick = tickAt(rect.right() + 1);

    vsq::MeasureLineIterator it(&(sequence()->timesigList), assistStep);
    if(!it.hasNext())
    {
        return;
    }
    vsq::MeasureLine ml = it.next();

    vsq::tick_t current = beginTick / assistStep * assistStep;
    while(current < ml.tick)
    {
        if(current % (sequence()->getTickPerQuarter() * ml.numerator * 4 / ml.denominator) == 0)
        {
            drawBarLine(current, painter);
        }
        else if(current % (sequence()->getTickPerQuarter() * ml.numerator / ml.denominator) == 0)
        {
            drawBeatLine(current, painter);
        }
        else
        {
            drawAssistLine(current, painter);
        }
        current += assistStep;
    }

    for(; ml.tick < endTick && it.hasNext(); ml = it.next())
    {
        // 小節線
        if(ml.isBorder)
        {
            drawBarLine(ml.tick, painter);
        }
        // 補助線
        else if(ml.tick * ml.numerator / ml.denominator == 0)
        {
            drawBeatLine(ml.tick, painter);
        }
        else
        {
            drawAssistLine(ml.tick, painter);
        }
    }

    while(current < endTick)
    {
        if(current % (sequence()->getTickPerQuarter() * ml.numerator * 4 / ml.denominator) == 0)
        {
            drawBarLine(current, painter);
        }
        else if(current % (sequence()->getTickPerQuarter() * ml.numerator / ml.denominator) == 0)
        {
            drawBeatLine(current, painter);
        }
        else
        {
            drawAssistLine(current, painter);
        }
        current += assistStep;
    }

    paintAfter(rect, painter);
    painter->setPen(old);
}

