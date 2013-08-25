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
 *         It contains wave buffer.
 */
class MazeBuffer
{
public:
    MazeBuffer(const MazeProject &project);

    const AudioBuffer &wave1() const;
    const AudioBuffer &wave2() const;
private:
    static void _setWave(AudioBuffer &wave, const QString &path);
    AudioBuffer _wave1;
    AudioBuffer _wave2;
};

#endif // MAZEBUFFER_H
