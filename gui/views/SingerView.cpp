/*
 *
 *    SingerView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QHash>
#include <QLabel>

#include "../models/EventSelection.h"

#include "SingerView.h"

SingerView::SingerView(int trackId, int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent) :
    AbstractLabelView(divCount, noteHeight, beatWidth, model, parent)
{
    _trackId = trackId;
    reset();
}

void SingerView::setLabels()
{
    if(_trackId < 0 || sequence()->tracks()->size() <= _trackId)
    {
        return;
    }
    _labels.clear();
    const vsq::Track *track = sequence()->track(_trackId);
    vsq::EventListIndexIterator it = track->getIndexIterator(vsq::EventListIndexIteratorKind::SINGER);
    while(it.hasNext())
    {
        const vsq::Event *e = track->events()->get(it.next());
        QString text(e->singerHandle.ids.data());
        QLabel *l = registerLabel(text, e->clock);
        _labels.insert(e->id, l);
    }
}

void SingerView::trackChanged(int id)
{
    if(id == _trackId)
    {
        return;
    }
    _trackId = id;
    reset();
}

void SingerView::_setLabelColor(EventSelection *s, const QColor &c)
{
    if(_trackId != s->trackId())
    {
        return;
    }
    foreach(int i, s->ids())
    {
        if(_labels.contains(i))
        {
            QLabel *l = _labels[i];
            QPalette p(l->palette());
            p.setColor(l->backgroundRole(), c);
            l->setPalette(p);
        }
    }
}

void SingerView::changeSelection(EventSelection *current, EventSelection *previous)
{
    _setLabelColor(previous, labelColor);
    _setLabelColor(current, selectedColor);
}
