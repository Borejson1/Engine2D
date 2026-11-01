#include "PrimitiveRenderer.h"
#include <cmath>
#include <algorithm>
#include <queue>

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

void PrimitiveRenderer::drawCircleTrig(int x0, int y0, float radius, sf::Color color)
{
    float step = 1.0f / radius;
    float maxAngle = 1.5707963267948966f;

    for (float alpha = 0.0f; alpha <= maxAngle; alpha += step)
    {
        float x = radius * std::cos(alpha);
        float y = radius * std::sin(alpha);

        int ix = static_cast<int>(std::round(x));
        int iy = static_cast<int>(std::round(y));

        drawPoint(static_cast<float>(x0 + ix), static_cast<float>(y0 + iy), color);
        drawPoint(static_cast<float>(x0 - ix), static_cast<float>(y0 + iy), color);
        drawPoint(static_cast<float>(x0 + ix), static_cast<float>(y0 - iy), color);
        drawPoint(static_cast<float>(x0 - ix), static_cast<float>(y0 - iy), color);
    }
}

void PrimitiveRenderer::drawEllipseTrig(int x0, int y0, float rx, float ry, sf::Color color)
{
    float maxR = std::max(rx, ry);
    if (maxR <= 0.0f) return;

    float step = 1.0f / maxR;
    float maxAngle = 1.5707963267948966f;

    for (float alpha = 0.0f; alpha <= maxAngle; alpha += step)
    {
        float x = rx * std::cos(alpha);
        float y = ry * std::sin(alpha);

        int ix = static_cast<int>(std::round(x));
        int iy = static_cast<int>(std::round(y));

        drawPoint(static_cast<float>(x0 + ix), static_cast<float>(y0 + iy), color);
        drawPoint(static_cast<float>(x0 - ix), static_cast<float>(y0 + iy), color);
        drawPoint(static_cast<float>(x0 + ix), static_cast<float>(y0 - iy), color);
        drawPoint(static_cast<float>(x0 - ix), static_cast<float>(y0 - iy), color);
    }
}

void PrimitiveRenderer::borderFill(int startX, int startY, sf::Color fillColor, sf::Color borderColor)
{
    sf::Vector2u windowSize = m_target.getSize();
    if (startX < 0 || startX >= static_cast<int>(windowSize.x) ||
        startY < 0 || startY >= static_cast<int>(windowSize.y)) {
        return;
    }

    sf::RenderWindow* window = dynamic_cast<sf::RenderWindow*>(&m_target);
    if (!window) return;

    sf::Texture texture;
    if (!texture.resize({ windowSize.x, windowSize.y })) return;
    texture.update(*window);
    sf::Image image = texture.copyToImage();

    sf::Color currentColor = image.getPixel({ static_cast<unsigned int>(startX), static_cast<unsigned int>(startY) });

    if (currentColor == fillColor || currentColor == borderColor) {
        return;
    }

    std::queue<sf::Vector2i> pixelQueue;
    pixelQueue.push({ startX, startY });

    while (!pixelQueue.empty()) {
        sf::Vector2i p = pixelQueue.front();
        pixelQueue.pop();

        int x = p.x;
        int y = p.y;

        if (x < 0 || x >= static_cast<int>(windowSize.x) ||
            y < 0 || y >= static_cast<int>(windowSize.y)) {
            continue;
        }

        sf::Color pixelColor = image.getPixel({ static_cast<unsigned int>(x), static_cast<unsigned int>(y) });

        if (pixelColor != fillColor && pixelColor != borderColor) {
            drawPoint(static_cast<float>(x), static_cast<float>(y), fillColor);
            image.setPixel({ static_cast<unsigned int>(x), static_cast<unsigned int>(y) }, fillColor);

            pixelQueue.push({ x + 1, y });
            pixelQueue.push({ x - 1, y });
            pixelQueue.push({ x, y + 1 });
            pixelQueue.push({ x, y - 1 });
        }
    }
}

void PrimitiveRenderer::floodFill(int startX, int startY, sf::Color fillColor, sf::Color targetColor)
{
    sf::RenderWindow* window = dynamic_cast<sf::RenderWindow*>(&m_target);
    if (!window) return;

    sf::Vector2u windowSize = window->getSize();
    if (startX < 0 || startX >= static_cast<int>(windowSize.x) ||
        startY < 0 || startY >= static_cast<int>(windowSize.y)) {
        return;
    }

    sf::Texture texture;
    if (!texture.resize({ windowSize.x, windowSize.y })) return;
    texture.update(*window);
    sf::Image image = texture.copyToImage();

    sf::Color currentColor = image.getPixel({ static_cast<unsigned int>(startX), static_cast<unsigned int>(startY) });

    if (currentColor == fillColor || currentColor != targetColor) {
        return;
    }

    std::queue<sf::Vector2i> pixelQueue;
    pixelQueue.push({ startX, startY });

    while (!pixelQueue.empty()) {
        sf::Vector2i p = pixelQueue.front();
        pixelQueue.pop();

        int x = p.x;
        int y = p.y;

        if (x < 0 || x >= static_cast<int>(windowSize.x) ||
            y < 0 || y >= static_cast<int>(windowSize.y)) {
            continue;
        }

        sf::Color pixelColor = image.getPixel({ static_cast<unsigned int>(x), static_cast<unsigned int>(y) });

        if (pixelColor == targetColor) {
            drawPoint(static_cast<float>(x), static_cast<float>(y), fillColor);
            image.setPixel({ static_cast<unsigned int>(x), static_cast<unsigned int>(y) }, fillColor);

            pixelQueue.push({ x + 1, y });
            pixelQueue.push({ x - 1, y });
            pixelQueue.push({ x, y + 1 });
            pixelQueue.push({ x, y - 1 });
        }
    }
}