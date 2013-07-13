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
