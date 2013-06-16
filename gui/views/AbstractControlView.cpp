/*
 *
 *    AbstractControlView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/16
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <Sequence.hpp>

#include "AbstractControlView.h"

AbstractControlView::AbstractControlView(
        int trackId,
        int beatWidth,
        int noteHeight,
        const vsq::Sequence *sequence,
        QWidget *parent
        ) : AbstractSequenceView(trackId, beatWidth, noteHeight, sequence, parent)
{
}

void AbstractControlView::dataChanged(int tickBegin, int tickEnd)
{
    int posBegin = beatWidth() * tickBegin / sequence()->getTickPerQuarter();
    int posEnd = beatWidth() * tickEnd / sequence()->getTickPerQuarter();
    update(posBegin, 0, posEnd + 1, height());
}
