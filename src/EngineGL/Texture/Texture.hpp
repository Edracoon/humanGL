#ifndef TEXTURE_HPP
# define TEXTURE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "../vendors/stb/stb_image.h"
#include "../vendors/lib.h"

using namespace std;

class Texture
{
	public:
		int                 width, height, nrChannels;
		unsigned char       *data;
		unsigned int        textureID;
		bool                active = false;

		Texture();
		~Texture();

	bool					loadTexture(const char* filePath);
	void                    setActive(bool active);

	bool					isFileTexture(const char* filePath);

	// print operator overload
	friend ostream& operator<<(ostream& os, const Texture& texture);
};

#endif