/*
 *
 *    ControlCurveSelection.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTROLCURVESELECTION_H
#define CONTROLCURVESELECTION_H

#include <QObject>
#include <QString>
#include <QList>

/**
 *  @brief 今何のコントロールを選択しているかを表すクラスです．
 */
class ControlCurveSelection : public QObject
{
    Q_OBJECT
public:
    explicit ControlCurveSelection(int maxPrevious, QObject *parent = 0);

    /**
     *  @brief 今現在選択されているコントロール名を変更します．
     */
    void changeMain(const QString &mainName);

    /** @brief 現在選択しているコントロール名 */
    QString mainName;
    /** @brief 以前選択していたコントロール名．後ろほど最近追加されたものが格納されている． */
    QList<QString> subNames;
    /** @brief 以前選択していたコントロールを何個覚えているべきか */
    int maxPrevious;
signals:
    void changeControlCurve(ControlCurveSelection &);
};

#endif // CONTROLCURVESELECTION_H
