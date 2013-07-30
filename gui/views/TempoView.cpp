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

#include "../models/SequenceModel.h"
#include "TempoView.h"

TempoView::TempoView(int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent) :
    AbstractLabelView(divCount, noteHeight, beatWidth, model, parent)
{
    reset();
}

void TempoView::setLabels()
{
    const vsq::TempoList &tempos = model()->sequence()->tempoList;
    for(int i = 0; i < tempos.size(); i++)
    {
        const vsq::Tempo &t = tempos.get(i);
        double tempo = (double)(60 * 1000000) / (double)t.tempo;
        QString text = QString::number(tempo);
        registerLabel(text, t.clock);
    }
    update();
}
