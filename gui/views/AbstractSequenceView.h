/*
 *
 *    AbstractSequenceView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef ABSTRACTSEQUENCEVIEW_H
#define ABSTRACTSEQUENCEVIEW_H

#include <QWidget>

namespace vsq
{
class Sequence;
}

/**
 *  @brief シーケンスを表示する基底クラス．
 */
class AbstractSequenceView : public QWidget
{
    Q_OBJECT
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] sequence 表示すべきシーケンス．
     *  @param [in] trackId 表示すべきトラック番号．
     *  @param [in] parent 親 Widget ．
     */
    explicit AbstractSequenceView(const vsq::Sequence *sequence, int trackId, QWidget *parent);

    /**
     *  @brief 今現在表示しているトラック番号を返します．
     */
    int trackId() const
    {
        return _trackId;
    }

    /**
     *  @brief  表示すべきシーケンスを変更します．
     *          与えられたシーケンスは view クラス内では変更できません．
     *  @param [in] sequence 変更後のシーケンス．
     */
    void setSequence(const vsq::Sequence *sequence)
    {
        _sequence = sequence;
        update();
    }

    /**
     *  @brief  現在表示しているシーケンスへのポインタを返します．
     */
    const vsq::Sequence *sequence() const
    {
        return _sequence;
    }

protected:
    virtual void paintEvent(QPaintEvent *e);

signals:
    
public slots:
    /**
     *  @brief データの変更通知を受け取るスロットです．与えられた tick 単位での範囲を通知で受け取ります．
     *  @param [in] tickBegin 開始 tick
     *  @param [in] tickEnd 終了 tick
     */
    virtual void dataChanged(int tickBegin, int tickEnd);

    /**
     *  @brief 該当する領域を描画します．
     *  @param [in] region 描画すべき領域．
     *  @param [in/out] painter 描画対象から得た QPainter クラスへのポインタ．
     */
    void paint(const QRegion &region, QPainter *painter);

    /**
     *  @brief 該当する矩形を描画します．
     *  @param [in] rect 描画すべき矩形．
     *  @param [in/out] painter 描画対象から得た QPainter クラスへのポインタ．
     */
    virtual void paint(const QRect &rect, QPainter *painter) = 0;

    /**
     *  @brief 表示すべきトラックが変更された際に通知を受け取るスロットです．
     */
    virtual void trackChanged(int id);

    /**
     *  @brief 四分音符の幅が変更された際に通知を受け取るスロットです．
     */
    virtual void beatWidthChanged(int w) = 0;

    /**
     *  @brief 音符の高さが変更された際に通知を受け取るスロットです．
     */
    virtual void noteHeightChanged(int h) = 0;
private:
    const vsq::Sequence *_sequence; //! @brief 現在表示しているシーケンス
    int _trackId;                   //! @brief 現在表示しているトラック番号

    QWidget *_parent;               //! @brief 親Widget
};

#endif // ABSTRACTSEQUENCEVIEW_H