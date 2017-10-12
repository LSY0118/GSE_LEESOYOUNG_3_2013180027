#pragma once

#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

typedef struct myVector
{
	float x;
	float y;
	float z;
	myVector()
	{
		x = y = z = 0;
	}
	myVector(float _x, float _y, float _z = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	myVector operator *(const myVector& r1)
	{
		return myVector(x * r1.x, y * r1.y, z * r1.z);
	}
	myVector operator +(const myVector& r1)
	{
		return myVector(x + r1.x, y + r1.y, z + r1.z);
	}
	void Normalize()
	{
		float len = sqrtf(x * x + y * y + z * z);
		x /= len;
		y /= len;
		z /= len;
	}
}MYVECTOR;

class GameObject
{
public:
	GameObject();
	~GameObject();

	MYVECTOR& GetPos();
	MYVECTOR& GetScale();
	MYVECTOR& GetColor();

	void Render();
	void Update();
	void SetPosition(const float& x, const float& y);

private:
	void Initialize();

	bool m_Initialized = false;

	MYVECTOR m_vPosition;
	MYVECTOR m_fScale;
	MYVECTOR m_Color;
	MYVECTOR m_Speed;
};

