/*
 *
 *    SequenceModel.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "SequenceModel.h"

#include "actions/NoteAppendAction.h"
#include "actions/NoteChangeAction.h"

SequenceModel::SequenceModel(vsq::Sequence *sequence, QObject *parent) :
    QObject(parent)
{
    _sequence = sequence;
    noteSnapTick = 120;
    edgeWidth = 16;
}

const vsq::Sequence *SequenceModel::sequence() const
{
    return _sequence;
}

int SequenceModel::snappedTick(int tick) const
{
    return (int)((double)tick / noteSnapTick + 0.5) * noteSnapTick;
}

const vsq::Event *SequenceModel::eventAt(int trackId, int eventId) const
{
    if(trackId < 0 || _sequence->tracks()->size() <= trackId)
    {
        return NULL;
    }
    vsq::Track *track = _sequence->track(trackId);
    return track->events()->findFromId(eventId);
}

void SequenceModel::updateEvents(int trackId, const QList<vsq::Event> &changes)
{
    QList<vsq::Event> before;
    foreach(const vsq::Event &e, changes)
    {
        const vsq::Event *counterpart = eventAt(trackId, e.id);
        if(counterpart)
        {
            before.append(counterpart->clone());
        }
    }
    NoteChangeAction *action = new NoteChangeAction(trackId, before, changes);
    connect(action, SIGNAL(notesToUpdate(int, QList<vsq::Event>&)), this, SLOT(onEventsUpdated(int,QList<vsq::Event>&)));
    _history.push(action);
}

void SequenceModel::appendEvents(int trackId, const QList<vsq::Event> &events)
{
    if(trackId < 0 || _sequence->tracks()->size() <= trackId)
    {
        return;
    }
    NoteAppendAction *action = new NoteAppendAction(trackId, events);
    connect(action, SIGNAL(notesToAppend(int, QList<vsq::Event>&)), this, SLOT(onEventsAppended(int, QList<vsq::Event>&)));
    connect(action, SIGNAL(notesToRemove(int, QList<vsq::Event>&)), this, SLOT(onEventsRemoved(int, QList<vsq::Event>&)));
    _history.push(action);
}

void SequenceModel::onEventsAppended(int trackId, QList<vsq::Event> &notes)
{
    for(int i = 0; i < notes.size(); i++)
    {
        vsq::Event &e = notes[i];
        e.id = _sequence->track(trackId)->events()->add(e);
    }
}

void SequenceModel::onEventsRemoved(int trackId, QList<vsq::Event> &notes)
{
    for(int i = 0; i < notes.size(); i++)
    {
        vsq::Event &e = notes[i];
        e.id = _sequence->track(trackId)->events()->add(e);
        int index = _sequence->track(trackId)->events()->findIndexFromId(e.id);
        if(index >= 0)
        {
            _sequence->track(trackId)->events()->removeAt(index);
        }
        else
        {
            qDebug("error in SequenceModel; Remove event @ negative index!");
        }
    }
}

void SequenceModel::onEventsUpdated(int trackId, QList<vsq::Event> &notes)
{
    for(int i = 0; i < notes.size(); i++)
    {
        vsq::Event &e = notes[i];
        _sequence->track(trackId)->events()->setForId(e.id, e);
    }
    emit dataChanged();
}
