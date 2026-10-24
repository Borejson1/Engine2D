#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

class Engine
{
public:
    Engine();
    ~Engine();

    void init(sf::Vector2u windowSize, const std::string& title, bool fullscreen = false);
    void setParameters(unsigned int fps, bool enableKeyboard, bool enableMouse);

    void run();

    void clearScreen(sf::Color color);
    void log(const std::string& message);
    void close();

    void setRenderCallback(std::function<void(sf::RenderWindow&)> callback);

private:
    void handleEvents();
    void update(float dt);
    void render();

private:
    sf::RenderWindow m_window;
    std::vector<sf::VideoMode> m_modes;
    sf::Clock m_clock;
    std::ofstream m_logFile;

    sf::Vector2u m_windowSize{ 800, 600 };
    std::string m_title{ "EngineMaster2D" };
    bool m_isFullscreen{ false };
    unsigned int m_frameRateLimit{ 60 };
    bool m_isKeyboardEnabled{ true };
    bool m_isMouseEnabled{ true };
    sf::Color m_clearColor{ sf::Color::Black };

    std::function<void(sf::RenderWindow&)> m_renderCallback;
};