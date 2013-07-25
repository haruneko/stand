/*
 *
 *    NoteClickHandler.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QLabel>
#include <QEvent>
#include <QMouseEvent>

#include "../models/EventSelection.h"
#include "../models/SequenceModel.h"
#include "../views/NoteView.h"

#include "NoteClickHandler.h"

vsq::Event (NoteClickHandler::* const NoteClickHandler::_eventFunctions[])(const QPoint &, QLabel *) = {
    NULL,
    &NoteClickHandler::_eventMoved,
    &NoteClickHandler::_eventExtendedForward,
    &NoteClickHandler::_eventExtendedBackward,
};

NoteClickHandler::NoteClickHandler(SequenceModel *model, EventSelection *selection, NoteView *view) :
    QObject(view)
{
    _view = NULL;
    setSequence(model);
    setSelection(selection);
    setView(view);
}

void NoteClickHandler::_destroy()
{
    if(!_view)
    {
        return;
    }
    QList<QLabel *> labels = _view->labels();
    foreach(QLabel *l, labels)
    {
        l->removeEventFilter(this);
    }
}

void NoteClickHandler::setSelection(EventSelection *selection)
{
    _selection = selection;
}

void NoteClickHandler::setSequence(SequenceModel *model)
{
    _model = model;
}

void NoteClickHandler::setView(NoteView *view)
{
    if(_view == view)
    {
        return;
    }
    _destroy();
    QList<QLabel *> labels = _view->labels();
    foreach(QLabel *l, labels)
    {
        l->installEventFilter(this);
    }
}

bool NoteClickHandler::eventFilter(QObject *o, QEvent *e)
{
    QLabel *l = dynamic_cast<QLabel *>(o);
    if(l)
    {
        bool ret = false;
        switch(e->type())
        {
        case QEvent::MouseButtonPress:
            ret = _mousePressed(l, (QMouseEvent *)e);
            break;
        case QEvent::MouseMove:
            ret = _mouseMoved(l, (QMouseEvent *)e);
            break;
        case QEvent::MouseButtonRelease:
            ret = _mouseReleased(l, (QMouseEvent *)e);
            break;
        }
        return ret;
    }
    return QObject::eventFilter(o, e);
}

bool NoteClickHandler::_mousePressed(QLabel *l, QMouseEvent *e)
{
    // 初期化
    _mouseDragged = false;
    _labelLocations.clear();
    // 選択されたラベルの現在位置取得
    QList<QPair<int, QLabel *> > &labels = _view->labels(_selection->trackId(), _selection->ids());
    for(int i = 0; i < labels.size(); i++)
    {
        _labelLocations.insert(labels[i].second, QPair<int, QRect>(labels[i].first, labels[i].second->rect()));
    }

    // 親オブジェクト内での位置を計算する．
    _mouseClicked = QPoint(l->x() + e->x(), l->y() + e->y());

    if(e->x() < _model->edgeWidth)
    {
        _operationType = ExtendForward;
    }
    else if(l->width() - e->x() < _model->edgeWidth)
    {
        _operationType = ExtendBackward;
    }
    else
    {
        _operationType = Move;
    }
    return true;
}

bool NoteClickHandler::_mouseMoved(QLabel *l, QMouseEvent *e)
{
    _mouseDragged = true;

    QPoint current(l->x() + e->x(), l->y() + e->y());
    QPoint diff = current - _mouseClicked;

    if(_eventFunctions[_operationType])
    {
        _updateLabels(diff, _eventFunctions[_operationType]);
    }

    return true;
}

bool NoteClickHandler::_mouseReleased(QLabel *l, QMouseEvent *e)
{
    if(!_mouseDragged)
    {
        _operationType = Select;
    }
    QPoint diff(e->globalX() - _mouseClicked.x(), e->globalY() - _mouseClicked.y());

    if(_operationType == Select)
    {
        _selectNotes(l, e);
    }
    else
    {
        _updateNotes(diff, _eventFunctions[_operationType]);
    }

    return true;
}

vsq::Event NoteClickHandler::_eventExtendedBackward(const QPoint &diff, QLabel *l)
{
    const QPair<int, QRect> &val = _labelLocations[l];
    vsq::Event e = _model->eventAt(_selection->trackId(), val.first)->clone();
    vsq::tick_t tick = _model->snappedTick(_view->tickAt(val.second.right() + diff.x()));
    e.setLength(qMax((vsq::tick_t)0, tick - e.clock));
    return e;
}

vsq::Event NoteClickHandler::_eventExtendedForward(const QPoint &diff, QLabel *l)
{
    const QPair<int, QRect> &val = _labelLocations[l];
    vsq::Event e = _model->eventAt(_selection->trackId(), val.first)->clone();
    vsq::tick_t length = e.getLength();
    vsq::tick_t tick = e.clock;
    e.clock = _model->snappedTick(_view->tickAt(val.second.x() + diff.x()));
    length = qMax((vsq::tick_t)0, e.clock - tick);
    e.setLength(length);
    return e;
}

vsq::Event NoteClickHandler::_eventMoved(const QPoint &diff, QLabel *l)
{
    const QPair<int, QRect> &val = _labelLocations[l];
    vsq::Event e = _model->eventAt(_selection->trackId(), val.first)->clone();
    e.clock = _model->snappedTick(_view->tickAt(val.second.x() + diff.x()));
    e.note = _view->noteAt(val.second.y() + diff.y() + _view->noteHeight() / 2);
    return e;
}

void NoteClickHandler::_updateLabels(const QPoint &diff, vsq::Event (NoteClickHandler::*updateFunction)(const QPoint &, QLabel *))
{
    foreach(QLabel *l, _labelLocations.keys())
    {
        vsq::Event e = (this->*updateFunction)(diff, l);
        int x = _view->xAt(e.clock);
        int width = _view->xAt(e.clock + e.getLength()) - x;
        l->setGeometry(x, _view->yAt(e.note), width, _view->noteHeight());
    }
}

void NoteClickHandler::_updateNotes(const QPoint &diff, vsq::Event (NoteClickHandler::*updateFunction)(const QPoint &, QLabel *))
{
    QList<vsq::Event> changes;
    int trackId = _selection->trackId();
    foreach(QLabel *l, _labelLocations.keys())
    {
        changes.append((this->*updateFunction)(diff, l));
    }
    _model->updateNotes(trackId, changes);
}

void NoteClickHandler::_selectNotes(QLabel *l, QMouseEvent *e)
{

}
