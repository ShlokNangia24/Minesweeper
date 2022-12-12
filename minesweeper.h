#pragma once
#include "Toolbox.h"
#include "SFML/Graphics.hpp"
int launch();
void restart(Toolbox& toolbox);
void render(Toolbox& toolbox, Event event);
void toggleDebugMode(Toolbox& toolbox);
bool getDebugMode(Toolbox& toolbox){return toolbox.debugMode;};
void testOne(Toolbox& toolbox);
void testTwo(Toolbox& toolbox);


