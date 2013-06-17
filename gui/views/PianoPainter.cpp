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

PianoPainter::PianoPainter(const QColor &w, const QColor &b, const QColor &l)
{
    whiteKeyColor = w;
    blackKeyColor = b;
    lineColor = l;
}

void PianoPainter::paint(int noteHeight, const QRect &rect, QPainter *painter)
{
    QPen old(painter->pen());
    int beginNote = 127 - rect.top() / noteHeight;
    int endNote = 127 - rect.bottom() / noteHeight - 1;

    painter->setPen(lineColor);
    for(int note = beginNote; note >= endNote; note--)
    {
        const QColor &c = IsBlackKey(note) ? blackKeyColor : whiteKeyColor;
        int y = (note - 127) * noteHeight;
        painter->fillRect(rect.left(), y, rect.width(), noteHeight, c);
        painter->drawLine(rect.left(), y, rect.right(), y);
    }

    painter->setPen(old);
}
