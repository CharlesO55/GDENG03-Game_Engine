#pragma once
#include <iostream>

struct vec3 {
	float x, y, z;

	void print() const {
		std::cout << '(' << x << ', ' << y << ', ' << z << ')';
	}
};

struct vertex {
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;

	void print() const {
		position.print();
		color.print(); 
		std::cout << std::endl;
	}
};

__declspec(align(16))
struct constant
{
	float m_time;
};