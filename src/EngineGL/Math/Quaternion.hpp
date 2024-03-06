#pragma once

#include <iostream>
#include <cmath>
#include "Vector.hpp"

using namespace std;

class Quaternion {
	public:
		float w, x, y, z;

		Quaternion(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Quaternion(float angle, Vec3 axis) {
			float halfAngle = angle / 2;
			w = cos(halfAngle);
			x = axis.x * sin(halfAngle);
			y = axis.y * sin(halfAngle);
			z = axis.z * sin(halfAngle);
		}

		Quaternion() {
			x = 0.f;
			y = 0.f;
			z = 0.f;
			w = 1.f;
		}

		Quaternion(Quaternion const &src) {
			*this = src;
		}

		Quaternion& operator=(Quaternion const &src) {
			w = src.w;
			x = src.x;
			y = src.y;
			z = src.z;
			return *this;
		}

		// normalize the quaternion
		void normalize() {
			float len = 1.f / this->length();
			x *= len;
			y *= len;
			z *= len;
			w *= len;
		}

		// return the length of the quaternion
		float length() {
			return sqrt(x * x + y * y + z * z + w * w);
		}

		// reset the quaternion to identity
		void reset() {
			x = 0.f;
			y = 0.f;
			z = 0.f;
			w = 1.f;
		}

		Quaternion operator*(Quaternion const &src) const {
			Quaternion result;
			result.w = w * src.w - x * src.x - y * src.y - z * src.z;
			result.x = w * src.x + x * src.w + y * src.z - z * src.y;
			result.y = w * src.y - x * src.z + y * src.w + z * src.x;
			result.z = w * src.z + x * src.y - y * src.x + z * src.w;
			return result;
		}

		Quaternion operator*(Vec3 const &src) const {
			Quaternion result;
			result.w = -x * src.x - y * src.y - z * src.z;
			result.x = w * src.x + y * src.z - z * src.y;
			result.y = w * src.y - x * src.z + z * src.x;
			result.z = w * src.z + x * src.y - y * src.x;
			return result;
		}

		Quaternion operator*(float const &src) const {
			Quaternion result;
			result.w = w * src;
			result.x = x * src;
			result.y = y * src;
			result.z = z * src;
			return result;
		}

		Quaternion operator+(Vec3 const &src) const {
			Quaternion result;
			result.x = x + src.x;
			result.y = y + src.y;
			result.z = z + src.z;
			return result;
		}

		Quaternion operator-(Vec3 const &src) const {
			Quaternion result;
			result.x = x - src.x;
			result.y = y - src.y;
			result.z = z - src.z;
			return result;
		}
};