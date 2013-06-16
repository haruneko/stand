#-------------------------------------------------
#
# Project created by QtCreator 2013-03-20T01:23:00
#
#-------------------------------------------------

QT       += core gui multimedia

Release:TARGET = Stand
Debug:TARGET = Standd

DESTDIR = ../lib/

TEMPLATE = lib
CONFIG += staticlib

SOURCES +=\
    utility/ToImage.cpp \
    utility/SpecgramColorPalette.cpp \
    dsp/Specgram.cpp \
    io/RiffFile.cpp \
    io/RiffChunk.cpp \
    io/audio/WaveWriter.cpp \
    io/audio/WaveReader.cpp \
    io/audio/AudioTrack.cpp \
    dsp/WindowFunctions.cpp \
    io/audio/helper/AudioHelper.cpp \
    dsp/seem/SeemInterface.cpp \
    dsp/seem/SimpleSeem.cpp \
    dsp/fftsg/fftsg.cpp \
    dsp/Envelope.cpp \
    dsp/world/tandem_ap.cpp \
    dsp/world/synthesis_ap.cpp \
    dsp/world/synthesis.cpp \
    dsp/world/star.cpp \
    dsp/world/platinum.cpp \
    dsp/world/matlabfunctions.cpp \
    dsp/world/fft.cpp \
    dsp/world/dio.cpp \
    dsp/world/common.cpp \
    dsp/seem/StarSeem.cpp \
    dsp/oscillator/AbstractSteadyOscillator.cpp \
    dsp/oscillator/OscillatorInterface.cpp \
    dsp/oscillator/SineOscillator.cpp \
    dsp/ffem/FfemInterface.cpp \
    dsp/ffem/DioFfem.cpp \
    dsp/seem/PlatinumSeem.cpp \
    dsp/world/ResidualExtractor.cpp \
    dsp/AudioBuffer.cpp \
    dsp/synthesis/VocoderRenderer.cpp \
    dsp/synthesis/VocoderInterface.cpp \
    utility/ExcitationColorPalette.cpp \
    dsp/synthesis/PitchGeneratorInterface.cpp \
    dsp/synthesis/SpectrumGeneratorInterface.cpp \
    dsp/synthesis/WorldSynthesis.cpp \
    dsp/synthesis/GeneratorSpecgram.cpp \
    dsp/synthesis/GeneratorEnvelope.cpp

HEADERS  += \
    utility/ToImage.h \
    utility/SpecgramColorPalette.h \
    dsp/Specgram.h \
    io/RiffFile.h \
    io/RiffChunk.h \
    io/audio/WaveWriter.h \
    io/audio/WaveReader.h \
    io/audio/AudioTrack.h \
    io/audio/helper/AudioHelper.h \
    dsp/WindowFunctions.h \
    dsp/seem/SeemInterface.h \
    dsp/seem/SimpleSeem.h \
    dsp/fftsg/fftsg.h \
    dsp/Envelope.h \
    dsp/world/tandem_ap.h \
    dsp/world/synthesis_ap.h \
    dsp/world/synthesis.h \
    dsp/world/star.h \
    dsp/world/platinum.h \
    dsp/world/matlabfunctions.h \
    dsp/world/fft.h \
    dsp/world/dio.h \
    dsp/world/constant_numbers.h \
    dsp/world/common.h \
    dsp/seem/StarSeem.h \
    dsp/oscillator/AbstractSteadyOscillator.h \
    dsp/oscillator/OscillatorInterface.h \
    dsp/oscillator/SineOscillator.h \
    dsp/ffem/FfemInterface.h \
    dsp/ffem/DioFfem.h \
    dsp/seem/PlatinumSeem.h \
    dsp/world/ResidualExtractor.h \
    io/audio/AudioBufferWriter.h \
    io/audio/AudioBufferReader.h \
    dsp/AudioBuffer.h \
    dsp/synthesis/VocoderRenderer.h \
    dsp/synthesis/VocoderInterface.h \
    utility/ExcitationColorPalette.h \
    dsp/synthesis/PitchGeneratorInterface.h \
    dsp/synthesis/SpectrumGeneratorInterface.h \
    dsp/synthesis/WorldSynthesis.h \
    dsp/synthesis/GeneratorSpecgram.h \
    dsp/synthesis/GeneratorEnvelope.h

