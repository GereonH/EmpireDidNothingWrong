#ifndef PARTICLE_H
#define PARTICLE_H


#include <QGraphicsItem>

class Particle
{
public:
    Particle(QGraphicsItem* item, QPointF point);

    QGraphicsItem *item() const;
    void setItem(QGraphicsItem *item);

    QPointF point() const;
    void setPoint(const QPointF &point);

    void update(int timeInterval);

private:
    QGraphicsItem* m_item;
    QPointF m_point;
    QPointF m_dir;
};

#endif // PARTICLE_H
