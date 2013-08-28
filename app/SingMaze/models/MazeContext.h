/*
 *
 *    MazeContext.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef MAZECONTEXT_H
#define MAZECONTEXT_H

#include <QString>

class MazeBuffer;
class MazeProject;

class MazeContext
{
public:
    MazeContext(const QString &wave1Path, const QString &wave2Path, double pixelPerSecond, int height, double msFramePeriod);
    ~MazeContext();

    MazeBuffer *buffer;
    MazeProject *project;
    double pixelPerSecond() const;
    bool isValid() const;
private:
    double _pixelPerSecond;
};

#endif // MAZECONTEXT_H
