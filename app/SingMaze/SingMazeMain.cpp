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

#include "SingMazeMain.h"
#include "ui_SingMazeMain.h"

SingMazeMain::SingMazeMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SingMazeMain)
{
    ui->setupUi(this);
}

SingMazeMain::~SingMazeMain()
{
    delete ui;
}
