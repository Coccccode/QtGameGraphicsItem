#include "mathcustom.h"

int MathCustom::random(int min, int max)
{
   // qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return (qrand() + 1) % (max - min) + min;
}

int MathCustom::randomA(int min, int max)
{
    QRandomGenerator::global()->bounded(min,max);
}

QString MathCustom::number(int i)
{

      return i < 10 ?  "0" + QString::number(i) : QString::number(i);
}

MathCustom::MathCustom()
{

}
