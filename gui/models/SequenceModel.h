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
     *  @param [in] trackId トラック番号
     *  @param [in] changes 変更のあるノートとその情報
     */
    void updateEvents(int trackId, const QList<vsq::Event> &changes);

    void appendEvents(int trackId, const QList<vsq::Event> &events);
signals:
    void dataChanged();
public slots:

private slots:
    /**
     *  @brief 実際に値を変更するスロットです. Action クラスの SIGNAL と接続されます.
     *         undo コマンドから呼び出され実際に値を変更しますが, Action クラス以外から呼び出さないで下さい.
     *  @param [in] trackId トラック番号
     *  @param [in] changes 変更のあるノートとその情報
     */
    void apply(int trackId, QList<vsq::Event> &changes);

private:
    vsq::Sequence *_sequence;
    /** 編集履歴 */
    QUndoStack _history;
};

#endif // SEQUENCEMODEL_H
