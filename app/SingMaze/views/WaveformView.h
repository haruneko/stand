/*
 *
 *    WaveformView.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef WAVEFORMVIEW_H
#define WAVEFORMVIEW_H

#include <QLabel>

/**
 *  @brief Shows waveform.
 */
class WaveformView : public QLabel
{
public:
    explicit WaveformView(const QImage &image, double pixelPerSecond, QWidget *parent = 0);
    void setImage(const QImage &image, double pixelPerSecond);
protected:
    void resizeEvent(QResizeEvent *e);
private slots:
    void onPixelPerSecondChanged(double w);
private:
    double _currentPixelPersecond;
    double _basePixelPerSecond;
    QPixmap _basePixmap;
};

#endif // WAVEFORMVIEW_H
