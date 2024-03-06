#include "EngineGL/Engine.hpp"
#include "EngineGL/Color.hpp"

using namespace std;

int main(int ac, char **av)
{
	// Create engine and init window
	engine.initWindow();

	// Make this model the torax of the human
	engine.addModel("resources/rectangle.obj", Color::Orange);
	engine.models[0].Scale(1.0f);
	engine.models[0].Translate(0.f, 0.0f, 0.f);

	// Load the left arm
	engine.addModel("resources/rectangle.obj", Color::Pink);
	engine.models[1].Scale(0.5f);
	engine.models[1].Translate(-0.05f, 0.05f, 0.f);

	// Load the right arm
	engine.addModel("resources/rectangle.obj", Color::Pink);
	engine.models[2].Scale(0.5f);
	engine.models[2].Translate(0.05f, 0.05f, 0.f);

	// Load the left leg
	engine.addModel("resources/rectangle.obj", Color::Green);
	engine.models[3].Scale(0.5f);
	engine.models[3].Translate(-0.02f, -0.15f, 0.f);

	// Load the right leg
	engine.addModel("resources/rectangle.obj", Color::Green);
	engine.models[4].Scale(0.5f);
	engine.models[4].Translate(0.02f, -0.15f, 0.f);

	// Load the head
	engine.addModel("./resources/skull.obj");
	engine.models[5].Scale(0.5f);
	engine.models[5].Translate(0.f, 0.2f, 0.f);


	// Scale everything down
	for (auto& model : engine.models)
		model.Scale(0.25f);

	// Load shaders 
    engine.loadShader("./src/EngineGL/Shader/shaders/vertex_core.glsl", "./src/EngineGL/Shader/shaders/fragment_core.glsl");
	engine.shader.activate();

	// Rendering loop
	engine.render();

	// Clean up after rendering loop
	engine.cleanUp();
	glfwTerminate();

	return 0;
}