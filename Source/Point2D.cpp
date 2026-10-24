#include "Point2D.h"
#include "PrimitiveRenderer.h"

Point2D::Point2D() : m_x(0.0f), m_y(0.0f) {}
Point2D::Point2D(float x, float y) : m_x(x), m_y(y) {}

float Point2D::getX() const { return m_x; }
float Point2D::getY() const { return m_y; }
void Point2D::setX(float x) { m_x = x; }
void Point2D::setY(float y) { m_y = y; }
void Point2D::setPosition(float x, float y) { m_x = x; m_y = y; }

void Point2D::draw(PrimitiveRenderer& renderer, sf::Color color) const
{
    renderer.drawPoint(m_x, m_y, color);
}