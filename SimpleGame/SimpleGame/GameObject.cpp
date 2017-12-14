#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	Initialize(MYVECTOR(100.f, 100.f, 0.f), MYVECTOR(5.f, 3.f, 0.f), MYVECTOR(1.f, 1.f, 0.f), 30.f);
}

GameObject::GameObject(const MYVECTOR& Pos, const MYVECTOR& Dir, const MYVECTOR& Color, const float& Scale, OBJECT_TYPE myType, OBJECT_TYPE myTeam)
{
	m_myType = myType;
	m_myTeam = myTeam;
	Initialize(Pos, Dir, Color, Scale);
}


GameObject::~GameObject()
{
}

void GameObject::Initialize(const MYVECTOR& Pos, const MYVECTOR& Dir, const MYVECTOR& Color, const float& Scale)
{
	m_vPosition = Pos;
	m_fScale = Scale;
	m_Color = Color;
	m_Direction = Dir;
	m_AniLevel = 0;

	if (m_myType == OBJECT_BUILDING)
	{
		m_Life = 500;
		m_Speed = 0;
		m_myDepthLevel = DEPTH_BUILDING;
	}
	if (m_myType == OBJECT_CHAR)
	{
		m_Life = 100;
		m_Speed = 300;
		m_myDepthLevel = DEPTH_CHAR;
	}
	if (m_myType == OBJECT_BULLET)
	{
		m_Life = 15;
		m_Speed = 100;
		m_myDepthLevel = DEPTH_ARR_BUL;
	}
	if (m_myType == OBJECT_ARROW)
	{
		m_Life = 10;
		m_Speed = 100;
		m_myDepthLevel = DEPTH_ARR_BUL;
	}

	m_maxLife = m_Life;
	m_AniTime = timeGetTime() * 0.001f;

	m_ParticleTime = 0.f;
}

void GameObject::Update(float elapsedTime)
{
	float curTime = timeGetTime() * 0.001f;
	
	m_ParticleTime += (elapsedTime * 0.001f);
	if (m_ParticleTime >= 0.5f)
		m_ParticleTime -= 0.1f;

	if (curTime - m_AniTime >= 0.3f)
	{
		m_AniLevel += 1;
		if (m_AniLevel > 3)
			m_AniLevel = 0;

		m_AniTime = curTime;
	}
	
	m_vPosition = m_vPosition + (m_Direction * elapsedTime * 0.001f) * m_Speed;

	if (m_vPosition.x + m_fScale >= WINDOW_WIDTH / 2 || m_vPosition.x - m_fScale <= -WINDOW_WIDTH / 2)
	{
		if (m_myType == OBJECT_ARROW || m_myType == OBJECT_BULLET)
		{
			m_Life = -1.f;
		}
		else
			m_Direction.x *= -1.f;
	}
	if (m_vPosition.y + m_fScale >= WINDOW_HEIGHT / 2 || m_vPosition.y - m_fScale <= -WINDOW_HEIGHT / 2)
	{
		if (m_myType == OBJECT_ARROW || m_myType == OBJECT_BULLET)
		{
			m_Life = -1.f;
		}
		else
			m_Direction.y *= -1.f;
	}
}

void GameObject::Render()
{
	
}

MYVECTOR& GameObject::GetPos()
{
	return m_vPosition;
}

float& GameObject::GetScale()
{
	return m_fScale;
}

MYVECTOR& GameObject::GetColor()
{
	return m_Color;
}

void GameObject::SetPosition(const float& x, const float& y)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
}

bool GameObject::checkCrush(GameObject* checkObj)
{
	float myMaxX = m_vPosition.x + m_fScale / 2;
	float myMaxY = m_vPosition.y + m_fScale / 2;
	float checkMaxX = checkObj->m_vPosition.x + checkObj->m_fScale / 2;
	float checkMaxY = checkObj->m_vPosition.y + checkObj->m_fScale / 2;
	float myMinX = m_vPosition.x - m_fScale / 2;
	float myMinY = m_vPosition.y - m_fScale / 2;
	float checkMinX = checkObj->m_vPosition.x - checkObj->m_fScale / 2;
	float checkMinY = checkObj->m_vPosition.y - checkObj->m_fScale / 2;

	if (myMaxX < checkMinX)
		return false;
	if (myMinX > checkMaxX)
		return false;
	if (myMaxY < checkMinY)
		return false;
	if (myMinY > checkMaxY)
		return false;

	return true;
}


