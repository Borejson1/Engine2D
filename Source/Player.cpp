#include "Player.h"
#include "PrimitiveRenderer.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

Player::Player(float startX, float startY)
    : m_position(startX, startY), m_speed(200.0f)
{
}

void Player::update(float deltaTime)
{
    float movement = m_speed * deltaTime;
    bool moved = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        translate(0.0f, -movement);
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        translate(0.0f, movement);
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        translate(-movement, 0.0f);
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        translate(movement, 0.0f);
        moved = true;
    }

    if (moved)
    {
        if (m_trail.empty() ||
            std::abs(m_trail.back().getX() - m_position.getX()) > 4.0f ||
            std::abs(m_trail.back().getY() - m_position.getY()) > 4.0f)
        {
            m_trail.push_back(m_position);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F7))
    {
        clearTrail();
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

    sf::CircleShape shape(10.0f);
    shape.setPosition({ m_position.getX() - 10.0f, m_position.getY() - 10.0f });
    shape.setFillColor(sf::Color::Green);
    target.draw(shape);
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