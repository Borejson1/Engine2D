#pragma once
#include "SpriteObject.h"
#include "GameObject.h"
#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include <vector>

class Engine;
class Player : public SpriteObject, public UpdatableObject {
private:
    float m_speed;
    Point2D m_position;
    std::vector<Point2D> m_trail;
    int m_animOffset = 16;
    bool m_isMoving = false;
    Engine* m_engine = nullptr;
    float m_clearTrailTimer = 5.0f;

public:
    Player(float startX, float startY, Engine* engine = nullptr);

    void clearTrail();
    void draw(PrimitiveRenderer& renderer, sf::Color color);

    virtual void update(float deltaTime) override;
    virtual void draw(sf::RenderTarget& target) override;
    virtual void animate() override;

    virtual void translate(float tx, float ty) override;
    virtual void rotate(float angle) override;
    virtual void scale(float kx, float ky) override;
};