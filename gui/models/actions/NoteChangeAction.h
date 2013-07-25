/*
 *
 *    NoteChangeAction.h
 *                                    (c) HAL@shurabaP
 *                                        2013/07/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef NOTECHANGEACTION_H
#define NOTECHANGEACTION_H

#include <QObject>
#include <QUndoCommand>
#include <Event.hpp>

class SequenceModel;

/**
 *  @brief ノート情報の変更に関する undo, redo を行うクラス
 */
class NoteChangeAction : public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    explicit NoteChangeAction(int trackId, const QList<vsq::Event> &before, const QList<vsq::Event> &after, SequenceModel *model, QUndoCommand *parent = 0);

    void undo();
    void redo();
signals:
    void updateSequence(int, QList<vsq::Event> &);

private:
    int _trackId;
    QList<vsq::Event> _before;
    QList<vsq::Event> _after;
    SequenceModel *_model;
};

#endif // NOTECHANGEACTION_H
