#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	Initialize(MYVECTOR(100.f, 100.f, 0.f), MYVECTOR(5.f, 3.f, 0.f), MYVECTOR(1.f, 1.f, 0.f), 30.f);
}

GameObject::GameObject(const MYVECTOR& Pos, const MYVECTOR& Speed, const MYVECTOR& Color, const float& Scale)
{
	Initialize(Pos, Speed, Color, Scale);
}


GameObject::~GameObject()
{
}

void GameObject::Initialize(const MYVECTOR& Pos, const MYVECTOR& Speed, const MYVECTOR& Color, const float& Scale)
{
	m_vPosition = Pos;
	m_fScale = Scale;
	m_Color = Color;
	m_Speed = Speed; 
	m_Life = 100.f;
	m_createTime = timeGetTime() * 0.01f;
}

void GameObject::Update(float elapsedTime)
{
	m_vPosition = m_vPosition + (m_Speed * elapsedTime * 0.001f);

	if (m_vPosition.x >= WINDOW_WIDTH / 2 || m_vPosition.x <= -WINDOW_WIDTH / 2)
		m_Speed.x *= -1;
	if (m_vPosition.y >= WINDOW_HEIGHT / 2 || m_vPosition.y <= -WINDOW_HEIGHT / 2)
		m_Speed.y *= -1;

	m_Life -= 0.2f;
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

