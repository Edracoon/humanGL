#include "EngineGL/Engine.hpp"

using namespace std;

int main(int ac, char **av)
{
	if (av[1] == NULL || av[2] == NULL)
	{
		cout << "No object file specified" << endl;
		return 1;
	}

	engine.initWindow();

	engine.addModel(av[1]);
	engine.addModel(av[2]);

    engine.loadShader("./src/EngineGL/Shader/shaders/vertex_core.glsl", "./src/EngineGL/Shader/shaders/fragment_core.glsl");

    // engine.model.setVertices(NO_COLOR_MODE);

	engine.models[0].texLoc =  glGetUniformLocation(engine.shader.id, "tex");

	engine.shader.activate();

	cout << engine.models[0] << endl;

	engine.render();

	engine.models[0].deleteBuffers();

	glfwTerminate();

	return 0;
}