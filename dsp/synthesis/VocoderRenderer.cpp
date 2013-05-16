/*
 *
 *    VocoderRenderer.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/14
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QAudioFormat>

#include "../AudioBuffer.h"

#include "VocoderInterface.h"
#include "PitchGeneratorInterface.h"
#include "SpectrumGeneratorInterface.h"

#include "VocoderRenderer.h"

void VocoderRenderer::_prepareBuffer(AudioBuffer *dst, int samplingFrequency, double msLength)
{
    QAudioFormat format;
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setSampleRate(samplingFrequency);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);

    // alloc buffer
    dst->setFormat(format);
    dst->setMsLength(msLength);

    // clear buffer
    for(int i = 0; i < dst->length(); i++)
    {
        dst->data()[0][i] = 0;
    }

}

void VocoderRenderer::_render(AudioBuffer *dst,
                                double msBegin,
                                double msEnd,
                                VocoderInterface *vocoder,
                                PitchGeneratorInterface *pitch,
                                SpectrumGeneratorInterface *specgram,
                                SpectrumGeneratorInterface *residual)
{
    int fs = dst->format().sampleRate();
    double *buffer = dst->data()[0];
    int fftLength = specgram->fftLength();

    double ms = msBegin;
    while(ms < msEnd)
    {
        int index = fs * ms / 1000.0;
        double f0 = pitch->generate(ms);
        const double *s = specgram->generate(ms);
        const double *r = residual->generate(ms);
        vocoder->synthesize(buffer + index, fftLength, s, r);

        // f0 == 0 のときは無声音として扱う.
        ms += (f0 != 0) ? 1000.0 / f0 : vocoder->msecForUnvoicedFrame();
    }
}

bool VocoderRenderer::render(AudioBuffer *dst,
                             int samplingFrequency,
                             double msBegin,
                             double msEnd,
                             VocoderInterface *vocoder,
                             PitchGeneratorInterface *pitch,
                             SpectrumGeneratorInterface *specgram, SpectrumGeneratorInterface *residual)
{
    if(!dst || !pitch || specgram || !residual || !vocoder)
    {
        qDebug("VocoderRenderer::render(); // invalid args.");
        return false;
    }
    if(specgram->fftLength() != residual->fftLength())
    {
        qDebug("VocoderRenderer::render(); // invalid fft size for spectrum and residual");
        return false;
    }

    msEnd = qMin(pitch->msTimeLength(), qMin(specgram->msTimeLength(), qMin(residual->msTimeLength(), msEnd)));

    // 合成区間が存在しない.
    if(msEnd < msBegin)
    {
        qDebug("VocoderRenderer::render(); // invalid output range; %e ms to %e ms", msBegin, msEnd);
        return false;
    }

    _prepareBuffer(dst, samplingFrequency, msEnd - msBegin);

    // TODO: render wave.
    _render(dst, msBegin, msEnd, vocoder, pitch, specgram, residual);

    return true;
}
