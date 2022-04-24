#ifndef GAMEPATH_H
#define GAMEPATH_H

#include <QObject>
#include <QPoint>
class gamePath
{
public:
    gamePath();
    gamePath(QString &lineType);
    QPoint getPos();
private:
    double x;
    double y;
    double k;
    double b;
    QString lineType;
};

#endif // GAMEPATH_H
