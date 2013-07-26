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

#include <QLabel>
#include "AbstractGridView.h"

#include "PianoPainter.h"

class EventSelection;

/**
 *  @brief シーケンスからピアノロールを表示するクラス．
 */
class NoteView : public AbstractGridView
{
public:
    explicit NoteView(
            int trackId,
            int divCount,
            int noteHeight,
            int beatWidth,
            SequenceModel *model,
            QWidget *parent = 0
            );

    virtual ~NoteView();
    void setNoteHeight(int noteHeight);

    QColor barLineColor;        //! @brief 小節線の描画色
    QColor beatLineColor;       //! @brief 拍ごとの線の描画色
    QColor assistLineColor;     //! @brief 補助線の描画色

    QColor noteColor;           //! @brief 音符の描画色
    QColor noteTextColor;       //! @brief 音符のテキスト描画色
    QColor noteInvalidColor;    //! @brief 音符の情報が不適切な際の描画色
    QColor noteSelectedColor;   //! @brief 音符の選択時の描画色

    /**
     *  @brief ノート番号に対応する y 座標を返します．ビュー上での位置はピアノロール上で上辺に対応します．
     */
    int yAt(int note);


    /**
     *  @brief  該当する y 座標での音高を返します.
     */
    int noteAt(int y) const;

    int noteHeight() const
    {
        return _noteHeight;
    }

    /**
     *  @brief このクラスが保持している音符のラベルを返します．
     */
    QList<QLabel *> labels();
    /**
     *  @brief このクラスが保持している音符のラベルをトラック番号を指定して ID つきで返します.
     */
    QList<QPair<int, QLabel *> > labels(int trackId);
    /**
     *  @brief このクラスが保持している音符のラベルをトラック番号と ID を指定して ID つきで返します.
     */
    QList<QPair<int, QLabel *> > labels(int trackId, const QList<int> &ids);
public slots:
    // @Override
    virtual void trackChanged(int id);
    // @Override
    virtual void beatWidthChanged(int w);
    // @Override
    virtual void noteHeightChanged(int h);
    /**
     *  @brief 音符の選択が変更されたときのシグナルを受け取るスロットです．
     *  @param[in] current 現在新たに選択されている音符などのイベント．
     *  @param[in] previous 直前まで選択されていた音符などのイベント．
     */
    void changeSelection(EventSelection *current, EventSelection *previous);

protected:
    // @Override
    virtual void paintBefore(const QRect &rect, QPainter *painter);
    // @Override
    virtual void paintAfter(const QRect &rect, QPainter *painter);
    // @Override
    virtual void drawBarLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void drawBeatLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void drawAssistLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void modelChanged();
private:
    void _destroy();
    void _reset();
    void _setLabelColor(EventSelection *s, const QColor& c);
    QLabel *_labelFromEvent(const vsq::Event *e);

    int _noteHeight;
    int _trackId;
    PianoPainter high;
    PianoPainter middle;
    PianoPainter low;
    QVector<QHash<int, QLabel *> > _noteLabels;
};

#endif // NOTEVIEW_H
