/*
 *
 *    NoteView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include "AbstractGridView.h"

#include "PianoPainter.h"

/**
 *  @brief シーケンスからピアノロールを表示するクラス．
 */
class NoteView : public AbstractGridView
{
public:
    NoteView(int divCount, int noteHeight, int beatWidth, const vsq::Sequence *sequence, int trackId, QWidget *parent = 0);
    void setNoteHeight(int noteHeight);

    /**
     *  @brief 小節線の描画色．
     */
    QColor barLineColor;

    /**
     *  @brief 補助線の描画色．
     */
    QColor assistLineColor;

    /**
     *  @brief 音符の色
     */
    QColor noteColor;
    /**
     *  @brief 音符の境界線色
     */
    QColor noteBorderColor;
    /**
     *  @brief 音符の歌詞の色
     */
    QColor noteTextColor;
    /**
     *  @brief ノート番号に対応する y 座標を返します．ビュー上での位置はピアノロール上で上辺に対応します．
     */
    int yAt(int note);

    int noteHeight() const
    {
        return _noteHeight;
    }
public slots:
    // @Override
    virtual void noteHeightChanged(int h);

protected:
    // @Override
    virtual void paintBefore(const QRect &rect, QPainter *painter);
    // @Override
    virtual void paintAfter(const QRect &rect, QPainter *painter);
    // @Override
    virtual void drawBarLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void drawAssistLine(vsq::tick_t tick, QPainter *painter);
private:
    /**
     *  @brief シーケンス上の音符を描画します．
     *  @todo 選択した状態で色を変える．
     */
    void _drawNotes(const QRect &rect, QPainter *painter);
    void _drawOneNote(const vsq::Event *event, QPainter *painter);

    int _noteHeight;
    PianoPainter high;
    PianoPainter middle;
    PianoPainter low;
};

#endif // NOTEVIEW_H
