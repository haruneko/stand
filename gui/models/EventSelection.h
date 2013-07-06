/*
 *
 *    EventSelection.h
 *                                    (c) HAL@shurabaP
 *                                        2013/07/06
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef EVENTSELECTION_H
#define EVENTSELECTION_H

#include <QObject>

/**
 *  @brief イベントの選択範囲を表すクラスです．
 */
class EventSelection : public QObject
{
    Q_OBJECT
public:
    explicit EventSelection(QObject *parent = 0);
    virtual ~EventSelection();

    int trackId() const;
    const QList<int> &ids() const;

public slots:
    /**
     *  @brief 保持しているデータをクリアします．このスロットは selectionChanged シグナルを送信します．
     */
    void clear();
    /**
     *  @brief 保持しているトラック ID を変更します．このスロットは selectionChanged シグナルを送信します．
     */
    void setTrackId(int trackId);

    /**
     *  @brief 保持しているノート ID 列を変更します．このスロットは selectionChanged シグナルを送信します．
     */
    void setIds(const QList<int> &ids);
signals:
    void selectionChanged(EventSelection *current, EventSelection *previous);

private:
    void _changeSelection(int trackId, const QList<int> &ids);

    int _trackId;
    QList<int> _ids;
    EventSelection *_previous;
};

#endif // EVENTSELECTION_H
