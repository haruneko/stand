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

/**
 *  @brief シーケンスを表示する基底クラス．
 */
class AbstractSequenceView : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractSequenceView(int trackId, int beatWidth, int noteHeight, QWidget *parent = 0);

    int beatWidth() const
    {
        return _beatWidth;
    }

    int noteHegiht() const
    {
        return _noteHeight;
    }

    /**
     *  @brief 今現在表示しているトラック番号を返します．
     */
    int trackId() const
    {
        return _trackId;
    }
signals:
    
public slots:
    /**
     *  @brief データの変更通知を受け取るスロットです．与えられた tick 単位での範囲を通知で受け取ります．
     *  @param [in] tickBegin 開始 tick
     *  @param [in] tickEnd 終了 tick
     */
    virtual void dataChanged(int tickBegin, int tickEnd);

    /**
     *  @brief 表示すべきトラックが変更された際に通知を受け取るスロットです．
     */
    virtual void trackChanged(int id);

    virtual void beatWidthChanged(int w);
    virtual void noteHeightChanged(int h);
private:
    int _trackId;
    int _beatWidth;
    int _noteHeight;
};

#endif // ABSTRACTSEQUENCEVIEW_H
