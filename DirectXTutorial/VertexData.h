#pragma once
#include <iostream>

#include "Vector3D.h"
#include "Matrix4.h"


struct vec3 {
	float x, y, z;

	void print() const {
		std::cout << '(' << x << ', ' << y << ', ' << z << ')';
	}
};

struct vertex {
	Vector3D position;
	//Vector3D position1;
	Vector3D color;
	Vector3D color1;

	/*void print() const {
		position.print();
		color.print(); 
		std::cout << std::endl;
	}*/
};

__declspec(align(16))
struct constant
{
	Matrix4 m_world;
	Matrix4 m_view;
	Matrix4 m_proj;
	float m_time;
};