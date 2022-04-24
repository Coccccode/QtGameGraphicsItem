#include "qgraphicsbackgroundscene.h"
QGraphicsBackgroundScene::QGraphicsBackgroundScene(QObject *parent):QGraphicsScene (parent)
{

}

QGraphicsBackgroundScene::QGraphicsBackgroundScene(const QString path, QObject *parent)
{
    this->path = path;
}

QGraphicsBackgroundScene::QGraphicsBackgroundScene()
{

}

void QGraphicsBackgroundScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(views().count()==0)
        return;
    // 计算视窗的大小,消除图元拖动时出现的残影
    QString background_img = ":/img/famer.png";
    QGraphicsView* pView=views().first();
    QRect contentRect=pView->viewport()->contentsRect();
    QRectF sceneRect =pView->mapToScene(contentRect).boundingRect();
    //绘制指定图片作为背景
    QPixmap pixmap(path);
    painter->drawPixmap(sceneRect,pixmap,QRect());
}


