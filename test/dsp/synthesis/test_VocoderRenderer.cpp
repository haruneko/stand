/*
 *
 *    test_VocoderRenderer.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */


#include <QDir>
#include <QTest>

#include "dsp/AudioBuffer.h"
#include "io/audio/WaveWriter.h"

#include "dsp/synthesis/GeneratorEnvelope.h"
#include "dsp/synthesis/GeneratorSpecgram.h"
#include "dsp/synthesis/VocoderRenderer.h"
#include "dsp/synthesis/WorldSynthesis.h"

#include "dsp/ffem/DioFfem.h"
#include "dsp/seem/StarSeem.h"
#include "dsp/seem/PlatinumSeem.h"

#include "dsp/world/synthesis.h"

const double msFramePeriod = 2.0;
const int fftLength = 2048;

/*!
 *  @brief  VocoderRenderer クラスのテスト
 *  @author HAL@shurabaP
 */
class VocoderRendererTest : public QObject
{
    Q_OBJECT
private:
    QString errmsg(double, double, int);
private slots:
    void compareToWorld_data();
    void compareToWorld();
};

void VocoderRendererTest::compareToWorld_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << "data/test.wav";
}

void VocoderRendererTest::compareToWorld()
{
    QFETCH(QString, data);

    AudioBuffer c, dst;

    QVERIFY2(c.read(data), ("Failed reading test wave; " + data).toUtf8().data());

    //================================================== WORLD で分析
    GeneratorEnvelope f0;
    GeneratorSpecgram specgram(NULL, msFramePeriod);
    GeneratorSpecgram residual(NULL, msFramePeriod);

    DioFfem().estimate(&f0, c.data(0), c.length(), c.format().sampleRate(), msFramePeriod);
    StarSeem(&f0).estimate(&specgram, c.data(0), c.length(), fftLength, c.format().sampleRate(), msFramePeriod);
    PlatinumSeem(&f0, &specgram).estimate(&residual, c.data(0), c.length(), fftLength, c.format().sampleRate(), msFramePeriod);

    //================================================== 合成開始
    double *expected = new double[c.length()];
    for(int i = 0; i < c.length(); i++)
    {
        expected[i] = 0.0;
    }

    Synthesis(f0.data(), f0.size(), specgram.data(), residual.data(), fftLength, msFramePeriod, c.format().sampleRate(), c.length(), expected);
    QVERIFY(VocoderRenderer().render(&dst, c.format().sampleRate(), 0, c.msLength(), fftLength, &(WorldSynthesis(fftLength)), &f0, &specgram, &residual));

    //=================================================== 比較開始
    WaveWriter().write(&dst, data + ".out.wav");
    const double *rendered = dst.data(0);
    // 最後はゴミが入るかもわからんので
    for(int i = 0; i < c.length() - fftLength / 2 && i < dst.length() - fftLength / 2; i++)
    {
        QVERIFY2(qFuzzyCompare(rendered[i], expected[i]), errmsg(rendered[i], expected[i], i).toUtf8().data());
    }
}

QString VocoderRendererTest::errmsg(double r, double e, int i)
{
    QString s = "(rendered = " + QString::number(r) + ", expected = " + QString::number(e) + " at " + QString::number(i);
    return s;
}


QTEST_MAIN(VocoderRendererTest)
#include "test_VocoderRenderer.moc"
