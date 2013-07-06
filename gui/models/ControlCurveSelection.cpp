/*
 *
 *    ControlCurveSelection.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "ControlCurveSelection.h"

ControlCurveSelection::ControlCurveSelection(int maxPrevious, QObject *parent) :
    QObject(parent)
{
    this->maxPrevious = maxPrevious;
}

void ControlCurveSelection::changeMain(const QString &mainName)
{
    if(this->mainName == mainName)
    {
        return;
    }
    subNames.append(this->mainName);
    this->mainName = mainName;
    // 個数超過分を排除
    while(subNames.size() > maxPrevious && !subNames.empty())
    {
        subNames.removeFirst();
    }
    emit changeControlCurve(*this);
}
