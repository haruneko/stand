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

#include "../world/matlabfunctions.h"

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
                                int fftLength,
                                VocoderInterface *vocoder,
                                PitchGeneratorInterface *pitch,
                                SpectrumGeneratorInterface *specgram,
                                SpectrumGeneratorInterface *residual)
{
    int fs = dst->format().sampleRate();
    double *buffer = dst->data()[0];

    double ms = msBegin;
    double msForUnvoicedFrame = vocoder->msForUnvoicedFrame();
    while(ms < msEnd)
    {
        int index = matlab_round(fs * ms / 1000.0);
        double f0 = pitch->generate(ms);
        const double *s = specgram->generate(ms);
        const double *r = residual->generate(ms);
        // 長さを丸めておく
        int length = (index + fftLength < dst->length()) ? fftLength : (dst->length() - index);
        vocoder->synthesize(buffer + index, length, fftLength, s, r);

        // f0 == 0 のときは無声音として扱う.
        ms += (f0 != 0) ? 1000.0 / f0 : msForUnvoicedFrame;
    }
}

bool VocoderRenderer::render(AudioBuffer *dst,
                             int samplingFrequency,
                             double msBegin,
                             double msEnd,
                             int fftLength,
                             VocoderInterface *vocoder,
                             PitchGeneratorInterface *pitch,
                             SpectrumGeneratorInterface *specgram, SpectrumGeneratorInterface *residual)
{
    if(!dst || !pitch || !specgram || !residual || !vocoder)
    {
        qDebug("VocoderRenderer::render(); // invalid args.");
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
    _render(dst, msBegin, msEnd, fftLength, vocoder, pitch, specgram, residual);

    return true;
}
