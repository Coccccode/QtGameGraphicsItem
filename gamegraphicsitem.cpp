#include "gamegraphicsitem.h"
#include "mathcustom.h"
#define PI 3.1415926535898
int GameGraphicsItem::startIndex = 1;
void GameGraphicsItem::moveTo(double x, double y,double startAngle) //以y轴正半轴为初始角y轴左边为负，右边为正
{
    double dx =  x - this->pos().x();
    double dy = y - this->pos().y();
    double angle;
    if(dx < 0 && dy < 0){
        angle = -atan(dx/dy)*180/PI;
    }
    else if(dx > 0 && dy < 0){
        angle = -atan(dx/dy)*180/PI;
    }
    else if(dx < 0 && dy > 0){
        angle = atan(dy/dx)*180/PI - 90;
    }
    else {
        angle = atan(dy/dx)*180/PI + 90;
    }
    this->setRotation(startAngle+angle);
    this->moveBy(dx,dy);
    //qDebug() << angle;
}

void GameGraphicsItem::log(QString &log)
{
    qDebug() << log;
}

void GameGraphicsItem::log(int index)
{
    qDebug() << index;
}
GameGraphicsItem::GameGraphicsItem(QObject *parent,QString imgSrc, bool isStatic, int time, int imgCount, QPointF pos,QList<int> list):QObject (parent)
{
    this->isStatic = isStatic;
    this->setPos(pos);
    this->phase = list;
    animTimer = new QTimer(this);
    if(!isStatic) {
        this->imgSrc = imgSrc;
        animTimer = new QTimer(this);
        connect(animTimer,SIGNAL(timeout()),this,SLOT(playAnimation()));
        animTimer->start(time);
        this->animTime = time;
        this->imgCount = imgCount;
       // animTimer->moveToThread(&thread);
        //thread.start();
    }else {
        this->imgSrc = imgSrc;
        this->setPixmap(imgSrc);
    }
    phaseIndex = 0;
    //this->setPos(pos);
    collideTimer = new QTimer(this);
    connect(collideTimer,&QTimer::timeout,this,[=]{
        if(this->collidesWithItem(collideItem))
        {
            emit SignalCollide();
        }
    });
    collideTimer->setInterval(25);

}

GameGraphicsItem::GameGraphicsItem(QObject *parent, QString imgSrc,QPointF pos):QObject (parent)
{
    this->setPos(pos);
    this->imgSrc = imgSrc;
    this->setPixmap(imgSrc);
    this->isStatic = true;
    collideTimer = new QTimer(this);
    collideTimer = new QTimer(this);
    connect(collideTimer,&QTimer::timeout,this,[=]{
        if(this->collidesWithItem(collideItem))
        {
            emit SignalCollide();
        }
    });
    collideTimer->setInterval(25);
}
GameGraphicsItem::GameGraphicsItem(QObject *parent,QString imgSrc, bool isStatic, int time, int imgCount, QPointF pos,QList<int> list,bool isStringNum):QObject (parent)
{
    this->isStatic = isStatic;
    this->setPos(pos);
    this->phase = list;
    if(!isStatic) {
        this->imgSrc = imgSrc;
        animTimer = new QTimer(this);
        connect(animTimer,SIGNAL(timeout()),this,SLOT(playAnimation()));
        animTimer->start(time);
        this->animTime = time;
        this->imgCount = imgCount;
        //animTimer->moveToThread(&thread);
        //thread.start();
    }else {
        this->imgSrc = imgSrc;
        this->setPixmap(imgSrc);
    }
    phaseIndex = 0;
    //this->setPos(pos);
    this->isStringNum = isStringNum;
    collideTimer = new QTimer(this);
    connect(collideTimer,&QTimer::timeout,this,[=]{
        if(this->collidesWithItem(collideItem))
        {
            emit SignalCollide();
        }
    });
    collideTimer->setInterval(25);

}
bool GameGraphicsItem::nextPhase()
{
    incremental = 1;
    if(index + startIndex < imgCount){

        animTimer->start();
        if(phase.length() >= 2 && index + startIndex == phase[phase.length()-2])
            return false;
        else
            return true;
    }else {
        //animTimer->stop();
        return false;
    }
}

