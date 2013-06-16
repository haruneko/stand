/*
 *
 *    AbstractControlView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef ABSTRACTCONTROLVIEW_H
#define ABSTRACTCONTROLVIEW_H

#include <Sequence.hpp>
#include "AbstractSequenceView.h"

/**
 *  @brief コントロールトラックに表示するクラスの基底クラス．
 */
class AbstractControlView : public AbstractSequenceView
{
    Q_OBJECT
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] trackId 表示すべきトラック番号．
     *  @param [in] beatWidth 一拍分の横幅．
     *  @param [in] sequence 表示すべきシーケンス．
     *  @param [in] parent 親 Widget ．
     */
    explicit AbstractControlView(
            int beatWidth,
            const vsq::Sequence *sequence,
            int trackId,
            QWidget *parent
            );

    /**
     *  @brief 該当する x 座標での tick 時刻を返します．
     */
    vsq::tick_t tickAt(int x) const;

    /**
     *  @brief 該当する tick 時刻での x 座標を返します．
     */
    int xAt(vsq::tick_t tick) const;
public slots:
    // @Override
    void dataChanged(int tickBegin, int tickEnd);
    // @Override
    virtual void beatWidthChanged(int w);
    // @Override
    virtual void noteHeightChanged(int h);

    virtual void paint(const QRect &rect, QPainter *painter) = 0;

private:
    int _beatWidth;
};

#endif // ABSTRACTCONTROLVIEW_H
