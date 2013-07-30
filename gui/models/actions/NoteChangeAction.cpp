/*
 *
 *    NoteChangeAction.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/07/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "../SequenceModel.h"

#include "NoteChangeAction.h"

NoteChangeAction::NoteChangeAction(int trackId, const QList<vsq::Event> &before, const QList<vsq::Event> &after, QUndoCommand *parent) :
    QUndoCommand(parent)
{
    _trackId = trackId;
    _before = before;
    _after = after;
}

void NoteChangeAction::undo()
{
    QUndoCommand::undo();
    emit notesToUpdate(_trackId, _before);
}

void NoteChangeAction::redo()
{
    QUndoCommand::redo();
    emit notesToUpdate(_trackId, _before);
}
