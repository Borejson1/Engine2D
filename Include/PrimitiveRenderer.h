#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Point2D.h"
#include "LineSegment.h"

class PrimitiveRenderer
{
public:
    explicit PrimitiveRenderer(sf::RenderTarget& target);

    void drawPoint(float x, float y, sf::Color color = sf::Color::White);
    void drawLine(float x0, float y0, float x1, float y1, sf::Color color = sf::Color::White);
    void drawCircle(float x, float y, float radius, sf::Color color = sf::Color::White, bool filled = false);
    void drawRectangle(float x, float y, float width, float height, sf::Color color = sf::Color::White, bool filled = false);

    void drawLineIncremental(float x0, float y0, float x1, float y1, sf::Color color = sf::Color::White);

    void drawPolyline(const std::vector<Point2D>& points, bool closed = false, sf::Color color = sf::Color::White);
    void drawPolyline(const std::vector<LineSegment>& segments, sf::Color color = sf::Color::White);

private:
    sf::RenderTarget& m_target;
};