bool GameGraphicsItem::backPhase()
{
    if(!animTimer->isActive() && index == 0)
        return false;
    qDebug() << phaseIndex;
    incremental = -1;
    animTimer->stop();
    animTimer->start();
    return true;
}

void GameGraphicsItem::playAnimation()
{
    if(isStart)
    {
        if(!phase.isEmpty() && phaseIndex == 0){
            phaseIndex += 1;
            animTimer->stop();
            //return ;
        }
        if(isLog)
        {
            qDebug() << "phaseIndex:" << phaseIndex;
            qDebug() << "index:"  <<index;
        }
        if(!phase.isEmpty() && phaseIndex - 1 < phase.length() && index + 1 == phase[phaseIndex - 1]){
            qDebug() << "phaseIndex" << phaseIndex;
            if(phaseIndex + incremental >= 1)
            {
                phaseIndex = phaseIndex + incremental;
            }
            animTimer->stop();
            emit phaseEnd(phaseIndex - 1);
            //return ;
        }
        QString num;
        if(isStringNum && index + startIndex < 10){
            num ="0" + QString::number(index + startIndex);
        }
        else {
            num = QString::number(index + startIndex);
        }

        QString src;
        src = imgSrc + num + suffix;
        this->setPixmap(src);

        if( index + incremental >= 0 && index + incremental < imgCount)
        {

            index = index + incremental;

        }
        else
        {
            if(phase.isEmpty())
            {
                index = 0;
                incremental = 1;
                phaseIndex = 1;
            }
            else
            {
                animTimer->stop();
            }
        }
        if(isLog)
        {
            log(src);
            log(index);
        }
    }
}

void GameGraphicsItem::afterCollide()
{

}

void GameGraphicsItem::move()
{
    static int t = 0;
    static bool flag = true;
    this->moveBy(0,0.01*t);
    if(flag == false)
    {
        t = t - 1;
    }
    else
    {
        t = t + 1;
    }
    if(t >= 100)
    {
        flag = false;
    }
    else if(t <= -100)
    {
        flag = true;
    }

}

void GameGraphicsItem::setIsLog(bool value)
{
    isLog = value;
}

void GameGraphicsItem::movey()
{
    moveTimer = new QTimer();
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    moveTimer->start(10);

}

void GameGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    emit Clicked();
}

void GameGraphicsItem::setCollideItem(GameGraphicsItem *value)
{
    collideItem = value;
    collideTimer->start();
}

int GameGraphicsItem::getPhaseIndex() const
{
    return phaseIndex;
}

void GameGraphicsItem::setPhaseIndex(int value)
{
    phaseIndex = value;
}

void GameGraphicsItem::SetPixmap()
{
    QString num;
    if(isStringNum && index + startIndex < 10){
        num ="0" + QString::number(index + startIndex);
    }
    else {
        num = QString::number(index + startIndex);
    }

    QString src;
    src = imgSrc + num + suffix;
    this->setPixmap(src);
}


int GameGraphicsItem::getIndex() const
{
    return index;
}

int GameGraphicsItem::getImgCount() const
{
    return imgCount;
}

void GameGraphicsItem::setImgCount(int value)
{
    imgCount = value;
}

void GameGraphicsItem::setIndex(int value)
{
    index = value;
}

void GameGraphicsItem::setPhase(const QList<int> &value)
{
    phase = value;
}

void GameGraphicsItem::start()
{
    isStart = true;
    //animTimer->start();
}

void GameGraphicsItem::stop()
{
    isStart = false;
    //animTimer->stop();
}



QString GameGraphicsItem::getImgSrc() const
{
    return imgSrc;
}

void GameGraphicsItem::setImgSrc(const QString &value)
{
    imgSrc = value;
    if(isStatic == true)
    {
        this->setPixmap(imgSrc);
    }
}

bool GameGraphicsItem::isAnime()
{
    return animTimer->isActive();
}

void GameGraphicsItem::moveStop()
{
    moveTimer->stop();
}

void GameGraphicsItem::moveStart()
{
    moveTimer->start();
}
