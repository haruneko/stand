/*
 *
 *    AbstractPianoPainter.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>
#include <QRect>

#include "../utility/Utility.h"
#include "PianoPainter.h"

PianoPainter::PianoPainter(int minNote, int maxNote, const QColor &whiteKeyColor, const QColor &blackKeyColor, const QColor &lineColor)
{
    this->minNote = minNote;
    this->maxNote = maxNote;
    this->whiteKeyColor = whiteKeyColor;
    this->blackKeyColor = blackKeyColor;
    this->lineColor = lineColor;
}

void PianoPainter::paint(int noteHeight, const QRect &rect, QPainter *painter)
{
    QPen old(painter->pen());
    int beginNote = 127 - rect.top() / noteHeight;
    int endNote = 127 - rect.bottom() / noteHeight - 1;
    beginNote = qMin(beginNote, maxNote);
    endNote = qMax(endNote, minNote);

    painter->setPen(lineColor);
    for(int note = beginNote; note >= endNote; note--)
    {
        const QColor &c = IsBlackKey(note) ? blackKeyColor : whiteKeyColor;
        int y = (127 - note) * noteHeight;
        painter->fillRect(rect.left(), y, rect.width(), noteHeight, c);
        painter->drawLine(rect.left(), y, rect.right() + 1, y);
    }

    painter->setPen(old);
}
