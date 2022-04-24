#ifndef QGRAPHICSBACKGROUNDSCENE_H
#define QGRAPHICSBACKGROUNDSCENE_H
#include "gamegraphicsitem_global.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPixmap>
#include <QDebug>
#include <QObject>

class GAMEGRAPHICSITEMSHARED_EXPORT QGraphicsBackgroundScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QGraphicsBackgroundScene(QObject *parent = nullptr);
     QGraphicsBackgroundScene(const QString path,QObject *parent = nullptr);
    QGraphicsBackgroundScene();
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    QString path;
};

#endif // QGRAPHICSBACKGROUNDSCENE_H
