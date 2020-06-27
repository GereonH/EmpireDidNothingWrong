#include "particle.h"

#include <QRandomGenerator>

static QRandomGenerator gen;

static float frictionDampingFactor = 0.8;
static float dampeningFactor = 0.5;

Particle::Particle(QGraphicsItem* item, QPointF point) :
    m_item(item), m_point(point) {

    m_dir.setX(gen.generateDouble() - 0.5);
    m_dir.setY(gen.generateDouble() - 0.5);
}

QGraphicsItem *Particle::item() const
{
    return m_item;
}

void Particle::setItem(QGraphicsItem *item)
{
    m_item = item;
}

QPointF Particle::point() const
{
    return m_point;
}

void Particle::setPoint(const QPointF &point)
{
    m_point = point;
}

void Particle::update(int timeInterval) {

}
