/*
 *
 *    MazeView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QWidget>

class TimeMapModel;
class Envelope;

class MazeView : public QWidget
{
    Q_OBJECT
public:
    explicit MazeView(TimeMapModel *timeMap, Envelope *contour, int secWidth, QWidget *parent = 0);
    void setTimeMap(TimeMapModel *timeMap);
    void setContour(Envelope *contour);

    int xAt(double ms) const;
    int yAt(double r) const;
    double msAt(int x) const;
    double ratioAt(int y) const;
protected:
    void paintEvent(QPaintEvent *e);
private:
    TimeMapModel *_timeMap;
    Envelope *_contour;
    int _secWidth;
};

#endif // MAZEVIEW_H
