/*
 *
 *    DisplayConf.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/26
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef DISPLAYCONF_H
#define DISPLAYCONF_H

#include <QObject>

/**
 *  @brief Represents a configuretion how to display views.
 */
class DisplayConf : public QObject
{
    Q_OBJECT
public:
    explicit DisplayConf(double pixelPerSecond, QObject *parent = 0);

    double pixelPerSecond() const;
    void setPixelPerSecond(double pixelPerSecond);
signals:
    void widthChanged(double pixelPerSecond);
private:
    double _pixelPerSecond;
};

#endif // DISPLAYCONF_H
