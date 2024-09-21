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
	vec3 color;

	void print() const {
		position.print();
		color.print(); 
		std::cout << std::endl;
	}
};