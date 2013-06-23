/*
 *
 *    PianoView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QMouseEvent>
#include <QMoveEvent>
#include <QPaintEvent>
#include <QPainter>

#include "../utility/Utility.h"
#include "PianoView.h"

PianoView::PianoView(int noteHeight, QWidget *parent) :
    QWidget(parent),
    _n0(this), _n1(this), _n2(this), _n3(this), _n4(this),
    piano(0, 128)
{
    _noteHeight = -1;
    noteHeightChanged(noteHeight);

    QPalette palette(_n0.palette());
    palette.setColor(_n0.foregroundRole(), Qt::black);
    _n0.setPalette(palette);
    palette.setColor(_n0.foregroundRole(), Qt::white);
    _n1.setPalette(palette);
    _n2.setPalette(palette);
    _n3.setPalette(palette);
    _n4.setPalette(palette);
    _n0.raise();

    leaveEvent(NULL);

    setMouseTracking(true);
}

void PianoView::noteHeightChanged(int h)
{
    if(_noteHeight == h)
    {
        return;
    }
    _noteHeight = h;
    QFont font(_n0.font());
    font.setWeight(QFont::Bold);
    font.setPixelSize(_noteHeight - 2);
    _n0.setFont(font);
    _n1.setFont(font);
    _n2.setFont(font);
    _n3.setFont(font);
    _n4.setFont(font);
    setMinimumHeight(128 * h);
    update();
}

void PianoView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    const QRegion &r = e->region();
    foreach(const QRect &rect, r.rects())
    {
        piano.paint(_noteHeight, rect, &painter);
    }
}

void PianoView::mouseMoveEvent(QMouseEvent *e)
{
    QString text = NoteName(127 - (e->y() / _noteHeight));
    int w = _noteHeight * 6, h = _noteHeight;
    _n0.setText(text);
    _n1.setText(text);
    _n2.setText(text);
    _n3.setText(text);
    _n4.setText(text);
    int x = e->x() + 16;
    _n0.setGeometry(x, e->y(), w, h);
    _n1.setGeometry(x + 1, e->y(), w, h);
    _n2.setGeometry(x, e->y() + 1, w, h);
    _n3.setGeometry(x - 1, e->y(), w, h);
    _n4.setGeometry(x, e->y() - 1, w, h);
}

void PianoView::enterEvent(QEvent *)
{
    _n0.show();
    _n1.show();
    _n2.show();
    _n3.show();
    _n4.show();
}

void PianoView::leaveEvent(QEvent *)
{
    _n0.hide();
    _n1.hide();
    _n2.hide();
    _n3.hide();
    _n4.hide();
}

void PianoView::moveEvent(QMoveEvent *e)
{
    int w = _noteHeight * 6, h = _noteHeight;
    int dx = e->pos().x() - e->oldPos().x();
    int dy = e->pos().y() - e->oldPos().y();
    int x = _n0.x() - dx;
    int y = _n0.y() - dy;
    QString text = NoteName(127 - (y / _noteHeight));
    _n0.setText(text);
    _n1.setText(text);
    _n2.setText(text);
    _n3.setText(text);
    _n4.setText(text);
    _n0.setGeometry(x, y, w, h);
    _n1.setGeometry(x + 1, y, w, h);
    _n2.setGeometry(x, y + 1, w, h);
    _n3.setGeometry(x - 1, y, w, h);
    _n4.setGeometry(x, y - 1, w, h);
}
