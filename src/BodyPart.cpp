#include "BodyPart.hpp"

BodyPart::BodyPart(string path, Color color, float scale, float x, float y, float z) {
	model = Model(path, color);
	localScale = scale;
	localPosition = Vec3(x, y, z);
}

~BodyPart();

void Scale(float scale);
void Translate(float x, float y, float z);
void Rotate(float angle, float x, float y, float z);