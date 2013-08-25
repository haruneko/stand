/*
 *
 *    MazeView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPaintEvent>
#include <QPainter>

#include "../models/TimeMapModel.h"
#include "dsp/Envelope.h"

#include "MazeView.h"

MazeView::MazeView(TimeMapModel *timeMap, Envelope *contour, int secWidth, QWidget *parent) :
    QWidget(parent)
{
    _timeMap = NULL;
    _contour = NULL;
    _secWidth = secWidth;
    setTimeMap(timeMap);
    setContour(contour);
}

void MazeView::setTimeMap(TimeMapModel *timeMap)
{
    _timeMap = timeMap;
    update();
}

int MazeView::xAt(double ms) const
{
    return _secWidth * ms / 1000;
}

int MazeView::yAt(double r) const
{
    return height() * (0.5 - 0.5 * r);
}

double MazeView::msAt(int x) const
{
    return (double)x / (double)_secWidth * 1000.0;
}

double MazeView::ratioAt(int y) const
{
    return 1.0 - 2.0 * (double)y / (double)height();
}

void MazeView::setContour(Envelope *contour)
{
    int w = xAt(contour->msLength());
    resize(w, height());
    _contour = contour;
    update();
}

void MazeView::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(e->rect(), this->palette().background());
    double previousY = yAt(_contour->value(msAt(e->rect().left())));
    for(int x = e->rect().left() + 1; x <= e->rect().right(); x++)
    {
        // TODO: paint algorhythm here.
    }
}
