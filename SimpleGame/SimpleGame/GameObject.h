#pragma once

#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

class GameObject
{
public:
	GameObject();
	GameObject(const MYVECTOR& Pos, const MYVECTOR& Speed, const MYVECTOR& Color, const float& Scale);
	~GameObject();

	MYVECTOR& GetPos();
	float& GetScale();
	MYVECTOR& GetColor();
	float& GetLife() { return m_Life; }

	void Render();
	void Update(float nowTime);
	void SetPosition(const float& x, const float& y);
	bool checkCrush(GameObject* checkObj);
	//void DeleteObj();

	void SetColor(MYVECTOR& Color) { m_Color = Color; }
	
private:
	void Initialize(const MYVECTOR& Pos, const MYVECTOR& Speed, const MYVECTOR& Color, const float& Scale);
	bool m_Initialized = false;

	MYVECTOR m_vPosition;
	float m_fScale;
	MYVECTOR m_Color;
	MYVECTOR m_Speed;

	float m_createTime;
	float m_Life;
};

