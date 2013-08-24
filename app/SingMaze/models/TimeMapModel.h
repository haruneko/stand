/*
 *
 *    TimeMapModel.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef TIMEMAPMODEL_H
#define TIMEMAPMODEL_H

#include <QList>
#include <QPair>

/**
 *  @brief 声のモーフィング時の時間軸対応を表すクラスです.
 */
class TimeMapModel
{
public:
    bool append(const QPair<double, double> &val);

private:
    QList<QPair<double, double> > _correspondence;
};

#endif // TIMEMAPMODEL_H
