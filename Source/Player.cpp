#include "Player.h"
#include "Engine.h"
#include "PrimitiveRenderer.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

Player::Player(float startX, float startY, Engine* engine)
    : m_position(startX, startY), m_speed(200.0f), m_engine(engine)
{
}

void Player::update(float deltaTime)
{
    m_clearTrailTimer += deltaTime;

    float movement = m_speed * deltaTime;
    m_isMoving = false;

    float dx = 0.0f;
    float dy = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        dy -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        dy += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        dx -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        dx += 1.0f;

    if (dx != 0.0f || dy != 0.0f)
    {
        m_isMoving = true;

        float length = std::sqrt(dx * dx + dy * dy);
        float normDx = dx / length;
        float normDy = dy / length;

        translate(normDx * movement, normDy * movement);
        if (dy < 0 && dx == 0) m_animOffset = 0;
        else if (dy < 0 && dx > 0) m_animOffset = 8;
        else if (dy == 0 && dx > 0) m_animOffset = 16;
        else if (dy > 0 && dx > 0) m_animOffset = 24;
        else if (dy > 0 && dx == 0) m_animOffset = 32;
        else if (dy > 0 && dx < 0) m_animOffset = 40;
        else if (dy == 0 && dx < 0) m_animOffset = 48;
        else if (dy < 0 && dx < 0) m_animOffset = 56;
    }

    if (m_isMoving)
    {
        if (m_trail.empty() ||
            std::abs(m_trail.back().getX() - m_position.getX()) > 4.0f ||
            std::abs(m_trail.back().getY() - m_position.getY()) > 4.0f)
        {
            m_trail.push_back(m_position);
        }

        animationTimer += deltaTime;
        if (animationTimer >= (1.0f / framesPerSecond)) {
            animate();
            animationTimer = 0.0f;
        }
    }
    else
    {
        currentSpriteIndex = m_animOffset;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F7))
    {
        if (!m_trail.empty() && m_clearTrailTimer >= 5.0f)
        {
            clearTrail();
            m_clearTrailTimer = 0.0f;
            if (m_engine)
            {
                m_engine->log("Wyczyszczono slad gracza (F7).");
            }
        }
    }
}

void Player::animate()
{
    if (!sprites.empty()) {
        if (currentSpriteIndex < m_animOffset || currentSpriteIndex >= m_animOffset + 8) {
            currentSpriteIndex = m_animOffset;
        }
        else {
            currentSpriteIndex = m_animOffset + ((currentSpriteIndex - m_animOffset + 1) % 8);
        }
    }
}

void Player::draw(sf::RenderTarget& target)
{
    if (m_trail.size() > 1)
    {
        for (size_t i = 0; i < m_trail.size() - 1; ++i)
        {
            sf::Vertex line[] = {
                { sf::Vector2f{ m_trail[i].getX(), m_trail[i].getY() }, sf::Color::Yellow },
                { sf::Vector2f{ m_trail[i + 1].getX(), m_trail[i + 1].getY() }, sf::Color::Yellow }
            };
            target.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }

    if (!sprites.empty()) {
        sprites[currentSpriteIndex].setPosition({
            m_position.getX() - sprites[currentSpriteIndex].getGlobalBounds().size.x / 2.0f,
            m_position.getY() - sprites[currentSpriteIndex].getGlobalBounds().size.y / 2.0f
            });
        target.draw(sprites[currentSpriteIndex]);
    }
    else {
        sf::CircleShape shape(10.0f);
        shape.setPosition({ m_position.getX() - 10.0f, m_position.getY() - 10.0f });
        shape.setFillColor(sf::Color::Green);
        target.draw(shape);
    }
}

void Player::draw(PrimitiveRenderer& renderer, sf::Color color)
{
    if (m_trail.size() > 1)
    {
        for (size_t i = 0; i < m_trail.size() - 1; ++i)
        {
            renderer.drawLine(m_trail[i].getX(), m_trail[i].getY(), m_trail[i + 1].getX(), m_trail[i + 1].getY(), sf::Color::Yellow);
        }
    }
    renderer.drawCircle(m_position.getX(), m_position.getY(), 10.0f, color, true);
}

void Player::translate(float tx, float ty)
{
    m_position.translate(tx, ty);
}

void Player::rotate(float angle)
{
    m_position.rotate(angle);
}

void Player::scale(float kx, float ky)
{
    m_position.scale(kx, ky);
}

void Player::clearTrail()
{
    m_trail.clear();
}