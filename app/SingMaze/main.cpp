/*
 *
 *    main.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/24
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QtGui/QApplication>
#include "SingMazeMain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SingMazeMain w;
    w.show();
    
    return a.exec();
}
