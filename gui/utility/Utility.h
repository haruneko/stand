/*
 *
 *    Utility.h
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef STAND_GUI_UTILITY_H
#define STAND_GUI_UTILITY_H

#include <QDir>
#include <QColor>

class QWidget;

/*!
 * @brief ディレクトリを作成します．作成したいディレクトリがある場合は何もしません．
 * @param[in] w エラー時，メッセージを出すウィジェット．
 * @param[in] dir 作成したいディレクトリパス．
 * @param[in] confirm 指定したパスが存在しない場合作成の許可をユーザに求めるかどうかのフラグ．
 * @returns true: 作成が成功したか，ディレクトリが存在した． false: ディレクトリが存在せず作成もできなかった．
 */
bool makeDirectory(QWidget *w, const QDir &dir, bool confirm = false);

/*!
 * @brief ノート番号が黒鍵であるかどうかを調べます．
 */
bool IsBlackKey(unsigned char note);

/*!
 * @brief ノート番号に対応する文字列を返します．
 */
QString NoteName(unsigned char note);

/*!
 * @brief ノート番号に対応する周波数を返します．（ノート番号を実数指定する版）
 */
double NoteFrequency(double note);

/*!
 * @brief 周波数に対応するノート番号を返します．
 * @note 戻り値のノート番号は小数点以下を含みます．
 */
double NoteAt(double frequency);

/*!
 *  @brief 色を r : 1-r の割合で混ぜ合わせます．
 */
QColor mixColor(const QColor &a, const QColor &b, double r);

#endif // STAND_GUI_UTILITY_H
