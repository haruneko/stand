/*
 *
 *    ControlCurveSelector.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QEvent>
#include <QLabel>

#include "../models/ControlCurveSelection.h"
#include "../views/ControlCurveNameView.h"

#include "ControlCurveSelector.h"

ControlCurveSelector::ControlCurveSelector(ControlCurveSelection *selection, ControlCurveNameView *view) :
    QObject(view)
{
    _view = NULL;
    _selection = selection;
    setView(view);
}

void ControlCurveSelector::_destroy()
{
    if(_view)
    {
        QList<QLabel *> labels = _view->labels();
        foreach(QLabel *l, labels)
        {
            l->removeEventFilter(this);
        }
    }
}

void ControlCurveSelector::setView(ControlCurveNameView *view)
{
    _destroy();
    _view = view;

    QList<QLabel *> labels = _view->labels();
    foreach(QLabel *l, labels)
    {
        l->installEventFilter(this);
    }
}

bool ControlCurveSelector::eventFilter(QObject *o, QEvent *e)
{
    QLabel *l = dynamic_cast<QLabel *>(o);
    if(l)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            if(_selection->mainName != l->text())
            {
                _selection->changeMain(l->text());
            }
        }
    }
    return QObject::eventFilter(o, e);
}
