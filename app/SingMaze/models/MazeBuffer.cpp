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

#include "utility/ToImage.h"
#include "MazeBuffer.h"

#include "MazeProject.h"

MazeBuffer::MazeBuffer(const QString &path1, const QString &path2, double pixelPerSecond, int height)
{
    _pixelPerSecond = pixelPerSecond;
    _height = height;
    _setWave(_wave1, _wave1Image, path1, pixelPerSecond, height);
    _setWave(_wave2, _wave2Image, path2, pixelPerSecond, height);
}

void MazeBuffer::_setWave(AudioBuffer &wave, QImage &image, const QString &path, double pixelPerSecond, int height)
{
    if(!wave.read(path))
    {
        return;
    }
    double ms = wave.msLength();
    int width = ms / 1000.0 * pixelPerSecond;
    image = ToImage::fromWaveform(wave.data(0), wave.length(), width, height);
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

const QImage &MazeBuffer::wave1Image() const
{
    return _wave1Image;
}

const QImage &MazeBuffer::wave2Image() const
{
    return _wave2Image;
}
