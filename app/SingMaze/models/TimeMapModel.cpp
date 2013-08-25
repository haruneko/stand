/*
 *
 *    TimeMapModel.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "TimeMapModel.h"

bool TimeMapModel::append(const QPair<double, double> &val)
{
    for(int i = 0; i < _correspondence.length() - 1; i++)
    {
        if(val.first < _correspondence[i + 1].first)
        {
            if(val.second >= _correspondence[i + 1].second)
            {
                return false;
            }
            _correspondence.insert(i, val);
            return true;
        }
    }
    _correspondence.append(val);
    return true;
}

void TimeMapModel::remove(const QPair<double, double> &val)
{
    _correspondence.removeOne(val);
}

QPair<double, double> TimeMapModel::correspondenceAt(double ms, double ratio) const
{
    if(_correspondence.empty())
    {
        return QPair<double, double>(ms, ms);
    }
    for(int i = 1; i < _correspondence.length(); i++)
    {
        if(_isRight(ms, ratio, _correspondence.at(i - 1)) && _isLeft(ms, ratio, _correspondence.at(i)))
        {
            return _correspondenceAt(ms, ratio, _correspondence.at(i - 1), _correspondence.at(i));
        }
    }
    return _correspondenceAt(ms, ratio, _correspondence.last(), _correspondence.last());
}

const QList<QPair<double, double> > &TimeMapModel::map() const
{
    return _correspondence;
}

bool TimeMapModel::_isLeft(double ms, double ratio, const QPair<double, double> &line)
{
    return !_isRight(ms, ratio, line);
}

bool TimeMapModel::_isRight(double ms, double ratio, const QPair<double, double> &line)
{
    return (_msAt(ratio, line) < ms);
}

double TimeMapModel::_msAt(double ratio, const QPair<double, double> &line)
{
    double r = ratio / 2 + 0.5;
    return line.first * r + line.second * (1 - r);
}

QPair<double, double> TimeMapModel::_correspondenceAt(double ms, double ratio, const QPair<double, double> &left, const QPair<double, double> &right)
{
    double p1 = _msAt(ratio, left);
    double p2 = _msAt(ratio, right);
    double r = (ms - p1) / (p2 - p1);
    if(p1 == p2)
    {
        double diff = ms - p1;
        return QPair<double, double>(left.first + diff, left.second + diff);
    }
    return QPair<double, double>(left.first * (1 - r) + right.first * r, left.second * (1 - r) + right.second * r);
}
