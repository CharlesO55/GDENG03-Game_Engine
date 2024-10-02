#pragma once

class Vector3D {
public:
	Vector3D() : x(0), y(0), z(0) {};
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z) {};
	
	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		return v;
	}

	float x, y, z;
};