/*
 *
 *    TempoView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QLabel>
#include <QPainter>

#include "TempoView.h"

TempoView::TempoView(int divCount, int noteHeight, int beatWidth, const vsq::Sequence *sequence, QWidget *parent) :
    AbstractLabelView(divCount, noteHeight, beatWidth, sequence, parent)
{
    reset();
}

void TempoView::setLabels()
{
    const vsq::TempoList &tempos = sequence()->tempoList;
    for(int i = 0; i < tempos.size(); i++)
    {
        const vsq::Tempo &t = tempos.get(i);
        double tempo = (double)(60 * 1000000) / (double)t.tempo;
        QString text = QString::number(tempo);
        registerLabel(text, t.clock);
    }
    update();
}
