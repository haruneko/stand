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

#include <QLabel>
#include <QPainter>
#include <QPalette>

#include "NoteView.h"

NoteView::NoteView(int divCount, int noteHeight, int beatWidth, const vsq::Sequence *sequence, int trackId, QWidget *parent) :
    AbstractGridView(divCount, beatWidth, sequence, trackId, parent),
    low(0, 32, QColor(192, 192, 192), QColor(128, 128, 128), QColor(64, 64, 64)),
    middle(33, 72, QColor(255, 255, 255), QColor(224, 224, 255), QColor(64, 64, 64)),
    high(73, 128, QColor(192, 192, 192), QColor(128, 128, 128), QColor(64, 64, 64))
{
    _noteHeight = 0;
    setNoteHeight(noteHeight);

    barLineColor = QColor(64, 64, 96);
    assistLineColor = QColor(144, 144, 192);

    noteColor = QColor(192, 192, 255);
    noteInvalidColor = QColor(255, 192, 192);
    noteSelectedColor = QColor(128, 128, 255);
    noteTextColor = QColor(0, 0, 0);

    _reset();
}

NoteView::~NoteView()
{
    _destroy();
}

void NoteView::_destroy()
{
    qDeleteAll(_noteLabels);
    _noteLabels.clear();
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

    // 音符の高さ変更．
    foreach(QLabel *label, _noteLabels)
    {
        QPoint p(label->pos());
        long y = p.y() * noteHeight / _noteHeight;
        label->setGeometry(p.x(), y, label->width(), noteHeight);
    }
    _noteHeight = noteHeight;

    // 自身の高さ変更．
    setFixedHeight(noteHeight * 128);
    update();
}

void NoteView::noteHeightChanged(int h)
{
    setNoteHeight(h);
}

void NoteView::beatWidthChanged(int w)
{
    // 音符の長さ変更．
    if(w != beatWidth())
    {
        foreach(QLabel *label, _noteLabels)
        {
            QPoint p(label->pos());
            long x = p.x() * w / beatWidth();
            label->setGeometry(x, p.x(), w, label->height());
        }
    }
    AbstractGridView::beatWidthChanged(w);
}

void NoteView::sequenceChanged()
{
    _reset();
}

void NoteView::_reset()
{
    _destroy();
    const vsq::Track *track = sequence()->track(trackId());
    if(!track)
    {
        return;
    }
    vsq::EventListIndexIterator it = track->getIndexIterator(vsq::EventListIndexIteratorKind::NOTE);
    while(it.hasNext())
    {
        int index = it.next();
        const vsq::Event *e = track->events()->get(index);
        _noteLabels.append(_labelFromEvent(e));
    }
    setMinimumWidth(xAt(sequence()->getTotalClocks()));
}

QLabel *NoteView::_labelFromEvent(const vsq::Event *e)
{
    // ラベルの表示文章計算
    const vsq::Lyric &lyric = e->lyricHandle.getLyricAt(0);
    std::string text = lyric.phrase + " [" + lyric.getPhoneticSymbol() + "]";
    QString qtext(tr(text.data()));

    QLabel *l = new QLabel(qtext, this);
    int x = xAt(e->clock);
    int w = xAt(e->clock + e->getLength()) - x;
    int y = yAt(e->note);
    l->setGeometry(x, y, w, _noteHeight);
    l->setFrameStyle(QFrame::Box);
    l->setLineWidth(1);

    QFont font(l->font());
    font.setPixelSize(_noteHeight - 2);

    QPalette palette = l->palette();
    palette.setColor(QPalette::Text, noteTextColor);
    palette.setColor(QPalette::Background, noteColor);
    l->setPalette(palette);

    l->setWordWrap(true);
    l->show();

    return l;
}

void NoteView::paintBefore(const QRect &rect, QPainter *painter)
{
    // ピアノロールの部分を書く
    high.paint(_noteHeight, rect, painter);
    middle.paint(_noteHeight, rect, painter);
    low.paint(_noteHeight, rect, painter);
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

