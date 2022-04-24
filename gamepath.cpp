#include "gamepath.h"

gamePath::gamePath()
{

}

gamePath::gamePath(QString &lineType)
{
    this->lineType = lineType;

}

QPoint gamePath::getPos()
{
    return QPoint(x,y);
}
