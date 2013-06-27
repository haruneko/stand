/*
 *
 *    ControlCurveNameView.cpp
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
#include <QVBoxLayout>

#include "../utility/Utility.h"
#include "../models/ControlCurveSelection.h"

#include "../controllers/ControlCurveSelector.h"

#include "ControlCurveNameView.h"

ControlCurveNameView::ControlCurveNameView(const QList<QString> &labelNames, int noteHeight, QWidget *parent) :
    QWidget(parent),
    foregroundColor(128, 192, 255),
    backgroundColor(64, 64, 64)
{
    _noteHeight = noteHeight;
    QList<QString> names = labelNames;
    controlKindChanged(names);
}

ControlCurveNameView::~ControlCurveNameView()
{
    _destroy();
}

void ControlCurveNameView::_destroy()
{
    qDeleteAll(_labels);
    _labels.clear();
    setLayout(new QVBoxLayout(this));
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setContentsMargins(1, 1, 1, 1);
}

void ControlCurveNameView::controlKindChanged(QList<QString> &kinds)
{
    _destroy();
    foreach(const QString &kind, kinds)
    {
        layout()->addWidget(_registerLabel(kind));
    }
}

void ControlCurveNameView::noteHeightChanged(int h)
{
    foreach(QLabel *l, _labels)
    {
        l->setFixedHeight(h);
    }
}

void ControlCurveNameView::selectionChanged(ControlCurveSelection &selection)
{
    QColor main = mixColor(foregroundColor, backgroundColor, 1.0 / 2);
    QColor sub = mixColor(foregroundColor, backgroundColor, 1.0 / 3);
    for(QHash<QString, QLabel *>::iterator it = _labels.begin(); it != _labels.end(); it++)
    {
        const QString &key = it.key();
        QColor *c = NULL;
        if(selection.mainName == key)
        {
            c = &main;
        }
        else if(selection.subNames.contains(key))
        {
            c = &sub;
        }
        else
        {
            c = &backgroundColor;
        }
        QLabel *l = it.value();
        QPalette palette(l->palette());
        palette.setColor(l->backgroundRole(), *c);
        l->setPalette(palette);
    }
}

QLabel *ControlCurveNameView::_registerLabel(const QString &name)
{
    QLabel *l = new QLabel(name, this);
    QPalette palette(l->palette());
    palette.setColor(l->foregroundRole(), foregroundColor);
    palette.setColor(l->backgroundRole(), backgroundColor);
    l->setPalette(palette);
    l->setFixedHeight(_noteHeight);
    l->setFrameStyle(QFrame::Box);
    l->setAutoFillBackground(true);
    _labels.insert(name, l);

    return l;
}

void ControlCurveNameView::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(e->rect(), backgroundColor);
}

QList<QLabel *> ControlCurveNameView::labels()
{
    QList<QLabel *> ret;
    foreach(QLabel *l, _labels)
    {
        ret.append(l);
    }
    return ret;
}
