/*
 *
 *    SingMazeMain.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/24
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QFileDialog>
#include <QScrollBar>
#include "views/MazeView.h"
#include "views/WaveformView.h"
#include "views/ProjectDialog.h"
#include "models/MazeContext.h"
#include "models/MazeBuffer.h"
#include "models/MazeProject.h"

#include "SingMazeMain.h"
#include "ui_SingMazeMain.h"

SingMazeMain::SingMazeMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingMazeMain)
{
    ui->setupUi(this);
    _currentContext = NULL;
    ui->mazeView->setWidget(new MazeView(NULL, NULL, 1.0, this));
    ui->wave1View->setWidget(new WaveformView(QImage(), 1.0, this));
    ui->wave2View->setWidget(new WaveformView(QImage(), 1.0, this));
    connect(ui->mazeView->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->wave1View->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->mazeView->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->wave2View->horizontalScrollBar(), SLOT(setValue(int)));
}

SingMazeMain::~SingMazeMain()
{
    MazeView *mv = (MazeView *)ui->mazeView->widget();
    mv->setTimeMap(NULL);
    mv->setContour(NULL, 0);

    delete ui;
    delete _currentContext;
}

void SingMazeMain::_setContext(MazeContext *c)
{
    if(!c || !c->isValid())
    {
        return;
    }
    MazeView *mv = (MazeView *)ui->mazeView->widget();
    mv->setTimeMap(&c->project->timeMap);
    mv->setContour(&c->project->morphRatioContour, c->pixelPerSecond());
    WaveformView *wv1 = (WaveformView *)ui->wave1View->widget();
    WaveformView *wv2 = (WaveformView *)ui->wave2View->widget();
    wv1->setImage(c->buffer->wave1Image(), c->pixelPerSecond());
    wv2->setImage(c->buffer->wave2Image(), c->pixelPerSecond());
    wv1->setFixedWidth(mv->width());
    wv2->setFixedWidth(mv->width());

    delete _currentContext;
    _currentContext = c;
}

void SingMazeMain::onProjectNew()
{
    ProjectDialog *dialog = new ProjectDialog(tr("New project"), this);
    int result = dialog->exec();
    if(result != QDialog::Accepted)
    {
        delete dialog;
        return;
    }
    QPair<QString, QString> value = dialog->value();
    delete dialog;

    _setContext(new MazeContext(value.first, value.second, 100.0, ui->wave1View->height(), 2.0));
}

void SingMazeMain::onProjectOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a project."), QString(), tr("Project file(*.maze)"));
    if(fileName.isNull())
    {
        return;
    }
    // TODO : read project here.
}
