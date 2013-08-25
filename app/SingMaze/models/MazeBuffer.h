/*
 *
 *    MazeBuffer.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef MAZEBUFFER_H
#define MAZEBUFFER_H

#include "dsp/AudioBuffer.h"

class MazeProject;

/**
 *  @brief Is a buffer for MazeProject.
 *         This buffer is a data that is not saved with a project file,
 *         but neccessary one for Maze to run, such as wave buffer.
 */
class MazeBuffer
{
public:
    MazeBuffer(const QString &path1, const QString &path2);

    const AudioBuffer &wave1() const;
    const AudioBuffer &wave2() const;

    bool isValid() const;
private:
    static void _setWave(AudioBuffer &wave, const QString &path);
    AudioBuffer _wave1;
    AudioBuffer _wave2;
};

#endif // MAZEBUFFER_H
