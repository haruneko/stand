/*
 *
 *    NoteAppendAction.h
 *                                    (c) HAL@shurabaP
 *                                        2013/07/30
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef NOTEAPPENDACTION_H
#define NOTEAPPENDACTION_H

#include <Event.hpp>
#include <QUndoCommand>

class SequenceModel;

class NoteAppendAction : public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    explicit NoteAppendAction(int trackId, const QList<vsq::Event> &notes, QUndoCommand *parent = 0);

    void undo();
    void redo();
signals:
    void notesToAppend(int, QList<vsq::Event> &);
    void notesToRemove(int, QList<vsq::Event> &);

private:
    int _trackId;
    QList<vsq::Event> _notes;
};

#endif // NOTEAPPENDACTION_H
