#include "PrimitiveRenderer.h"
#include <cmath>
#include <algorithm>

PrimitiveRenderer::PrimitiveRenderer(sf::RenderTarget& target)
    : m_target(target)
{
}

void PrimitiveRenderer::drawPoint(float x, float y, sf::Color color)
{
    sf::Vertex vertex{ sf::Vector2f{ x, y }, color };
    m_target.draw(&vertex, 1, sf::PrimitiveType::Points);
}

void PrimitiveRenderer::drawLine(float x0, float y0, float x1, float y1, sf::Color color)
{
    sf::Vertex line[] = {
        { sf::Vector2f{ x0, y0 }, color },
        { sf::Vector2f{ x1, y1 }, color }
    };
    m_target.draw(line, 2, sf::PrimitiveType::Lines);
}

void PrimitiveRenderer::drawCircle(float x, float y, float radius, sf::Color color, bool filled)
{
    sf::CircleShape circle(radius);
    circle.setPosition({ x - radius, y - radius });
    if (filled)
    {
        circle.setFillColor(color);
    }
    else
    {
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(color);
        circle.setOutlineThickness(1.0f);
    }
    m_target.draw(circle);
}

void PrimitiveRenderer::drawRectangle(float x, float y, float width, float height, sf::Color color, bool filled)
{
    sf::RectangleShape rect({ width, height });
    rect.setPosition({ x, y });
    if (filled)
    {
        rect.setFillColor(color);
    }
    else
    {
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(color);
        rect.setOutlineThickness(1.0f);
    }
    m_target.draw(rect);
}

void PrimitiveRenderer::drawLineIncremental(float x0, float y0, float x1, float y1, sf::Color color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;

    if (std::abs(dx) >= std::abs(dy))
    {
        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
            dx = x1 - x0;
            dy = y1 - y0;
        }

        float m = (dx == 0.0f) ? 0.0f : (dy / dx);
        float y = y0;

        for (int x = static_cast<int>(std::round(x0)); x <= static_cast<int>(std::round(x1)); ++x)
        {
            drawPoint(static_cast<float>(x), std::round(y), color);
            y += m;
        }
    }
    else
    {
        if (y0 > y1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
            dx = x1 - x0;
            dy = y1 - y0;
        }

        float m = (dy == 0.0f) ? 0.0f : (dx / dy);
        float x = x0;

        for (int y = static_cast<int>(std::round(y0)); y <= static_cast<int>(std::round(y1)); ++y)
        {
            drawPoint(std::round(x), static_cast<float>(y), color);
            x += m;
        }
    }
}

void PrimitiveRenderer::drawPolyline(const std::vector<Point2D>& points, bool closed, sf::Color color)
{
    if (points.size() < 2) return;

    for (size_t i = 0; i < points.size() - 1; ++i)
    {
        drawLine(points[i].getX(), points[i].getY(), points[i + 1].getX(), points[i + 1].getY(), color);
    }

    if (closed)
    {
        drawLine(points.back().getX(), points.back().getY(), points.front().getX(), points.front().getY(), color);
    }
}

void PrimitiveRenderer::drawPolyline(const std::vector<LineSegment>& segments, sf::Color color)
{
    for (size_t i = 0; i < segments.size(); ++i)
    {
        segments[i].draw(*this, false, color);
    }
}