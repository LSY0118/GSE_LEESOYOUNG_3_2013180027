#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	Initialize();
}


GameObject::~GameObject()
{
}

void GameObject::Initialize()
{
	m_vPosition.x = 100.f;
	m_vPosition.y = 100.f;
	m_vPosition.z = 0.f;

	m_fScale.x = 30.f;
	m_fScale.y = 30.f;
	m_fScale.z = 30.f;

	m_Color.x = 1.f;
	m_Color.y = 0.f;
	m_Color.z = 0.f;

	m_Speed = MYVECTOR(5.f, 3.f, 0.f);
}

void GameObject::Update()
{
	m_vPosition = m_vPosition + m_Speed;

	if (m_vPosition.x >= WINDOW_WIDTH / 2 || m_vPosition.x <= -WINDOW_WIDTH / 2)
		m_Speed.x *= -1;
	if (m_vPosition.y >= WINDOW_HEIGHT / 2 || m_vPosition.y <= -WINDOW_HEIGHT / 2)
		m_Speed.y *= -1;
}

void GameObject::Render()
{
	
}

MYVECTOR& GameObject::GetPos()
{
	return m_vPosition;
}

MYVECTOR& GameObject::GetScale()
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

