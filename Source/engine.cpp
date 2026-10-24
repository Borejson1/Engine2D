#include "Engine.h"
#include <iostream>
#include <optional>

Engine::Engine()
{
    m_logFile.open("engine_log.txt", std::ios::out | std::ios::trunc);
    log("Inicjalizacja obiektu Engine.");
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
        log("Okno zainicjowane w trybie pelnoekranowym.");
    }
    else
    {
        m_window.create(sf::VideoMode(m_windowSize), m_title, sf::Style::Default, sf::State::Windowed);
        log("Okno zainicjowane w trybie okienkowym (" + std::to_string(windowSize.x) + "x" + std::to_string(windowSize.y) + ").");
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
    log("Ustawiono parametry: FPS=" + std::to_string(fps) + ", Klawiatura=" + (enableKeyboard ? "ON" : "OFF") + ", Mysz=" + (enableMouse ? "ON" : "OFF"));
}

void Engine::clearScreen(sf::Color color)
{
    m_clearColor = color;
    m_window.clear(color);
}

void Engine::log(const std::string& message)
{
    std::cout << "[LOG] " << message << std::endl;
    if (m_logFile.is_open())
    {
        m_logFile << message << std::endl;
    }
}

void Engine::close()
{
    if (m_window.isOpen())
    {
        log("Zamykanie okna silnika.");
        m_window.close();
    }
    if (m_logFile.is_open())
    {
        m_logFile.close();
    }
}

void Engine::setRenderCallback(std::function<void(sf::RenderWindow&)> callback)
{
    m_renderCallback = std::move(callback);
}

void Engine::run()
{
    log("Uruchomienie glownej petli gry.");
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
            log("Zmiana rozmiaru okna: " + std::to_string(resized->size.x) + "x" + std::to_string(resized->size.y));
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
                    log("Limit FPS zmieniony na: " + std::to_string(m_frameRateLimit));
                }
                else if (keyPressed->code == sf::Keyboard::Key::F3)
                {
                    m_isMouseEnabled = !m_isMouseEnabled;
                    if (m_isMouseEnabled) {
                        log("Obsluga myszy: ON");
                    }
                    else {
                        log("Obsluga myszy: OFF");
                    }
                }
            }
        }

        if (m_isMouseEnabled)
        {
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    log("Klikniecie myszy LPM: X=" + std::to_string(mousePressed->position.x) + " Y=" + std::to_string(mousePressed->position.y));
                }
            }
        }
    }
}

void Engine::update(float dt)
{
    
}

void Engine::render()
{
    clearScreen(m_clearColor);

    if (m_renderCallback)
    {
        m_renderCallback(m_window);
    }

    m_window.display();
}