#pragma once
#include <vector>

#include "Primitive.h"


class GameObjectManager
{
private:
	static GameObjectManager* instance;
	GameObjectManager();
	~GameObjectManager();


public:	
	std::vector<Primitive*> m_Objects;

public:
	static GameObjectManager* Get();

	void Init();
	void Update();
	void Release();

	void Register(Primitive* obj);
	void Destroy(Primitive* obj);


	void CreateWorld();
	void InstantiateObj(const std::wstring objName);
};