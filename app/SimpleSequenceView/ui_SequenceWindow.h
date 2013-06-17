/********************************************************************************
** Form generated from reading UI file 'SequenceWindow.ui'
**
** Created: Tue Jun 18 01:38:29 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQUENCEWINDOW_H
#define UI_SEQUENCEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SequenceWindow
{
public:
    QAction *actionOpen;
    QAction *actionE_xit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *Pianoroll;
    QWidget *scrollAreaWidgetContents;
    QScrollArea *Control;
    QWidget *scrollAreaWidgetContents_3;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *SequenceWindow)
    {
        if (SequenceWindow->objectName().isEmpty())
            SequenceWindow->setObjectName(QString::fromUtf8("SequenceWindow"));
        SequenceWindow->resize(660, 524);
        actionOpen = new QAction(SequenceWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionE_xit = new QAction(SequenceWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        centralWidget = new QWidget(SequenceWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Pianoroll = new QScrollArea(centralWidget);
        Pianoroll->setObjectName(QString::fromUtf8("Pianoroll"));
        Pianoroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        Pianoroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        Pianoroll->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 623, 277));
        Pianoroll->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(Pianoroll);

        Control = new QScrollArea(centralWidget);
        Control->setObjectName(QString::fromUtf8("Control"));
        Control->setMinimumSize(QSize(0, 180));
        Control->setMaximumSize(QSize(16777215, 180));
        Control->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Control->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Control->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 640, 178));
        Control->setWidget(scrollAreaWidgetContents_3);

        verticalLayout->addWidget(Control);

        SequenceWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SequenceWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 660, 24));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        SequenceWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionE_xit);

        retranslateUi(SequenceWindow);

        QMetaObject::connectSlotsByName(SequenceWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SequenceWindow)
    {
        SequenceWindow->setWindowTitle(QApplication::translate("SequenceWindow", "SequenceWindow", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("SequenceWindow", "&Open", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("SequenceWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("SequenceWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SequenceWindow: public Ui_SequenceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQUENCEWINDOW_H
