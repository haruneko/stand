/*
 *
 *    Specgram.h
 *                                    (c) HAL@shurabaP
 *                                        2013/03/21
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef SPECGRAM_H
#define SPECGRAM_H

/*!
 *  @brief スペクトログラムを保持するデータクラスです。メモリの確保と解放を担当します。
 *  @author HAL@shurabaP
 */
class Specgram
{
public:
    Specgram(int frameLength = 0, int frequencyLength = 0);
    virtual ~Specgram();

    /*!
     *  @brief 与えられた条件でメモリを確保します。
     *  @param[in] frameLength 総フレーム数
     *  @param[in] frequencyLength FFT 長
     */
    void alloc(int frameLength, int frequencyLength);

    /*!
     *  @brief データが正しく格納されているか確認します。
     */
    bool isValid() const;

    /*!
     *  @brief t フレームにおける f 番目の値を val に変更します。
     *  @attention 配列外アクセスをチェックしません。
     */
    void setValue(double val, int t, int f);

    /*!
     *  @brief t フレームにおける f 番目の値を返します。
     *  @attention 配列外アクセスをチェックしません。
     */
    double value(int t, int f) const;

    /*!
     *  @brief データを表すダブルポインタを返します。
     */
    const double * const *data() const;

    /*!
     *  @brief データに直接アクセスします。
     */
    double *operator[] (int t);

    /*!
     *  @brief スペクトルのフレーム数を返します。
     *  @return スペクトルのフレーム数
     */
    int frameLength() const;

    /*!
     *  @brief 周波数方向の要素数を帰します．
     */
    int frequencyLength() const;

    inline double **pointer()
    {
        return _data;
    }

private:    // private methods
    Specgram(const Specgram &);                 //! @brief コピーコンストラクタの禁止
    Specgram operator = (const Specgram &);     //! @brief 代入演算子の禁止
    void _destroy();

private:    // private members
    double **_data;

    int _frameLength;
    int _frequencyLength;
};

#endif // SPECGRAM_H
