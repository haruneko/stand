/*
 *
 *    SingerView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SINGERVIEW_H
#define SINGERVIEW_H

#include "AbstractLabelView.h"

class EventSelection;

/**
 *  @brief 歌手情報を表示するクラスです．
 */
class SingerView : public AbstractLabelView
{
    Q_OBJECT
public:
    explicit SingerView(int trackId, int divCount, int noteHeight, int beatWidth, SequenceModel *model, QWidget *parent);

public slots:
    /**
     *  @brief 音符の選択が変更されたときのシグナルを受け取るスロットです．
     *  @param[in] current 現在新たに選択されている音符などのイベント．
     *  @param[in] previous 直前まで選択されていた音符などのイベント．
     */
    void changeSelection(EventSelection *current, EventSelection *previous);

protected:
    // @Override
    void trackChanged(int id);
    // @Override
    void setLabels();
private:
    void _setLabelColor(EventSelection *s, const QColor &c);
    int _trackId;
    QHash<int, QLabel *> _labels;
};

#endif // SINGERVIEW_H
