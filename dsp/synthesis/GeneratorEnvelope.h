/*
 *
 *    GeneratorEnvelope.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef GENERATORENVELOPE_H
#define GENERATORENVELOPE_H

#include "../Envelope.h"
#include "PitchGeneratorInterface.h"

/*!
 *  @brief  Envelope クラスを用いた PitchGeneratorInterface の実装です．
 *          外部から与えられた Envelope クラス，または自分自身を用いてデータを生成します．
 */
class GeneratorEnvelope : public Envelope, public PitchGeneratorInterface
{
public:
    /*!
     *  @brief  外部からデータを与えて初期化します．
     *          NULL が与えられた場合自分自身のデータを使用します．
     */
    GeneratorEnvelope(Envelope *pitch = 0);

    /*!
     *  @brief  外部から与えられるデータを設定します．
     *          NULL が与えられた場合自分自身のデータを使用します．
     */
    void setEnvelope(Envelope *pitch);

    /*!
     *  @Override
     */
    double generate(double ms);

    /*!
     *  @Override
     */
    double msTimeLength() const;

private:
    Envelope *_pitch;
};

#endif // GENERATORENVELOPE_H
