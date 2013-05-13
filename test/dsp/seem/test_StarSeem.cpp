/*
 *
 *    test_StarSeem.cpp
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

#include "dsp/world/dio.h"
#include "dsp/world/star.h"

#include "dsp/Specgram.h"
#include "dsp/seem/StarSeem.h"
#include "dsp/ffem/DioFfem.h"

const double msFramePeriod = 2.0;

/*!
 *  @brief  StarSeem クラスの動作確認テスト.
 *          WORLD に実装された star_innner_ffem が計算する励起信号スペクトルと，
 *          StarSeem が計算する励起信号スペクトルが一致するか確認する．
 *  @author HAL@shurabaP
 */
class StarSeemTest : public QObject
{
    Q_OBJECT
private slots:
    void star_innner_ffem();
    void star_innner_ffem_data();

    void star_external_ffem();
    void star_external_ffem_data();
};


void StarSeemTest::star_innner_ffem_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << "data/test.wav";
}

void StarSeemTest::star_innner_ffem()
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
    specgram[0] = new double[timeLength * (fftLength / 2 + 1)];
    for(int i = 1; i < timeLength; i++)
    {
        specgram[i] = specgram[0] + i * (fftLength / 2 + 1);
    }

    Dio(c.data()[0], c.length(), c.format().sampleRate(), msFramePeriod, t, f0);
    Star(c.data()[0], c.length(), c.format().sampleRate(), msFramePeriod, f0, timeLength, specgram);
    /*=== WORLD による分析ここまで ===*/

    /*=== StarSeem による分析 === */
    Specgram *testset = new Specgram;
    QVERIFY2(StarSeem().estimate(testset, c.data()[0], c.length(), fftLength, c.format().sampleRate(), msFramePeriod), "Failed STAR SEEM");
    /*=== StarSeem による分析ここまで === */

    // 比較開始
    for(int t = 0; t < timeLength; t++)
    {
        for(int f = 0; f <= fftLength / 2; f++)
        {
            if(testset->value(t, f) != specgram[t][f])
            {
                QString s;
                s = "t = " + QString::number(t) + ", f = " + QString::number(f);
                s += " actual :" + QString::number(testset->data()[t][f]) + " , expceted :" + QString::number(specgram[t][f]);
                // WORLD 自体は同じだから値が全く同じでないとおかしい。
                QFAIL(("Error ;" + s).toUtf8().data());
            }
        }
    }

    delete[] specgram[0];
    delete[] specgram;
    delete[] t;
    delete[] f0;
}

void StarSeemTest::star_external_ffem_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << "data/test.wav";
}


void StarSeemTest::star_external_ffem()
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
    specgram[0] = new double[timeLength * (fftLength / 2 + 1)];
    for(int i = 1; i < timeLength; i++)
    {
        specgram[i] = specgram[0] + i * (fftLength / 2 + 1);
    }

    Dio(c.data()[0], c.length(), c.format().sampleRate(), msFramePeriod, t, f0);
    Star(c.data()[0], c.length(), c.format().sampleRate(), msFramePeriod, f0, timeLength, specgram);
    /*=== WORLD による分析ここまで ===*/

    /*=== StarSeem による分析 === */
    Envelope *e = new Envelope;
    QVERIFY2(DioFfem().estimate(e, c.data()[0], c.length(), c.format().sampleRate(), msFramePeriod), "Failed dio FFEM");
    // Envelope が正しいか確認する
    for(int i = 0; i < e->size(); i++)
    {
        QVERIFY2(e->value(i) == f0[i], "Error; invalid f0 envelope");
    }
    Specgram *testset = new Specgram;
    QVERIFY2(StarSeem(e).estimate(testset, c.data()[0], c.length(), fftLength, c.format().sampleRate(), msFramePeriod), "Failed STAR SEEM");
    /*=== StarSeem による分析ここまで === */

    // 比較開始
    for(int t = 0; t < timeLength; t++)
    {
        for(int f = 0; f <= fftLength / 2; f++)
        {
            if(testset->value(t, f) != specgram[t][f])
            {
                QString s;
                s = "t = " + QString::number(t) + ", f = " + QString::number(f);
                s += " actual :" + QString::number(testset->value(t, f)) + " , expceted :" + QString::number(specgram[t][f]);
                // WORLD 自体は同じだから値が全く同じでないとおかしい。
                QFAIL(("Error ;" + s).toUtf8().data());
            }
        }
    }

    delete[] specgram[0];
    delete[] specgram;
    delete[] t;
    delete[] f0;
}

QTEST_MAIN(StarSeemTest)
#include "test_StarSeem.moc"
