/*
 *
 *    AbstractGridView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef ABSTRACTGRIDVIEW_H
#define ABSTRACTGRIDVIEW_H

#include "AbstractControlView.h"

/**
 *  @brief グリッド表示のあるクラスの基底クラスです．
 */
class AbstractGridView : public AbstractControlView
{
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] divCount 四分音符を何回分割するか．
     *  @param [in] trackId 表示すべきトラック番号．
     *  @param [in] beatWidth 一拍分の横幅．
     *  @param [in] sequence 表示すべきシーケンス．
     *  @param [in] parent 親 Widget ．
     */
    explicit AbstractGridView(int divCount, int beatWidth, const vsq::Sequence *sequence, int trackId, QWidget *parent);

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
    // @Override
    void paint(const QRect &rect, QPainter *painter);
    virtual void divCountChanged(int divCount);
protected:
    /**
     *  @brief  補助線を描画します．
     *  @param [in] tick 描画 tick 位置
     */
    virtual void drawAssistLine(vsq::tick_t tick, QPainter *painter) = 0;
    /**
     *  @brief  小節線を描画します．
     *  @param [in] tick 描画 tick 位置
     */
    virtual void drawBarLine(vsq::tick_t tick, QPainter *painter) = 0;
    /**
     *  @brief  拍の開始線を描画します．
     */
    virtual void drawBeatLine(vsq::tick_t tick, QPainter *painter) = 0;
    /**
     *  @brief  グリッド線の描画前に呼び出されます．
     */
    virtual void paintBefore(const QRect &rect, QPainter *painter){ }
    /**
     *  @brief  グリッド線の描画後に呼び出されます．
     */
    virtual void paintAfter(const QRect &rect, QPainter *painter){ }

private:
    int _divCount;      //! @brief 四分音符を何回分割するか．
    QColor _color;      //! @brief 表示色
};

#endif // ABSTRACTGRIDVIEW_H
