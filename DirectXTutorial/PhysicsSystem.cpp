#include "PhysicsSystem.h"

#include "Debugger.h"

#include "EngineTime.h"
#include "PhysicsComponent.h"

#include "SceneObject.h"

PhysicsSystem* PhysicsSystem::instance = nullptr;

PhysicsSystem::PhysicsSystem()
{
    this->m_PhysicsCommon = new reactphysics3d::PhysicsCommon();

    reactphysics3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    //settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
    settings.gravity = reactphysics3d::Vector3(0, -4, 0);
    m_PhysicsWorld = m_PhysicsCommon->createPhysicsWorld(settings);


    Debugger::Success("[Physics System] Created");
}

PhysicsSystem::~PhysicsSystem()
{
    Debugger::Warning("[Physics System] Destroyed");
}

PhysicsSystem* PhysicsSystem::Get()
{
    return PhysicsSystem::instance;
}

void PhysicsSystem::Init()
{
    if (PhysicsSystem::instance == nullptr)
        PhysicsSystem::instance = new PhysicsSystem();
    else
        Debugger::Warning("[Physics System] Duplicate");
}

void PhysicsSystem::Release()
{

    // TO DO: FIX CLEAN UP
    /*while (Get()->m_Components.size() > 0) {
        delete Get()->m_Components.back();
        Get()->m_Components.pop_back();
    }*/

    /*for (int i = 0; i < Get()->m_Components.size(); i++) {
        delete Get()->m_Components[i];
    }*/
    Get()->m_Components.clear();

    delete PhysicsSystem::instance;
    PhysicsSystem::instance = nullptr;
}

void PhysicsSystem::Update()
{
    if (!Get())
        return;

    Get()->m_PhysicsWorld->update(EngineTime::getDeltaTime());

    for (PhysicsComponent* comp : Get()->m_Components) {
        comp->update();
    }
}

void PhysicsSystem::RegisterComponent(PhysicsComponent* comp)
{
    m_Map[comp->GetOwner()->GetInstanceID()] = comp;
    m_Components.push_back(comp);
}

void PhysicsSystem::UnregisterComponent(PhysicsComponent* comp) {
    m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), comp), m_Components.end());
    m_Map[comp->GetOwner()->GetInstanceID()] = nullptr;
    m_Map.erase(comp->GetOwner()->GetInstanceID());
}

bool PhysicsSystem::TryFindComponent(int obj_ID, PhysicsComponent*& out)
{
    if (m_Map.find(obj_ID) != m_Map.end()) {
        out = m_Map[obj_ID];

        return true;
    }
    return false;
}

std::vector<PhysicsComponent*> PhysicsSystem::GetAllComponents()
{
    return m_Components;
}

reactphysics3d::PhysicsCommon* PhysicsSystem::GetPhysicsCommon()
{
    return m_PhysicsCommon;
}

reactphysics3d::PhysicsWorld* PhysicsSystem::GetPhysicsWorld()
{
    return m_PhysicsWorld;
}
