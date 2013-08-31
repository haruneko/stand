/*
 *
 *    main.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/18
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QApplication>
#include "SequenceWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SequenceWindow w;
    w.show();
    
    return a.exec();
}
