#include "LineSegment.h"
#include "PrimitiveRenderer.h"

LineSegment::LineSegment() : m_start(0.0f, 0.0f), m_end(0.0f, 0.0f) {}
LineSegment::LineSegment(const Point2D& start, const Point2D& end) : m_start(start), m_end(end) {}
LineSegment::LineSegment(float x0, float y0, float x1, float y1) : m_start(x0, y0), m_end(x1, y1) {}

Point2D LineSegment::getStart() const { return m_start; }
Point2D LineSegment::getEnd() const { return m_end; }
void LineSegment::setStart(const Point2D& start) { m_start = start; }
void LineSegment::setEnd(const Point2D& end) { m_end = end; }

void LineSegment::draw(PrimitiveRenderer& renderer, bool useIncremental, sf::Color color) const
{
    if (useIncremental)
    {
        renderer.drawLineIncremental(m_start.getX(), m_start.getY(), m_end.getX(), m_end.getY(), color);
    }
    else
    {
        renderer.drawLine(m_start.getX(), m_start.getY(), m_end.getX(), m_end.getY(), color);
    }
}

void LineSegment::draw(sf::RenderTarget& target)
{
    sf::Vertex line[] = {
        { sf::Vector2f{ m_start.getX(), m_start.getY() }, sf::Color::White },
        { sf::Vector2f{ m_end.getX(), m_end.getY() }, sf::Color::White }
    };
    target.draw(line, 2, sf::PrimitiveType::Lines);
}

void LineSegment::translate(float tx, float ty)
{
    m_start.translate(tx, ty);
    m_end.translate(tx, ty);
}

void LineSegment::rotate(float angle)
{
    m_start.rotate(angle);
    m_end.rotate(angle);
}

void LineSegment::scale(float kx, float ky)
{
    m_start.scale(kx, ky);
    m_end.scale(kx, ky);
}