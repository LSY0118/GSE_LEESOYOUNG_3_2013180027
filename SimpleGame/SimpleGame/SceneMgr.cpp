#include "stdafx.h"
#include "SceneMgr.h"

#include "Renderer.h"
#include "GameObject.h"


SceneMgr::SceneMgr()
{
	Initialize();
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::Initialize()
{
	m_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = new GameObject(MYVECTOR(rand() % WINDOW_WIDTH - WINDOW_WIDTH / 2, rand() % WINDOW_HEIGHT - WINDOW_HEIGHT / 2, 0.f),
			MYVECTOR(rand() % 6 - 4, rand() % 4 - 3, 0.f), MYVECTOR(1.f, 1.f, 1.f), 30.f);
	}
}

void SceneMgr::Update()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i]->Update();

		for (int j = i; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (m_objects[i]->checkCrush(m_objects[j]))
			{
				m_objects[i]->SetColor(MYVECTOR(1.f, 0.f, 0.f));
				m_objects[j]->SetColor(MYVECTOR(1.f, 0.f, 0.f));
			}
			else
			{
				m_objects[i]->SetColor(MYVECTOR(1.f, 1.f, 1.f));
				m_objects[j]->SetColor(MYVECTOR(1.f, 1.f, 1.f));
			}
		}
	}
}

void SceneMgr::Render()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_Renderer->DrawSolidRect(m_objects[i]->GetPos().x, m_objects[i]->GetPos().y, m_objects[i]->GetPos().z, 
			m_objects[i]->GetScale(), m_objects[i]->GetColor().x, m_objects[i]->GetColor().y, m_objects[i]->GetColor().z, 1.f);
	}
}