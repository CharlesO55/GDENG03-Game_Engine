#pragma once

#include "Vector3D.h"

#include <reactphysics3d/mathematics/Vector3.h>

class Debugger {
public:
	static void Success(const char* t) {
		printf("\033[0;32m%s\033[0m\n", t);
	}

	static void Warning(const char* t) {
		printf("\033[0;33m%s\033[0m\n", t);
	}

	static void Error(const char* t) {
		printf("\033[31;7m%s\033[0m\n", t);
		throw t;
	}

	static void PrintVector(const Vector3D vec) {
		printf("(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
	}

	static void PrintVector(const reactphysics3d::Vector3 vec) {
		printf("(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
	}

	static void PrintMatrix(const float* values16) {
		std::cout << "[" << values16[0] << ", " << values16[1] << ", " << values16[2] << ", " << values16[3] << ",\n";
		std::cout << " " << values16[4] << ", " << values16[5] << ", " << values16[6] << ", " << values16[7] << ",\n";
		std::cout << " " << values16[8] << ", " << values16[9] << ", " << values16[10] << ", " << values16[11] << ",\n";
		std::cout << " " << values16[12] << ", " << values16[13] << ", " << values16[14] << ", " << values16[15] << "]\n";
	}
};