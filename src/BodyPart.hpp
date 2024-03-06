#include "EngineGL/Engine.hpp"
#include "Math/Quaternion.hpp"

using namespace std;

class BodyPart {
	public:
		Model model;

		// Reference to the parent body part
		BodyPart&			parent;
		// Child body parts
		vector<BodyPart>	children;

		// Local position relative to the parent as a vector
		Vec3			localPosition = Vec3(0.f, 0.f, 0.f);

		// Local rotation relative to the parent as a quaternion
		Quaternion		localRotation = Quaternion(1.f, 0.f, 0.f, 0.f);

		// Local scale relative to the parent
		float			localScale = 1.f;

		BodyPart(string path, Color color, float scale, float x, float y, float z);
		~BodyPart();

		void Scale(float scale);
		void Translate(float x, float y, float z);
		void Rotate(float angle, float x, float y, float z);
};