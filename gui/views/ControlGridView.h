/*
 *
 *    ControlGridView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTROLGRIDVIEW_H
#define CONTROLGRIDVIEW_H

#include "AbstractGridView.h"

/**
 *  @brief コントロールカーブを表示する際のグリッドを描画します．
 */
class ControlGridView : public AbstractGridView
{
    Q_OBJECT
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] divCount 四分音符を何回分割するか．
     *  @param [in] trackId 表示すべきトラック番号．
     *  @param [in] beatWidth 一拍分の横幅．
     *  @param [in] sequence 表示すべきシーケンス．
     *  @param [in] parent 親 Widget ．
     */
    explicit ControlGridView(int divCount, int beatWidth, const vsq::Sequence *sequence, int trackId, QWidget *parent);

protected:
    // @Override
    void drawAssistLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    void drawBarLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    void drawBeatLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    void paintAfter(const QRect &rect, QPainter *painter);
};

#endif // CONTROLGRIDVIEW_H
