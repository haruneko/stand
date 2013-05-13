/*
 *
 *    fftsg.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/01
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef FFTSG_H
#define FFTSG_H

/*!
 *  @file fftsg.h
 *  @brief FFTSG を使うためのヘッダファイルです．
 *  @author HAL@shurabaP
 */

/*!
 *  @brief 離散フーリエ変換．入力バッファは破壊されます．
 *  @param[in] n 要素数
 *  @param[in] isgn FFTの方向． 1 でフーリエ変換， -1 で逆フーリエ変換．
 *  @param[in/out] a 入出力用バッファ．
 *  @param[in] ip インデックス用バッファ．
 *  @param[in] w 作業用バッファ
 */
void cdft(int n, int isgn, double *a, int *ip, double *w);
void rdft(int n, int isgn, double *a, int *ip, double *w);
void ddct(int n, int isgn, double *a, int *ip, double *w);
void ddst(int n, int isgn, double *a, int *ip, double *w);
void dfct(int n, double *a, double *t, int *ip, double *w);
void dfst(int n, double *a, double *t, int *ip, double *w);

const int FFTSG_FORWARD = 1;
const int FFTSG_BACKWARD = -1;

#endif // FFTSG_H
