/*
 *
 *    test_PlatinumSeem.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/11
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include <QDir>
#include <QTest>

#include "dsp/AudioBuffer.h"

#include "dsp/Envelope.h"

#include "dsp/world/dio.h"
#include "dsp/world/star.h"
#include "dsp/world/platinum.h"
#include "dsp/world/constant_numbers.h"

#include "dsp/Specgram.h"
#include "dsp/seem/PlatinumSeem.h"


const double msFramePeriod = 2.0;

/*!
 *  @brief  PlatinumSeem クラスの動作確認テスト.
 *          WORLD に実装された PLATINUM が計算する励起信号スペクトルと，
 *          PlatinumSeem が計算する励起信号スペクトルが一致するか確認する．
 *  @author HAL@shurabaP
 */
class PlatinumSeemTest : public QObject
{
    Q_OBJECT
private slots:
    void platinum();
    void platinum_data();
};


void PlatinumSeemTest::platinum()
{
    QFETCH(QString, data);

    AudioBuffer c;

    QVERIFY2(c.read(data), ("Failed reading test wave; " + data).toUtf8().data());

    /*=== WORLD による分析 ===*/
    int timeLength = GetSamplesForDIO(c.format().sampleRate(), c.length(), msFramePeriod);
    int fftLength = GetFFTSizeForStar(c.format().sampleRate());
    double *f0 = new double[timeLength];
    double *t = new double[timeLength];
    double **specgram = new double*[timeLength];
    double **residual = new double*[timeLength];
    specgram[0] = new double[timeLength * (fftLength / 2 + 1)];
    residual[0] = new double[timeLength * fftLength];
    for(int i = 1; i < timeLength; i++)
    {
        specgram[i] = specgram[0] + i * (fftLength / 2 + 1);
        residual[i] = residual[0] + i * fftLength;
    }

    Dio(c.data(0), c.length(), c.format().sampleRate(), msFramePeriod, t, f0);
    Star(c.data(0), c.length(), c.format().sampleRate(), msFramePeriod, f0, timeLength, specgram);
    Platinum(c.data(0), c.length(), c.format().sampleRate(), t, f0, timeLength, specgram, fftLength, residual);
    /*=== WORLD による分析ここまで ===*/

    /*=== PlatinumSeem による分析 === */
    Specgram *testset = new Specgram;
    QVERIFY2(PlatinumSeem().estimate(testset, c.data(0), c.length(), fftLength, c.format().sampleRate(), msFramePeriod), "Failed platinum SEEM");
    /*=== PlatinumSeem による分析ここまで === */

    // 比較開始
    for(int t = 0; t < timeLength; t++)
    {
        // 最後の方の値は乱数が入っているので。
        if(t * msFramePeriod /1000.0 * c.format().sampleRate() + fftLength / 2 > c.length())
        {
            break;
        }
        for(int f = 0; f < fftLength; f++)
        {
            if(testset->value(t, f) != residual[t][f])
            {
                QString s;
                s = "t = " + QString::number(t) + ", f = " + QString::number(f);
                s += " actual :" + QString::number(testset->data()[t][f]) + " , expceted :" + QString::number(residual[t][f]);
                QFAIL(("Error ;" + s).toUtf8().data());
            }
        }
    }

    delete[] residual[0];
    delete[] residual;
    delete[] specgram[0];
    delete[] specgram;
    delete[] t;
    delete[] f0;
}

void PlatinumSeemTest::platinum_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << "data/test.wav";
}

QTEST_MAIN(PlatinumSeemTest)
#include "test_PlatinumSeem.moc"
