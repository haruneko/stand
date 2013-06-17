/*
 *
 *    test_Utility.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/06/17
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include "utility/Utility.h"

class UtilityTest : public QObject
{
    Q_OBJECT
    
public:
    UtilityTest();
    
private Q_SLOTS:
    /** isBlackKey が正しく黒鍵を返してくるか */
    void isBlackKey_returns_correct_flag();
    void isBlackKey_returns_correct_flag_data();

    /** NoteName が正しい音階名を返してくるか */
    void NoteName_returns_correct_value();
    void NoteName_returns_correct_value_data();

    /** NoteFrequency が正しい周波数を返してくるか */
    void NoteFrequency_returns_correct_frequency();
    void NoteFrequency_returns_correct_frequency_data();

    /** NoteAt が正しいノート番号を返してくるか */
    void NoteAt_returns_corrent_note_number();
    void NoteAt_returns_corrent_note_number_data();
};

UtilityTest::UtilityTest()
{
}

void UtilityTest::isBlackKey_returns_correct_flag_data()
{
    QTest::addColumn<int>("note");
    QTest::addColumn<bool>("expected");
    QTest::newRow("0") << 60 << false;
    QTest::newRow("1") << 63 << true;
    QTest::newRow("2") << 50 << false;
    QTest::newRow("3") << 22 << true;
}

void UtilityTest::isBlackKey_returns_correct_flag()
{
    QFETCH(int, note);
    QFETCH(bool, expected);
    QCOMPARE(IsBlackKey(note), expected);
}

void UtilityTest::NoteName_returns_correct_value_data()
{
    QTest::addColumn<int>("note");
    QTest::addColumn<QString>("expected");
    QTest::newRow("0") << 60 << "C5";
    QTest::newRow("1") << 57 << "A4";
    QTest::newRow("2") << 52 << "E4";
    QTest::newRow("3") << 22 << "B-1";
}

void UtilityTest::NoteName_returns_correct_value()
{
    QFETCH(int, note);
    QFETCH(QString, expected);
    QCOMPARE(NoteName(note), expected);
}

void UtilityTest::NoteFrequency_returns_correct_frequency_data()
{
    QTest::addColumn<int>("note");
    QTest::addColumn<double>("expected");
    QTest::newRow("0") << 60 << 523.2511306011972;
    QTest::newRow("1") << 57 << 440.0;
    QTest::newRow("2") << 52 << 329.6275569128699;
    QTest::newRow("3") << 22 << 58.27047018976124;
}

void UtilityTest::NoteFrequency_returns_correct_frequency()
{
    QFETCH(int, note);
    QFETCH(double, expected);
    QCOMPARE(NoteFrequency(note), expected);
}

void UtilityTest::NoteAt_returns_corrent_note_number_data()
{
    QTest::addColumn<int>("expected");
    QTest::addColumn<double>("frequency");
    QTest::newRow("0") << 60 << 523.2511306011972;
    QTest::newRow("1") << 57 << 440.0;
    QTest::newRow("2") << 52 << 329.6275569128699;
    QTest::newRow("3") << 22 << 58.27047018976124;
}

void UtilityTest::NoteAt_returns_corrent_note_number()
{
    QFETCH(double, frequency);
    QFETCH(int, expected);
    QCOMPARE(NoteAt(frequency), (double)expected);
}
QTEST_APPLESS_MAIN(UtilityTest)

#include "test_Utility.moc"
