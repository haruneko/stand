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
#include <QUndoStack>

/**
 *  @brief vsq::Sequence クラスの STAND 用ラッパです．
 */
class SequenceModel : public QObject
{
    Q_OBJECT
public:
    explicit SequenceModel(vsq::Sequence *sequence, QObject *parent = 0);

    const vsq::Sequence *sequence() const;

    /**
     *  @brief スナップされた位置を返します．
     */
    int snappedTick(int tick) const;

    /** @brief スナップする幅 */
    int noteSnapTick;
    /** @brief 末端と判断される幅 */
    int edgeWidth;

    /**
     *  @brief トラック番号とイベント番号を指定してイベントを取得します.
     *  @param [in] trackId トラック番号
     *  @param [in] eventId イベント番号
     *  @retval NULL 該当するトラック番号かイベント番号が存在しない.
     */
    const vsq::Event *eventAt(int trackId, int eventId) const;

    /**
     *  @brief 音符情報を変更します.
     */
    void updateNotes(int trackId, const QList<vsq::Event> &changes);
signals:
    void dataChanged();
public slots:
    
private:
    vsq::Sequence *_sequence;
    /** 編集履歴 */
    QUndoStack _history;
};

#endif // SEQUENCEMODEL_H
