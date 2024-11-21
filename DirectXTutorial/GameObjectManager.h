#pragma once
#include <vector>

#include "Primitive.h"


class GameObjectManager
{
private:
	static GameObjectManager* i;
	GameObjectManager();
	~GameObjectManager();

	std::vector<Primitive*> m_Objects;
	SceneObject* m_SelectedObject;

public:
	static GameObjectManager* Get();
	
	void Init();
	void Update();
	void Release();

	bool TryFind(std::string name, SceneObject* output);
	void Register(Primitive* obj);
	void Destroy(Primitive* obj);


public:
	void SelectObject(SceneObject* obj);
	SceneObject* GetSelectedObject();

	std::vector<Primitive*> GetAllObjects();



	void CreateWorld();
	void InstantiateObj(const std::wstring objName);

	void SpawnCubes(int nCubes = 10);
};