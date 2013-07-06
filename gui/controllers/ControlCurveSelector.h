/*
 *
 *    ControlCurveSelector.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTROLCURVESELECTOR_H
#define CONTROLCURVESELECTOR_H

#include <QObject>

class ControlCurveNameView;
class ControlCurveSelection;

/**
 *  @brief コントロールカーブを選ぶクラスです．
 */
class ControlCurveSelector : public QObject
{
    Q_OBJECT
public:
    explicit ControlCurveSelector(ControlCurveSelection *selection, ControlCurveNameView *view = 0);
    void setView(ControlCurveNameView *view);
protected:
    virtual bool eventFilter(QObject *o, QEvent *e);
private:
    void _destroy();
    ControlCurveSelection *_selection;
    ControlCurveNameView *_view;
};

#endif // CONTROLCURVESELECTOR_H
