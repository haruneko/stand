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

ContourModel::ContourModel(QObject *parent) :
    QObject(parent)
{
    _contour = NULL;
}

ContourModel::~ContourModel()
{
    delete _contour;
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

void ContourModel::setEnvelope(int length, double msFramePeriod)
{
    delete _contour;
    double *data = new double[length];
    for(int i = 0; i < length; i++)
    {
        data[i] = 0.0;
    }
    _contour = new Envelope(data, length, msFramePeriod, true);
}

const Envelope *ContourModel::contour() const
{
    return _contour;
}
