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

	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		if (m_RedBuilding[i])
		{
			delete m_RedBuilding[i];
			m_RedBuilding[i] = NULL;
		}

	}

	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		if (m_BlueBuilding[i])
		{
			delete m_BlueBuilding[i];
			m_BlueBuilding[i] = NULL;
		}

	}

	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_RedObj[i])
		{
			delete m_RedObj[i];
			m_RedObj[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_BlueObj[i])
		{
			delete m_BlueObj[i];
			m_BlueObj[i] = NULL;
		}
	}
}

void SceneMgr::Initialize()
{
	m_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_RedTexID = m_Renderer->CreatePngTexture("Resource/Jerry.png");
	m_BlueTexID = m_Renderer->CreatePngTexture("Resource/Tom.png");

	m_BlueBuilding[0] = new GameObject(MYVECTOR(0.f, -WINDOW_HEIGHT / 2 + 100.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(1.f, 1.f, 1.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_RED);
	m_BlueBuilding[1] = new GameObject(MYVECTOR(-WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 2 + 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(1.f, 1.f, 1.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_RED);
	m_BlueBuilding[2] = new GameObject(MYVECTOR(WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 2 + 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(1.f, 1.f, 1.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_RED);

	m_RedBuilding[0] = new GameObject(MYVECTOR(0.f, WINDOW_HEIGHT / 2 - 100.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(1.f, 1.f, 1.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_BLUE);
	m_RedBuilding[1] = new GameObject(MYVECTOR(-WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(1.f, 1.f, 1.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_BLUE);
	m_RedBuilding[2] = new GameObject(MYVECTOR(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(1.f, 1.f, 1.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_BLUE);

	BlueCharCoolDown = false;

	m_createBulletTime = timeGetTime() * 0.001f;
	m_createCharBlueTime = timeGetTime() * 0.001f;
	m_createCharRedTime = timeGetTime() * 0.001f;
	m_createArrowTime = timeGetTime() * 0.001f;
}

void SceneMgr::Update(float frameTime)
{
	float curTime = timeGetTime() * 0.001f;

	if (curTime - m_createBulletTime >= 10.f)
	{
		CreateBullet();
		m_createBulletTime = curTime;
	}

	if (curTime - m_createCharRedTime >= 5.f)
	{
		CreateRedChar();
		m_createCharRedTime = curTime;
	}

	if (curTime - m_createCharBlueTime >= 7.f)
	{
		BlueCharCoolDown = false;
	}

	if (curTime - m_createArrowTime >= 3.f)
	{
		CreateArrow();
		m_createArrowTime = curTime;
	}

	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		if (m_BlueBuilding[i])
		{
			m_BlueBuilding[i]->Update(frameTime);
		}

		if (m_RedBuilding[i])
		{
			m_RedBuilding[i]->Update(frameTime);
		}
	}

	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_BlueObj[i])
		{
			m_BlueObj[i]->Update(frameTime);
		}
		if (m_RedObj[i])
		{
			m_RedObj[i]->Update(frameTime);
		}
	}

	CrushCheck();

	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		
		if (m_BlueBuilding[i] && m_BlueBuilding[i]->GetLife() < 0.f)
		{
			delete m_BlueBuilding[i];
			m_BlueBuilding[i] = NULL;
		}

		if (m_RedBuilding[i] && m_RedBuilding[i]->GetLife() < 0.f)
		{
			delete m_RedBuilding[i];
			m_RedBuilding[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_BlueObj[i] && m_BlueObj[i]->GetLife() < 0.f)
		{
			delete m_BlueObj[i];
			m_BlueObj[i] = NULL;
		}

		if (m_RedObj[i] && m_RedObj[i]->GetLife() < 0.f)
		{
			delete m_RedObj[i];
			m_RedObj[i] = NULL;
		}
	}
}

void SceneMgr::Render()
{
	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		if (m_BlueBuilding[i])
		{
			m_Renderer->DrawTexturedRect(m_BlueBuilding[i]->GetPos().x, m_BlueBuilding[i]->GetPos().y, m_BlueBuilding[i]->GetPos().z, 
				m_BlueBuilding[i]->GetScale(), m_BlueBuilding[i]->GetColor().x, m_BlueBuilding[i]->GetColor().y, m_BlueBuilding[i]->GetColor().z,
				1.f, m_BlueTexID, DEPTH_BUILDING);

			m_Renderer->DrawSolidRectGauge(m_BlueBuilding[i]->GetPos().x, m_BlueBuilding[i]->GetPos().y + m_BlueBuilding[i]->GetScale() / 2.f + 5.f, m_BlueBuilding[i]->GetPos().z,
				m_BlueBuilding[i]->GetLife() / BUILDING_GAUGE, 5.f, 0.f, 0.f, 1.f, 1.f, m_BlueBuilding[i]->GetLife(), DEPTH_BUILDING);
		}

		if (m_RedBuilding[i])
		{
			m_Renderer->DrawTexturedRect(m_RedBuilding[i]->GetPos().x, m_RedBuilding[i]->GetPos().y, m_RedBuilding[i]->GetPos().z,
				m_RedBuilding[i]->GetScale(), m_RedBuilding[i]->GetColor().x, m_RedBuilding[i]->GetColor().y, m_RedBuilding[i]->GetColor().z,
				1.f, m_RedTexID, DEPTH_BUILDING);

			m_Renderer->DrawSolidRectGauge(m_RedBuilding[i]->GetPos().x, m_RedBuilding[i]->GetPos().y + m_RedBuilding[i]->GetScale() / 2.f + 5.f, m_RedBuilding[i]->GetPos().z,
				m_RedBuilding[i]->GetLife() / BUILDING_GAUGE, 5.f, 1.f, 0.f, 0.f, 1.f, m_RedBuilding[i]->GetLife(), DEPTH_BUILDING);
		}
	}

	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_BlueObj[i])
		{
			m_Renderer->DrawSolidRect(m_BlueObj[i]->GetPos().x, m_BlueObj[i]->GetPos().y, m_BlueObj[i]->GetPos().z,
				m_BlueObj[i]->GetScale(), m_BlueObj[i]->GetColor().x, m_BlueObj[i]->GetColor().y, m_BlueObj[i]->GetColor().z, 1.f, m_BlueObj[i]->GetDepthLevel());

			if (m_BlueObj[i]->GetObjType() == OBJECT_CHAR)
			{
				m_Renderer->DrawSolidRectGauge(m_BlueObj[i]->GetPos().x, m_BlueObj[i]->GetPos().y + m_BlueObj[i]->GetScale() / 2.f + 5.f, m_BlueObj[i]->GetPos().z,
					m_BlueObj[i]->GetLife() / CHAR_GAUGE, 5.f, 0.f, 0.f, 1.f, 1.f, m_BlueObj[i]->GetLife(), m_BlueObj[i]->GetDepthLevel());
			}
		}
		if (m_RedObj[i])
		{
			m_Renderer->DrawSolidRect(m_RedObj[i]->GetPos().x, m_RedObj[i]->GetPos().y, m_RedObj[i]->GetPos().z,
				m_RedObj[i]->GetScale(), m_RedObj[i]->GetColor().x, m_RedObj[i]->GetColor().y, m_RedObj[i]->GetColor().z, 1.f, m_RedObj[i]->GetDepthLevel());
			
			if (m_RedObj[i]->GetObjType() == OBJECT_CHAR)
			{
				m_Renderer->DrawSolidRectGauge(m_RedObj[i]->GetPos().x, m_RedObj[i]->GetPos().y + m_RedObj[i]->GetScale() / 2.f + 5.f, m_RedObj[i]->GetPos().z,
					m_RedObj[i]->GetLife() / CHAR_GAUGE, 5.f, 1.f, 0.f, 0.f, 1.f, m_RedObj[i]->GetLife(), m_RedObj[i]->GetDepthLevel());
			}
		}
	}
}

void SceneMgr::CreateBullet()
{
	bool blue = false;
	bool red = false;
	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		for (int j = 0; j < MAX_ARR_COUNT; ++j)
		{
			if (blue == false && m_BlueObj[j] == NULL)
			{
				if (m_BlueBuilding[i])
				{
					MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), 10.f, 0.f);
					dir.Normalize();
					m_BlueObj[j] = new GameObject(MYVECTOR(m_BlueBuilding[i]->GetPos()), dir, MYVECTOR(0.f, 0.f, 1.f), 4.f, OBJECT_BULLET, OBJECT_TEAM_BLUE);
					blue = true;
				}
				else
				{
					blue = true;
				}
			}
			if (red == false && m_RedObj[j] == NULL)
			{
				if (m_RedBuilding[i])
				{
					MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), -10.f, 0.f);
					dir.Normalize();
					m_RedObj[j] = new GameObject(MYVECTOR(m_RedBuilding[i]->GetPos()), dir, MYVECTOR(1.f, 0.f, 0.f), 4.f, OBJECT_BULLET, OBJECT_TEAM_RED);
					red = true;
				}
				else
				{
					red = true;
				}
			}

			if (blue && red)
			{
				blue = false;
				red = false;
				break;
			}
		}
	}
}

void SceneMgr::CreateRedChar()
{
	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_RedObj[i] == NULL)
		{
			int x = WINDOW_WIDTH / 2;
			int y = WINDOW_HEIGHT / 2 - 100.f;
			MYVECTOR pos = MYVECTOR(float(rand() % x - x), float(rand() % y + 100.f), 0.f);
			MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), -10.f, 0.f);
			dir.Normalize();
			m_RedObj[i] = new GameObject(pos, dir, MYVECTOR(1.f, 0.f, 0.f), 30.f, OBJECT_CHAR, OBJECT_TEAM_RED);
			
			return;
		}
	}
}

