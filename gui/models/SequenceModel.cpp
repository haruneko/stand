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

void SequenceModel::updateNotes(int trackId, const QList<vsq::Event> &changes)
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
    NoteChangeAction *action = new NoteChangeAction(trackId, before, changes, this);
    connect(action, SIGNAL(updateSequence(int, QList<vsq::Event>&)), this, SLOT(apply(int, QList<vsq::Event>&)));
    _history.push(new NoteChangeAction(trackId, before, changes, this));
}

void SequenceModel::apply(int trackId, QList<vsq::Event> &changes)
{
    if(trackId < 0 || _sequence->tracks()->size() <= trackId)
    {
        qWarning("SequenceModel::apply; tried to apply note changes in invalid track id: %d", trackId);
        return;
    }

    vsq::Track *track = _sequence->track(trackId);
    foreach(const vsq::Event &e, changes)
    {
        track->events()->setForId(e.id, e);
    }
    emit dataChanged();
}
