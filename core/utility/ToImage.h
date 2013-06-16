/*
 *
 *    ToImage.h
 *                                    (c) HAL@shurabaP
 *                                        2013/03/20
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef TOIMAGE_H
#define TOIMAGE_H

#include <float.h>
#include <QColor>
#include <QImage>

class Specgram;
class SpecgramColorPalette;
class QPoint;

/*!
 *  @brief 数値計算の結果をビジュアライズするクラスです。
 *         全ての公開メソッドは ToImage::from***(...); の形式で QImage クラスを生成します。
 *  @author HAL@shurabaP
 */
class ToImage
{
public:
    enum ScaleType;

    /*!
     *  @brief スペクトログラムを画像に変換します。
     *         与えられるスペクトログラムは正の実数かつ線形のパワースペクトルで表現されている必要があります。
     *  @param[in] spechram         スペクトログラムの 2 次元配列。
     *  @param[in] frameLength      スペクトログラムのフレーム数を表します。
     *  @param[in] frequencyLength  周波数方向の要素数を表します。パワースペクトルのため、通常は fftLength / 2 を与えて下さい。
     *  @param[in] maxValue         スペクトログラム中の最大値。
     *                              -DBL_MAX が指定されたとき、与えられたスペクトログラム中の最大値を用いて画像を生成します。
     *  @param[in] dBRange          スペクトログラムの表示する幅。 dB 単位で指定して下さい。
     *  @param[in] scale            色のスケールの種類．
     *  @param[in] palette          描画色を計算する SpecgramColorPalette インターフェースを与えます。
     *                              NULL が与えられた場合、デフォルトのパレットが使用されます。
     */
    static QImage fromSpecgram(const double *const *specgram,
                               int frameLength,
                               int frequencyLength,
                               double maxValue = -DBL_MAX,
                               double dBRange = 12.0,
                               ScaleType scale = LogScale,
                               const SpecgramColorPalette *palette = 0);

    /*!
     *  @brief fromSpecgram のラッパ関数です。
     *  @brief[in] specgram 画像にしたいスペクトログラム．
     *  @brief[in] palette  スペクトログラムの描画に使用するパレット．
     */
    static QImage fromSpecgram(const Specgram *specgram, ScaleType scale = LogScale, const SpecgramColorPalette * palette = 0);

    static QImage fromResidual(const Specgram *residual, const SpecgramColorPalette *palette = 0);

    /*!
     *  @brief 波形データから画像に変換します。
     *  @param[in] wave         波形データの配列を与えます。
     *  @param[in] length       波形データの配列長を表します。
     *  @param[in] width        作成する画像の幅を表します。
     *  @param[in] height       作成する画像の高さを表します。
     *  @param[in] lineColor    線の色です。デフォルトは黒です。
     *  @param[in] bgColor      背景色です。デフォルトは白です。
     *  @attention メソッド内部で NULL チェックは行われません。
     */
    static QImage fromWaveform(const double *wave, int length, int width, int height, uint lineColor = 0xff000000, uint bgColor = 0xffffffff);

public:
    /*!
     *  @brief  波形の値をどの軸で扱うかの列挙子．
     */
    enum ScaleType
    {
        UnknownScale = -1,      //! @brief  不明な軸
        LinearScale = 0,        //! @brief  線形な軸
        LogScale = 1            //! @brief  対数軸
    };

private:
    static double _maxValue(const double *const *specgram, int frameLength, int frequencyLength);
    static void _drawLine(QImage &dst, QPoint p1, QPoint p2, uint pixelValue);
};


#endif // TOIMAGE_H
