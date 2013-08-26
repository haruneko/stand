/*
 *
 *    ContourEditCommand.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTOUREDITCOMMAND_H
#define CONTOUREDITCOMMAND_H

#include <QUndoCommand>

class ContourModel;

class ContourEditCommand : public QUndoCommand
{
public:
    explicit ContourEditCommand(ContourModel *target, int beginIndex, const QList<double> newData, QUndoCommand *parent = 0);
    void undo();
    void redo();
private:
    int _beginIndex;
    QList<double> _newData;
    QList<double> _oldData;
    ContourModel *_target;
};

#endif // CONTOUREDITCOMMAND_H
