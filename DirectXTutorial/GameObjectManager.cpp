#include "GameObjectManager.h"

#include "Cube.h"
#include "Plane.h"
#include "Circle.h"
#include "Quad.h"
#include "ObjImport.h"

#include <string>

#include "Debugger.h"

GameObjectManager* GameObjectManager::instance = nullptr;

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
	return instance;
}

void GameObjectManager::Init()
{
	if (!GameObjectManager::instance) {
		GameObjectManager::instance = new GameObjectManager();
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
	delete GameObjectManager::instance;
}

void GameObjectManager::Register(Primitive* obj)
{
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
	Primitive* plane = new Plane(Vector3D(96 / 256.f, 125 / 256.f, 141 / 256.f));
	plane->initialize();
	plane->getTransform()->move(Vector3D(0, -5, 0));
	plane->getTransform()->scale(Vector3D(20));
	Register(plane);


	Primitive* cube = new Cube();
	cube->initialize();
	cube->getTransform()->setPosition(Vector3D(0, 5, 0));
	Register(cube);


	Primitive* biggerCube = new Cube();
	biggerCube->initialize();
	biggerCube->getTransform()->setPosition(Vector3D(-3, 5, 0));
	biggerCube->getTransform()->setScale(Vector3D(2));
	Register(biggerCube);

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
