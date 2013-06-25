/*
 *
 *    ControlCurvePainter.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>
#include <BPList.hpp>

#include "AbstractGridView.h"

#include "ControlCurvePainter.h"

ControlCurvePainter::ControlCurvePainter(const vsq::BPList *control, const AbstractGridView *parent)
{
    _control = control;
    _parent = parent;
}

void ControlCurvePainter::paint(const QRect &rect, QPainter *painter)
{
    if(!_control)
    {
        return;
    }

    int currentIndex = 0;
    vsq::tick_t begin = _parent->tickAt(rect.left());
    int beginVal = _control->getValueAt(begin, &currentIndex);
    int maximum = _control->getMaximum();
    int minimum = _control->getMinimum();
    vsq::BP current(beginVal, 0);
    if(_control->size() != 0)
    {
        current = _control->get(currentIndex);
    }
    int x = rect.left();

    for(; x <= rect.right() && currentIndex + 1 < _control->size();)
    {
        int nextX = _parent->xAt(_control->getKeyClock(currentIndex + 1));
        int y = _parent->height() * (1.0 - (current.value - minimum) / (double)maximum);
        painter->fillRect(x, y, nextX - x + 1, _parent->height() - y + 1, color);
        x = nextX;
    }
    if(x <= rect.right())
    {
        int y = _parent->height() * (1.0 - (current.value - minimum) / (double)maximum);
        painter->fillRect(x, y, rect.right() - x + 1, _parent->height() - y + 1, color);
    }
}
