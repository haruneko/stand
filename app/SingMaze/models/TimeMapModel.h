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
 *  @brief Represents correspondence between voice A and voice B.
 *         `TimeMapModel` contains ordered pair of time correspondence.
 *         It supplies the correspondent time of the specific time
 *         through the function `correspondenceAt(msec)`.
 *  @author HAL@shurabaP
 */
class TimeMapModel
{
public:
    /**
     *  @brief Appends the correspondence between the specific times.
     *  @param [in] val `val` contains the time of voice A as `val.first`
     *                  and the one of voice B as `val.second`
     *  @return Whether `append` succeeds or not.
     *          `append` fails when the line between `first` and `second`
     *          crosses any lines that the pair in this class makes.
     */
    bool append(const QPair<double, double> &val);

    /**
     *  @brief Removes the correspondence.
     *         This method will remove if this class has exactly the same data as `val`,
     *         otherwise do nothing.
     *  @param [in] val The data to be removed.
     */
    void remove(const QPair<double, double> &val);

    /**
     *  @brief Calculates the coresspondent time in voice A and voice B.
     *  @param [in] ratio must be in the range [-1.0, 1.0].
     *                    The larger, the superior voice A is.
     *  @return Correspondence times of voice A and voice B.
     */
    QPair<double, double> correspondenceAt(double ms, double ratio);
private:
    bool _isLeft(double ms, double ratio, const QPair<double, double> &line);
    bool _isRight(double ms, double ratio, const QPair<double, double> &line);
    double _msAt(double ratio, const QPair<double, double> &line);
    QPair<double, double> _correspondenceAt(double ms, double ratio, const QPair<double, double> &left, const QPair<double, double> &right);
    QList<QPair<double, double> > _correspondence;
};

#endif // TIMEMAPMODEL_H
