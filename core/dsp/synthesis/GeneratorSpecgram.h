/*
 *
 *    GeneratorSpecgram.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef GENERATORSPECGRAM_H
#define GENERATORSPECGRAM_H

#include "../Specgram.h"

#include "SpectrumGeneratorInterface.h"

/*!
 *  @brief  SpectrumGeneratorInterface の実装．
 *          Specgram クラスを継承し， generate メソッドでは
 *          Specgram の内容を
 */
class GeneratorSpecgram : public Specgram, public SpectrumGeneratorInterface
{
public:
    /*!
     *  @brief  初期値に Specgram クラスを与えて初期化します．
     *          この際 NULL が与えられた場合自分自身のデータを使用します．
     */
    GeneratorSpecgram(Specgram *specgram = 0, double msFramePeriod = 2.0);

    /*!
     *  @brief  スペクトル生成に使用する Specgram クラスを設定します．
     *          この際 NULL が与えられた場合自分自身のデータを使用します．
     *  @return 無し
     */
    void setSpecgram(Specgram *specgram, double msFramePeriod);

    /*!
     *  @brief  自身が保持する Specgram クラスを返します．
     *  @return 生成に使用する Specgram クラス．
     */
    Specgram *specgram();

    /*!
     *  @brief  現在保持しているフレーム長を返します．
     *  @return 現在のフレーム長
     */
    double msFramePeriod() const;

    /*!
     *  @Override
     */
    const double *generate(double ms) const;

    /*!
     *  @Override
     */
    double msTimeLength() const;

    /*!
     *  @Override
     */
    int fftLength() const;

private:
    double _msFramePeriod;
    Specgram *_specgram;
};

#endif // GENERATORSPECGRAM_H
