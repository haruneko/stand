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

#include "dsp/Envelope.h"
#include "../models/TimeMapModel.h"
#include "../models/ContourModel.h"

#include "MazeView.h"

MazeView::MazeView(TimeMapModel *timeMap, ContourModel *contour, double pixelPerSecond, QWidget *parent) :
    QWidget(parent)
{
    _timeMap = NULL;
    _contour = NULL;
    _pixelPerSecond = pixelPerSecond;
    setTimeMap(timeMap);
    setContour(contour, pixelPerSecond);
}

MazeView::~MazeView()
{
    this->disconnect();
}

void MazeView::setTimeMap(TimeMapModel *timeMap)
{
    if(_timeMap)
    {
        disconnect(_timeMap, SIGNAL(dataChanged()), this, SLOT(update()));
    }
    _timeMap = timeMap;
    if(_timeMap)
    {
        connect(_timeMap, SIGNAL(dataChanged()), this, SLOT(update()));
    }
    update();
}

void MazeView::setContour(ContourModel *contour, double pixelPerSecond)
{
    if(_contour)
    {
        disconnect(_contour, SIGNAL(dataChanged(int,int)), this, SLOT(onContourChanged(int,int)));
    }
    _contour = contour;
    _pixelPerSecond = pixelPerSecond;
    _resizeForWidth();
    if(_contour)
    {
       connect(_contour, SIGNAL(dataChanged(int,int)), this, SLOT(onContourChanged(int,int)));
    }
    update();
}

int MazeView::xAt(double ms) const
{
    return _pixelPerSecond * ms / 1000;
}

int MazeView::yAt(double r) const
{
    return height() * (0.5 - 0.5 * r);
}

double MazeView::msAt(int x) const
{
    return (double)x / _pixelPerSecond * 1000.0;
}

double MazeView::ratioAt(int y) const
{
    return 1.0 - 2.0 * (double)y / (double)height();
}

void MazeView::_resizeForWidth()
{
    if(!_contour)
    {
        return;
    }
    int w = xAt(_contour->contour()->msLength());
    setFixedWidth(w);
    update();
}

void MazeView::onContourChanged(int begin, int end)
{
    if(begin > end)
    {
        qSwap(begin, end);
    }
    int xBegin = xAt(_contour->contour()->msFramePeriod() * begin);
    int xEnd = xAt(_contour->contour()->msFramePeriod() * end);
    update(QRect(xBegin, 0, xEnd, height()));
}

void MazeView::onWidthPerSecondChanged(double w)
{
    _pixelPerSecond = w;
    _resizeForWidth();
}

void MazeView::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    if(!_timeMap || !_contour)
    {
        return;
    }
    QPainter p(this);
    p.fillRect(e->rect(), this->palette().background());
    p.setBrush(this->palette().foreground());
    double previousY = yAt(_contour->contour()->value(msAt(e->rect().left())));
    for(int x = e->rect().left() + 1; x <= e->rect().right(); x++)
    {
        int y = yAt(_contour->contour()->value(msAt(x)));
        p.drawLine(x - 1, previousY, x, y);
        previousY = y;
    }
    // TODO : change brush here
    for(int i = 0; i < _timeMap->map().size(); i++)
    {
        const QPair<double, double> &pair = _timeMap->map().at(i);
        p.drawLine(xAt(pair.first), 0, xAt(pair.second), height());
    }
}
