/*
 *
 *    test_DioFfem.cpp
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

#include "dsp/Envelope.h"
#include "dsp/ffem/DioFfem.h"

class DioFfemTest : public QObject
{
    Q_OBJECT
private slots:
    void dio();
    void dio_data();
};

void DioFfemTest::dio()
{
    QFETCH(QString, data);

    AudioBuffer c;

    QVERIFY2(c.read(data), ("Failed reading test wave; " + data).toUtf8().data());

    /*=== WORLD による分析 ===*/
    int timeLength = GetSamplesForDIO(c.format().sampleRate(), c.length(), 2.0);
    double *f0 = new double[timeLength];
    double *time = new double[timeLength];

    Dio(c.data()[0], c.length(), c.format().sampleRate(), 2.0, time, f0);
    /*=== WORLD による分析ここまで ===*/

    /*=== DioFfem による分析 === */
    Envelope *e = new Envelope;
    QVERIFY2(DioFfem().estimate(e, c.data()[0], c.length(), c.format().sampleRate(), 2.0), "Failed dio FFEM");
    /*=== DioFfem による分析ここまで === */
    // 比較開始
    for(int t = 0; t < timeLength; t++)
    {
        QString s;
        s = "t = " + QString::number(t);
        // WORLD 自体は同じだから値が全く同じでないとおかしい。
        QVERIFY2(e->value(t) == f0[t], ("Error; " + s).toUtf8().data());
    }
    delete[] time;
    delete[] f0;
}

void DioFfemTest::dio_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << "data/test.wav";
}

QTEST_MAIN(DioFfemTest)
#include "test_DioFfem.moc"
