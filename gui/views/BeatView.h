/*
 *
 *    BeatView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/22
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef BEATVIEW_H
#define BEATVIEW_H

#include <QSet>
#include "AbstractGridView.h"

class QLabel;

/**
 *  @brief 拍子情報を表示するクラス．
 */
class BeatView : public AbstractGridView
{
    Q_OBJECT
public:
    explicit BeatView(int divCount, int noteHeight, int beatWidth, const vsq::Sequence *sequence, QWidget *parent);

    /** @brief 補助線の色 */
    QColor barLineColor;
    /** @brief 背景色 */
    QColor backgroundColor;
    /** @brief 文字色 */
    QColor fontColor;
public slots:
    // @Override
    void noteHeightChanged(int h);

protected:
    // @Override
    virtual void drawAssistLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void drawBarLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void drawBeatLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    virtual void paintBefore(const QRect &rect, QPainter *painter);
private:
    void _destroy();
    void _reset();
    /** @brief 拍子情報を表示するためのラベル */
    QSet<QLabel *> _beatLabels;

    int _noteHeight;
};

#endif // BEATVIEW_H
