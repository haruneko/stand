/*
 *
 *    WaveformView.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/08/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QResizeEvent>

#include "WaveformView.h"

WaveformView::WaveformView(const QImage &image, double pixelPerSecond, QWidget *parent) :
    QLabel(parent)
{
    setFixedWidth(image.width());
    setImage(image, pixelPerSecond);
}

void WaveformView::onPixelPerSecondChanged(double w)
{
    double r = w / (double)_basePixmap.width();
    setPixmap(_basePixmap.scaled(_basePixmap.width() * r, height()));
    setFixedWidth(_basePixmap.width() * r);
    _currentPixelPersecond = w;
    update();
}

void WaveformView::resizeEvent(QResizeEvent *e)
{
    setPixmap(pixmap()->scaled(pixmap()->width(), e->size().height()));
}

void WaveformView::setImage(const QImage &image, double pixelPerSecond)
{
    _basePixmap = QPixmap::fromImage(image);
    _basePixelPerSecond = pixelPerSecond;
    onPixelPerSecondChanged(pixelPerSecond);
}
