/*
 *
 *    ToImage.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/03/20
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <cmath>
#include <iostream>
#include "../dsp/Specgram.h"
#include "SpecgramColorPalette.h"

#include "ToImage.h"

namespace
{
class DefaultColorPalette : public SpecgramColorPalette
{
public:
    uint color(double value, double maxValue, double minValue) const
    {
        int r = (256 * 3 - 1) * ((value - minValue) / (maxValue - minValue));
        uint c = 0xff000000;
        c += (r <   0) ? 0 :
             (r < 256) ? r :
             (r < 512) ? (0xff + (r - 256) * 0x100) :
             (r < 768) ? (0xffff + (r - 512) * 0x10000) :
             0xffffff;
        return c;
    }

    uint bgColor() const
    {
        return 0;
    }
};
const static DefaultColorPalette defaultColorPalette;
}

void ToImage::_drawLine(QImage &dst, QPoint p1, QPoint p2, uint pixelValue)
{
    int dy = abs(p1.y() - p2.y());
    int dx = abs(p1.x() - p2.x());
    if(dx > dy)
    {
        dx = qMax(1, dx); //
        if(p1.x() > p2.x())
        {
            QPoint tmp(p2);
            p2 = p1;
            p1 = tmp;
        }
        for(int x = p1.x(); x <= p2.x(); x++)
        {
            int y = p1.y() + (p2.y() - p1.y()) * (x - p1.x()) / dx;
            dst.setPixel(x, y, pixelValue);
        }
    }
    else
    {
        dy = qMax(1, dy); //
        if(p1.y() > p2.y())
        {
            QPoint tmp(p2);
            p2 = p1;
            p1 = tmp;
        }
        for(int y = p1.y(); y <= p2.y(); y++)
        {
            int x = p1.x() + (p2.x() - p1.x()) * (y - p1.y()) / dy;
            dst.setPixel(x, y, pixelValue);
        }
    }
}

double ToImage::_maxValue(const double *const*specgram, int frameLength, int frequencyLength)
{
    double maxValue = -DBL_MAX;

    for(int t = 0; t < frameLength; t++)
    {
        for(int f = 0; f < frequencyLength; f++)
        {
            maxValue = qMax(log10(specgram[t][f] + DBL_MIN), maxValue);
        }
    }

    return maxValue;
}

QImage ToImage::fromSpecgram(const double *const *specgram,
                             int frameLength,
                             int frequencyLength,
                             double maxValue,
                             double dBRange,
                             ScaleType type,
                             const SpecgramColorPalette *palette)
{
    QImage ret(frameLength, frequencyLength, QImage::Format_ARGB32);

    // パレットが指定されていないとき，デフォルトを使用する
    if(!palette)
    {
        palette = &defaultColorPalette;
    }

    if(maxValue == -DBL_MAX && type == LogScale)
    {
        maxValue = _maxValue(specgram, frameLength, frequencyLength);
    }
    double minValue = maxValue - dBRange;

    ret.fill(palette->bgColor());

    // スケールの設定は後から付け足した．無理があるので要修正
    if(type == LogScale)
    {
        for(int t = 0; t < frameLength; t++)
        {
            for(int f = 0; f < frequencyLength; f++)
            {
                double dB = log10(specgram[t][f] + DBL_MIN);
                uint c = palette->color(dB, maxValue, minValue);
                ret.setPixel(t, frequencyLength - f - 1, c);
            }
        }
    }
    else
    {
        maxValue = -DBL_MAX;
        minValue = DBL_MAX;
        for(int t = 0; t < frameLength; t++)
        {
            for(int f = 0; f < frequencyLength; f++)
            {
                minValue = qMin(minValue, specgram[t][f]);
                maxValue = qMax(maxValue, specgram[t][f]);
            }
        }
        for(int t = 0; t < frameLength; t++)
        {
            for(int f = 0; f < frequencyLength; f++)
            {
                uint c = palette->color(specgram[t][f], maxValue, minValue);
                ret.setPixel(t, frequencyLength - f - 1, c);
            }
        }
    }
    return ret;
}

QImage ToImage::fromSpecgram(const Specgram *specgram, ScaleType scale, const SpecgramColorPalette *palette)
{
    double maxValue = _maxValue(specgram->data(), specgram->frameLength(), specgram->frequencyLength());
    return fromSpecgram(specgram->data(), specgram->frameLength(), specgram->frequencyLength(), maxValue, 12.0, scale, palette);
}

QImage ToImage::fromWaveform(const double *wave, int length, int width, int height, uint lineColor, uint bgColor)
{
    if(!wave || length <= 0 || width <= 0 || height <= 0)
    {
        return QImage();
    }

    double maxValue = -DBL_MAX;
    for(int i = 0; i < length; i++)
    {
        maxValue = qMax(fabs(wave[i]), maxValue);
    }
    QImage ret(width, height, QImage::Format_ARGB32);
    ret.fill(bgColor);
    int mid = (height + 1) / 2;
    _drawLine(ret, QPoint(0, mid), QPoint(width, mid), lineColor);

    double previous = height / 2.0 - wave[0] / maxValue * height / 2.0;

    for(int i = 1; i < length; i++)
    {
        double value = wave[i] / maxValue;
        double current = height / 2.0 - value * height / 2;
        _drawLine(ret, QPoint(i - 1, previous), QPoint(i, current), lineColor);
        previous = current;
    }

    return ret;
}
