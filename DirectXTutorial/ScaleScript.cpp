#include "ScaleScript.h"

#include "SceneObject.h"

#include "EngineTime.h"

#include <cmath>

ScaleScript::ScaleScript(SceneObject* owner) : Component(ComponentID::ROTATOR, owner)
{
}

void ScaleScript::update()
{
	m_Owner->getTransform()->setScale(
		Vector3D::lerp(Vector3D(1), Vector3D(2), (sin(EngineTime::getTotalTime()) + 1) / 2)
	);

	
}