#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"

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

    engine.setRenderCallback([&](sf::RenderWindow& window) {
        PrimitiveRenderer renderer(window);

        p1.draw(renderer, sf::Color::Yellow);

        segDDA.draw(renderer, true, sf::Color::Green);

        segSteep.draw(renderer, true, sf::Color::Cyan);

        renderer.drawLine(100.0f, 120.0f, 700.0f, 170.0f, sf::Color::Red);

        renderer.drawCircle(200.0f, 350.0f, 40.0f, sf::Color::Magenta, false);
        renderer.drawRectangle(150.0f, 450.0f, 100.0f, 60.0f, sf::Color::White, true);

        renderer.drawPolyline(polylinePoints, true, sf::Color::Yellow);
        });

    engine.run();
    return 0;
}