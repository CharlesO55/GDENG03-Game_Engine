#pragma once
#include "Matrix4x4.h"

#include "Component.h"
#include "Transformation.h"

#include <vector>

class SceneObject
{
public:
	SceneObject(std::string name);
	~SceneObject();

	void setChild(SceneObject* child);

	bool tryGetComponent(ComponentID ID, Component*& result);
	void AddComponent(Component* component);


	Transformation* getTransform();
	std::string getName();


protected:
	SceneObject* m_child = nullptr;
	std::vector<Component*> m_Components = {};

	std::string m_Name;
};