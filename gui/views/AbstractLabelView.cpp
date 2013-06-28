/*
 *
 *    AbstractLabelView.cpp
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

#include "AbstractLabelView.h"

AbstractLabelView::AbstractLabelView(int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent) :
    AbstractGridView(divCount, beatWidth, model, parent),
    barLineColor(128, 192, 255),
    fontColor(128, 192, 255),
    backgroundColor(64, 64, 64)
{
    _noteHeight = noteHeight;
}

AbstractLabelView::~AbstractLabelView()
{
    clear();
}

void AbstractLabelView::beatWidthChanged(int w)
{
    if(beatWidth() == w)
    {
        return;
    }
    foreach(QLabel *l, labels)
    {
        l->setGeometry(l->pos().x() * w / beatWidth(), l->pos().y(), w, _noteHeight - 1);
    }

    AbstractGridView::beatWidthChanged(w);
}

void AbstractLabelView::noteHeightChanged(int h)
{
    if(_noteHeight == h)
    {
        return;
    }
    _noteHeight = h;
    setFixedHeight(h);
    update();
}

void AbstractLabelView::sequenceChanged()
{
    reset();
    update();
}

void AbstractLabelView::paintBefore(const QRect &rect, QPainter *painter)
{
    painter->fillRect(rect, backgroundColor);
    painter->setPen(barLineColor);
    painter->drawLine(rect.left(), height(), rect.right(), height());
}

void AbstractLabelView::drawBarLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->drawLine(x, 0 , x, height());
}

void AbstractLabelView::drawBeatLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->drawLine(x, height() / 2, x, height());
}

void AbstractLabelView::drawAssistLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->drawLine(x, height() * 3 / 4, x, height());
}

void AbstractLabelView::clear()
{
    qDeleteAll(labels);
    labels.clear();
}

void AbstractLabelView::reset()
{
    clear();
    setMinimumWidth(xAt(sequence()->getTotalClocks()));

    setLabels();

    update();
}

QLabel *AbstractLabelView::registerLabel(const QString &text, vsq::tick_t tick)
{
    int x = xAt(tick);
    QLabel *l = new QLabel(text, this);
    QPalette palette(l->palette());
    QColor background(fontColor);
    background.setAlpha(64);
    palette.setColor(l->foregroundRole(), fontColor);
    palette.setColor(l->backgroundRole(), background);
    l->setPalette(palette);
    l->setAutoFillBackground(true);

    QFont font(l->font());
    font.setBold(false);
    font.setPixelSize(_noteHeight - 2);
    l->setFont(font);

    l->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    l->setGeometry(x, 0, beatWidth(), _noteHeight);
    labels.insert(l);

    l->setWordWrap(true);

    return l;
}
