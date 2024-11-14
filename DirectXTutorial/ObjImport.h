#pragma once
#include "Primitive.h"

class ObjImport : public Primitive
{
public:
    ObjImport(const wchar_t* textureFile, const wchar_t* objFile);

    void initialize() override;
    void draw() override;

private:
    MeshPtr m_Mesh = nullptr;
};

