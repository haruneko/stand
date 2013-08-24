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

MazeBuffer::MazeBuffer(const QString &wave1Path, const QString &wave2Path)
{
    setWave1(wave1Path);
    setWave2(wave2Path);
}

void MazeBuffer::setWave1(const QString &path)
{
    _setWave(_wave1, path);
}

void MazeBuffer::setWave2(const QString &path)
{
    _setWave(_wave2, path);
}

void MazeBuffer::_setWave(AudioBuffer &wave, const QString &path)
{
    wave.read(path);
}
