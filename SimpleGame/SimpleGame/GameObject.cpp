#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	Initialize(MYVECTOR(100.f, 100.f, 0.f), MYVECTOR(5.f, 3.f, 0.f), MYVECTOR(1.f, 1.f, 0.f), 30.f);
}

GameObject::GameObject(const MYVECTOR& Pos, const MYVECTOR& Dir, const MYVECTOR& Color, const float& Scale, OBJECT_TYPE myType)
{
	m_myType = myType;
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

	if (m_myType == OBJECT_BUILDING)
	{
		m_Life = 500;
		m_Speed = 0;
		m_Action = true;
	}
	if (m_myType == OBJECT_CHARACTER)
	{
		m_Life = 100;
		m_Speed = 300;
		m_Action = true;
	}
	if (m_myType == OBJECT_BULLET)
	{
		m_Life = 20;
		m_Speed = 600;
		m_Action = true;
	}
	if (m_myType == OBJECT_ARROW)
	{
		m_Life = 10;
		m_Speed = 100;
		m_Action = false;
	}

	m_createTime = timeGetTime() * 0.001f;
}

void GameObject::Update(float elapsedTime)
{
	float curTime = timeGetTime() * 0.001f;
	if (curTime - m_createTime >= 3.f && m_myType == OBJECT_ARROW && m_Action == false)
	{
		m_Action = true;
	}

	m_vPosition = m_vPosition + (m_Direction * elapsedTime * 0.001f) * m_Speed;

	if (m_vPosition.x >= WINDOW_WIDTH / 2 || m_vPosition.x <= -WINDOW_WIDTH / 2)
		m_Direction.x *= -1;
	if (m_vPosition.y >= WINDOW_HEIGHT / 2 || m_vPosition.y <= -WINDOW_HEIGHT / 2)
		m_Direction.y *= -1;
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
	if (!m_Action)
		return false;

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


