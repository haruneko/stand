/*
 *
 *    PianoPainter.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef PIANOPAINTER_H
#define PIANOPAINTER_H

#include <QColor>

class QRect;
class QPainter;

/**
 *  @brief  ピアノロールなど半音ごとの描画を行うクラス．
 */
class PianoPainter
{
public:
    /**
     *  @brief 初期値で初期化する．
     */
    PianoPainter(
            int minNote,
            int maxNote,
            const QColor &whiteKeyColor = Qt::white,
            const QColor &blackKeyColor = Qt::darkGray,
            const QColor &lineColor = Qt::black
            );
    /**
     *  @brief 指定範囲に指定された半音の幅でピアノロールを描画します．
     *  @param [in] noteHeight 半音１つ分の縦幅．
     *  @param [in] rect 描画領域．
     *  @param [in] painter 描画対象．
     */
    void paint(int noteHeight, const QRect &rect, QPainter *painter);

    QColor whiteKeyColor;   //! @brief 白鍵の色
    QColor blackKeyColor;   //! @brief 黒鍵の色
    QColor lineColor;       //! @brief 線の色
    int minNote;
    int maxNote;
};

#endif // PIANOPAINTER_H
