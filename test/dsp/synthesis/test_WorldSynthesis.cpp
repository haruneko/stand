/*
 *
 *    test_WorldSynthesis.cpp
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

#include "dsp/synthesis/WorldSynthesis.h"

const int fftLength = 2048;

/*!
 *  @brief  WorldSynthesis クラスの動作確認テスト.
 *  @author HAL@shurabaP
 */
class WorldSynthesisTest : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();

    // spectrum, residual にパルスのスペクトルを与えたときにパルスが出てくるか．
    void checkPulse();

private:
    double *dst;
    double *spectrum;
    double *residual;
};

void WorldSynthesisTest::init()
{
    dst = new double[fftLength];
    spectrum = new double[fftLength];
    residual = new double[fftLength];
    for(int i = 0; i < fftLength; i++)
    {
        dst[i] = 0.0;
    }
}

void WorldSynthesisTest::cleanup()
{
    delete[] dst;
    delete[] spectrum;
    delete[] residual;
}

void WorldSynthesisTest::checkPulse()
{
    for(int i = 0; i < fftLength; i++)
    {
        spectrum[i] = 1.0;
    }

    residual[0] = 1.0;
    for(int i = 1; i < fftLength / 2; i++)
    {
        residual[2*i-1] = 1.0;
        residual[2*i] = 0.0;
    }
    residual[fftLength - 1] = 1.0;

    WorldSynthesis synth(fftLength);

    synth.synthesize(dst, fftLength, spectrum, residual);

    // 一つ目だけは値が入る．
    QCOMPARE(dst[0], 1.0);
    for(int i = 1; i < fftLength; i++)
    {
        // 残りは 0 にならないとおかしい．
        QCOMPARE(dst[i], 0.0);
    }
}



QTEST_MAIN(WorldSynthesisTest)
#include "test_WorldSynthesis.moc"
