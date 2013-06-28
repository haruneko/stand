/*
 *
 *    SingerView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SINGERVIEW_H
#define SINGERVIEW_H

#include "AbstractLabelView.h"

/**
 *  @brief 歌手情報を表示するクラスです．
 */
class SingerView : public AbstractLabelView
{
public:
    explicit SingerView(int trackId, int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent);
protected:
    // @Override
    void trackChanged(int id);
    // @Override
    void setLabels();
private:
    int _trackId;
};

#endif // SINGERVIEW_H
