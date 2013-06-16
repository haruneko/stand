/*
 *
 *    AudioStream.cpp
 *                                    (c) HAL 2012
 *
 *  This class provides I/O functions for AudioDevice.
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "AudioStream.h"

#include <QIODevice>
#include <QByteArray>

using namespace stand::io::audio;

AudioStream::AudioStream(const QAudioFormat &format, QObject *parent) :
    QObject(parent)
{
    _output = NULL;
    _buffer = NULL;
    _device = NULL;
    _msBufferLength = MsMinimumBufferLength;
    _samplesBufferLength = 0;
    _samplesPosition = 0;
    setFormat(format);
}

AudioStream::~AudioStream()
{
    _destroy();
}

void AudioStream::_create()
{
    // お片づけするよ！
    _destroy();
    // 出力作るよ！
    _output = new QAudioOutput(_format, this);
    qint64 bytesBufferLength = _msBufferLength * _format.channelCount() * _format.sampleRate() * _format.sampleSize() / 8 / 1000;
    _output->setBufferSize(bytesBufferLength);
    _output->setNotifyInterval(_msBufferLength / 4); // 間隔はこれくらいでいいのだろうか．
    connect(_output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(_outputStateChanged(QAudio::State)));

    // バッファ作るよ！
    _samplesBufferLength = msBufferLength() * _format.sampleRate() / 1000;
    _buffer = new double*[_format.channelCount()];
    _buffer[0] = new double[_format.channelCount() * _samplesBufferLength];

    for(int i = 1; i < _format.channelCount(); i++)
    {
        _buffer[i] = _buffer[0] + i * _samplesBufferLength;
    }
}

void AudioStream::_destroy()
{
    stop();

    // メモリ解放
    delete _output;
    if(_buffer)
    {
        delete[] _buffer[0];
    }
    delete[] _buffer;
    // ゼロ初期化
    _output = NULL;
    _buffer = NULL;
    _device = NULL;
    _msBufferLength = MsMinimumBufferLength;
    _samplesBufferLength = 0;
    _samplesPosition = 0;
}

void AudioStream::setFormat(const QAudioFormat &format)
{
    if(_output && _output->state() != QAudio::StoppedState)
    {
        qWarning("AudioStream::setFormat(); // Called while output is running.");
        return;
    }
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    _format = format;
    qDebug("AudioStream::setFormat(); // show format info");
    qDebug(" channel count = %d", format.channelCount());
    qDebug(" Sample rate = %d[Hz]", format.sampleRate());
    qDebug(" Sample size = %d", format.sampleSize());
    qDebug(" Sample Type = %d", format.sampleType());
    qDebug(" Byte order = %d", format.byteOrder());
    qDebug(" codec = \"%s\"", format.codec().toUtf8().data());

    if(!info.isFormatSupported(format))
    {
        _format = info.nearestFormat(_format);
        qWarning("AudioStream::setFormat(); // Unsupported format");
        qWarning(" channel count = %d -> %d", format.channelCount(), format.channelCount());
        qWarning(" Sample rate = %d[Hz] -> %d[Hz]", format.sampleRate(), _format.sampleRate());
        qWarning(" Sample size = %d -> %d", format.sampleSize(), _format.sampleSize());
        qWarning(" Sample Type = %d -> %d", format.sampleType(), _format.sampleType());
        qWarning(" Byte order = %d -> %d", format.byteOrder(), _format.byteOrder());
        qWarning(" codec = \"%s\" -> \"%s\"", format.codec().toUtf8().data(), _format.codec().toUtf8().data());
    }

    if(_format.sampleType() != QAudioFormat::SignedInt)
    {
        qWarning("AudioDevice class supports only SignedInt type.");
        _format.setSampleType(QAudioFormat::SignedInt);
    }

    if(_format.isValid())
    {
        _msBufferLength = qMax(_msBufferLength, MsMinimumBufferLength);
        _create();
    }
}

void AudioStream::setBufferLength(qint64 msBufferLength)
{
    if(_output && _output->state() != QAudio::StoppedState)
    {
        qWarning("AudioStream::setBufferLength(); // Called while output is running.");
        return;
    }
    if(_output) // 出力デバイス作成済みのときはバッファサイズを変える．
    {
        _msBufferLength = qMax(msBufferLength, MsMinimumBufferLength);
        qint64 bytesBufferLength = _msBufferLength * _format.channelCount() * _format.sampleSize() / 8 / 1000;
        _output->setBufferSize(bytesBufferLength);
        _output->setNotifyInterval(_msBufferLength / 4);
    }
    else
    {
        _msBufferLength = msBufferLength;
        setFormat(_format);
    }
}

void AudioStream::start()
{
    if(!_output || _output->state() == QAudio::ActiveState)
    {
        return;
    }
    _samplesPosition = 0;
    _device = _output->start();
    _notified();
    connect(_output, SIGNAL(notify()), this, SLOT(_notified()));
}

void AudioStream::stop()
{
    if(!_output || _output->state() == QAudio::StoppedState)
    {
        return;
    }
    _samplesPosition = 0;
    _output->stop();
    disconnect(_output, SIGNAL(notify()), this, SLOT(_notified()));
    _device = NULL;
}

void AudioStream::seek(qint64 position)
{
    // 残ったバッファどうしようかねえ．
    _output->reset();
    _samplesPosition = position;
    _notified();
}

void AudioStream::_notified()
{
    if(!_device || !_output)
    {
        return;
    }

    // オーディオ用バッファに何サンプルの空きがあるか計算．
    qint64 freeSamples = _output->bytesFree() / _format.channelCount() / (_format.sampleSize() / 8);

    /*
    qDebug("AudioStream::_notified(); // %d samples set for buffer", _samplesBufferLength);
    qDebug(" free: %d bytes out of %ld bytes which means %d smaples.", _output->bytesFree(), _output->bufferSize(), freeSamples);
    qDebug(" Current state = %d, Current error = %d", _output->state(), _output->error());
    qDebug(" Current notify interval = %d ms.", _output->notifyInterval());
    */

    if(freeSamples <= 0)
    {
        return;
    }

    for(int i = 0; i < _format.channelCount(); i++)
    {
        for(int j = 0; j < freeSamples; j++)
        {
            _buffer[i][j] = 0.0;
        }
    }

    emit requireBuffer(_buffer, _format, _samplesPosition, freeSamples);

    _writeBuffer(freeSamples);

    _samplesPosition += freeSamples;
}

