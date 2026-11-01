#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class PrimitiveRenderer;

class Point2D : public DrawableObject, public TransformableObject
{
private:
    float m_x;
    float m_y;

public:
    Point2D();
    Point2D(float x, float y);

    float getX() const;
    float getY() const;
    void set(float x, float y);

    void draw(sf::RenderTarget& target) override;
   

    void translate(float tx, float ty) override;
    void rotate(float angle) override;
    void scale(float kx, float ky) override;

    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::White);
};