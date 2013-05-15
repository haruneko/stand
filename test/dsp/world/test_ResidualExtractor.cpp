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

#include "dsp/Specgram.h"
#include "dsp/world/fft.h"
#include "dsp/world/ResidualExtractor.h"
#include "dsp/world/platinum.h"

// テスト用 FFT 長
const int FFT_LENGTH = 2048;


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

    //! @brief WORLD 内部関数を用いた動作確認
    void convertToComplexWithPatinumTest();

    //! @brief 励起信号スペクトル列から信号列が得られるか動作確認
    void extractTest();
};

ResidualExtractorTest::ResidualExtractorTest()
{
}

void ResidualExtractorTest::convertToComplexTest()
{
    fft_complex *src = new fft_complex[FFT_LENGTH / 2 + 1];
    fft_complex *dst = new fft_complex[FFT_LENGTH / 2 + 1];
    double *residual = new double[FFT_LENGTH];
    for(int i = 0; i <= FFT_LENGTH / 2; i++)
    {
        src[i][0] = rand() / (double)RAND_MAX;
        src[i][1] = rand() / (double)RAND_MAX;
    }
    src[0][1] = src[FFT_LENGTH / 2][1] = 0.0;

    residual[0] = src[0][0];
    for(int i = 1; i < FFT_LENGTH / 2; i++)
    {
        residual[i*2-1] = src[i][0];
        residual[i*2] = src[i][1];
    }
    residual[FFT_LENGTH - 1] = src[FFT_LENGTH / 2][0];

    ResidualExtractor::convertToComplex(dst, residual, FFT_LENGTH);

    for(int i = 0; i <= FFT_LENGTH / 2; i++)
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
    // すべての要素の実部 1.0, 虚部 0.0 である入力からフーリエ逆変換を計算する.
    fft_complex *fft_in = new fft_complex[FFT_LENGTH / 2 + 1];
    double *fft_out = new double[FFT_LENGTH];
    fft_plan p = fft_plan_dft_c2r_1d(FFT_LENGTH, fft_in, fft_out, FFT_BACKWARD);

    for(int i = 0; i <= FFT_LENGTH / 2; i++)
    {
        fft_in[i][0] = 1.0;
        fft_in[i][1] = 0.0;
    }

    fft_execute(p);

    // すべての要素の実部 1.0, 虚部 0.0 である WORLD 形式の入力からフーリエ逆変換を計算する.
    double *extract = new double[FFT_LENGTH];
    double *residual = new double[FFT_LENGTH];

    residual[0] = 1.0;
    for(int i = 1; i < FFT_LENGTH / 2; i++)
    {
        residual[i*2-1] = 1.0;
        residual[i*2] = 0.0;
    }
    residual[FFT_LENGTH-1] = 1.0;
    ResidualExtractor::extractOneFrame(extract, residual, FFT_LENGTH);

    // 比較する
    for(int i = 0; i < FFT_LENGTH; i++)
    {
        QCOMPARE(fft_out[i], extract[i]);
    }

    delete[] residual;
    delete[] extract;
    fft_destroy_plan(p);
    delete[] fft_in;
    delete[] fft_out;
}

