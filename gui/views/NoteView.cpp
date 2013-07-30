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

#include <QHash>
#include <QLabel>
#include <QPainter>
#include <QPalette>

#include "../models/EventSelection.h"
#include "../models/SequenceModel.h"

#include "NoteView.h"

NoteView::NoteView(int trackId, int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent) :
    AbstractGridView(divCount, beatWidth, model, parent),
    low(0, 32, QColor(192, 192, 192), QColor(128, 128, 128), QColor(64, 64, 64)),
    middle(33, 72, QColor(255, 255, 255), QColor(224, 224, 255), QColor(64, 64, 64)),
    high(73, 128, QColor(192, 192, 192), QColor(128, 128, 128), QColor(64, 64, 64))
{
    _trackId = trackId;
    _noteHeight = 0;
    setNoteHeight(noteHeight);

    barLineColor = QColor(128, 128, 192);
    beatLineColor = QColor(160, 160, 255);
    assistLineColor = QColor(176, 176, 176);

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
    for(int i = 0; i < _noteLabels.size(); i++)
    {
        qDeleteAll(_noteLabels[i]);
    }
    _noteLabels.clear();
}

int NoteView::yAt(int note)
{
    return (127 - note) * _noteHeight;
}

int NoteView::noteAt(int y) const
{
    // [0, _noteHeight] が notenum = 127
    return (127 - y / _noteHeight);
}

void NoteView::setNoteHeight(int noteHeight)
{
    if(noteHeight == _noteHeight)
    {
        return;
    }

    // 音符の高さ変更．
    for(int i = 0; i < _noteLabels.size(); i++)
    {
        foreach(QLabel *label, _noteLabels[i])
        {
            QPoint p(label->pos());
            long y = p.y() * noteHeight / _noteHeight;
            label->setGeometry(p.x(), y, label->width(), noteHeight);
        }
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
    if(w == beatWidth())
    {
        return;
    }

    // 音符の長さ変更．
    for(int i = 0; i < _noteLabels.size(); i++)
    {
        foreach(QLabel *label, _noteLabels[i])
        {
            QPoint p(label->pos());
            long x = p.x() * w / beatWidth();
            label->setGeometry(x, p.x(), w, label->height());
        }
    }
    AbstractGridView::beatWidthChanged(w);
}

void NoteView::modelChanged()
{
    _reset();
}

void NoteView::_reset()
{
    _destroy();

    _noteLabels.resize(model()->trackSize());
    for(int i = 0; i < model()->trackSize(); i++)
    {
        QHash<int, QLabel *> &labels = _noteLabels[i];
        const vsq::Track *track = model()->track(i);
        vsq::EventListIndexIterator it = track->getIndexIterator(vsq::EventListIndexIteratorKind::NOTE);
        while(it.hasNext())
        {
            int index = it.next();
            const vsq::Event *e = track->events()->get(index);
            labels[e->id] = _labelFromEvent(e);
        }
    }
    setMinimumWidth(xAt(model()->sequence()->getTotalClocks()));
}

void NoteView::setNoteLabelProperty(QLabel *l)
{
    l->setFrameStyle(QFrame::Box);
    l->setLineWidth(1);

    QFont font(l->font());
    font.setPixelSize(_noteHeight - 2);

    QPalette palette = l->palette();
    palette.setColor(l->foregroundRole(), noteTextColor);
    palette.setColor(l->backgroundRole(), noteColor);
    l->setPalette(palette);

    l->setAutoFillBackground(true);

    l->setWordWrap(true);
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

    setNoteLabelProperty(l);

    return l;
}

void NoteView::trackChanged(int id)
{
    int old = _trackId;
    AbstractSequenceView::trackChanged(id);
    if(old == _trackId)
    {
        return;
    }
    foreach(QLabel *label, _noteLabels[old])
    {
        label->hide();
    }
    foreach(QLabel *label, _noteLabels[id])
    {
        label->show();
    }
    _trackId = id;
}

int NoteView::currentTrackId() const
{
    return _trackId;
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
    // 基準線． yAt は top を返すので．
    int y = yAt(47);
    painter->setPen(QColor(192, 0, 0));
    painter->drawLine(rect.left(), y, rect.right() + 1, y);
    // 手抜きだけどプリメジャー部
    painter->fillRect(0, 0, xAt(0), height(), QColor(0, 0, 0, 128));
}

void NoteView::drawAssistLine(vsq::tick_t tick, QPainter *painter)
{
    /*int x = xAt(tick);
    painter->setPen(assistLineColor);
    painter->drawLine(x, 0, x, height());*/
}

void NoteView::drawBarLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(barLineColor);
    painter->drawLine(x, 0, x, height());
}

void NoteView::drawBeatLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(beatLineColor);
    painter->drawLine(x, 0, x, height());
}

QList<QLabel *> NoteView::labels()
{
    QList<QLabel *> ret;
    for(int i = 0; i < _noteLabels.size(); i++)
    {
        foreach(QLabel *l, _noteLabels[i])
        {
            ret.append(l);
        }
    }
    return ret;
}

QList<QPair<int, QLabel *> > NoteView::labels(int trackId)
{
    QList<QPair<int, QLabel *> > ret;
    if(0 <= trackId && trackId < _noteLabels.size())
    {
        foreach(int id, _noteLabels[trackId].keys())
        {
            ret.append(QPair<int, QLabel *>(id, _noteLabels[trackId][id]));
        }
    }
    return ret;
}

QList <QPair<int, QLabel *> > NoteView::labels(int trackId, const QList<int> &ids)
{
    QList<QPair<int, QLabel *> > ret;
    if(0 <= trackId && trackId < _noteLabels.size())
    {
        foreach(int id, ids)
        {
            ret.append(QPair<int, QLabel *>(id, _noteLabels[trackId][id]));
        }
    }
    return ret;
}

void NoteView::changeSelection(EventSelection *current, EventSelection *previous)
{
    _setLabelColor(previous, noteColor);
    _setLabelColor(current, noteColor);
}

void NoteView::_setLabelColor(EventSelection *s, const QColor &c)
{
    int trackId = s->trackId();
    // トラック ID が範囲外なら何もしない
    if(trackId < 0 || _noteLabels.size() <= trackId)
    {
        return;
    }
    QHash<int, QLabel *> &labels = _noteLabels[trackId];
    foreach(int i, s->ids())
    {
        if(labels.contains(i))
        {
            QLabel *l = labels[i];
            QPalette p(l->palette());
            p.setColor(l->backgroundRole(), c);
            l->setPalette(p);
        }
    }
}
