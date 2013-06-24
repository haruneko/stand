/*
 *
 *    ControlSelectionView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QLabel>
#include <QHash>
#include <QPainter>
#include <QPaintEvent>
#include <QBoxLayout>

#include "ControlSelectionView.h"

ControlSelectionView::ControlSelectionView(const QList<QString> &labelNames, int noteHeight, QWidget *parent) :
    QWidget(parent),
    foregroundColor(128, 192, 255),
    backgroundColor(64, 64, 64)
{
    _noteHeight = noteHeight;
    controlKindChanged(labelNames);
}

ControlSelectionView::~ControlSelectionView()
{
    _destroy();
}

void ControlSelectionView::_destroy()
{
    qDeleteAll(_labels);
    _labels.clear();
    setLayout(new QBoxLayout(QBoxLayout::TopToBottom, this));
    layout()->setContentsMargins(0, 0, 0, 0);
}

void ControlSelectionView::controlKindChanged(const QList<QString> &kinds)
{
    _destroy();
    foreach(const QString &kind, kinds)
    {
        layout()->addWidget(_registerLabel(kind));
    }
}

QLabel *ControlSelectionView::_registerLabel(const QString &name)
{
    QLabel *l = new QLabel(name, this);
    QPalette palette(l->palette());
    palette.setColor(l->foregroundRole(), foregroundColor);
    palette.setColor(l->backgroundRole(), backgroundColor);
    l->setPalette(palette);
    l->setFixedHeight(_noteHeight);
    l->setFrameStyle(QFrame::Box);
    _labels.insert(name, l);
    return l;
}

void ControlSelectionView::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(e->rect(), backgroundColor);
}
