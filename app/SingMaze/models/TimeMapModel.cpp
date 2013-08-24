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
