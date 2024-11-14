#include "MeshManager.h"
#include "Mesh.h"

#include "Debugger.h"
MeshManager::MeshManager()
{
	Debugger::Success("[Mesh Manager] Created.");
}


MeshManager::~MeshManager()
{
	Debugger::Warning("[Mesh Manager] Destroyed.");
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Mesh>(createResourceFromFile(file_path));
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path);
	}
	catch (...) {
		Debugger::Error("[Mesh Manager] Failed to create mesh");
	}

	return mesh;
}