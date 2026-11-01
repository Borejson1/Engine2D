#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    virtual ~GameObject() = default;
};

class UpdatableObject : public virtual GameObject
{
public:
    virtual void update(float deltaTime) = 0;
};

class DrawableObject : public virtual GameObject
{
public:
    virtual void draw(sf::RenderTarget& target) = 0;
};

class TransformableObject : public virtual GameObject
{
public:
    virtual void translate(float tx, float ty) = 0;
    virtual void rotate(float angle) = 0;
    virtual void scale(float kx, float ky) = 0;
};

class ShapeObject : public DrawableObject, public TransformableObject
{
public:

};