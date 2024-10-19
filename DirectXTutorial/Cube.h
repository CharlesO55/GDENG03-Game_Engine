#pragma once
#include "Primitive.h"

class Cube : public Primitive
{
public:
	Cube();
	Cube(Vector3D color);
	~Cube();


	virtual void update() override;
private:
	Vector3D m_rotSpeed;
};