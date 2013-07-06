/*
 *
 *    EventSelection.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/07/06
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "EventSelection.h"

EventSelection::EventSelection(QObject *parent) :
    QObject(parent)
{
    _trackId = 0;
    _previous = NULL;
}

EventSelection::~EventSelection()
{
    delete _previous;
}

void EventSelection::_changeSelection(int trackId, const QList<int> &ids)
{
    delete _previous;
    _previous = new EventSelection;
    _previous->_trackId = _trackId;
    _previous->_ids = _ids;
    _trackId = trackId;
    _ids = ids;
    emit selectionChanged(this, _previous);
}

void EventSelection::clear()
{
    _changeSelection(0, QList<int>());
}

void EventSelection::setTrackId(int trackId)
{
    _changeSelection(trackId, _ids);
}

void EventSelection::setIds(const QList<int> &ids)
{
    _changeSelection(_trackId, ids);
}

int EventSelection::trackId() const
{
    return _trackId;
}

const QList<int> &EventSelection::ids() const
{
    return _ids;
}
