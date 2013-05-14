/*
 *
 *    test_ResidualExtractor.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/14
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include "dsp/world/fft.h"
#include "dsp/world/ResidualExtractor.h"

class ResidualExtractorTest : public QObject
{
    Q_OBJECT
    
public:
    ResidualExtractorTest();
    
private Q_SLOTS:
    //! @brief 実数列から複素数へ変換する機能のテスト
    void convertToComplexTest();

    //! @brief パルス波を使った FFT の比較テスト
    void checkPulseFFTTest();
};

ResidualExtractorTest::ResidualExtractorTest()
{
}

void ResidualExtractorTest::convertToComplexTest()
{
    int fftLength = 2048;
    fft_complex *src = new fft_complex[fftLength / 2 + 1];
    fft_complex *dst = new fft_complex[fftLength / 2 + 1];
    double *residual = new double[fftLength];
    for(int i = 0; i <= fftLength / 2; i++)
    {
        src[i][0] = rand() / (double)RAND_MAX;
        src[i][1] = rand() / (double)RAND_MAX;
    }
    src[0][1] = src[fftLength / 2][1] = 0.0;

    residual[0] = src[0][0];
    for(int i = 1; i < fftLength / 2; i++)
    {
        residual[i*2-1] = src[i][0];
        residual[i*2] = src[i][1];
    }
    residual[fftLength - 1] = src[fftLength / 2][0];

    ResidualExtractor::convertToComplex(dst, residual, fftLength);

    for(int i = 0; i <= fftLength / 2; i++)
    {
        QCOMPARE(src[i][0], dst[i][0]);
        QCOMPARE(src[i][1], dst[i][1]);
    }

    delete[] src;
    delete[] dst;
    delete[] residual;
}

void ResidualExtractorTest::checkPulseFFTTest()
{
    int fftLength = 2048;

    // すべての要素の実部 1.0, 虚部 0.0 である入力からフーリエ逆変換を計算する.
    fft_complex *fft_in = new fft_complex[fftLength / 2 + 1];
    double *fft_out = new double[fftLength];
    fft_plan p = fft_plan_dft_c2r_1d(fftLength, fft_in, fft_out, FFT_BACKWARD);

    for(int i = 0; i <= fftLength / 2; i++)
    {
        fft_in[i][0] = 1.0;
        fft_in[i][1] = 0.0;
    }

    fft_execute(p);

    // すべての要素の実部 1.0, 虚部 0.0 である WORLD 形式の入力からフーリエ逆変換を計算する.
    double *extract = new double[fftLength];
    double *residual = new double[fftLength];

    residual[0] = 1.0;
    for(int i = 1; i < fftLength / 2; i++)
    {
        residual[i*2-1] = 1.0;
        residual[i*2] = 0.0;
    }
    residual[fftLength-1] = 1.0;
    ResidualExtractor::extractOneFrame(extract, residual, fftLength);

    // 比較する
    for(int i = 0; i < fftLength; i++)
    {
        QCOMPARE(fft_out[i], extract[i]);
    }

    delete[] residual;
    delete[] extract;
    fft_destroy_plan(p);
    delete[] fft_in;
    delete[] fft_out;
}

QTEST_APPLESS_MAIN(ResidualExtractorTest)

#include "test_ResidualExtractor.moc"
