/*
 *
 *    RiffFile.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/03/27
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <QtGlobal>

#include "RiffFile.h"

RiffFile::RiffFile(const char *path)
{
    data = NULL;
    _size = 0;
    if(path)
    {
        read(path);
    }
}

RiffFile::~RiffFile(void)
{
    _destroy();
}

void RiffFile::_destroy()
{
    delete[] data;
    data = NULL;
    chunks.clear();
    for(int i = 0; i < 5; i++)
    {
        header[i] = 0;
    }
}

bool RiffFile::read(const char *path)
{
    // ぬるぽがっ
    if(!path)
    {
        qDebug("RiffFile::read(NULL);");
        return false;
    }

    // open file.
    FILE *fp = fopen(path, "rb");
    if(!fp)
    {
        qDebug("RiffFile::read(%s); // File not found.", path);
        return false;
    }
    int32_t size = 0;
    _destroy();

    // is RIFF format ?
    fread(header, 4, sizeof(char), fp);
    if(strcmp(header, "RIFF") != 0)
    {
        qDebug("RiffFile::read(%s); // This file is not RIFF file.", path);
        fclose(fp);
        return false;
    }

    // get total size of the file.
    fread(&size, 1, sizeof(int32_t), fp);
    if(size <= 0)
    {
        qDebug("RiffFile::read(%s); // File size (%d bytes) is invalid.", path, size);
        fclose(fp);
        return false;
    }
    _size = size;
    data = new char[size];

    // read all data.
    int readSize;
    if(size != (readSize = fread(data, sizeof(char), size, fp)))
    {
        qDebug("RiffFile::read(%s); // File size(%d bytes) is invalid.", path, size);
        qDebug(" Actual size = %d, read buffer size = %d.", readSize, size);
        qDebug(" This may cause an error.");
        size = readSize;
//        fclose(fp);
//        return false;
    }
    fclose(fp);

    // set chunks
    int i;
    for(i = 0; i < 4; i++)
    {
        header[i] = data[i];
    }

    while(size - i >= 8)
    {
        // ToDo:: set chunk
        char *p = &(data[i]);
        int32_t l;
        memcpy(&l, &(data[i + 4]), sizeof(int32_t));
        if(i + l + 8 > size)
        {
            qDebug("RiffFile::read(%s); // File size(%d bytes) is invalid.", path, size);
            qDebug(" Current position = %d, size = %d.", i + l + 8, size);
            qDebug(" This may cause an error.");
        }
        RiffChunk c(p, p + 8, l);
        chunks.push_back(c);
        i += l + 8;
    }

    return true;
}

bool RiffFile::is(const char *s) const
{
    bool ret = true;
    for(int i = 0; i < 4; i++)
    {
        ret &= (header[i] == s[i]);
    }
    return ret;
}

const RiffChunk *RiffFile::chunk(const char *s) const
{
    const RiffChunk *c = NULL;
    for(unsigned int i = 0; i < chunks.size(); i++)
    {
        if(chunks[i].is(s))
        {
            c = &chunks[i];
            break;
        }
    }
    return c;
}

