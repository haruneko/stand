/*
 *
 *    BeatView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/22
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef BEATVIEW_H
#define BEATVIEW_H

#include "AbstractLabelView.h"

class QLabel;

/**
 *  @brief 拍子情報を表示するクラス．
 */
class BeatView : public AbstractLabelView
{
    Q_OBJECT
public:
    explicit BeatView(int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent);

protected:
    // @Override
    virtual void setLabels();
private:
};

#endif // BEATVIEW_H
