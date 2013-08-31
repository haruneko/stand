/*
 *
 *    NoteModifier.cpp
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

#include "NoteModifier.h"

vsq::Event (NoteModifier::* const NoteModifier::_eventFunctions[])(const QPoint &, const QPair<int, QRect> &) = {
    NULL,
    &NoteModifier::_eventMoved,
    &NoteModifier::_eventExtendedForward,
    &NoteModifier::_eventExtendedBackward,
};

NoteModifier::NoteModifier(SequenceModel *model, EventSelection *selection, NoteView *view) :
    QObject(view)
{
    _view = NULL;
    setSequence(model);
    setSelection(selection);
    setView(view);
}

void NoteModifier::_destroy()
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

void NoteModifier::setSelection(EventSelection *selection)
{
    _selection = selection;
}

void NoteModifier::setSequence(SequenceModel *model)
{
    _model = model;
}

void NoteModifier::setView(NoteView *view)
{
    if(_view == view)
    {
        return;
    }
    _destroy();
    if(!_view)
    {
        QList<QLabel *> labels = _view->labels();
        foreach(QLabel *l, labels)
        {
            l->installEventFilter(this);
        }
    }
}

bool NoteModifier::eventFilter(QObject *o, QEvent *e)
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

bool NoteModifier::_mousePressed(QLabel *l, QMouseEvent *e)
{
    // 初期化
    _mouseDragged = false;
    _labelLocations.clear();
    // 選択されたラベルの現在位置取得
    const QList<QPair<int, QLabel *> > &labels = _view->labels(_selection->trackId(), _selection->ids());
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

bool NoteModifier::_mouseMoved(QLabel *l, QMouseEvent *e)
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

bool NoteModifier::_mouseReleased(QLabel *l, QMouseEvent *e)
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

vsq::Event NoteModifier::_eventExtendedBackward(const QPoint &diff, const QPair<int, QRect> &val)
{
    vsq::Event e = _model->eventAt(_selection->trackId(), val.first)->clone();
    vsq::tick_t tick = _model->snappedTick(_view->tickAt(val.second.right() + diff.x()));
    e.setLength(qMax((vsq::tick_t)0, tick - e.clock));
    return e;
}

vsq::Event NoteModifier::_eventExtendedForward(const QPoint &diff, const QPair<int, QRect> &val)
{
    vsq::Event e = _model->eventAt(_selection->trackId(), val.first)->clone();
    vsq::tick_t length = e.getLength();
    vsq::tick_t tick = e.clock;
    e.clock = _model->snappedTick(_view->tickAt(val.second.x() + diff.x()));
    length = qMax((vsq::tick_t)0, e.clock - tick);
    e.setLength(length);
    return e;
}

vsq::Event NoteModifier::_eventMoved(const QPoint &diff, const QPair<int, QRect> &val)
{
    vsq::Event e = _model->eventAt(_selection->trackId(), val.first)->clone();
    e.clock = _model->snappedTick(_view->tickAt(val.second.x() + diff.x()));
    e.note = _view->noteAt(val.second.y() + diff.y() + _view->noteHeight() / 2);
    return e;
}

void NoteModifier::_updateLabels(const QPoint &diff, vsq::Event (NoteModifier::*updateFunction)(const QPoint &, const QPair<int, QRect> &))
{
    foreach(QLabel *l, _labelLocations.keys())
    {
        vsq::Event e = (this->*updateFunction)(diff, _labelLocations[l]);
        int x = _view->xAt(e.clock);
        int width = _view->xAt(e.clock + e.getLength()) - x;
        l->setGeometry(x, _view->yAt(e.note), width, _view->noteHeight());
    }
}

void NoteModifier::_updateNotes(const QPoint &diff, vsq::Event (NoteModifier::*updateFunction)(const QPoint &, const QPair<int, QRect> &))
{
    QList<vsq::Event> changes;
    int trackId = _selection->trackId();
    foreach(QLabel *l, _labelLocations.keys())
    {
        changes.append((this->*updateFunction)(diff, _labelLocations[l]));
    }
    _model->updateEvents(trackId, changes);
}

void NoteModifier::_selectNotes(QLabel *l, QMouseEvent *e)
{
    QList<int> ids;
    if(e->modifiers() & Qt::ControlModifier)
    {
        // コントロール押されていたら今の選択範囲に追加するなど
        ids = _selection->ids();
    }
    int id = _labelLocations[l].first;

    if(!ids.contains(id))
    {
        // 選択済みでなければ選択に追加
        ids.append(id);
    }
    else
    {
        // 選択済みであれば選択解除
        ids.removeOne(id);
    }
    _selection->setIds(ids);
}
