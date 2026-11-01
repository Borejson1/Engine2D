#include "Player.h"
#include "PrimitiveRenderer.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player(float startX, float startY)
    : m_position(startX, startY), m_speed(200.0f)
{
}

void Player::update(float deltaTime)
{
    float movement = m_speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        translate(0.0f, -movement);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        translate(0.0f, movement);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        translate(-movement, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        translate(movement, 0.0f);
    }
}

void Player::draw(sf::RenderTarget& target)
{
    sf::CircleShape shape(10.0f);
    shape.setPosition({ m_position.getX() - 10.0f, m_position.getY() - 10.0f });
    shape.setFillColor(sf::Color::Green);
    target.draw(shape);
}

void Player::draw(PrimitiveRenderer& renderer, sf::Color color)
{
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