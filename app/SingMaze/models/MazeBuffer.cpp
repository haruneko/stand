/*
 *
 *    MazeBuffer.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include "MazeBuffer.h"

#include "MazeProject.h"

MazeBuffer::MazeBuffer(const QString &path1, const QString &path2)
{
    _setWave(_wave1, path1);
    _setWave(_wave2, path2);
}

void MazeBuffer::_setWave(AudioBuffer &wave, const QString &path)
{
    wave.read(path);
}

const AudioBuffer &MazeBuffer::wave1() const
{
    return _wave1;
}

const AudioBuffer &MazeBuffer::wave2() const
{
    return _wave2;
}

bool MazeBuffer::isValid() const
{
    return (!_wave1.isEmpty() && !_wave2.isEmpty());
}
