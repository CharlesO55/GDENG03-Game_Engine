#include "SceneObject.h"

SceneObject::SceneObject(std::string name) : m_Name(name) {
	m_Components = {new Transformation(this)};
}

SceneObject::~SceneObject(){
	while (m_Components.size() > 0) {
		delete m_Components.back();
		m_Components.pop_back();
	}
}

void SceneObject::setChild(SceneObject* child)
{
	this->m_child = child;
}


bool SceneObject::tryGetComponent(ComponentID ID, Component*& result)
{
	for (int i = 0; i < m_Components.size(); i++) {
		if (m_Components[i]->GetID() == ID) {
			result = m_Components[i];
			return true;
		}
	}

	return false;
}

void SceneObject::AddComponent(Component* component)
{
	std::cout << '[' << m_Name << "] Added " << component->GetName() << std::endl;
	this->m_Components.push_back(component);
}

Transformation* SceneObject::getTransform()
{
	return (Transformation*)this->m_Components[0];
}

std::string SceneObject::getName()
{
	return m_Name;
}