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
    AbstractGridView(divCount, beatWidth, sequence, trackId, parent)
{
}

void ControlGridView::paintAfter(const QRect &rect, QPainter *painter)
{
    // 真ん中の横線
    painter->setPen(color());
    painter->drawLine(rect.left(), height() / 2, rect.right() + 1, height() / 2);
    // 1/4, 3/4 の横線
    QColor weakColor(color().red(), color().green(), color().blue(), color().alpha() / 2);
    painter->setPen(weakColor);
    painter->drawLine(rect.left(), height() / 4, rect.right() + 1, height() / 4);
    painter->drawLine(rect.left(), height() * 3 / 4, rect.right() + 1, height() * 3 / 4);
}

void ControlGridView::drawBarLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(color());
    painter->drawLine(x, 0, x, height());
}

void ControlGridView::drawBeatLine(vsq::tick_t tick, QPainter *painter)
{
    QColor weakColor(color().red(), color().green(), color().blue(), color().alpha() * 3 /4);
    int x = xAt(tick);
    painter->setPen(weakColor);
    int h = height();
    painter->drawLine(x, 0, x, h / 8);
    painter->drawLine(x, h * 3 / 8, x, h * 5 / 8);
    painter->drawLine(x, h * 7 / 8, x, h);
}

void ControlGridView::drawAssistLine(vsq::tick_t tick, QPainter *painter)
{
    QColor weakColor(color().red(), color().green(), color().blue(), color().alpha() / 2);
    int x = xAt(tick);
    painter->setPen(weakColor);
    int h = height();
    painter->drawLine(x, 0, x, h / 16);
    painter->drawLine(x, h * 7 / 16, x, h * 9 / 16);
    painter->drawLine(x, h * 15 / 16, x, h);
}
