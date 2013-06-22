/*
 *
 *    ControlCurveView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTROLCURVEVIEW_H
#define CONTROLCURVEVIEW_H

#include "AbstractGridView.h"

namespace vsq
{
class BPList;
}

/**
 *  @brief コントロールカーブを表示するクラスです．
 */
class ControlCurveView : public AbstractGridView
{
    Q_OBJECT
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] controlName 表示すべきコントロールカーブの名称．
     *  @param [in] divCount 補助線の間隔．
     *  @param [in] beatWidth 一拍分の横幅．
     *  @param [in] sequence 表示すべきシーケンス．
     *  @param [in] parent 親 Widget ．
     */
    explicit ControlCurveView(
            int trackId,
            const std::string &controlName,
            int divCount,
            int beatWidth,
            const vsq::Sequence *sequence,
            QWidget *parent
            );

    /** @brief このコントロールの背景色 */
    QColor backgroundColor;
    /** @brief このコントロールの描画色 */
    QColor color;

    /**
     *  @brief  描画すべきコントロールカーブの名前を指定します．
     *          見つからない名前を指定した場合，描画を行わなくなります．
     */
    void setControlName(const std::string &controlName);

protected:
    // @Override
    void paintEvent(QPaintEvent *e);

public slots:
    // @Override
    void paint(const QRect &rect, QPainter *painter);
    // @Override
    void trackChanged(int id);

private:
    std::string _controlName;       //! @brief 現在保持しているコントロールカーブの名前
    const vsq::BPList *_control;    //! @brief 現在保持しているコントロールカーブ

    int _trackId;                   //! @brief 表示しているトラック番号
};

#endif // CONTROLCURVEVIEW_H
