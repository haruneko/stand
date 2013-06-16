/*
 *
 *    RiffChunk.h
 *                                    (c) HAL@shurabaP
 *                                        2013/03/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __RIFFCHUNK_h__
#define __RIFFCHUNK_h__

/*!
 *  @brief RIFF ファイルのチャンクを扱うクラスです。
 *  @note このクラスはデータの実体を持ちません。参照先のデータが解放されるとエラーになります。
 *  @author HAL@shurabaP
 */
class RiffChunk
{
public:
    /*!
     *  @brief チャンクを設定します。
     *  @param[in] h ヘッダ文字列。
     *  @param[in] p データ開始位置へのポインタ。
     *  @param[in] length データ長
     *  @note ヘッダはコピーされますがデータはコピーされません。
     */
    RiffChunk(const char *h = 0, const char *p = 0, int length = 0);

    /*!
     *  @brief チャンクを設定します。
     *  @param[in] h ヘッダ文字列。
     *  @param[in] p データ開始位置へのポインタ。
     *  @param[in] length データ長
     *  @note ヘッダはコピーされますがデータはコピーされません。
     */
    void set(const char *h, const char *p, int length);

    /*!
     *  @brief チャンク名を比較します。
     *  @param[in] s 比較対象のチャンク名
     *  @return 与えられたチャンク名が一致しているかどうか。
     */
    bool is(const char *s) const;

    const char *data() const
    {
        return _p;
    }

    const char *header() const
    {
        return _header;
    }

    /*!
     *  @brief データのバイト長を返します。
     */
    int length() const
    {
        return _length;
    }

private:
    char _header[5];
    const char *_p;
    int _length;
};

#endif
