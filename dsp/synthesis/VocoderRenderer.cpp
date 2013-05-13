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
#include "../Envelope.h"
#include "../Specgram.h"

#include "VocoderInterface.h"

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

bool VocoderRenderer::render(AudioBuffer *dst, int samplingFrequency, const Envelope *f0, const Specgram *specgram, const Specgram *residual, double msFramePeriod, VocoderInterface *vocoder)
{
    if(!dst || !f0 || specgram || !residual || !vocoder)
    {
        qDebug("VocoderRenderer::render(); // invalid args.");
        return false;
    }
    if(f0->size() != specgram->frameLength() || specgram->frameLength() != residual->frameLength())
    {
        qDebug("VocoderRenderer::render(); // invalid sized parameters");
        return false;
    }

    _prepareBuffer(dst, samplingFrequency, specgram->frameLength() * msFramePeriod);

    // TODO: render wave.

    return true;
}
