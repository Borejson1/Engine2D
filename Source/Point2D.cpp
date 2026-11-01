#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include <cmath>

Point2D::Point2D() : m_x(0.0f), m_y(0.0f) {}

Point2D::Point2D(float x, float y) : m_x(x), m_y(y) {}

float Point2D::getX() const { return m_x; }
float Point2D::getY() const { return m_y; }

void Point2D::set(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Point2D::draw(sf::RenderTarget& target)
{
    sf::Vertex vertex{ sf::Vector2f{ m_x, m_y }, sf::Color::White };
    target.draw(&vertex, 1, sf::PrimitiveType::Points);
}



void Point2D::translate(float tx, float ty)
{
    m_x += tx;
    m_y += ty;
}

void Point2D::rotate(float angle)
{
    float rad = angle * 3.14159265358979323846f / 180.0f;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    float newX = m_x * cosA - m_y * sinA;
    float newY = m_x * sinA + m_y * cosA;

    m_x = newX;
    m_y = newY;
}

void Point2D::scale(float kx, float ky)
{
    m_x *= kx;
    m_y *= ky;
}

void Point2D::draw(PrimitiveRenderer& renderer, sf::Color color)
{
    renderer.drawPoint(m_x, m_y, color);
}