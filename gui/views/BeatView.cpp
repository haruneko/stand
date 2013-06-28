/*
 *
 *    BeatView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/22
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QLabel>
#include <QPainter>

#include "BeatView.h"

BeatView::BeatView(int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent) :
    AbstractLabelView(divCount, noteHeight, beatWidth, model, parent)
{
    reset();
}

void BeatView::setLabels()
{
    const vsq::TimesigList &timesigs = sequence()->timesigList;
    for(int i = 0; i < timesigs.size(); i++)
    {
        const vsq::Timesig &t = timesigs.get(i);
        QString text = QString::number(t.numerator) + "/" + QString::number(t.denominator);
        registerLabel(text, t.getClock());
    }
}
