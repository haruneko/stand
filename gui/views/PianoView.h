/*
 *
 *    PianoView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/23
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef PIANOVIEW_H
#define PIANOVIEW_H

#include <QWidget>
#include <QLabel>
#include "PianoPainter.h"

/**
 *  @brief ピアノの鍵盤を表示します．
 */
class PianoView : public QWidget
{
    Q_OBJECT
public:
    explicit PianoView(int noteHeight, QWidget *parent = 0);

    /** @brief 鍵盤表示用 */
    PianoPainter piano;
signals:
    
public slots:
    /** @brief 音符半音分の縦幅が変わった時に呼ばれる */
    void noteHeightChanged(int h);
protected:
    // @Override
    void paintEvent(QPaintEvent *e);
    // @Override
    void mouseMoveEvent(QMouseEvent *e);
    // @Overrude
    void enterEvent(QEvent *);
    // @Override
    void leaveEvent(QEvent *);
    // @Override
    void moveEvent(QMoveEvent *e);
private:
    int _noteHeight;
    QLabel _n0, _n1, _n2, _n3, _n4;
};

#endif // PIANOVIEW_H
