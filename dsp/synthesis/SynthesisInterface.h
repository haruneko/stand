/*
 *
 *    SynthesisInterface.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/13
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SYNTHESISINTERFACE_H
#define SYNTHESISINTERFACE_H

/*!
 *  @brief  ボコーダーの枠組みで合成を行うためのインターフェース
 *  @author HAL@shurabaP
 */
class SynthesisInterface
{
public:
    /*!
     *  @brief          1 フレーム分の合成を行います．
     *                  出力先である dst に対し与えられた情報から合成した波形を足し込むことで，
     *                  音声波形を合成します．
     *  @param[out] dst 書き込み先バッファ．
     *                  バッファにはあらかじめ前後の波形が書き込まれている可能性があるため，
     *                  出力する際には必ず足し算を行うようにして下さい．
     *  @param[in]  frameLength 1 フレームのサンプル長
     *  @param[in]  spectrum    該当フレームにおけるパワースペクトル
     *  @param[in]  residual    該当フレームにおける残差波形，もしくは非周期性指標などへのポインタ．
     */
    virtual void synthesize(double *dst, int frameLength, const double *spectrum, const double *residual) = 0;
};

#endif // SYNTHESISINTERFACE_H
