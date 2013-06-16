#include <iostream>

#include "dsp/Specgram.h"
#include "dsp/seem/SimpleSeem.h"
#include "dsp/AudioBuffer.h"
#include "io/audio/WaveReader.h"
#include "utility/ToImage.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "usage; SimpleSpecgram [input path]" << std::endl;
        return -1;
    }

    AudioBuffer b;
    if(!WaveReader().read(&b, argv[1]))
    {
        std::cout << argv[1] << " is not WAVE file." << std::endl;
        return -1;
    }

    Specgram s;
    SimpleSeem().estimate(&s, b.data()[0], b.length(), 2048, b.format().sampleRate(), 2.0);
    ToImage::fromSpecgram(&s).save(QString(argv[1]) + ".png");

    return 0;
}

