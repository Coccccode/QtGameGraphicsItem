#include "timetool.h"

TimeTool::TimeTool()
{
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(StressFunc()));
}

void TimeTool::sleep(int time)
{
    QTime delayTime = QTime::currentTime().addMSecs(time);	//在当前时间上增加3S
    /* lyh delete -> 避免有拉拽小票冲突 */
    while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

void TimeTool::int2QString(double num)
{

}

void TimeTool::timeStart(int sec)
{
    time = sec;
    timer->start(1000);
}

void TimeTool::setTime(int value)
{
    time = value;
}

int TimeTool::getTime() const
{
    return time;
}

QString TimeTool::secToTime(int sec)
{
    if(sec >= 0)
    {
        int se = sec % 60;
        int mi = sec / 60 % 60;
        return  numToStr(mi) + ":" + numToStr(se);
    }
    else {
        return "00:00";
    }

}

QString TimeTool::numToStr(int num)
{
    if(num < 10)
        return "0" + QString::number(num);
    else {
        return QString::number(num);
    }
}

void TimeTool::stop()
{
    timer->stop();
}

void TimeTool::start(int msec)
{
    timer->start(1000);
}

void TimeTool::StressFunc()
{
    time--;
    emit timeSec();
    if(time >= 0)
        emit timeSec(time);
    if(time < 0)
    {
        emit timeEnd();
        timer->stop();
    }
}
