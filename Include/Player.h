#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Point2D.h"

class PrimitiveRenderer;

class Player : public UpdatableObject, public ShapeObject
{
private:
    Point2D m_position;
    float m_speed;

public:
    Player(float startX, float startY);

    void update(float deltaTime) override;

    void draw(sf::RenderTarget& target) override;
    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Green);

    void translate(float tx, float ty) override;
    void rotate(float angle) override;
    void scale(float kx, float ky) override;
};