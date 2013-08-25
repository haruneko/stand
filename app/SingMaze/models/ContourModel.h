/*
 *
 *    ContourModel.h
 *                                    (c) HAL@shurabaP
 *                                        2013/08/25
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef CONTOURMODEL_H
#define CONTOURMODEL_H

#include <QObject>

class Envelope;

/**
 *  @brief Represents contour.
 *         This class emits the signal `dataChanged`, when data has changed.
 */
class ContourModel : public QObject
{
    Q_OBJECT
public:
    explicit ContourModel(Envelope *e, QObject *parent = 0);

    void setData(int index, const QList<double> &data);
    const Envelope *data() const;
signals:
    /**
     *  @brief Is emited when data has changed.
     *         This signal has the range of data change.
     *  @param begin Begin index of data change.
     *  @param end End index of data change.
     */
    void dataChanged(int begin, int end);
private:
    Envelope *_contour;
};

#endif // CONTOURMODEL_H
