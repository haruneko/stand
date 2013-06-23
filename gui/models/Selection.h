/*
 *
 *    Selection.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/22
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SELECTION_H
#define SELECTION_H

#include <QList>

/**
 *  @brief  シーケンスの選択範囲を表すクラスです．
 */
class Selection
{
public:
    enum Type
    {
        None = -1,
        Id,
        Range
    };

    Type type;
    QList<int> ids;
    int trackId;
    int begin;
    int end;
};

#endif // SELECTION_H
