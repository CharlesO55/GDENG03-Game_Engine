#pragma once
#include "Matrix4.h"

class SceneObject
{
public:
	SceneObject();
	~SceneObject();
	void setChild(SceneObject* child);

	Matrix4 transform;
	
protected:
	SceneObject* m_child = nullptr;
};