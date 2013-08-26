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
#include "views/MazeView.h"
#include "views/WaveformView.h"
#include "views/ProjectDialog.h"

#include "SingMazeMain.h"
#include "ui_SingMazeMain.h"

SingMazeMain::SingMazeMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingMazeMain)
{
    ui->setupUi(this);
    ui->mazeView->setWidget(new MazeView(NULL, NULL, 1.0, this));
    ui->wave1View->setWidget(new WaveformView(QImage(), 1.0, this));
}

SingMazeMain::~SingMazeMain()
{
    delete ui;
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
    delete dialog;
    // TODO : read waves here.
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
