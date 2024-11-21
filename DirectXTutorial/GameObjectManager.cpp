#include "GameObjectManager.h"

#include "Cube.h"
#include "Plane.h"
#include "Circle.h"
#include "Quad.h"
#include "ObjImport.h"

#include <string>

#include "PhysicsComponent.h"

#include "Debugger.h"

GameObjectManager* GameObjectManager::i = nullptr;

GameObjectManager::GameObjectManager()
{
	Debugger::Success("[GameObject Manager] Created");
}

GameObjectManager::~GameObjectManager()
{
	Debugger::Warning("[GameObject Manager] Destroyed");
}

GameObjectManager* GameObjectManager::Get()
{
	return i;
}

void GameObjectManager::SelectObject(SceneObject* obj)
{
	m_SelectedObject = obj;
}

SceneObject* GameObjectManager::GetSelectedObject()
{
	return m_SelectedObject;
}

std::vector<Primitive*> GameObjectManager::GetAllObjects()
{
	return m_Objects;
}

void GameObjectManager::Init()
{
	if (!GameObjectManager::i) {
		GameObjectManager::i = new GameObjectManager();
	}
	else
		Debugger::Error("[GameObject Manager] Init twice");
}

void GameObjectManager::Update()
{
	for (int i = 0; i < m_Objects.size(); i++) {
		m_Objects[i]->update();
		m_Objects[i]->updateMVP();
		m_Objects[i]->draw();
	}
}

void GameObjectManager::Release()
{
	while (m_Objects.size() > 0) {
		delete m_Objects.back();
		m_Objects.pop_back();
	}
	m_SelectedObject = nullptr;

	delete GameObjectManager::i;
	GameObjectManager::i = nullptr;
}

bool GameObjectManager::TryFind(std::string name, SceneObject* output)
{
	for (int i = 0; i < m_Objects.size(); i++) {
		if (m_Objects[i]->GetName() == name)
			output = m_Objects[i];
			return true;
	}

	return false;
}

void GameObjectManager::Register(Primitive* obj)
{
	if (TryFind(obj->GetName(), nullptr)) {
		obj->SetName(obj->GetName() + " (" + std::to_string(m_Objects.size()) + ")");
	}
	
	m_Objects.push_back(obj);
}

void GameObjectManager::Destroy(Primitive* obj)
{
	auto res = std::find(m_Objects.begin(), m_Objects.end(), obj);

	if (res != m_Objects.end()) {
		m_Objects.erase(res);
	}
}

void GameObjectManager::CreateWorld()
{
	// CREATE A PLANE
	/*Primitive* plane = new Plane(Vector3D(96 / 256.f, 125 / 256.f, 141 / 256.f));
	plane->initialize();
	plane->getTransform()->move(Vector3D(0, -5, 0));
	plane->getTransform()->scale(Vector3D(20, 0.1, 20));
	Register(plane);*/

	//plane->getTransform()->update();
	//new PhysicsComponent(plane, reactphysics3d::BodyType::STATIC);

	Primitive* plane = new Cube(Vector3D(96 / 256.f, 125 / 256.f, 141 / 256.f));
	plane->initialize();
	//plane->getTransform()->setScale(Vector3D(20));
	plane->getTransform()->setPosition(Vector3D(0, -5, 0));
	plane->getTransform()->scale(Vector3D(20, 0.01f, 20));
	plane->getTransform()->update();
	Register(plane);

	plane->getTransform()->update();
	//new PhysicsComponent(plane, reactphysics3d::BodyType::STATIC);
	
	/*Primitive* cube = new Cube(Vector3D(1));
	cube->initialize();
	cube->getTransform()->setPosition(Vector3D(0, 0, 0));
	cube->getTransform()->update();
	Register(cube);*/

	//new PhysicsComponent(cube, reactphysics3d::BodyType::STATIC);

	SpawnCubes(1);
}

void GameObjectManager::InstantiateObj(const std::wstring objName)
{
	const Vector3D& spawnPos = Vector3D(m_Objects.size());
	
	std::wstring objFile = L"..\\Assets\\Meshes\\" + objName + L".obj";
	const wchar_t* texFile = L"..\\Assets\\Textures\\brick.png";
	
	Primitive* newObj = new ObjImport(texFile, objFile.c_str());
	newObj->initialize();
	newObj->getTransform()->setPosition(spawnPos);

	m_Objects.push_back(newObj);
}

void GameObjectManager::SpawnCubes(int nCubes)
{
	for (int i = 0; i < nCubes; i++) {
		Primitive* cube = new Cube();
		cube->initialize();
		cube->getTransform()->setPosition(Vector3D(0, 20, 0));
		cube->getTransform()->update();
		Register(cube);

		//new PhysicsComponent(cube);
	}
}
