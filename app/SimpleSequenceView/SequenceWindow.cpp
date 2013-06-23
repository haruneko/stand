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

#include <QScrollBar>
#include <QSlider>

#include "views/NoteView.h"
#include "views/ControlGridView.h"
#include "views/BeatView.h"
#include "views/TempoView.h"
#include "views/SingerView.h"

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

    ui->Pianoroll->horizontalScrollBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->Pianoroll->verticalScrollBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSlider *h = new QSlider(Qt::Horizontal, ui->Pianoroll);
    h->setMaximumWidth(80);
    QSlider *v = new QSlider(Qt::Vertical, ui->Pianoroll);
    v->setMaximumHeight(80);
    ui->Pianoroll->addScrollBarWidget(h, Qt::AlignRight);
    ui->Pianoroll->addScrollBarWidget(v, Qt::AlignBottom);

    ui->Pianoroll->setWidget(new NoteView(0, 4, 16, 40, sequence, ui->Pianoroll));
    ui->Control->setWidget(new ControlGridView(4, 40, sequence, ui->Control));
    ui->Beat->setWidget(new BeatView(4, 16, 40, sequence, ui->Beat));
    ui->Tempo->setWidget(new TempoView(4, 16, 40, sequence, ui->Beat));
    ui->Singer->setWidget(new SingerView(0, 4, 16, 40, sequence, ui->Beat));

    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Control->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Beat->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Tempo->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->Pianoroll->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->Singer->horizontalScrollBar(), SLOT(setValue(int)));
}

SequenceWindow::~SequenceWindow()
{
    delete ui;
}
