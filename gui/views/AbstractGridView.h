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

#include "AbstractSequenceView.h"

/**
 *  @brief グリッド表示のあるクラスの基底クラスです．
 */
class AbstractGridView : public AbstractSequenceView
{
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] divCount 四分音符を何回分割するか．
     *  @param [in] beatWidth 一拍分の横幅．
     *  @param [in] sequence 表示すべきシーケンス．
     *  @param [in] parent 親 Widget ．
     */
    explicit AbstractGridView(int divCount, int beatWidth, SequenceModel *model, QWidget *parent);

    /** グリッド線の色 */
    QColor gridLineColor;

    /**
     *  @brief  グリッドの細かさを指定します．
     *  @param [in] divCount 四分音符を何回分割するか．
     */
    void setDivCount(int divCount);

    /**
     *  @brief 該当する x 座標での tick 時刻を返します．
     *          このメソッドは premeasure を考慮した値を返します．
     */
    vsq::tick_t tickAt(int x) const;

    /**
     *  @brief  該当する tick 時刻での x 座標を返します．
     *          このメソッドは premeasure を考慮した値を返します．
     */
    int xAt(vsq::tick_t tick) const;

    /**
     *  @brief 現在の一拍分の横幅を返します．
     */
    int beatWidth() const
    {
        return _beatWidth;
    }
public slots:
    // @Override
    void paint(const QRect &rect, QPainter *painter);
    // @Override
    virtual void beatWidthChanged(int w);

    /**
     *  @brief 補助線の分割数への変更通知を受け取ります．
     *  @param [in] divCount 四分音符の分割数．
     */
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
    int _beatWidth;     //! @brief 一拍分の横幅
};

#endif // ABSTRACTGRIDVIEW_H
