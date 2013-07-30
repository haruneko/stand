/*
 *
 *    TrackSelectionView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>

#include <Track.hpp>

#include "../models/SequenceModel.h"
#include "TrackSelectionView.h"

TrackSelectionView::TrackSelectionView(int noteHeight, SequenceModel *model, QWidget *parent) :
    AbstractSequenceView(model, parent),
    foregroundColor(128, 192, 255),
    backgroundColor(64, 64, 64)
{
    _noteHeight = noteHeight;
    _currentTrackId = 0;
    setFixedHeight(noteHeight);
    modelChanged();
}

TrackSelectionView::~TrackSelectionView()
{
    _destroy();
}

void TrackSelectionView::_destroy()
{
    qDeleteAll(_trackNames);
    _trackNames.clear();
}

void TrackSelectionView::paint(const QRect &rect, QPainter *painter)
{
    painter->fillRect(rect, backgroundColor);
}

void TrackSelectionView::beatWidthChanged(int /*w*/)
{
}

void TrackSelectionView::noteHeightChanged(int h)
{
    if(h == _noteHeight)
    {
        return;
    }
    _noteHeight = h;
    setFixedHeight(_noteHeight);
    foreach(QLabel *l, _trackNames)
    {
        l->setGeometry(l->x(), l->y(), l->width(), h);
    }

    update();
}

void TrackSelectionView::trackChanged(int id)
{
    if(id == _currentTrackId)
    {
        return;
    }
    // 今選択されているものを非選択色に
    if(0 <= _currentTrackId && _currentTrackId < _trackNames.size())
    {
        QLabel *l = _trackNames[_currentTrackId];
        QPalette palette(l->palette());
        palette.setColor(l->backgroundRole(), backgroundColor);
        l->setPalette(palette);
        l->update();
    }
    // 選択されたものを選択色に
    if(0 <= id && id < _trackNames.size())
    {
        QLabel *l = _trackNames[id];
        QPalette palette(l->palette());
        QColor c(foregroundColor);
        c.setAlpha(64);
        palette.setColor(l->backgroundRole(), c);
        l->setPalette(palette);
        l->update();
    }
}

void TrackSelectionView::modelChanged()
{
    _destroy();
    const std::vector<vsq::Track> *tracks = model()->sequence()->tracks();
    for(int i = 0; i < tracks->size(); i++)
    {
        QLabel *l = new QLabel(tr((*tracks)[i].getName().data()), this);
        QPalette p(l->palette());
        p.setColor(l->foregroundRole(), foregroundColor);
        p.setColor(l->backgroundRole(), backgroundColor);
        l->setPalette(p);
        l->setAutoFillBackground(true);
        l->setFrameStyle(QFrame::Box);
        l->setLineWidth(1);
        l->setGeometry(i * 64, 0, 64, _noteHeight);
        _trackNames.append(l);
    }
    _currentTrackId = -1;
    trackChanged(0);
}
