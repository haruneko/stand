#include <cmath>
#include <QMessageBox>
#include <QHash>

#include "Utility.h"

/** 黒鍵を表します． */
const static bool is_black_key[12] = {
    false,
    true,
    false,
    true,
    false,
    false,
    true,
    false,
    true,
    false,
    true,
    false
};
/** 音階名を表します． */
const static char *key_name[12] = {
    "C",
    "C+",
    "D",
    "E-",
    "E",
    "F",
    "F+",
    "G",
    "G+",
    "A",
    "B-",
    "B"
};
const static double a4_frequency = 440.0;
const static int a4_note_number = 57;

bool makeDirectory(QWidget *w, const QDir &dir, bool confirm)
{
    // 存在する場合は真を返して終了．
    if(dir.exists())
    {
        return true;
    }
    // 確認する場合
    if(confirm)
    {
        int val = QMessageBox::warning(w,
                                       QObject::tr("Confirm"),
                                       dir.path() + QObject::tr("\ndoes not exist. Do you want to create the directory"),
                                       QMessageBox::Yes, QMessageBox::No);
        if(val == QMessageBox::No)
        {
            return false;
        }
    }
    // ディレクトリを作成．
    if(!dir.mkpath(dir.absolutePath()))
    {
        QMessageBox::critical(w, QObject::tr("Error"), dir.path() + QObject::tr("\nCould not mkdir."));
        return false;
    }
    return true;
}

bool IsBlackKey(unsigned char note)
{
    return is_black_key[note % 12];
}

QString NoteName(unsigned char note)
{
    int octave = note / 12;
    return QString(key_name[note % 12]) + QString::number(octave);
}

double NoteFrequency(double note)
{
    return a4_frequency * pow(2.0, (note - a4_note_number) / 12.0);
}

double NoteAt(double frequency)
{
    return log(frequency / a4_frequency) / log(2.0) * 12.0 + a4_note_number;
}

QColor mixColor(const QColor &a, const QColor &b, double r)
{
    double _r = 1 - r;
    int red = a.red() * r + b.red() * _r;
    int green = a.green() * r + b.green() * _r;
    int blue = a.blue() * r + b.blue() * _r;
    int alpha = a.alpha() * r + b.alpha() * _r;
    return QColor(red, green, blue, alpha);
}

bool collides(const QRect &a, const QRect &b)
{
    return a.left() < b.right() && a.top() < b.bottom() && b.left() < a.right() && b.top() < a.bottom();
}
