#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include <reactphysics3d/reactphysics3d.h>
class PhysicsComponent;

class PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	typedef std::vector<PhysicsComponent*> ComponentList;


private:
	static PhysicsSystem* instance;
	
	PhysicsSystem();
	PhysicsSystem(const PhysicsSystem&) {};
	PhysicsSystem& operator=(const PhysicsSystem&) {};
	
	~PhysicsSystem();

private:
	ComponentList m_Components;
	reactphysics3d::PhysicsCommon* m_PhysicsCommon;
	reactphysics3d::PhysicsWorld* m_PhysicsWorld;

public:
	static PhysicsSystem* Get();

	static void Init();
	static void Release();

	void RegisterComponent(PhysicsComponent* comp);
	void UnregisterComponent(PhysicsComponent* comp);
	ComponentList GetAllComponents();
	reactphysics3d::PhysicsCommon* GetPhysicsCommon();
	reactphysics3d::PhysicsWorld* GetPhysicsWorld();
};

