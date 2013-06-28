/*
 *
 *    AbstractLabelView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef ABSTRACTLABELVIEW_H
#define ABSTRACTLABELVIEW_H

#include <QSet>

#include "AbstractGridView.h"

class QLabel;

/**
 *  @brief ラベルを使ったビューの基底クラス．
 */
class AbstractLabelView : public AbstractGridView
{
    Q_OBJECT
public:
    explicit AbstractLabelView(int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent);
    virtual ~AbstractLabelView();

    /** @brief 補助線の色 */
    QColor barLineColor;
    /** @brief 背景色 */
    QColor backgroundColor;
    /** @brief 文字色 */
    QColor fontColor;
public slots:
    // @Override
    void beatWidthChanged(int w);
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
    // @Override
    void sequenceChanged();
    /**
     *  @brief  このメソッド内でラベルを登録して下さい．
     */
    virtual void setLabels() = 0;

    /**
     *  @brief  指定した時刻のラベルを作成し，管理用のセットに登録します．
     *  @param [in] text 表示するテキスト
     *  @param [in] tick 時刻
     *  @return 登録されたラベル．さらに詳しい設定をしたい場合戻り値を使って編集できます．
     */
    QLabel *registerLabel(const QString &text, vsq::tick_t tick);

    /** @brief 情報を表示するためのラベル */
    QSet<QLabel *> labels;

    /** @brief ラベルを全て削除します． */
    void clear();

    /** @brief ラベルを現在の情報から設定します． */
    void reset();
private:
    int _noteHeight;
};

#endif // ABSTRACTLABELVIEW_H
