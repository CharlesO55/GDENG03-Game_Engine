#include "Plane.h"

Plane::Plane()
{
	m_verts = {
		{ Vector3D(-1,0,-1), Vector3D(-1,0,-1),   Vector3D(1), Vector3D(1) }, //BL
		{ Vector3D(-1,0,1), Vector3D(-1,0,1),   Vector3D(1), Vector3D(1) }, //TL
		{ Vector3D(1, 0, 1), Vector3D(1, 0, 1),  Vector3D(1),  Vector3D(1) },	//TR
		{ Vector3D(1, 0, -1), Vector3D(1, 0, -1),    Vector3D(1), Vector3D(1) }  //BR
	};

	m_indices = {
		0, 1, 2,
		2, 3, 0,
		2, 1, 0,
		0, 3, 2
	};
}


Plane::~Plane()
{
	release();
}
