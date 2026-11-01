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
    void drawCircleTrig(int x0, int y0, float radius, sf::Color color = sf::Color::White);
    void drawRectangle(float x, float y, float width, float height, sf::Color color = sf::Color::White, bool filled = false);

    void drawLineIncremental(float x0, float y0, float x1, float y1, sf::Color color = sf::Color::White);

    void drawPolyline(const std::vector<Point2D>& points, bool closed = false, sf::Color color = sf::Color::White);
    void drawPolyline(const std::vector<LineSegment>& segments, sf::Color color = sf::Color::White);

    void drawEllipseTrig(int x0, int y0, float rx, float ry, sf::Color color = sf::Color::White);
    
    void borderFill(int startX, int startY, sf::Color fillColor, sf::Color borderColor);
    void floodFill(int startX, int startY, sf::Color fillColor, sf::Color targetColor);
private:
    sf::RenderTarget& m_target;
};