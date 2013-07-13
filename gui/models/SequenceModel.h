/*
 *
 *    SequenceModel.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/28
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SEQUENCEMODEL_H
#define SEQUENCEMODEL_H

#include <Sequence.hpp>
#include <QObject>

/**
 *  @brief vsq::Sequence クラスの STAND 用ラッパです．
 */
class SequenceModel : public QObject
{
    Q_OBJECT
public:
    explicit SequenceModel(vsq::Sequence *sequence, QObject *parent = 0);

    const vsq::Sequence *sequence() const;
    /** @brief スナップする幅 */
    int noteSnapTick;
    /** @brief 末端と判断される幅 */
    int edgeWidth;

signals:
    void dataChanged();
public slots:
    
private:
    vsq::Sequence *_sequence;
};

#endif // SEQUENCEMODEL_H
