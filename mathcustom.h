#ifndef MATHCUSTOM_H
#define MATHCUSTOM_H
#include "gamegraphicsitem_global.h"
#include <QTime>
#include <QRandomGenerator>
#include <QString>
class GAMEGRAPHICSITEMSHARED_EXPORT MathCustom
{
public:
    MathCustom();
    static int random(int min,int max);
    static int randomA (int min,int max);
    static QString number(int i);
};

#endif // MATH_H
