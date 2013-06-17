/*
 *
 *    SequenceWindow.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/18
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "views/NoteView.h"
#include "views/ControlCurveView.h"

#include "SequenceWindow.h"
#include "ui_SequenceWindow.h"

SequenceWindow::SequenceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SequenceWindow)
{
    ui->setupUi(this);

    sequence = new vsq::Sequence("test", 3, 4, 4, 500000);
    vsq::Event e(480 * 4, vsq::EventType::UNKNOWN);
    sequence->updateTotalClocks();
    sequence->track(0)->events()->add(e);
    ui->Pianoroll->setWidget(new NoteView(4, 16, 160, sequence, 0, this));
    ui->Control->setWidget(new ControlCurveView("BrightnessBPList", 120, sequence, 0, this));
}

SequenceWindow::~SequenceWindow()
{
    delete ui;
}