void AudioStream::_outputStateChanged(QAudio::State s)
{
    qDebug("AudioStream::outputStateChanged(%d);", s);
    qDebug(" Current state = %d, Current error = %d", _output ? _output->state() : -1, _output ? _output->error() : -1);
    if(s != QAudio::ActiveState)
    {
        qint64 bytesBufferLength = _msBufferLength * _format.channelCount() * _format.sampleRate() * _format.sampleSize() / 8 / 1000;
        _output->setBufferSize(bytesBufferLength);
    }
}

void AudioStream::_writeBuffer(qint64 length)
{
    switch(_format.sampleSize())
    {
    case 8:
        _writeBuffer8(length);
        break;
    case 16:
        _writeBuffer16(length);
        break;
    case 32:
        _writeBuffer32(length);
        break;
    default:
        qFatal("AudioStram::_writeBuffer(); // Unknown sample size; %d", _format.sampleSize());
    }
}

void AudioStream::_writeBuffer8(qint64 length)
{
    int size = length * _format.channelCount();
    char *buf = new char[size];

    int c = 0;
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < _format.channelCount(); j++)
        {
            // Signed にしても結局 Unsigned 扱いになる(Windows 7)
            buf[c] = 128 + _buffer[j][i] * 127;
            c++;
        }
    }

    qint64 l;
    l = _device->write(buf, size);
    delete[] buf;
}

void AudioStream::_writeBuffer16(qint64 length)
{
    int size = length * _format.channelCount();
    short *buf = new short[size];

    int c = 0;
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < _format.channelCount(); j++)
        {
            buf[c] = (short)(_buffer[j][i] * 32767);
            c++;
        }
    }

    _device->write((char *)buf, size * 2);
    delete[] buf;
}

void AudioStream::_writeBuffer32(qint64 length)
{
    int size = length * _format.channelCount();
    int *buf = new int[size];

    int c = 0;
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < _format.channelCount(); j++)
        {
            buf[c] = _buffer[j][i] * 2147483647;
            c++;
        }
    }

    _device->write((char *)buf, size * 4);
    delete[] buf;
}

