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

#include "../views/NoteView.h"

#include "NoteClickHandler.h"

NoteClickHandler::NoteClickHandler(NoteView *view) :
    QObject(view)
{
    _view = NULL;
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
    _mouseDragged = false;
    _mouseClicked = e->pos();
    return true;
}

bool NoteClickHandler::_mouseMoved(QLabel *l, QMouseEvent *e)
{
    _mouseDragged = true;
    return true;
}

bool NoteClickHandler::_mouseReleased(QLabel *l, QMouseEvent *e)
{
    return true;
}

