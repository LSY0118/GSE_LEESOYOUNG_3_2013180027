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
	delete m_Renderer;
	m_Renderer = NULL;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i])
		{
			delete m_objects[i];
			m_objects[i] = NULL;
		}
	}
}

void SceneMgr::Initialize()
{
	m_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	//for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	//{
	//	m_objects[i] = new GameObject(MYVECTOR(rand() % WINDOW_WIDTH - WINDOW_WIDTH / 2, rand() % WINDOW_HEIGHT - WINDOW_HEIGHT / 2, 0.f),
	//		MYVECTOR(rand() % 6 - 4, rand() % 4 - 3, 0.f), MYVECTOR(1.f, 1.f, 1.f), 30.f);
	//}
}

void SceneMgr::Update(float frameTime)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i])
		{
			m_objects[i]->Update(frameTime);
			if (m_objects[i]->GetLife() < 0.f)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = i + 1; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (m_objects[i] && m_objects[j])
			{
				if (m_objects[i]->checkCrush(m_objects[j]))
				{
					m_objects[i]->SetColor(MYVECTOR(1.f, 0.f, 0.f));
					m_objects[j]->SetColor(MYVECTOR(1.f, 0.f, 0.f));
				}
				else
				{
					// 버그 있음.
					//m_objects[i]->SetColor(MYVECTOR(1.f, 1.f, 1.f));
					m_objects[j]->SetColor(MYVECTOR(1.f, 1.f, 1.f));
				}
			}
		}
	}
	
}

void SceneMgr::Render()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i])
		{
			m_Renderer->DrawSolidRect(m_objects[i]->GetPos().x, m_objects[i]->GetPos().y, m_objects[i]->GetPos().z,
				m_objects[i]->GetScale(), m_objects[i]->GetColor().x, m_objects[i]->GetColor().y, m_objects[i]->GetColor().z, 1.f);
		}
	}
}

void SceneMgr::CreateObject(float x, float y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (!m_objects[i])
		{
			m_objects[i] = new GameObject(MYVECTOR(x, y, 0.f), MYVECTOR(float(rand() % 200 - 100), float(rand() % 200 - 100), 0.f), MYVECTOR(1.f, 1.f, 1.f), 30.f);
			return;
		}
	}
}