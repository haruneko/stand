/*
 *
 *    Envelope.h
 *                                    (c) HAL@shurabaP
 *                                        2013/05/04
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <QtGlobal>

/*!
 *  @brief エンベロープを保存するクラスです．
 *  @author HAL@shurabaP
 */
class Envelope
{
public:
    /*!
     *  @brief 与えられたデータで初期化します．
     *  @param[in] data エンベロープを格納した配列．
     *  @param[in] size 配列サイズ．
     *  @param[in] msFramePeriod index 1 つ分に対応する時間長[ms]
     *  @param[in] autodelete このクラスが保持する配列を廃棄時に削除してよいかどうか．
     */
    explicit Envelope(double *data = 0, int size = 0, double msFramePeriod = 0, bool autodelete = false);

    /*!
     *  @brief autodelete が true のとき，デストラクタでは保持している配列が解放されます．
     */
    virtual ~Envelope();

    /*!
     *  @brief 保持しているデータを返します．
     */
    const double *data() const;

    /*!
     *  @brief 配列のインデックス 1 つ分に対応する時間長をミリ秒単位で返します．
     */
    double msFramePeriod() const;

    /*!
     *  @brief 与えられた位置の値を返します．
     *  @param[in] 値を得たい位置．
     */
    double value(double ms) const;

    /*!
     *  @overload
     *  @brief インデックスで得たい位置を指定して値を得ます．
     *  @param[in] 値を得たいインデックス
     */
    double value(int index) const;

    /*!
     *  @brief 内部の配列サイズを返します．
     */
    int size() const;

    /*!
     *  @brief 包絡全体の時間長をミリ秒単位で返します．
     */
    double msLength() const;

    /*!
     *  @brief 与えられたデータで初期化します．
     *  @param[in] data エンベロープを格納した配列．
     *  @param[in] size 配列サイズ．
     *  @param[in] msFramePeriod index 1 つ分に対応する時間長[ms]
     *  @param[in] autodelete このクラスが保持する配列を廃棄時に削除してよいかどうか．
     */
    void set(double *data, int size, double msFramePeriod, bool autodelete = false);

    inline double &operator[](int index)
    {
        if(!_data)
        {
            return _defaultValue;
        }

        index = qMax(0, qMin(index, _size - 1));

        return _data[index];
    }

private:
    void _destroy();
    double *_data;
    double _msFramePeriod;
    qint32 _size;
    bool _autodelete;
    double _defaultValue;
};

#endif // ENVELOPE_H
