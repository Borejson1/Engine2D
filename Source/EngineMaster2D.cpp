#include "EngineMaster2D.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <iostream>

int main()
{
    const std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    sf::Vector2u windowSize{ 800, 600 };
    bool isFullscreen = false;

    unsigned int frameRateLimit = 60;
    bool isKeyboardEnabled = true;
    bool isMouseEnabled = true;
    float animationSpeed = 200.0f;

    sf::RenderWindow window(sf::VideoMode(windowSize), "EngineMaster2D", sf::Style::Default, sf::State::Windowed);
    window.setFramerateLimit(frameRateLimit);

    sf::CircleShape ball(25.0f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition({ 400.0f, 300.0f });

    sf::Vector2f ballVelocity{ 1.0f, 0.5f };

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        float dt = elapsedTime.asSeconds();

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({ 0.0f, 0.0f }, { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });
                window.setView(sf::View(visibleArea));
                std::cout << "[Resized] W: " << resized->size.x << " H: " << resized->size.y << std::endl;
            }

            if (isKeyboardEnabled)
            {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->code == sf::Keyboard::Key::F11)
                    {
                        isFullscreen = !isFullscreen;
                        if (isFullscreen && !modes.empty())
                        {
                            window.create(modes[0], "EngineMaster2D", sf::State::Fullscreen);
                            std::cout << "[F11] Fullscreen" << std::endl;
                        }
                        else
                        {
                            window.create(sf::VideoMode(windowSize), "EngineMaster2D", sf::Style::Default, sf::State::Windowed);
                            std::cout << "[F11] Okno Resizable" << std::endl;
                        }
                        window.setFramerateLimit(frameRateLimit);
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::F1)
                    {
                        frameRateLimit = (frameRateLimit == 60) ? 144 : 60;
                        window.setFramerateLimit(frameRateLimit);
                        std::cout << "[F1] FPS: " << frameRateLimit << std::endl;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::F2)
                    {
                        animationSpeed = (animationSpeed == 200.0f) ? 400.0f : 200.0f;
                        std::cout << "[F2] V: " << animationSpeed << std::endl;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::F3)
                    {
                        isMouseEnabled = !isMouseEnabled;
                        std::cout << "[F3] Mysz: " << (isMouseEnabled ? "ON" : "OFF") << std::endl;
                    }
                }
            }

            if (isMouseEnabled)
            {
                if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mousePressed->button == sf::Mouse::Button::Left)
                    {
                        std::cout << "[LPM] X: " << mousePressed->position.x << " Y: " << mousePressed->position.y << std::endl;
                    }
                }
            }
        }

        sf::Vector2f currentSize = window.getView().getSize();
        sf::Vector2f pos = ball.getPosition();

        pos += ballVelocity * animationSpeed * dt;

        if (pos.x < 0.0f)
        {
            pos.x = 0.0f;
            ballVelocity.x = -ballVelocity.x;
        }
        else if (pos.x + ball.getRadius() * 2.0f > currentSize.x)
        {
            pos.x = currentSize.x - ball.getRadius() * 2.0f;
            ballVelocity.x = -ballVelocity.x;
        }

        if (pos.y < 0.0f)
        {
            pos.y = 0.0f;
            ballVelocity.y = -ballVelocity.y;
        }
        else if (pos.y + ball.getRadius() * 2.0f > currentSize.y)
        {
            pos.y = currentSize.y - ball.getRadius() * 2.0f;
            ballVelocity.y = -ballVelocity.y;
        }

        ball.setPosition(pos);

        window.clear(sf::Color::Blue);
        window.draw(ball);
        window.display();
    }

    return 0;
}