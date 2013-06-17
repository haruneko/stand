/*
 *
 *    NoteView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>

#include "NoteView.h"

NoteView::NoteView(int divCount, int noteHeight, int beatWidth, const vsq::Sequence *sequence, int trackId, QWidget *parent) :
    AbstractGridView(divCount, beatWidth, sequence, trackId, parent),
    low(0, 32, QColor(192, 192, 192), QColor(128, 128, 128), QColor(64, 64, 64)),
    middle(33, 72, QColor(255, 255, 255), QColor(224, 224, 255), QColor(64, 64, 64)),
    high(73, 128, QColor(192, 192, 192), QColor(128, 128, 128), QColor(64, 64, 64))
{
    _noteHeight = 0;
    setNoteHeight(noteHeight);
    barLineColor = Qt::black;
    assistLineColor = Qt::darkGray;
    noteColor = QColor(192, 192, 255);
    noteBorderColor = QColor(64, 64, 128);
}

int NoteView::yAt(int note)
{
    return (127 - note) * _noteHeight;
}

void NoteView::setNoteHeight(int noteHeight)
{
    if(noteHeight == _noteHeight)
    {
        return;
    }
    _noteHeight = noteHeight;
    setFixedHeight(noteHeight * 128);
    update();
}

void NoteView::noteHeightChanged(int h)
{
    setNoteHeight(h);
}

void NoteView::paintBefore(const QRect &rect, QPainter *painter)
{
    // ピアノロールの部分を書く
    high.paint(_noteHeight, rect, painter);
    middle.paint(_noteHeight, rect, painter);
    low.paint(_noteHeight, rect, painter);
}

void NoteView::paintAfter(const QRect &rect, QPainter *painter)
{
    _drawNotes(rect, painter);
}

void NoteView::drawAssistLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(assistLineColor);
    painter->drawLine(x, 0, x, height());
}

void NoteView::drawBarLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(barLineColor);
    painter->drawLine(x, 0, x, height());
}

void NoteView::_drawNotes(const QRect &rect, QPainter *painter)
{
    const vsq::Track *track = sequence()->track(trackId());
    if(!track)
    {
        return;
    }

    vsq::EventListIndexIterator it = track->getIndexIterator(vsq::EventListIndexIteratorKind::NOTE);
    if(!it.hasNext())
    {
        return;
    }

    vsq::tick_t begin = tickAt(rect.left());
    vsq::tick_t end = tickAt(rect.right());
    QFont old(painter->font());
    QFont font(old);
    font.setPixelSize(_noteHeight - 2);
    painter->setFont(font);
    for(int index = it.next(); it.hasNext(); index = it.next())
    {
        const vsq::Event *event = track->events()->get(index);
        vsq::tick_t eventEnd = event->clock + event->getLength();
        // 範囲外（前方）
        if(begin < eventEnd)
        {
            continue;
        }
        // 範囲外（後方）
        if(end < event->clock)
        {
            break;
        }
        _drawOneNote(event, painter);
    }
    painter->setFont(old);
}

void NoteView::_drawOneNote(const vsq::Event *event, QPainter *painter)
{
    int x = xAt(event->clock);
    int y = yAt(event->note);
    int w = xAt(event->getLength());

    const vsq::Lyric lyric = event->lyricHandle.getLyricAt(0);
    std::string text = lyric.phrase + " [" + lyric.getPhoneticSymbol() + "]";
    painter->setPen(noteBorderColor);
    painter->fillRect(x, y, w, _noteHeight, noteColor);
    painter->drawRect(x, y, w, _noteHeight);
    painter->setPen(noteTextColor);
    painter->drawText(x + 1, y + 1, w - 2, _noteHeight - 2, Qt::AlignLeft, tr(text.data()), &(QRect(x + 1, y + 1, w - 2, _noteHeight - 2)));
}
