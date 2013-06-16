#include "AudioRenderer.h"

using namespace stand::io::audio;

AudioRenderer::AudioRenderer(int sampleRate, int samplesLength, const QAudioFormat &format, QObject *parent) :
    AudioChunk(0, samplesLength, format, parent)
{
    _sampleRate = sampleRate;
}

AudioRenderer::~AudioRenderer()
{
}

void AudioRenderer::render()
{
    setReadiness(false);

    for(int i = 0; i < samplesLength() * format().channelCount(); i++)
    {
        buffer()[0][i] = 0.0;
    }
    emit requireBuffer(buffer(), format(), samplesPosition(), samplesLength());

    setReadiness(true);
}
