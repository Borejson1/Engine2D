#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include "Player.h"
#include <memory>
#include <string>

int main()
{
    Engine engine;
    engine.init({ 800, 600 }, "EngineMaster2D - Test", false);
    engine.setParameters(60, true, true);
    engine.clearScreen(sf::Color(30, 30, 30));

    Point2D p1(100.0f, 100.0f);
    Point2D p2(700.0f, 150.0f);
    Point2D p3(300.0f, 100.0f);
    Point2D p4(350.0f, 500.0f);

    LineSegment segDDA(p1, p2);
    LineSegment segSteep(p3, p4);

    std::vector<Point2D> polylinePoints = {
        Point2D(400.0f, 300.0f),
        Point2D(500.0f, 250.0f),
        Point2D(600.0f, 350.0f),
        Point2D(450.0f, 450.0f)
    };

    Player player(400.0f, 300.0f, &engine);

    const std::string basePath = "../../../Assets/";

    std::string animFiles[] = {
        basePath + "Move1.png",
        basePath + "Move2.png",
        basePath + "Move3.png",
        basePath + "Move4.png",
        basePath + "Move5.png",
        basePath + "Move6.png",
        basePath + "Move7.png",
        basePath + "Move8.png"
    };

    for (const auto& file : animFiles) {
        auto tex = std::make_shared<sf::Texture>();
        if (tex->loadFromFile(file)) {
            int frameWidth = tex->getSize().x / 8;
            int frameHeight = tex->getSize().y;

            for (int i = 0; i < 8; i++) {
                sf::IntRect rect({ i * frameWidth, 0 }, { frameWidth, frameHeight });
                player.addSpriteFrame(tex, rect);
            }
        }
    }

    engine.setRenderCallback([&](sf::RenderWindow& window) {
        player.update(0.016f);
        PrimitiveRenderer renderer(window);

        p1.draw(renderer, sf::Color::Yellow);
        segDDA.draw(renderer, true, sf::Color::Green);
        segSteep.draw(renderer, true, sf::Color::Cyan);
        renderer.drawLine(100.0f, 120.0f, 700.0f, 170.0f, sf::Color::Red);
        renderer.drawCircle(200.0f, 350.0f, 40.0f, sf::Color::Magenta, false);
        renderer.drawRectangle(150.0f, 450.0f, 100.0f, 60.0f, sf::Color::White, true);
        renderer.drawPolyline(polylinePoints, true, sf::Color::Yellow);
        renderer.drawCircleTrig(200, 200, 45, sf::Color::Blue);
        renderer.drawEllipseTrig(550, 180, 80, 40, sf::Color(255, 165, 0));
        renderer.floodFill(180, 480, sf::Color::Green, sf::Color(30, 30, 30));
        renderer.drawRectangle(100.0f, 400.0f, 120.0f, 80.0f, sf::Color::White, false);
        renderer.borderFill(150, 440, sf::Color::Cyan, sf::Color::White);

        player.draw(window);
        });

    engine.run();
    return 0;
}