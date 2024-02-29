#include "../vendors/lib.h"

#include "../Model/Model.hpp"

#ifndef SHADER_HPP
# define SHADER_HPP

using namespace std;

class Shader {
	public:
		unsigned int id;

        Shader();
		Shader(const char * vertexShaderPath, const char * fragmentShaderPath);
		void activate();

		string loadShaderString(const char* filepath);
		GLuint compileShader(const char* filepath, GLenum type);

		// uniform functions
		// void setMat4(std::string name, Mat4 val);
};

#endif
