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

#include <QHash>
#include "AbstractGridView.h"

namespace vsq
{
class BPList;
}

class AbstractControlPainter;
class ControlCurveSelection;

/**
 *  @brief コントロールカーブを表示するクラスです．
 */
class ControlCurveView : public AbstractGridView
{
    Q_OBJECT
public:
    /**
     *  @brief 与えられた値で初期化します．
     *  @param [in] names <表示名，コントロール名>の連想配列．
     *  @param [in] divCount 補助線の間隔．
     *  @param [in] beatWidth 一拍分の横幅．
     *  @param [in] sequence 表示すべきシーケンス．
     *  @param [in] parent 親 Widget ．
     */
    explicit ControlCurveView(
            const QHash<QString, std::string> &labels,
            int trackId,
            int divCount,
            int beatWidth,
            SequenceModel *model,
            QWidget *parent
            );
    virtual ~ControlCurveView();

    /** 背景色 */
    QColor backgroundColor;
    /** 編集中のコントロールの色 */
    QColor controlColor;
    /** 少し前に表示していたコントロールの色 */
    QColor controlSubColor;

public slots:
    // @Override
    void trackChanged(int id);
    /**
     *  @brief コントロールトラックの選択が変更された際に呼ばれるスロットです．
     */
    void controlCurveSelectionChanged(ControlCurveSelection &selection);
    // @Override
    void noteHeightChanged(int /*h*/){ }

protected:
    // @Override
    void sequenceChanged();
    // @Override
    void paintBefore(const QRect &rect, QPainter *painter);
    // @Override
    void drawAssistLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    void drawBarLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    void drawBeatLine(vsq::tick_t tick, QPainter *painter);
    // @Override
    void paintAfter(const QRect &rect, QPainter *painter);

private:
    void _destroy();
    void _reset();
    QList<AbstractControlPainter *> _shownPainters;
    QHash<QString, AbstractControlPainter *> _painters;
    QHash<QString, std::string> _controlNames;
    int _trackId;                   //! @brief 表示しているトラック番号
};

#endif // CONTROLCURVEVIEW_H
