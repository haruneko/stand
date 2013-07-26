/*
 *
 *    NoteSelector.h
 *                                    (c) HAL@shurabaP
 *                                        2013/07/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef NOTESELECTOR_H
#define NOTESELECTOR_H

#include <QLabel>
#include <QObject>

class EventSelection;
class NoteView;
class QMouseEvent;

class NoteSelector : public QObject
{
    Q_OBJECT
public:
    explicit NoteSelector(EventSelection *selection, NoteView *view);
    virtual ~NoteSelector();

    QColor SelectAreaColor;

public slots:
    void setView(NoteView *view);
    void setSelection(EventSelection *selection);
protected:
    bool eventFilter(QObject *o, QEvent *e);
private:
    void _destroy();

    void _onMouseClicked(QMouseEvent *e);
    void _onMouseMoved(QMouseEvent *e);
    void _onMouseReleased(QMouseEvent *e);

    void _updateSelection();
    static bool _collides(const QRect &a, const QRect &b);

    EventSelection *_selection;
    NoteView *_view;
    QLabel *_rect;
    QList<QPair<int, QLabel *> > _viewData;
};

#endif // NOTESELECTOR_H
