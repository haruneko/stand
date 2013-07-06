/*
 *
 *    ControlCurveView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QPainter>
#include <QPaintEvent>

#include <BPList.hpp>
#include <Track.hpp>

#include "../models/ControlCurveSelection.h"

#include "AbstractControlPainter.h"
#include "ControlCurvePainter.h"

#include "ControlCurveView.h"

ControlCurveView::ControlCurveView(const QHash<QString, string> &labels, int trackId, int divCount, int beatWidth, SequenceModel *model, QWidget *parent)
    : AbstractGridView(divCount, beatWidth, model, parent),
      backgroundColor(64, 64, 64),
      controlColor(255, 255, 255, 192),
      controlSubColor(128, 192, 192, 192)
{
    _trackId = trackId;
    _controlNames = labels;
    _reset();
}

ControlCurveView::~ControlCurveView()
{
    _destroy();
}

void ControlCurveView::_destroy()
{
    qDeleteAll(_painters);
    _painters.clear();
    _shownPainters.clear();
}

void ControlCurveView::_reset()
{
    _destroy();
    if(_trackId < 0 || sequence()->tracks()->size() <= _trackId)
    {
        return;
    }
    const vsq::Track *track = sequence()->track(_trackId);
    for(QHash<QString, std::string>::iterator it = _controlNames.begin(); it != _controlNames.end(); it++)
    {
        const vsq::BPList *control = track->curve(it.value());
        if(!control)
        {
            continue;
        }
        _painters.insert(it.key(), new ControlCurvePainter(control, this));
    }
}

void ControlCurveView::trackChanged(int id)
{
    if(id != _trackId)
    {
        _reset();
        update();
    }
    _trackId = id;
}

void ControlCurveView::modelChanged()
{
    _reset();
}

void ControlCurveView::controlCurveSelectionChanged(ControlCurveSelection &selection)
{
    _shownPainters.clear();
    for(int i = 0; i < selection.subNames.size(); i++)
    {
        // 値が含まれていてもメインと同じなら表示しない．
        if(_painters.contains(selection.subNames[i]) && selection.subNames[i] != selection.mainName)
        {
            AbstractControlPainter *p = _painters[selection.subNames[i]];
            p->color = controlSubColor;
            _shownPainters.push_back(p);
        }
    }
    if(_painters.contains(selection.mainName))
    {
        AbstractControlPainter *p = _painters[selection.mainName];
        p->color = controlColor;
        _shownPainters.push_back(p);
    }
    update();
}

void ControlCurveView::paintBefore(const QRect &rect, QPainter *painter)
{
    painter->fillRect(rect, backgroundColor);
    foreach(AbstractControlPainter *p, _shownPainters)
    {
        p->paint(rect, painter);
    }
}

void ControlCurveView::paintAfter(const QRect &rect, QPainter *painter)
{
    // 真ん中の横線
    painter->setPen(gridLineColor);
    painter->drawLine(rect.left(), height() / 2, rect.right() + 1, height() / 2);
    // 1/4, 3/4 の横線
    QColor weakColor(gridLineColor.red(), gridLineColor.green(), gridLineColor.blue(), gridLineColor.alpha() / 2);
    painter->setPen(weakColor);
    painter->drawLine(rect.left(), height() / 4, rect.right() + 1, height() / 4);
    painter->drawLine(rect.left(), height() * 3 / 4, rect.right() + 1, height() * 3 / 4);
}

void ControlCurveView::drawBarLine(vsq::tick_t tick, QPainter *painter)
{
    int x = xAt(tick);
    painter->setPen(gridLineColor);
    painter->drawLine(x, 0, x, height());
}

void ControlCurveView::drawBeatLine(vsq::tick_t tick, QPainter *painter)
{
    QColor weakColor(gridLineColor.red(), gridLineColor.green(), gridLineColor.blue(), gridLineColor.alpha() * 3 /4);
    int x = xAt(tick);
    painter->setPen(weakColor);
    int h = height();
    painter->drawLine(x, 0, x, h / 8);
    painter->drawLine(x, h * 3 / 8, x, h * 5 / 8);
    painter->drawLine(x, h * 7 / 8, x, h);
}

void ControlCurveView::drawAssistLine(vsq::tick_t tick, QPainter *painter)
{
    QColor weakColor(gridLineColor.red(), gridLineColor.green(), gridLineColor.blue(), gridLineColor.alpha() / 2);
    int x = xAt(tick);
    painter->setPen(weakColor);
    int h = height();
    painter->drawLine(x, 0, x, h / 16);
    painter->drawLine(x, h * 7 / 16, x, h * 9 / 16);
    painter->drawLine(x, h * 15 / 16, x, h);
}
