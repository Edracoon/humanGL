#include "Engine.hpp"

using namespace std;

class Color {
	public:
		
		static const Vec3 Blue;
		static const Vec3 Green;
		static const Vec3 Red;

		static const Vec3 Gray;
		static const Vec3 Black;
		static const Vec3 White;

		static const Vec3 Yellow;
		static const Vec3 Cyan;
		static const Vec3 Magenta;

		static const Vec3 Orange;
		static const Vec3 Purple;
		static const Vec3 Pink;
};

const Vec3 Color::Blue = Vec3(0.f, 0.f, 1.f);
const Vec3 Color::Green = Vec3(0.f, 1.f, 0.f);
const Vec3 Color::Red = Vec3(1.f, 0.f, 0.f);

const Vec3 Color::Gray = Vec3(0.5f, 0.5f, 0.5f);
const Vec3 Color::Black = Vec3(0.f, 0.f, 0.f);
const Vec3 Color::White = Vec3(1.f, 1.f, 1.f);

const Vec3 Color::Yellow = Vec3(1.f, 1.f, 0.f);
const Vec3 Color::Cyan = Vec3(0.f, 1.f, 1.f);
const Vec3 Color::Magenta = Vec3(1.f, 0.f, 1.f);

const Vec3 Color::Orange = Vec3(1.f, 0.5f, 0.f);
const Vec3 Color::Purple = Vec3(0.5f, 0.f, 1.f);
const Vec3 Color::Pink = Vec3(1.f, 0.f, 0.5f);

