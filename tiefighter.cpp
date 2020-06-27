#include "tiefighter.h"

#include <QGraphicsPixmapItem>
#include <QDebug>

TieFighter::TieFighter(QGraphicsItem* item, QPointF point)
    : Particle(item, point)
{
    qDebug("TieFighter created");
}