void SceneMgr::CreateBlueChar(float x, float y)
{
	if (y > 0.f || BlueCharCoolDown == true)
		return;

	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_BlueObj[i] == NULL)
		{
			MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), 10.f, 0.f);
			dir.Normalize();
			m_BlueObj[i] = new GameObject(MYVECTOR(x, y, 0.f), dir, MYVECTOR(0.f, 0.f, 1.f), 30.f, OBJECT_CHAR, OBJECT_TEAM_BLUE);
		
			m_createCharBlueTime = timeGetTime() * 0.001f;
			BlueCharCoolDown = true;

			return;
		}
	}
}

void SceneMgr::CreateArrow()
{
	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_RedObj[i] && m_RedObj[i]->GetObjType() == OBJECT_CHAR)
		{
			for (int j = 0; j < MAX_ARR_COUNT; ++j)
			{
				if (m_RedObj[j] == NULL)
				{
					MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), float(rand() % 5 - 5), 0.f);
					dir.Normalize();
					m_RedObj[j] = new GameObject(m_RedObj[i]->GetPos(), dir, MYVECTOR(1.f, 1.f, 0.f), 4.f, OBJECT_ARROW, OBJECT_TEAM_RED);
					break;
				}
			}
		}
		
		if (m_BlueObj[i] && m_BlueObj[i]->GetObjType() == OBJECT_CHAR)
		{
			for (int j = 0; j < MAX_ARR_COUNT; ++j)
			{
				if (m_BlueObj[j] == NULL)
				{
					MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), float(rand() % 5 - 5), 0.f);
					dir.Normalize();
					m_BlueObj[j] = new GameObject(m_BlueObj[i]->GetPos(), dir, MYVECTOR(0.f, 1.f, 1.f), 4.f, OBJECT_ARROW, OBJECT_TEAM_BLUE);
					break;
				}
			}
		}
	}
}

