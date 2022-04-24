#ifndef GAMEGRAPHICSITEM_H
#define GAMEGRAPHICSITEM_H

#include "gamegraphicsitem_global.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QString>
#include <cmath>
#include <QPoint>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
class GAMEGRAPHICSITEMSHARED_EXPORT GameGraphicsItem:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameGraphicsItem(QObject *parent = nullptr, QString imgSrc = "", bool isStatic = true, int time = 50, int imgCount = 0, QPointF pos = QPointF(0.0,0.0), QList<int> list = {});
    GameGraphicsItem(QObject *parent = nullptr, QString imgSrc = "" ,QPointF pos = QPointF(0.0,0.0));
    bool nextPhase();
    bool backPhase();
    void setPhase(const QList<int> &value);
    void start();
    void stop();
    QPropertyAnimation animation;

    GameGraphicsItem(QObject *parent, QString imgSrc, bool isStatic, int time, int imgCount, QPointF pos, QList<int> list, bool isStringNum);
    QString getImgSrc() const;
    void setImgSrc(const QString &value);
    bool isAnime();
    void moveStop();
    void moveStart();
public slots:
    void playAnimation();
    void afterCollide();
    void move();
signals:
    void SignalCollide();
    void Clicked();
    void phaseEnd(int phaseIndex);
public:
    static int startIndex;

    void setIsLog(bool value);

    void movey();
    void log(int index);
    void setIndex(int value);

    int getImgCount() const;
    void setImgCount(int value);

    int getIndex() const;

    int getPhaseIndex() const;
    void setPhaseIndex(int value);

    void SetPixmap();
    void setCollideItem(GameGraphicsItem *value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
protected:
    bool isStatic;
    bool isWeight;
    bool isLog = false;

    int animTime;
    int imgCount;
    int index = 0;
    int incremental = 1;
    //QThread thread;
    double weight;
    QString suffix = ".png";
    QTimer *animTimer;
    QTimer *moveTimer;
    QTimer *collideTimer;
    QString imgSrc;
    bool isStringNum = false;
    bool isStart = true;
    QList<int> phase;
    int phaseIndex = 0;
    GameGraphicsItem *collideItem;//碰撞所需的Item
    void moveTo(double x, double y, double startAngle);
    void log(QString &log);
    void playAnime(int x,int y);
};

#endif // GAMEGRAPHICSITEM_H
