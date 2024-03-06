#pragma once

#include <iostream>
#include <cmath>
#include "Vector.hpp"

using namespace std;

class Mat4 {
	public:
		float mat[4][4];

		Mat4(float x1, float x2, float x3, float x4,
			 float y1, float y2, float y3, float y4,
			 float z1, float z2, float z3, float z4,
			 float w1, float w2, float w3, float w4) {
			mat[0][0] = x1; mat[0][1] = x2; mat[0][2] = x3; mat[0][3] = x4;
			mat[1][0] = y1; mat[1][1] = y2; mat[1][2] = y3; mat[1][3] = y4;
			mat[2][0] = z1; mat[2][1] = z2; mat[2][2] = z3; mat[2][3] = z4;
			mat[3][0] = w1; mat[3][1] = w2; mat[3][2] = w3; mat[3][3] = w4;
		}

		Mat4(float homogene = 1.0f) {
			mat[0][0] = 1.0f; mat[0][1] = 0.0f; mat[0][2] = 0.0f; mat[0][3] = 0.0f;
			mat[1][0] = 0.0f; mat[1][1] = 1.0f; mat[1][2] = 0.0f; mat[1][3] = 0.0f;
			mat[2][0] = 0.0f; mat[2][1] = 0.0f; mat[2][2] = 1.0f; mat[2][3] = 0.0f;
			mat[3][0] = 0.0f; mat[3][1] = 0.0f; mat[3][2] = 0.0f; mat[3][3] = homogene;
		}

		Mat4(Mat4 const &src) {
			*this = src;
		}

		Mat4& operator=(Mat4 const &src) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					mat[i][j] = src.mat[i][j];
				}
			}
			return *this;
		}

		Mat4 operator*(Mat4 const &src) const {
			Mat4 result;

			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					result.mat[i][j] = 0;
					for (int k = 0; k < 4; ++k) {
						result.mat[i][j] += this->mat[i][k] * src.mat[k][j];
					}
				}
			}

			return result;
		}
		

		friend std::ostream& operator<<(std::ostream& os, const Mat4& obj) {
			for (int i = 0; i < 4; i++) {
				os << "[ ";
				for (int j = 0; j < 4; j++) {
					os << obj.mat[i][j];
					if (j < 3) {
						os << ", ";
					}
				}
				os << " ]" << std::endl;
			}
			return os;
		}
	
		Mat4	translate(Vec3 vector) {
			Mat4 translation(1.f, 0.f, 0.f, 0.f,
							0.f, 1.f, 0.f, 0.f,
							0.f, 0.f, 1.f, 0.f,
							vector.x, vector.y, vector.z, 1.f);

			// Multipliez la matrice de translation avec la matrice actuelle
			return translation * *this;
		}

		Vec4 multiplyVector(const Vec4 vector) const {
			Vec4 result(
				mat[0][0] * vector.x + mat[0][1] * vector.y + mat[0][2] * vector.z + mat[0][3] * vector.w,
				mat[1][0] * vector.x + mat[1][1] * vector.y + mat[1][2] * vector.z + mat[1][3] * vector.w,
				mat[2][0] * vector.x + mat[2][1] * vector.y + mat[2][2] * vector.z + mat[2][3] * vector.w,
				mat[3][0] * vector.x + mat[3][1] * vector.y + mat[3][2] * vector.z + mat[3][3] * vector.w
			);

			return result;
		}

		Mat4 rotate(float angle, float x, float y, float z) {
			Mat4 result(1.0f);

			float radians = angle * (M_PI / 180.0f);
			float c = cos(radians);
			float s = sin(radians);
			float one_minus_c = 1.0f - c;

			float xy = x * y;
			float xz = x * z;
			float yz = y * z;
			float xs = x * s;
			float ys = y * s;
			float zs = z * s;

			float f00 = x * x * one_minus_c + c;
			float f01 = xy * one_minus_c + zs;
			float f02 = xz * one_minus_c - ys;
			float f10 = xy * one_minus_c - zs;
			float f11 = y * y * one_minus_c + c;
			float f12 = yz * one_minus_c + xs;
			float f20 = xz * one_minus_c + ys;
			float f21 = yz * one_minus_c - xs;
			float f22 = z * z * one_minus_c + c;

			result.mat[0][0] = mat[0][0] * f00 + mat[1][0] * f01 + mat[2][0] * f02;
			result.mat[0][1] = mat[0][1] * f00 + mat[1][1] * f01 + mat[2][1] * f02;
			result.mat[0][2] = mat[0][2] * f00 + mat[1][2] * f01 + mat[2][2] * f02;
			result.mat[0][3] = mat[0][3] * f00 + mat[1][3] * f01 + mat[2][3] * f02;
			result.mat[1][0] = mat[0][0] * f10 + mat[1][0] * f11 + mat[2][0] * f12;
			result.mat[1][1] = mat[0][1] * f10 + mat[1][1] * f11 + mat[2][1] * f12;
			result.mat[1][2] = mat[0][2] * f10 + mat[1][2] * f11 + mat[2][2] * f12;
			result.mat[1][3] = mat[0][3] * f10 + mat[1][3] * f11 + mat[2][3] * f12;
			result.mat[2][0] = mat[0][0] * f20 + mat[1][0] * f21 + mat[2][0] * f22;
			result.mat[2][1] = mat[0][1] * f20 + mat[1][1] * f21 + mat[2][1] * f22;
			result.mat[2][2] = mat[0][2] * f20 + mat[1][2] * f21 + mat[2][2] * f22;
			result.mat[2][3] = mat[0][3] * f20 + mat[1][3] * f21 + mat[2][3] * f22;

			return result;
		}

		void scale(const Vec3 factors) {
			mat[0][0] *= factors.x;
			mat[1][1] *= factors.y;
			mat[2][2] *= factors.z;
		}

		void resetScaleDiagonal() {
			mat[0][0] = 1.0f;
			mat[1][1] = 1.0f;
			mat[2][2] = 1.0f;
		}

		float* GetDataPtr() {
			return &mat[0][0];
		}
};