/*
 *
 *    RiffFile.h
 *                                    (c) HAL@shurabaP
 *                                        2013/03/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef __RIFFFILE_H__
#define __RIFFFILE_H__

#include <vector>

#include "RiffChunk.h"

/*!
 *  @brief RIFF ファイルのデータを保持するクラスです。
 *  @author HAL@shurabaP
 */
class RiffFile
{
public:
    /*!
     *  @brief パスを指定してデータを読み込みます。
     */
    RiffFile(const char *path = 0);
    ~RiffFile();

    /*!
     *  @brief パスを指定してデータを読み込みます。
     *  @param[in] path ファイルパス。
     *  @return 読み込みの成否。
     */
    bool read(const char *path);

    /*!
     *  @brief RIFF　ファイルの種別を確認します。
     *  @param[in] s ヘッダ名。
     *  @return 保持しているヘッダ名が与えられたヘッダ名と等しいかどうか。
     */
    bool is(const char *s) const;

    inline int size() const
    {
        return _size;
    }

    /*!
     *  @brief 指定されたヘッダに対応すチャンクを返します。
     *  @param[in] s 検索したいチャンク名。
     *  @return 対応するチャンクへのポインタ。
     *  @retval NULL 存在しないヘッダ名の場合 NULL を返します。
     */
    const RiffChunk *chunk(const char *s) const;

private:
    void _destroy();
    char *data;
    char header[5];
    int _size;
    std::vector<RiffChunk> chunks;
};

#endif
