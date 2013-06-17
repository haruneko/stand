/*
 *
 *    SequenceWindow.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/18
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SEQUENCEWINDOW_H
#define SEQUENCEWINDOW_H

#include <Sequence.hpp>

#include <QMainWindow>

namespace Ui {
class SequenceWindow;
}

class SequenceWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SequenceWindow(QWidget *parent = 0);
    ~SequenceWindow();
    
private:
    Ui::SequenceWindow *ui;
    vsq::Sequence *sequence;
};

#endif // SEQUENCEWINDOW_H
