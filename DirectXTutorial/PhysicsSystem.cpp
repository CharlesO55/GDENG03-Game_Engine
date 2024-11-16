#include "PhysicsSystem.h"

#include "Debugger.h"


PhysicsSystem* PhysicsSystem::instance = nullptr;

PhysicsSystem::PhysicsSystem()
{
    this->m_PhysicsCommon = new reactphysics3d::PhysicsCommon();

    reactphysics3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
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
    delete PhysicsSystem::instance;
}

void PhysicsSystem::RegisterComponent(PhysicsComponent* comp)
{
    m_Components.push_back(comp);
}

PhysicsSystem::ComponentList PhysicsSystem::GetAllComponents()
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
