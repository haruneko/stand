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

#include <QString>
#include <QList>

/**
 *  @brief 今何のコントロールを選択しているかを表すクラスです．
 */
class ControlCurveSelection
{
public:
    /** @brief 現在選択しているコントロール名 */
    QString mainName;
    /** @brief 以前選択していたコントロール名 */
    QList<QString> subNames;
};

#endif // CONTROLCURVESELECTION_H
