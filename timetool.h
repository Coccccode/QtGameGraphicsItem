#ifndef TIMETOOL_H
#define TIMETOOL_H
#include "gamegraphicsitem_global.h"
#include <QObject>
#include<QTime>
#include <QEventLoop>
#include <QCoreApplication>
#include <QTimer>
class GAMEGRAPHICSITEMSHARED_EXPORT TimeTool:public QObject
{
    Q_OBJECT
public:
    TimeTool();
     void static sleep(int time);
    QTimer *timer;
    void int2QString(double num);
    void timeStart(int sec);
    int time = 10000;

    QString timeStr;
    int getTime() const;
     QString static secToTime(int sec) ;
    QString static numToStr(int num);
    void stop();
    void start(int msec);
    QString getTimeStr() const;
    void setTimeStr(const QString &value);

    void setTime(int value);

public slots:
    void StressFunc();

signals:
    void timeEnd();
    void timeSec(int sec);
    void timeSec();
};

#endif // TIMETOOL_H
