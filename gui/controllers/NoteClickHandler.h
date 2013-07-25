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
#include <QHash>
#include <QRect>

#include <Event.hpp>

class QLabel;
class QMouseEvent;
class NoteView;
class SequenceModel;
class EventSelection;

/**
 *  @brief 音符を表すラベル上で行われたマウスイベントを処理するクラス
 */
class NoteClickHandler : public QObject
{
    Q_OBJECT
public:
    /**
     *  @brief 初期値を与えて初期化します．
     *  @param model このクラスが影響を与えるモデル
     *  @param selection このクラスが影響を与える選択範囲
     *  @param view このクラスが操作するビュー．
     */
    NoteClickHandler(SequenceModel *model, EventSelection *selection, NoteView *view);
    virtual ~NoteClickHandler();

    /**
     *  @brief ビューを交換します．すべての設定はリセットされます．
     */
    void setView(NoteView *view);

public slots:
    /**
     *  @brief 編集対象のモデルを変更します．
     */
    void setSequence(SequenceModel *model);
    /**
     *  @brief 選択範囲を表すクラスを変更します．
     */
    void setSelection(EventSelection *selection);
protected:
    // @Override
    virtual bool eventFilter(QObject *o, QEvent *e);
private:
    // Qt のイベントを受けるメソッド
    bool _mousePressed(QLabel *l, QMouseEvent *e);
    bool _mouseMoved(QLabel *l, QMouseEvent *e);
    bool _mouseReleased(QLabel *l, QMouseEvent *e);

    void _destroy();

    // 移動距離からイベント一個分を計算する関数
    vsq::Event _eventExtendedForward(const QPoint& diff, QLabel *l);
    vsq::Event _eventExtendedBackward(const QPoint &diff, QLabel *l);
    vsq::Event _eventMoved(const QPoint &diff, QLabel *l);
    void _selectNotes(QLabel *l , QMouseEvent *e);
    void _updateLabels(const QPoint &diff, vsq::Event (NoteClickHandler::*updateFunction)(const QPoint &diff, QLabel *l));
    void _updateNotes(const QPoint &diff, vsq::Event (NoteClickHandler::*updateFunction)(const QPoint &diff, QLabel *l));

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

    SequenceModel *_model;
    EventSelection *_selection;
    QHash<QLabel *, QPair<int, QRect> > _labelLocations;

    static vsq::Event (NoteClickHandler::* const _eventFunctions[])(const QPoint &, QLabel *);
};

#endif // NOTECLICKHANDLER_H
