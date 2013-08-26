/*
 *
 *    ProjectDialog.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>

class MazeProject;
class QLineEdit;

namespace Ui {
class ProjectDialog;
}

/**
 *  @brief Receives a project setting from a user.
 *         This class returns two waves' paths.
 *  @author HAL@shurabaP
 */
class ProjectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjectDialog(const QString &title, QWidget *parent = 0);
    ~ProjectDialog();

    /**
     *  @brief Returns two waves' paths.
     */
    QPair<QString, QString> value() const;
protected:
    bool eventFilter(QObject *o, QEvent *e);
private slots:
    void _wave1Clicked();
    void _wave2Clicked();
private:
    static void _setLineValue(QWidget *widget, QLineEdit *target);
    Ui::ProjectDialog *ui;
};

#endif // PROJECTDIALOG_H