void ResidualExtractorTest::convertToComplexWithPatinumTest()
{
    // 変数準備するよ！
    double *wave = new double[FFT_LENGTH];
    double *residual = new double[FFT_LENGTH];
    fft_complex *pulseSpectrum = new fft_complex[FFT_LENGTH];
    fft_complex *waveSpectrum = new fft_complex[FFT_LENGTH];
    fft_complex *extracted = new fft_complex[FFT_LENGTH];
    fft_plan p = fft_plan_dft_r2c_1d(FFT_LENGTH, wave, waveSpectrum, FFT_FORWARD);

    // 波形書くよ！
    for(int i = 0; i < FFT_LENGTH; i++)
    {
        wave[i] = rand() / (double)RAND_MAX;
    }

    // パルスのスペクトル書き込むよ！
    for(int i = 0; i <= FFT_LENGTH / 2; i++)
    {
        pulseSpectrum[i][0] = 1.0;
        pulseSpectrum[i][1] = 0.0;
    }

    // FFT だよ
    fft_execute(p);

    // WORLD からのコピペで residual を PLATINUM 形式で埋めるよ
    residual[0] = waveSpectrum[0][0] / pulseSpectrum[0][0];
    double tmp;
    for (int i = 0; i < FFT_LENGTH / 2 - 1; ++i) {
      tmp =                     pulseSpectrum[i + 1][0] * pulseSpectrum[i + 1][0] +
                                pulseSpectrum[i + 1][1] * pulseSpectrum[i + 1][1];
      residual[i * 2 + 1] = (   pulseSpectrum[i + 1][0] * waveSpectrum[i + 1][0] +
                                pulseSpectrum[i + 1][1] * waveSpectrum[i + 1][1]) / tmp;
      residual[i * 2 + 2] = (  -pulseSpectrum[i + 1][1] * waveSpectrum[i + 1][0] +
                                pulseSpectrum[i + 1][0] * waveSpectrum[i + 1][1]) / tmp;
    }
    residual[FFT_LENGTH - 1] = waveSpectrum[FFT_LENGTH / 2][0] / pulseSpectrum[FFT_LENGTH / 2][0];

    ResidualExtractor::convertToComplex(extracted, residual, FFT_LENGTH);

    QCOMPARE(extracted[0][0], waveSpectrum[0][0]);
    for(int i = 1; i < FFT_LENGTH / 2; i++)
    {
        QCOMPARE(extracted[i][0], waveSpectrum[i][0]);
        QCOMPARE(extracted[i][1], waveSpectrum[i][1]);
    }
    QCOMPARE(extracted[FFT_LENGTH / 2][0], waveSpectrum[FFT_LENGTH / 2][0]);

    fft_destroy_plan(p);
    delete[] residual;
    delete[] extracted;
    delete[] pulseSpectrum;
    delete[] waveSpectrum;
    delete[] wave;
}

void ResidualExtractorTest::extractTest()
{
    const int timeLength = 1000;
    Specgram residual(timeLength, FFT_LENGTH);
    Specgram wave(timeLength, FFT_LENGTH);

    double *fft_in = new double[FFT_LENGTH];
    fft_complex *fft_out = new fft_complex[FFT_LENGTH / 2 + 1];
    double *oneresidual = new double[FFT_LENGTH];
    fft_plan p = fft_plan_dft_r2c_1d(FFT_LENGTH, fft_in, fft_out, FFT_FORWARD);

    for(int i = 0; i < FFT_LENGTH; i++)
    {
        fft_in[i] = rand() / (double)RAND_MAX;
    }
    fft_execute(p);

    oneresidual[0] = fft_out[0][0];
    for(int i = 1; i < FFT_LENGTH / 2; i++)
    {
        oneresidual[i*2-1] = fft_out[i][0];
        oneresidual[i*2] = fft_out[i][1];
    }
    oneresidual[FFT_LENGTH - 1] = fft_out[FFT_LENGTH / 2][0];

    // residual 埋める！
    for(int t = 0; t < timeLength; t++)
    {
        for(int f = 0; f < FFT_LENGTH; f++)
        {
            residual[t][f] = oneresidual[f];
        }
    }

    // wave に展開
    ResidualExtractor::extract(&wave, &residual);

    // 最後に比較
    for(int t = 0; t < timeLength; t++)
    {
        for(int f = 0; f < FFT_LENGTH; f++)
        {
            // FFT を順→逆で通すと FFTSG の場合値が FFTLength　倍される。
            QCOMPARE(wave.value(t, f), fft_in[f] * FFT_LENGTH);
        }
    }

    fft_destroy_plan(p);
    delete[] fft_in;
    delete[] fft_out;
    delete[] oneresidual;
}

QTEST_APPLESS_MAIN(ResidualExtractorTest)

#include "test_ResidualExtractor.moc"
