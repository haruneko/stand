/*
 *
 *    ContourEditCommand.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "dsp/Envelope.h"
#include "../models/ContourModel.h"

#include "ContourEditCommand.h"

ContourEditCommand::ContourEditCommand(ContourModel *target, int beginIndex, const QList<double> newData, QUndoCommand *parent) :
    QUndoCommand(parent)
{
    _beginIndex = beginIndex;
    _newData = newData;
    _target = target;
    int endIndex = qMin(beginIndex + newData.size(), target->contour()->size());
    for(int i = beginIndex; i < endIndex; i++)
    {
        _oldData.append(target->contour()->value(i));
    }
}

void ContourEditCommand::undo()
{
    _target->setData(_beginIndex, _oldData);
    QUndoCommand::undo();
}

void ContourEditCommand::redo()
{
    _target->setData(_beginIndex, _newData);
    QUndoCommand::redo();
}

