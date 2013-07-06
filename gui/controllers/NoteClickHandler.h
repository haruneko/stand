/*
 *
 *    NoteClickHandler.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef NOTECLICKHANDLER_H
#define NOTECLICKHANDLER_H

#include <QObject>
#include <QPoint>

class QLabel;
class QMouseEvent;
class NoteView;

/**
 *  @brief 音符を表すラベル上で行われたマウスイベントを処理するクラス
 */
class NoteClickHandler : public QObject
{
    Q_OBJECT
public:
    NoteClickHandler(NoteView *view);
    virtual ~NoteClickHandler();

    void setView(NoteView *view);
protected:
    virtual bool eventFilter(QObject *o, QEvent *e);
private:
    bool _mousePressed(QLabel *l, QMouseEvent *e);
    bool _mouseMoved(QLabel *l, QMouseEvent *e);
    bool _mouseReleased(QLabel *l, QMouseEvent *e);

    void _destroy();

    NoteView *_view;

    /** @brief マウスドラッグ判定用 */
    bool _mouseDragged;
    /** @brief マウスクリック位置 */
    QPoint _mouseClicked;

    /** @brief 操作判定用 */
    enum
    {
        None = -1,
        Select,
        Move,
        ExtendForward,
        ExtendBackward
    } _operationType;
};

#endif // NOTECLICKHANDLER_H
