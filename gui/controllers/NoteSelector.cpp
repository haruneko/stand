/*
 *
 *    NoteSelector.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/07/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QEvent>
#include <QMouseEvent>

#include "../models/EventSelection.h"
#include "../utility/Utility.h"
#include "../views/NoteView.h"

#include "NoteSelector.h"

NoteSelector::NoteSelector(EventSelection *selection, NoteView *view) :
    QObject(view),
    SelectAreaColor(128, 192, 192, 128)
{
    _selection = selection;
    _view = NULL;
    _rect = NULL;
    setView(view);
}

NoteSelector::~NoteSelector()
{
    _destroy();
}

void NoteSelector::_destroy()
{
    if(!_view)
    {
        return;
    }
    _view->removeEventFilter(this);
    _view = NULL;
    delete _rect;
    _rect = NULL;
}

void NoteSelector::setSelection(EventSelection *selection)
{
    _selection = selection;
}

void NoteSelector::setView(NoteView *view)
{
    _view = view;
    delete _rect;
    _rect = NULL;
    if(_view)
    {
        _view->installEventFilter(this);
        _rect = new QLabel(_view);
        QPalette palette(_rect->palette());
        palette.setColor(_rect->backgroundRole(), SelectAreaColor);
        _rect->setPalette(palette);
    }
}

bool NoteSelector::eventFilter(QObject *o, QEvent *e)
{
    NoteView *v = dynamic_cast<NoteView *>(o);
    // ビューとオブジェクトが一致してラベルが生きてたら処理する
    if(v && _rect && v == _view)
    {
        switch(e->type())
        {
        case QEvent::MouseButtonPress:
            _onMouseClicked((QMouseEvent *)e);
            break;
        case QEvent::MouseMove:
            _onMouseMoved((QMouseEvent *)e);
            break;
        case QEvent::MouseButtonRelease:
            _onMouseReleased((QMouseEvent *)e);
            break;
        }
    }
    return QObject::eventFilter(o, e);
}

void NoteSelector::_onMouseClicked(QMouseEvent *e)
{
    _rect->show();
    _rect->raise();
    _rect->setGeometry(_rect->x(), _rect->y(), 0, 0);
    _viewData = _view->labels(_selection->trackId());
}

void NoteSelector::_onMouseMoved(QMouseEvent *e)
{
    _rect->setGeometry(_rect->x(), _rect->y(), _rect->x() - e->x(), _rect->y() - e->y());
}

void NoteSelector::_onMouseReleased(QMouseEvent *e)
{
    _viewData.clear();
    _rect->hide();
}

void NoteSelector::_updateSelection()
{
    QList<int> ids;
    QPair<int, QLabel *> &val = _viewData.first();
    foreach(val, _viewData)
    {
        if(collides(_rect->rect(), val.second->rect()))
        {
            ids.append(val.first);
        }
    }
    if(ids != _selection->ids())
    {
        _selection->setIds(ids);
    }
}
