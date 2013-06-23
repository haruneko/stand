/*
 *
 *    ControlCurveView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>
#include <QPaintEvent>

#include <BPList.hpp>
#include <Track.hpp>
#include "ControlCurveView.h"

ControlCurveView::ControlCurveView(int trackId, const string &controlName, int divCount, int beatWidth, const vsq::Sequence *sequence, QWidget *parent)
    : AbstractGridView(divCount, beatWidth, sequence, parent)
{
    _controlName = controlName;
    backgroundColor = Qt::black;
    color = Qt::white;
    _control = NULL;
    _trackId = trackId;
    if(sequence && (0 <= trackId && trackId < sequence->tracks()->size()))
    {
        _control = sequence->track(trackId)->curve(controlName);
    }
}

void ControlCurveView::trackChanged(int id)
{
    if(id != _trackId)
    {
        _control = sequence()->track(id)->curve(_controlName);
        update();
    }
    _trackId = id;
}

void ControlCurveView::setControlName(const std::string &curveName)
{
    if(_controlName == curveName)
    {
        return;
    }
    _control = sequence()->track(_trackId)->curve(curveName);
    update();
}

void ControlCurveView::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QRegion region(e->region());
    foreach(const QRect &r, region.rects())
    {
        p.fillRect(r, backgroundColor);
        paint(r, &p);
    }
}

void ControlCurveView::paint(const QRect &rect, QPainter *painter)
{
    if(!_control)
    {
        return;
    }

    int currentIndex;
    vsq::tick_t begin = tickAt(rect.left());
    _control->getValueAt(begin, &currentIndex);
    int maximum = _control->getMaximum();
    int minimum = _control->getMinimum();
    vsq::BP current = _control->get(currentIndex);
    int x = rect.left();

    for(; x <= rect.right() && currentIndex + 1 < _control->size();)
    {
        int nextX = xAt(_control->getKeyClock(currentIndex + 1));
        int y = height() * (1.0 - (current.value - minimum) / (double)maximum);
        painter->fillRect(x, y, nextX - x + 1, height() - y + 1, color);
        x = nextX;
    }
    if(x <= rect.right())
    {
        int y = height() * (1.0 - (current.value - minimum) / (double)maximum);
        painter->fillRect(x, y, rect.right() - x + 1, height() - y + 1, color);
    }
}
