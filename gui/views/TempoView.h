/*
 *
 *    TempoView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef TEMPOVIEW_H
#define TEMPOVIEW_H

#include "AbstractLabelView.h"

/**
 *  @brief テンポを表示するクラス．
 */
class TempoView : public AbstractLabelView
{
public:
    explicit TempoView(int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent);

protected:
    // @Override
    virtual void setLabels();
};

#endif // TEMPOVIEW_H
