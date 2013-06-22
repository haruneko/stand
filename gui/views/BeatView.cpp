/*
 *
 *    BeatView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/22
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>

#include "BeatView.h"

BeatView::BeatView(int divCount, int noteHeight, int beatWidth, const vsq::Sequence *sequence, QWidget *parent) :
    AbstractGridView(divCount, beatWidth, sequence, parent),
    barLineColor(128, 192, 255),
    fontColor(128, 192, 255),
    backgroundColor(64, 64, 64)
{
    _noteHeight = noteHeight;
}

void BeatView::noteHeightChanged(int h)
{
    if(_noteHeight == h)
    {
        return;
    }
    _noteHeight = h;
    setFixedHeight(h);
    update();
}

void BeatView::paintBefore(const QRect &rect, QPainter *painter)
{
    painter->fillRect(rect, backgroundColor);
    painter->setPen(barLineColor);
    painter->drawLine(rect.left(), height(), rect.right(), height());
}

void BeatView::drawBarLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->drawLine(x, 0 , x, height());
}

void BeatView::drawBeatLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->drawLine(x, height() / 2, x, height());
}

void BeatView::drawAssistLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->drawLine(x, height() * 3 / 4, x, height());
}

