#pragma once
#include "ComponentID.h"
#include <string>

class SceneObject;


class Component
{
public:
	Component(std::string name, ComponentID ID, SceneObject* owner);
	~Component();

	std::string GetName();
	const ComponentID GetID();
	const SceneObject* GetOwner();

	virtual void update() = 0;

protected:
	std::string m_Name;
	ComponentID m_ID;


	SceneObject* m_Owner = nullptr;
};