#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <cmath>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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