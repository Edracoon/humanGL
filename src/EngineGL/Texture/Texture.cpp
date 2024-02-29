#include "Texture.hpp"

Texture::Texture() {
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->nrChannels = 0;
	this->data = NULL;
	this->active = false;
}

Texture::~Texture() { }

void	Texture::setActive(bool active) {
	if (active) {
		glActiveTexture(this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		// glUniform1i(glGetUniformLocation(this->shader.id, "ourTexture"), 0);  // 0 correspond à l'indice d'échantillonnage de la texture
		this->active = true;
	}
	else {
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		this->active = false;
	}
}

bool	Texture::loadTexture(const char* filePath) {

	if (!this->isFileTexture(filePath)) {
		cout << "loadTexture: file is not a texture: " << filePath << endl;
		return false;
	}

	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	this->data = stbi_load(filePath, &this->width, &this->height, &this->nrChannels, 0);
	if (this->data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(this->data);
	this->active = true;
	cout << "Texture loaded" << endl;
	return true;
}

bool	Texture::isFileTexture(const char* filePath) {
	// Convert the file path to lowercase for case-insensitive comparison
	std::string lowerPath(filePath);
	std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(), ::tolower);

	// Check if the file has a recognized image extension
	return (lowerPath.find(".jpg") != std::string::npos ||
			lowerPath.find(".jpeg") != std::string::npos ||
			lowerPath.find(".png") != std::string::npos ||
			lowerPath.find(".bmp") != std::string::npos ||
			// Add more supported extensions if needed
			// ...
			false);
}

ostream& operator<<(ostream& os, const Texture& texture) {
	// os << "Texture: '" << texture.textureName << "'" << endl;
	// os << "  Ambient: " << texture.ambient[0] << " | " << texture.ambient[1] << " | " << texture.ambient[2] << endl;
	// os << "  Diffuse: " << texture.diffuse[0] << " | " << texture.diffuse[1] << " | " << texture.diffuse[2] << endl;
	// os << "  Specular: " << texture.specular[0] << " | " << texture.specular[1] << " | " << texture.specular[2] << endl;
	// os << "  Specular exponent: " << texture.Ns << endl;
	// os << "  Optical density: " << texture.Ni << endl;
	// os << "  Dissolve factor: " << texture.d << endl;
	// os << "  Illumination model: " << texture.illum;
	return os;
}

