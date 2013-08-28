/*
 *
 *    ProjectFactory.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QFileInfo>

#include "dsp/AudioBuffer.h"
#include "../models/MazeProject.h"
#include "../models/MazeBuffer.h"

#include "ProjectFactory.h"

QPair<MazeProject *, MazeBuffer *> ProjectFactory::create(const QString &path1, const QString &path2, double pixelPerSecond, int height, double msFramePeriod)
{
    MazeBuffer *buffer = new MazeBuffer(path1, path2, pixelPerSecond, height);
    if(!buffer->isValid())
    {
        delete buffer;
        return QPair<MazeProject *, MazeBuffer *>(NULL, NULL);
    }
    int size = qMax(buffer->wave1().msLength(), buffer->wave2().msLength()) / msFramePeriod;

    MazeProject *project = new MazeProject;
    project->wave1Path = QFileInfo(path1);
    project->wave2Path = QFileInfo(path2);

    project->morphRatioContour.setEnvelope(size, msFramePeriod);
    project->timeMap.append(QPair<double, double>(0.0, 0.0));
    project->timeMap.append(QPair<double, double>(buffer->wave1().msLength(), buffer->wave2().msLength()));
    return QPair<MazeProject *, MazeBuffer *>(project, buffer);
}
