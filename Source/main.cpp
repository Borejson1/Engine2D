#include "Engine.h"

int main()
{
    Engine engine;

    engine.init({ 800, 600 }, "EngineMaster2D", false);
    engine.setParameters(60, true, true);

    engine.run();

    return 0;
}