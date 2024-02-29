#include "Shader.hpp"

Shader::Shader() {
    this->id = 0;
}

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath) {
	int success;
	char infoLog[512];

	cout << "vertexShaderPath = " << vertexShaderPath << endl;
	cout << "fragmentShaderPath = " << fragmentShaderPath << endl;

	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	this->id = glCreateProgram();
	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
	glLinkProgram(this->id);

	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint Shader::compileShader(const char* filepath, GLenum type) {
	int success;
	char infolog[512];

	// Compile shader
    unsigned int shader;
    shader = glCreateShader(type);

    string shaderSrc = this->loadShaderString(filepath);
    const GLchar* shaderc_str = shaderSrc.c_str();
    
	glShaderSource(shader, 1, &shaderc_str, NULL);
    glCompileShader(shader);

    // Catch error
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infolog);
        cout << "Error with vertex shader compilation : " << infolog << endl;
    }

	return shader;
}

void Shader::activate() {
	glUseProgram(this->id);
}

string Shader::loadShaderString(const char *filename) {
	ifstream file;
	stringstream buf;

	string ret("");

	file.open(filename);

	if (file.is_open()) {
		buf << file.rdbuf();
		ret = buf.str();
	}
	else {
		cout << "Could not open " << filename << endl;
	}

	file.close();

	return ret;
};