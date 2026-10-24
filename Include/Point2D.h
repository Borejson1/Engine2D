#pragma once
#include <SFML/Graphics.hpp>

class PrimitiveRenderer;

class Point2D
{
public:
    Point2D();
    Point2D(float x, float y);

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    void setPosition(float x, float y);

    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::White) const;

private:
    float m_x{ 0.0f };
    float m_y{ 0.0f };
};