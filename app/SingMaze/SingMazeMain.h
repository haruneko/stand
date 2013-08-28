/*
 *
 *    SingMazeMain.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/24
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SINGMAZEMAIN_H
#define SINGMAZEMAIN_H

#include <QMainWindow>

class MazeContext;

namespace Ui {
class SingMazeMain;
}

class SingMazeMain : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SingMazeMain(QWidget *parent = 0);
    ~SingMazeMain();

private slots:
    void onProjectNew();
    void onProjectOpen();
private:
    void _setContext(MazeContext *c);
    Ui::SingMazeMain *ui;
    MazeContext *_currentContext;
};

#endif // SINGMAZEMAIN_H
