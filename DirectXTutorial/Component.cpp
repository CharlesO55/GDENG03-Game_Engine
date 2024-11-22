#include "Component.h"

Component::Component(std::string name, ComponentID ID, SceneObject* owner) : m_Name(name), m_ID(ID), m_Owner(owner) {}

Component::~Component()
{
}

std::string Component::GetName()
{
    return m_Name;
}

const ComponentID Component::GetID()
{
    return m_ID;
}

const SceneObject* Component::GetOwner()
{
    return m_Owner;
}
