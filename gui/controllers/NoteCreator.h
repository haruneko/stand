/*
 *
 *    NoteCreator.h
 *                                    (c) HAL@shurabaP
 *                                        2013/07/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef NOTECREATOR_H
#define NOTECREATOR_H

#include <Event.hpp>
#include <QObject>

class EventSelection;
class NoteView;
class SequenceModel;

class QLabel;
class QMouseEvent;

class NoteCreator : public QObject
{
    Q_OBJECT
public:
    explicit NoteCreator(SequenceModel *model, NoteView *view);
    virtual ~NoteCreator();

public slots:
    void setView(NoteView *view);
    void setModel(SequenceModel *model);
protected:
    bool eventFilter(QObject *o, QEvent *e);
private:
    void _destroy();

    void _onMouseClicked(QMouseEvent *e);
    void _onMouseDragged(QMouseEvent *e);
    void _onMouseReleased(QMouseEvent *e);
    vsq::Event _eventFromTemporaryLabel();

    NoteView *_view;
    SequenceModel *_model;
    QLabel *_temporaryNote;
};

#endif // NOTECREATOR_H
