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

    switch(_operationType)
    {
    case Move:
        _move(diff, l, e);
        break;
    case ExtendForward:
        _extendForward(diff, l, e);
        break;
    case ExtendBackward:
        _extendBackward(diff, l, e);
        break;
    }

    return true;
}

void NoteClickHandler::_move(const QPoint &diff, QLabel *l, QMouseEvent *e)
{
    foreach(QLabel *l, _labelLocations.keys())
    {
        const QPair<int, QRect> &val = _labelLocations[l];
        int tick = _model->snappedTick(_view->tickAt(val.second.x() + diff.x()));
        int x = _view->xAt(tick);
        l->setGeometry(x, l->y(), l->width(), l->height());
    }
}

void NoteClickHandler::_extendForward(const QPoint &diff, QLabel */*l*/, QMouseEvent */*e*/)
{
    foreach(QLabel *l, _labelLocations.keys())
    {
        const QPair<int, QRect> &val = _labelLocations[l];
        int tick = _model->snappedTick(_view->tickAt(val.second.x() + diff.x()));
        int x = _view->xAt(tick);
        l->setGeometry(x, l->y(), l->rect().right() - x, l->height());
    }
}

void NoteClickHandler::_extendBackward(const QPoint &diff, QLabel *l, QMouseEvent *e)
{
    foreach(QLabel *l, _labelLocations.keys())
    {
        const QPair<int, QRect> &val = _labelLocations[l];
        int tick = _model->snappedTick(_view->tickAt(val.second.right() + diff.x()));
        int width = _view->xAt(tick) - l->x();
        l->setGeometry(l->x(), l->y(), width, l->height());
    }
}

bool NoteClickHandler::_mouseReleased(QLabel *l, QMouseEvent *e)
{
    if(!_mouseDragged)
    {
        _operationType = Select;
    }
    QPoint diff(e->globalX() - _mouseClicked.x(), e->globalY() - _mouseClicked.y());
    return true;
}

