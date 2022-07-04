#include <FEngine/Engine/Engine.hpp>
#include <stdio.h>

int main(int argc, char **argv) {

	Engine engine;

	engine.init(1280, 720, "Engine", false, false);

	while (!engine.window.isCloseRequested())
	{
		engine.update();
		engine.render();
	}

	engine.destroy();

	return 0;
}
