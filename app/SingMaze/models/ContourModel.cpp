/*
 *
 *    ContourModel.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "dsp/Envelope.h"

#include "ContourModel.h"

ContourModel::ContourModel(Envelope *e, QObject *parent) :
    QObject(parent)
{
}

void ContourModel::setData(int index, const QList<double> &data)
{
    index = qMax(0, index);
    int j = index;
    for(int i = 0; i < data.size(), j < _contour->size(); i++ ,j++)
    {
        (*_contour)[j] = data[i];
    }
    emit dataChanged(index, j);
}

const Envelope *ContourModel::data() const
{
    return _contour;
}
