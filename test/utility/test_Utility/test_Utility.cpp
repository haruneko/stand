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

    /** mixColor が正しい値を返してくるか */
    void mixColor_returns_correct_color();
    void mixColor_returns_correct_color_data();
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

void UtilityTest::mixColor_returns_correct_color_data()
{
    QTest::addColumn<int>("r1");
    QTest::addColumn<int>("g1");
    QTest::addColumn<int>("b1");
    QTest::addColumn<int>("a1");
    QTest::addColumn<int>("r2");
    QTest::addColumn<int>("g2");
    QTest::addColumn<int>("b2");
    QTest::addColumn<int>("a2");
    QTest::addColumn<double>("r");
    QTest::addColumn<int>("r3");
    QTest::addColumn<int>("g3");
    QTest::addColumn<int>("b3");
    QTest::addColumn<int>("a3");

    QTest::newRow("0") <<   0 <<   0 <<   0 <<   0 <<   0 <<   0 <<   0 <<   0 <<  1.0 <<   0 <<   0 <<   0 <<   0;
    QTest::newRow("1") << 255 << 255 << 255 << 255 <<   0 <<   0 <<   0 <<   0 <<  0.5 << 127 << 127 << 127 << 127;
    QTest::newRow("2") << 255 << 255 <<   0 <<   0 <<   0 <<   0 << 255 << 255 << 0.25 << (255 / 4) << (255 / 4) << (255 * 3 / 4) << (255 * 3 / 4);
}

void UtilityTest::mixColor_returns_correct_color()
{
    QFETCH(int, r1); QFETCH(int, g1); QFETCH(int, b1); QFETCH(int, a1);
    QFETCH(int, r2); QFETCH(int, g2); QFETCH(int, b2); QFETCH(int, a2);
    QFETCH(double, r);
    QFETCH(int, r3); QFETCH(int, g3); QFETCH(int, b3); QFETCH(int, a3);
    QColor ans = mixColor(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), r);
    QCOMPARE(ans.red(), r3);
    QCOMPARE(ans.green(), g3);
    QCOMPARE(ans.blue(), b3);
    QCOMPARE(ans.alpha(), a3);
}

QTEST_APPLESS_MAIN(UtilityTest)

#include "test_Utility.moc"
