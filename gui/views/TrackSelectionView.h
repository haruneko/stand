/*
 *
 *    TrackSelectionView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef TRACKSELECTIONVIEW_H
#define TRACKSELECTIONVIEW_H

#include <QLabel>

#include "AbstractSequenceView.h"

/**
 *  @brief シーケンスのトラック名と現在選択されているトラックを表示するクラスです．
 */
class TrackSelectionView : public AbstractSequenceView
{
    Q_OBJECT
public:
    explicit TrackSelectionView(int noteHeight, SequenceModel *model, QWidget *parent);
    virtual ~TrackSelectionView();

    /** @brief 背景色 */
    QColor backgroundColor;
    /** @brief 文字色 */
    QColor foregroundColor;

protected:
    // @Override
    void sequenceChanged();
public slots:
    // @Override
    virtual void paint(const QRect &rect, QPainter *painter);
    // @Override
    virtual void trackChanged(int id);
    // @Override
    virtual void beatWidthChanged(int w);
    // @Override
    virtual void noteHeightChanged(int h);
private:
    void _destroy();
    QList<QLabel *> _trackNames;
    int _noteHeight;
    int _currentTrackId;
};

#endif // TRACKSELECTIONVIEW_H
