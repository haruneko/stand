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
#include "ExcitationColorPalette.h"

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
        return 0xff000000;
    }
};
const static DefaultColorPalette defaultLogColorPalette;
const static ExcitationColorPalette defaultLinearColorPalette;
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
            if(x < 0 || dst.width() <= x || y < 0 || dst.height() <= y)
            {
                continue;
            }
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
            if(x < 0 || dst.width() <= x || y < 0 || dst.height() <= y)
            {
                continue;
            }
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
        palette = &defaultLogColorPalette;
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

    for(int x = 0; x < width; x++)
    {
        int t_begin = length * x / width;
        int t_end = length * (x + 1) / width;
        double min_value = wave[t_begin];
        double max_value = wave[t_begin];
        for(int t = t_begin + 1; t < t_end; t++)
        {
            min_value = qMin(min_value, wave[t]);
            max_value = qMax(max_value, wave[t]);
        }
        min_value /= maxValue;
        max_value /= maxValue;
        _drawLine(ret, QPoint(x, (height - min_value * height) / 2), QPoint(x, (height - max_value * height) / 2), lineColor);
    }

    return ret;
}

QImage ToImage::fromResidual(const Specgram *residual, const SpecgramColorPalette *palette)
{
    if(!residual || !residual->isValid())
    {
        return QImage();
    }
    if(!palette)
    {
        palette = &defaultLinearColorPalette;
    }
    double maxValue = -DBL_MAX;
    double minValue = DBL_MAX;
    for(int t = 0; t < residual->frameLength(); t++)
    {
        for(int f = 0; f < residual->frequencyLength(); f++)
        {
            minValue = qMin(minValue, residual->value(t, f));
            maxValue = qMax(maxValue, residual->value(t, f));
        }
    }

    int range = 512;

    QImage ret(QSize(residual->frequencyLength(), residual->frameLength() + range), QImage::Format_ARGB32);
    ret.fill(palette->bgColor());

    double diff = maxValue - minValue;
    for(int index = 0; index < residual->frameLength(); index++)
    {
        double prev = range / 2 + index - range / 2 * (residual->value(index, 0) - minValue) / diff;
        for(int tau = 1; tau < residual->frequencyLength(); tau++)
        {
            double val = (residual->value(index, tau) - minValue) / diff;
            uint c = palette->color(val - 0.5, 0.5, - 0.5);
            double current = range / 2 + index - range / 2 * val;
            _drawLine(ret, QPoint(tau - 1, prev), QPoint(tau, current), c);
            prev = current;
        }
    }
    return ret;
}
