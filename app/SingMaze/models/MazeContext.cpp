/*
 *
 *    MazeContext.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "../controllers/ProjectFactory.h"

#include "MazeContext.h"

MazeContext::MazeContext(const QString &wave1Path, const QString &wave2Path, double pixelPerSecond, int height, double msFramePeriod)
{
    QPair<MazeProject *, MazeBuffer *> pair = ProjectFactory().create(wave1Path, wave2Path, pixelPerSecond, height, msFramePeriod);
    project = pair.first;
    buffer = pair.second;
    _pixelPerSecond = pixelPerSecond;
}

MazeContext::~MazeContext()
{
    delete buffer;
    delete project;
}

double MazeContext::pixelPerSecond() const
{
    return _pixelPerSecond;
}
