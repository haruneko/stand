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

#include "AbstractControlView.h"

/**
 *  @brief コントロールカーブを表示する際のグリッドを描画します．
 */
class ControlGridView : public AbstractControlView
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

    /**
     *  @brief  グリッドの描画色を設定します．
     *  @param [in] color 表示色．
     */
    void setColor(const QColor &color);

    /**
     *  @brief  現在のグリッドの描画色を返します．
     */
    const QColor &color() const
    {
        return _color;
    }

    /**
     *  @brief  グリッドの細かさを指定します．
     *  @param [in] divCount 四分音符を何回分割するか．
     */
    void setDivCount(int divCount);

public slots:
    void paint(const QRect &rect, QPainter *painter);
private:
    void _drawAssistLine(vsq::tick_t tick, QPainter *painter);
    void _drawBarLine(vsq::tick_t tick, QPainter *painter);

    int _divCount;      //! @brief 四分音符を何回分割するか．
    QColor _color;      //! @brief 表示色
    QColor _weakColor;  //! @brief 弱拍の表示色
};

#endif // CONTROLGRIDVIEW_H
