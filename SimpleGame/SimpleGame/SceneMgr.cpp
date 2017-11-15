#include "stdafx.h"
#include "SceneMgr.h"

#include "Renderer.h"
#include "GameObject.h"

using namespace std;

SceneMgr::SceneMgr()
{
	Initialize();
}


SceneMgr::~SceneMgr()
{
	delete m_Renderer;
	m_Renderer = NULL;

	if (m_BuildingObj)
	{
		delete m_BuildingObj;
		m_BuildingObj = NULL;
	}

	for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
	{
		if (m_PlayerObj[i])
		{
			delete m_PlayerObj[i];
			m_PlayerObj[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_BUL_ARR_COUNT; ++i)
	{
		if (m_BulletObj[i])
		{
			delete m_BulletObj[i];
			m_BulletObj[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_BUL_ARR_COUNT; ++i)
	{
		if (m_ArrowObj[i])
		{
			delete m_ArrowObj[i];
			m_ArrowObj[i] = NULL;
		}
	}
}

void SceneMgr::Initialize()
{
	m_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_BuildingTexID = m_Renderer->CreatePngTexture("Resource/building.png");

	m_BuildingObj = new GameObject(MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(1.f, 1.f, 0.f), 80.f, OBJECT_BUILDING);

	m_createBulletTime = timeGetTime() * 0.001f;
}

void SceneMgr::Update(float frameTime)
{
	float curTime = timeGetTime() * 0.001f;
	if (curTime - m_createBulletTime >= 0.5f)
	{
		for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			if (m_PlayerObj[i])
			{
				for (int j = 0; j < MAX_BUL_ARR_COUNT; ++j)
				{
					if (!m_ArrowObj[j])
					{
						MYVECTOR pos = MYVECTOR(m_PlayerObj[i]->GetPos().x, m_PlayerObj[i]->GetPos().y, m_PlayerObj[i]->GetPos().z);
						MYVECTOR Dir = MYVECTOR(float(rand() % 200 - 100), float(rand() % 200 - 100), 0.f);
						Dir.Normalize();
						m_ArrowObj[j] = new GameObject(pos, Dir, MYVECTOR(0.f, 1.f, 0.f), 10.f, OBJECT_ARROW);
						break;
					}
				}
			}
		}
		
		for (int i = 0; i < MAX_BUL_ARR_COUNT; ++i)
		{
			if (!m_BulletObj[i] && m_BuildingObj)
			{
				MYVECTOR pos = MYVECTOR(m_BuildingObj->GetPos().x, m_BuildingObj->GetPos().y, m_BuildingObj->GetPos().z);
				MYVECTOR Dir = MYVECTOR(float(rand() % 200 - 100), float(rand() % 200 - 100), 0.f);
				Dir.Normalize();
				m_BulletObj[i] = new GameObject(pos, Dir, MYVECTOR(1.f, 0.f, 0.f), 10.f, OBJECT_BULLET);;
				break;
			}
		}
		m_createBulletTime = curTime;
	}

	if (m_BuildingObj)
		m_BuildingObj->Update(frameTime);
	
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
	{
		if (m_PlayerObj[i])
		{
			m_PlayerObj[i]->Update(frameTime);
		}
	}

	for (int i = 0; i < MAX_BUL_ARR_COUNT; ++i)
	{
		if (m_BulletObj[i])
		{
			m_BulletObj[i]->Update(frameTime);
		}

		if (m_ArrowObj[i])
		{
			m_ArrowObj[i]->Update(frameTime);
		}
	}

	CrushCheck();
}

void SceneMgr::Render()
{
	if(m_BuildingObj)
		m_Renderer->DrawTexturedRect(m_BuildingObj->GetPos().x, m_BuildingObj->GetPos().y, m_BuildingObj->GetPos().z, m_BuildingObj->GetScale(), m_BuildingObj->GetColor().x, m_BuildingObj->GetColor().y, m_BuildingObj->GetColor().z, 0.f, m_BuildingTexID);
		
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
	{
		if (m_PlayerObj[i])
		{
			m_Renderer->DrawSolidRect(m_PlayerObj[i]->GetPos().x, m_PlayerObj[i]->GetPos().y, m_PlayerObj[i]->GetPos().z,
				m_PlayerObj[i]->GetScale(), m_PlayerObj[i]->GetColor().x, m_PlayerObj[i]->GetColor().y, m_PlayerObj[i]->GetColor().z, 1.f);
		}
	}

	for (int i = 0; i < MAX_BUL_ARR_COUNT; ++i)
	{
		if (m_BulletObj[i])
		{
			m_Renderer->DrawSolidRect(m_BulletObj[i]->GetPos().x, m_BulletObj[i]->GetPos().y, m_BulletObj[i]->GetPos().z,
				m_BulletObj[i]->GetScale(), m_BulletObj[i]->GetColor().x, m_BulletObj[i]->GetColor().y, m_BulletObj[i]->GetColor().z, 1.f);
		}
		
		if (m_ArrowObj[i])
		{
			m_Renderer->DrawSolidRect(m_ArrowObj[i]->GetPos().x, m_ArrowObj[i]->GetPos().y, m_ArrowObj[i]->GetPos().z,
				m_ArrowObj[i]->GetScale(), m_ArrowObj[i]->GetColor().x, m_ArrowObj[i]->GetColor().y, m_ArrowObj[i]->GetColor().z, 1.f);
		}
	}

}

void SceneMgr::CreateObject(float x, float y)
{
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
	{
		if (!m_PlayerObj[i])
		{
			MYVECTOR Dir = MYVECTOR(float(rand() % 200 - 100), float(rand() % 200 - 100), 0.f);
			Dir.Normalize();
			m_PlayerObj[i] = new GameObject(MYVECTOR(x, y, 0.f), Dir, MYVECTOR(1.f, 1.f, 1.f), 20.f, OBJECT_CHARACTER);
			return;
		}
	}
}

void SceneMgr::CrushCheck()
{
	for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
	{
		if (m_PlayerObj[i])
		{
			for (int j = 0; j < MAX_BUL_ARR_COUNT; ++j)
			{
				if (m_BulletObj[j])
				{
					if (m_PlayerObj[i]->checkCrush(m_BulletObj[j]))
					{
						m_PlayerObj[i]->DecreaseHP(m_BulletObj[j]->GetLife());

						delete m_BulletObj[j];
						m_BulletObj[j] = NULL;
					}
				}

				//if (m_ArrowObj[j])
				//{
				//	if (m_PlayerObj[i]->checkCrush(m_ArrowObj[j]))
				//	{
				//		m_PlayerObj[i]->DecreaseHP(m_ArrowObj[j]->GetLife());

				//		delete m_ArrowObj[j];
				//		m_ArrowObj[j] = NULL;
				//	}
				//}
			}

			if (m_BuildingObj)
			{
				if (m_PlayerObj[i]->checkCrush(m_BuildingObj))
				{
					m_BuildingObj->DecreaseHP(m_PlayerObj[i]->GetLife());
					m_PlayerObj[i]->DecreaseHP(m_BuildingObj->GetLife());
				}
			}

			if (m_PlayerObj[i]->GetLife() <= 0.f)
			{
				delete m_PlayerObj[i];
				m_PlayerObj[i] = NULL;
			}
		}
	}

	for (int j = 0; j < MAX_BUL_ARR_COUNT; ++j)
	{
		if (m_ArrowObj[j] && m_BuildingObj)
		{
			if (m_ArrowObj[j]->checkCrush(m_BuildingObj))
			{
				m_BuildingObj->DecreaseHP(m_ArrowObj[j]->GetLife());

				delete m_ArrowObj[j];
				m_ArrowObj[j] = NULL;
			}
		}
	}

	if (m_BuildingObj)
	{
		if (m_BuildingObj->GetLife() <= 0.f)
		{
			delete m_BuildingObj;
			m_BuildingObj = NULL;
		}
	}
}