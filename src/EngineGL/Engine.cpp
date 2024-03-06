#include "Engine.hpp"
#include "Callback.hpp"

using namespace std;

Engine engine;

Engine::Engine() {
	this->model = Model();
	this->shader = Shader();
}

Engine::~Engine() { }

void	Engine::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// For MACOS
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	this->window = glfwCreateWindow(800, 600, "HumanGL", NULL, NULL);

	if (this->window == NULL)
	{
		cout << "Could not create window" << endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		return;
	}    

	// Setup all callbacks
	glfwSetFramebufferSizeCallback(this->window, Callback::framebufferSizeCallback);  
	glfwSetKeyCallback(this->window, Callback::keyCallback);
	glfwSetScrollCallback(this->window, Callback::scrollCallback);
	glfwSetDropCallback(this->window, Callback::dropCallback);
}

void	Engine::loadModel(const char * path)
{
	this->model = Model(path);
	this->model.loadModel();
	this->model.setVertices(NO_COLOR_MODE);
	
	this->models = vector<Model>();
	this->models.push_back(this->model);
}

void	Engine::addModel(const char * path, Vec3 color)
{
	Model model = Model(path);

	model.color = color;

	model.loadModel();
	model.setVertices(TEXTURE_MODE);

	model.texLoc =  glGetUniformLocation(this->shader.id, "tex");

	this->models.push_back(model);
}

void	Engine::loadShader(const char * vertexShaderPath, const char * fragmentShaderPath)
{
	this->shader = Shader(vertexShaderPath, fragmentShaderPath);
}

void	Engine::render()
{
	while (!glfwWindowShouldClose(this->window))
	{
		// rendering
		glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& model : this->models)
		{
			// model.Rotate(0.2f, 0.2f, 0.2f, 0.0f);
			model.draw(this->shader.id);
		}

		glfwSwapBuffers(this->window);
		glfwPollEvents();    
	}
}

void	Engine::cleanUp()
{
	for (auto& model : this->models)
		model.deleteBuffers();

	this->shader.deleteShader();
}