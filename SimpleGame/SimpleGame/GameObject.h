#pragma once

#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "SceneMgr.h"

class GameObject
{
public:
	GameObject();
	GameObject(const MYVECTOR& Pos, const MYVECTOR& Dir, const MYVECTOR& Color, const float& Scale, OBJECT_TYPE myType, OBJECT_TYPE myTeam);
	virtual ~GameObject();

	MYVECTOR& GetPos();
	float& GetScale();
	MYVECTOR& GetColor();
	MYVECTOR& GetDir() { return m_Direction; }
	float& GetLife() { return m_Life; }
	float& GetMaxLife() { return m_maxLife; }
	float& GetDepthLevel() { return m_myDepthLevel; }
	int& GetAniLevel() { return m_AniLevel;	}
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

	float m_AniTime;
	float m_Life;
	float m_Speed;
	
	float m_myDepthLevel;
	int m_AniLevel;

	OBJECT_TYPE m_myType;
	OBJECT_TYPE m_myTeam;

	float m_maxLife;
};