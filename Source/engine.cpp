#include "Engine.h"
#include <iostream>
#include <optional>

Engine::Engine()
    : m_ball(25.0f)
{
    m_logFile.open("engine_log.txt", std::ios::out | std::ios::trunc);
    log("Utworzono obiekt Engine.");

    m_ball.setFillColor(sf::Color::White);
    m_ball.setPosition({ 400.0f, 300.0f });
}

Engine::~Engine()
{
    close();
}

void Engine::init(sf::Vector2u windowSize, const std::string& title, bool fullscreen)
{
    m_windowSize = windowSize;
    m_title = title;
    m_isFullscreen = fullscreen;
    m_modes = sf::VideoMode::getFullscreenModes();

    if (m_isFullscreen && !m_modes.empty())
    {
        m_window.create(m_modes[0], m_title, sf::State::Fullscreen);
        log("Inicjacja okna w trybie Fullscreen.");
    }
    else
    {
        m_window.create(sf::VideoMode(m_windowSize), m_title, sf::Style::Default, sf::State::Windowed);
        log("Inicjacja okna w trybie Windowed.");
    }

    m_window.setFramerateLimit(m_frameRateLimit);
}

void Engine::setParameters(unsigned int fps, bool enableKeyboard, bool enableMouse)
{
    m_frameRateLimit = fps;
    m_isKeyboardEnabled = enableKeyboard;
    m_isMouseEnabled = enableMouse;

    if (m_window.isOpen())
    {
        m_window.setFramerateLimit(m_frameRateLimit);
    }

    log("Zaktualizowano parametry silnika (FPS: " + std::to_string(fps) + ").");
}

void Engine::run()
{
    log("Start glownej petli gry.");
    while (m_window.isOpen())
    {
        float dt = m_clock.restart().asSeconds();

        handleEvents();
        update(dt);
        render();
    }
}

void Engine::handleEvents()
{
    while (const std::optional<sf::Event> event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            close();
        }

        if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            sf::FloatRect visibleArea({ 0.0f, 0.0f }, { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });
            m_window.setView(sf::View(visibleArea));
            log("[Resized] W: " + std::to_string(resized->size.x) + " H: " + std::to_string(resized->size.y));
        }

        if (m_isKeyboardEnabled)
        {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::F11)
                {
                    init(m_windowSize, m_title, !m_isFullscreen);
                }
                else if (keyPressed->code == sf::Keyboard::Key::F1)
                {
                    m_frameRateLimit = (m_frameRateLimit == 60) ? 144 : 60;
                    m_window.setFramerateLimit(m_frameRateLimit);
                    log("[F1] FPS: " + std::to_string(m_frameRateLimit));
                }
                else if (keyPressed->code == sf::Keyboard::Key::F2)
                {
                    m_animationSpeed = (m_animationSpeed == 200.0f) ? 400.0f : 200.0f;
                    log("[F2] V: " + std::to_string(m_animationSpeed));
                }
                else if (keyPressed->code == sf::Keyboard::Key::F3)
                {
                    m_isMouseEnabled = !m_isMouseEnabled;
                    log(std::string("[F3] Mysz: ") + (m_isMouseEnabled ? "ON" : "OFF"));
                }
            }
        }

        if (m_isMouseEnabled)
        {
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    log("[LPM] X: " + std::to_string(mousePressed->position.x) + " Y: " + std::to_string(mousePressed->position.y));
                }
            }
        }
    }
}

void Engine::update(float dt)
{
    sf::Vector2f currentSize = m_window.getView().getSize();
    sf::Vector2f pos = m_ball.getPosition();
    float diameter = m_ball.getRadius() * 2.0f;

    pos += m_ballVelocity * m_animationSpeed * dt;

    if (pos.x < 0.0f) { pos.x = 0.0f; m_ballVelocity.x = -m_ballVelocity.x; }
    else if (pos.x + diameter > currentSize.x) { pos.x = currentSize.x - diameter; m_ballVelocity.x = -m_ballVelocity.x; }

    if (pos.y < 0.0f) { pos.y = 0.0f; m_ballVelocity.y = -m_ballVelocity.y; }
    else if (pos.y + diameter > currentSize.y) { pos.y = currentSize.y - diameter; m_ballVelocity.y = -m_ballVelocity.y; }

    m_ball.setPosition(pos);
}

void Engine::clearScreen(sf::Color color)
{
    m_window.clear(color);
}

void Engine::render()
{
    clearScreen(m_bgColor);
    m_window.draw(m_ball);
    m_window.display();
}

void Engine::log(const std::string& message)
{
    std::cout << message << std::endl;
    if (m_logFile.is_open())
    {
        m_logFile << message << std::endl;
    }
}

void Engine::close()
{
    if (m_window.isOpen())
    {
        log("Zamykanie okna i deinicjacja silnika.");
        m_window.close();
    }
    if (m_logFile.is_open())
    {
        m_logFile.close();
    }
}