#include "SceneObject.h"

SceneObject::SceneObject()
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::setChild(SceneObject* child)
{
	this->m_child = child;
}