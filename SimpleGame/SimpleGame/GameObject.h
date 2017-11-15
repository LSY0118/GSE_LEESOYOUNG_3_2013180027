#pragma once

#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "SceneMgr.h"

class GameObject
{
public:
	GameObject();
	GameObject(const MYVECTOR& Pos, const MYVECTOR& Dir, const MYVECTOR& Color, const float& Scale, OBJECT_TYPE myType);
	virtual ~GameObject();

	MYVECTOR& GetPos();
	float& GetScale();
	MYVECTOR& GetColor();
	float& GetLife() { return m_Life; }
	OBJECT_TYPE& GetObjType() { return m_myType; }

	void Render();
	void Update(float nowTime);
	void SetPosition(const float& x, const float& y);
	bool checkCrush(GameObject* checkObj);
	//void DeleteObj();

	void DecreaseHP(float dhp) { m_Life -= dhp; }

	void SetColor(MYVECTOR& Color) { m_Color = Color; }
	
protected:
	void Initialize(const MYVECTOR& Pos, const MYVECTOR& Dir, const MYVECTOR& Color, const float& Scale);
	bool m_Initialized = false;

	MYVECTOR m_vPosition;
	float m_fScale;
	MYVECTOR m_Color;
	MYVECTOR m_Direction;

	float m_createTime;
	float m_Life;
	float m_Speed;

	bool m_Action;
	float m_ActionTime;

	OBJECT_TYPE m_myType;
};