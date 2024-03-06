#ifndef ENGINE_HPP
# define ENGINE_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "vendors/lib.h"

#include "Model/Model.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Shader/Shader.hpp"

class Engine {
	public:
		Model			model;
		Shader			shader;

		vector<Model>	models;

		GLFWwindow		*window;

		Engine();
		~Engine();

		void	loadModel(const char * path);
		void	addModel(const char * path, Vec3 color = Vec3(1.f, 1.f, 1.f));

		void	loadShader(const char * vertexShaderPath, const char * fragmentShaderPath);

		void	initWindow();
		void	render();

		void	cleanUp();
};

extern Engine engine;

#endif