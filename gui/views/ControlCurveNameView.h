/*
 *
 *    ControlCurveNameView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTROLCURVENAMEVIEW_H
#define CONTROLCURVENAMEVIEW_H

#include <QHash>
#include <QWidget>

class QLabel;
class ControlCurveSelection;

/**
 *  @brief 現在編集中のコントローラが何か表示します．
 */
class ControlCurveNameView : public QWidget
{
    Q_OBJECT
public:
    explicit ControlCurveNameView(const QList<QString> &labelNames, int noteHeight, QWidget *parent = 0);
    virtual ~ControlCurveNameView();

    /**
     *  @brief 表示しているラベルをリストにして返します．
     */
    QList<QLabel *> labels();
    QList<const QLabel *> labels() const;

    /** @brief 線とフォント色 */
    QColor foregroundColor;
    /** @brief 背景色 */
    QColor backgroundColor;
public slots:
    /**
     *  @brief コントロールトラックの選択が変更された際に呼ばれるスロットです．
     */
    void selectionChanged(ControlCurveSelection &selection);
    /**
     *  @brief 半音分の高さが変化した際に呼ばれるスロットです．
     */
    void noteHeightChanged(int h);
    /**
     *  @brief 表示すべきコントロールのキー名に変更があった際の通知を受け取ります．
     *  @param [in] kinds
     */
    void controlKindChanged(QList<QString> &kinds);

protected:
    // @Override
    virtual void paintEvent(QPaintEvent *e);

private:
    void _destroy();
    QLabel *_registerLabel(const QString &name);

    QHash<QString, QLabel *> _labels;
    int _noteHeight;
};

#endif // CONTROLCURVENAMEVIEW_H
