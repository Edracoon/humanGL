#include "EngineGL/Engine.hpp"
#include "BodyPart.hpp"

using namespace std;

class Human {
	public:
		// Body parts
		BodyPart torso;
		BodyPart leftArm;
		BodyPart rightArm;
		BodyPart leftLeg;
		BodyPart rightLeg;
		BodyPart head;

		Model model = Model(path);
		model.color = color;
		model.loadModel();
		model.setVertices(TEXTURE_MODE);
		model.texLoc = glGetUniformLocation(this->shader.id, "tex");

		Human();
		~Human();

		void initBodyParts();

		void Scale(float scale);
		void Translate(float x, float y, float z);
		void Rotate(float angle, float x, float y, float z);
};