void SceneMgr::CrushCheck()
{
	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		for (int j = 0; j < MAX_ARR_COUNT; ++j)
		{
			if (m_BlueObj[i] && m_RedObj[j])
			{
				if (!(m_BlueObj[i]->GetObjType() == OBJECT_CHAR && m_RedObj[j]->GetObjType() == OBJECT_CHAR))
				{
					if (m_BlueObj[i]->checkCrush(m_RedObj[j]))
					{
						float iHp, jHp;
						iHp = m_BlueObj[i]->GetLife();
						jHp = m_RedObj[j]->GetLife();

						m_BlueObj[i]->DecreaseHP(jHp);
						m_RedObj[j]->DecreaseHP(iHp);
					}
				}
			}
		}

		for (int k = 0; k < MAX_BUILD_COUNT; ++k)
		{
			if (m_BlueObj[i] && m_RedBuilding[k])
			{
				if (m_BlueObj[i]->checkCrush(m_RedBuilding[k]))
				{
					float iHp, kHp;
					iHp = m_BlueObj[i]->GetLife();
					kHp = m_RedBuilding[k]->GetLife();
					
					m_BlueObj[i]->DecreaseHP(kHp);
					m_RedBuilding[k]->DecreaseHP(iHp);
				}
			}

			if (m_RedObj[i] && m_BlueBuilding[k])
			{
				if (m_RedObj[i]->checkCrush(m_BlueBuilding[k]))
				{
					float iHp, kHp;
					iHp = m_RedObj[i]->GetLife();
					kHp = m_BlueBuilding[k]->GetLife();

					m_RedObj[i]->DecreaseHP(kHp);
					m_BlueBuilding[k]->DecreaseHP(iHp);
				}
			}
		}
	}
}