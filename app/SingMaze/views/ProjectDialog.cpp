/*
 *
 *    ProjectDialog.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QFileDialog>
#include "../models/MazeProject.h"

#include "ProjectDialog.h"
#include "ui_ProjectDialog.h"

ProjectDialog::ProjectDialog(const QString &title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);
    ui->wave1Line->installEventFilter(this);
    ui->wave2Line->installEventFilter(this);
    this->setWindowTitle(title);
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

bool ProjectDialog::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->wave1Line && e->type() == QEvent::MouseButtonPress)
    {
        ui->wave1Button->click();
        return true;
    }
    if(o == ui->wave2Line && e->type() == QEvent::MouseButtonPress)
    {
        ui->wave2Button->click();
        return true;
    }
    return QDialog::eventFilter(o, e);
}

void ProjectDialog::_wave1Clicked()
{
    _setLineValue(this, ui->wave1Line);
}

void ProjectDialog::_wave2Clicked()
{
    _setLineValue(this, ui->wave2Line);
}

QPair<QString, QString> ProjectDialog::value() const
{
    return QPair<QString, QString>(ui->wave1Line->text(), ui->wave2Line->text());
}

void ProjectDialog::_setLineValue(QWidget *widget, QLineEdit *target)
{
    QString val = QFileDialog::getOpenFileName(
                widget,
                tr("Select Waveform"),
                QString(),
                tr("Wave files (*.wav)")
                );
    if(!val.isNull())
    {
        target->setText(val);
    }
}
