/*
 *
 *    ProjectFactory.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef PROJECTFACTORY_H
#define PROJECTFACTORY_H

#include <QString>
#include <QPair>

class MazeProject;
class MazeBuffer;

/**
 *  @brief Is a factory class of `MazeProject`.
 *         Simply creates a `MazeProject` instance from two waves' paths.
 */
class ProjectFactory
{
public:
    /**
     *  @brief Creates a `MazeProject` instance.
     *         A calling object MUST delete the creaeted instance.
     *  @param path1 Wave 1 path.
     *  @param path2 Wave 2 path.
     *  @param msFramePeriod Represents resolution of ratio contour.
     *  @return A newly created project and its buffer.
     *  @retval (NULL, NULL) Failed to read wave files.
     */
    QPair<MazeProject *, MazeBuffer *> create(const QString &path1, const QString &path2, double msFramePeriod = 2.0);
};

#endif // PROJECTFACTORY_H
