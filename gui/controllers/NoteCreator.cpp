/*
 *
 *    NoteCreator.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/07/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QEvent>
#include <QMouseEvent>

#include "../models/SequenceModel.h"
#include "../views/NoteView.h"

#include "NoteCreator.h"

NoteCreator::NoteCreator(SequenceModel *model, NoteView *view) :
    QObject(view)
{
    _view = NULL;
    _temporaryNote = NULL;
    setView(_view);
}

NoteCreator::~NoteCreator()
{
    _destroy();
}

void NoteCreator::_destroy()
{
    if(_view)
    {
        _view->removeEventFilter(this);
    }
    _view = NULL;
}

void NoteCreator::setView(NoteView *view)
{
    _destroy();;
    _view = view;
}

void NoteCreator::setModel(SequenceModel *model)
{
    _model = model;
}

bool NoteCreator::eventFilter(QObject *o, QEvent *e)
{
    NoteView *v = dynamic_cast<NoteView *>(o);
    if(v && v == _view)
    {
        switch(e->type())
        {
        case QEvent::MouseButtonPress:
            _onMouseClicked((QMouseEvent *)e);
            break;
        case QEvent::MouseMove:
            _onMouseDragged((QMouseEvent *)e);
            break;
        case QEvent::MouseButtonRelease:
            _onMouseReleased((QMouseEvent *)e);
            break;
        }
        return true;
    }
    return QObject::eventFilter(o, e);
}

void NoteCreator::_onMouseClicked(QMouseEvent *e)
{
    delete _temporaryNote;
    _temporaryNote = new QLabel("a", _view);
    int tick = _model->snappedTick(_view->tickAt(e->x()));
    int note = _view->noteAt(e->y());
    int x = _view->xAt(tick);
    int y = _view->yAt(note);
    _temporaryNote->setGeometry(x, y, 1, _view->noteHeight());
    _view->setNoteLabelProperty(_temporaryNote);
    _temporaryNote->show();
}

void NoteCreator::_onMouseDragged(QMouseEvent *e)
{
    int tick = _model->snappedTick(_view->tickAt(e->x()));
    int x1 = _view->xAt(tick);
    int x2 = _temporaryNote->x();
    int x = qMin(x1, x2);
    int width = abs(x1 - x2);
    _temporaryNote->setGeometry(x, _temporaryNote->y(), width, _view->noteHeight());
}

void NoteCreator::_onMouseReleased(QMouseEvent *e)
{
    _onMouseDragged(e);
    QList<vsq::Event> events;
    events << _eventFromTemporaryLabel();
    _model->appendEvents(_view->currentTrackId(), events);
    delete _temporaryNote;
    _temporaryNote = NULL;
}
