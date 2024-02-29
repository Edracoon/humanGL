#pragma once

#include <iostream>
#include <cmath>

using namespace std;

class Vec4 {
	public : 
		float x, y, z, w;

		Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		void translate(float tx, float ty, float tz) {
			x += tx;
			y += ty;
			z += tz;
		}
};

class Vec3 {
	public:
		float x, y, z;

		// Constructeur
		Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		// Affichage
		void display() {
			std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
		}

		// Produit vectoriel
		Vec3 cross(const Vec3& other) const {
			return Vec3(
				y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x
			);
		}

		// Produit scalaire
		float dot(const Vec3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}

		// Norme du vecteur
		float length() const {
			return std::sqrt(x * x + y * y + z * z);
		}

		// Normalisation du vecteur
		Vec3 normalize() const {
			float len = length();
			if (len != 0.0f) {
				return Vec3(x / len, y / len, z / len);
			}
			return *this;
		}
};