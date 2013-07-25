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
