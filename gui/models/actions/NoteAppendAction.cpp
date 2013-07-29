/*
 *
 *    NoteAppendAction.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/07/30
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "NoteAppendAction.h"

NoteAppendAction::NoteAppendAction(int trackId, const QList<vsq::Event> &notes, QUndoCommand *parent) :
    QUndoCommand(parent)
{
    _trackId = trackId;
    _notes = notes;
}

void NoteAppendAction::undo()
{
    emit notesToRemove(_trackId, _notes);
}

void NoteAppendAction::redo()
{
    emit notesToAppend(_trackId, _notes);
}
