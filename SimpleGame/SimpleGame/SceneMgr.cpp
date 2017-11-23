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

	m_BlueBuilding[0] = new GameObject(MYVECTOR(0.f, -WINDOW_HEIGHT / 2 + 100.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(0.f, 1.f, 0.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_RED);
	m_BlueBuilding[1] = new GameObject(MYVECTOR(-WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 2 + 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(0.f, 1.f, 0.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_RED);
	m_BlueBuilding[2] = new GameObject(MYVECTOR(WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 2 + 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(0.f, 1.f, 0.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_RED);

	m_RedBuilding[0] = new GameObject(MYVECTOR(0.f, WINDOW_HEIGHT / 2 - 100.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(0.f, 1.f, 0.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_BLUE);
	m_RedBuilding[1] = new GameObject(MYVECTOR(-WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(0.f, 1.f, 0.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_BLUE);
	m_RedBuilding[2] = new GameObject(MYVECTOR(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 150.f, 0.f), MYVECTOR(0.f, 0.f, 0.f), MYVECTOR(0.f, 1.f, 0.f), 100.f, OBJECT_BUILDING, OBJECT_TEAM_BLUE);

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
}

void SceneMgr::Render()
{
	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		if (m_BlueBuilding[i])
		{
			m_Renderer->DrawTexturedRect(m_BlueBuilding[i]->GetPos().x, m_BlueBuilding[i]->GetPos().y, m_BlueBuilding[i]->GetPos().z, 
				m_BlueBuilding[i]->GetScale(), m_BlueBuilding[i]->GetColor().x, m_BlueBuilding[i]->GetColor().y, m_BlueBuilding[i]->GetColor().z,
				0.f, m_BlueTexID);
		}

		if (m_RedBuilding[i])
		{
			m_Renderer->DrawTexturedRect(m_RedBuilding[i]->GetPos().x, m_RedBuilding[i]->GetPos().y, m_RedBuilding[i]->GetPos().z,
				m_RedBuilding[i]->GetScale(), m_RedBuilding[i]->GetColor().x, m_RedBuilding[i]->GetColor().y, m_RedBuilding[i]->GetColor().z,
				0.f, m_RedTexID);
		}
	}

	for (int i = 0; i < MAX_ARR_COUNT; ++i)
	{
		if (m_BlueObj[i])
		{
			m_Renderer->DrawSolidRect(m_BlueObj[i]->GetPos().x, m_BlueObj[i]->GetPos().y, m_BlueObj[i]->GetPos().z,
				m_BlueObj[i]->GetScale(), m_BlueObj[i]->GetColor().x, m_BlueObj[i]->GetColor().y, m_BlueObj[i]->GetColor().z, 1.f);
		}
		if (m_RedObj[i])
		{
			m_Renderer->DrawSolidRect(m_RedObj[i]->GetPos().x, m_RedObj[i]->GetPos().y, m_RedObj[i]->GetPos().z,
				m_RedObj[i]->GetScale(), m_RedObj[i]->GetColor().x, m_RedObj[i]->GetColor().y, m_RedObj[i]->GetColor().z, 1.f);
		}
	}
}

void SceneMgr::CreateBullet()
{
	bool blue = false;
	bool red = false;
	for (int i = 0; i < MAX_BUILD_COUNT; ++i)
	{
		for (int i = 0; i < MAX_ARR_COUNT; ++i)
		{
			if (blue == false && m_BlueObj[i] == NULL)
			{
				MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), 10.f, 0.f);
				dir.Normalize();
				m_BlueObj[i] = new GameObject(MYVECTOR(m_BlueBuilding[i]->GetPos()), dir, MYVECTOR(0.f, 0.f, 1.f), 4.f, OBJECT_BULLET, OBJECT_TEAM_BLUE);
				blue = true;
			}
			if (red == false && m_RedObj[i] == NULL)
			{
				MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), -10.f, 0.f);
				dir.Normalize();
				m_RedObj[i] = new GameObject(MYVECTOR(m_RedBuilding[i]->GetPos()), dir, MYVECTOR(1.f, 0.f, 0.f), 4.f, OBJECT_BULLET, OBJECT_TEAM_RED);
				red = true;
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
			cout << pos.x << " " << pos.y << endl;
			MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), -10.f, 0.f);
			dir.Normalize();
			m_RedObj[i] = new GameObject(pos, dir, MYVECTOR(1.f, 0.f, 0.f), 20.f, OBJECT_CHAR, OBJECT_TEAM_RED);
			
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
			m_BlueObj[i] = new GameObject(MYVECTOR(x, y, 0.f), dir, MYVECTOR(0.f, 0.f, 1.f), 20.f, OBJECT_CHAR, OBJECT_TEAM_BLUE);
			cout << x << " " << y << endl;

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
					MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), 10.f, 0.f);
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
					MYVECTOR dir = MYVECTOR(float(rand() % 5 - 5), 10.f, 0.f);
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
	//for (int i = 0; i < MAX_ARR_COUNT; ++i)
	//{
	//	for (int j = i; j < MAX_ARR_COUNT; ++i)
	//	{
	//	}

	//	for (int k = 0; k < MAX_BUILD_COUNT; ++k)
	//	{
	//	}
	//}
	
	//for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
	//{
	//	if (m_PlayerObj[i])
	//	{
	//		for (int j = 0; j < MAX_BUL_ARR_COUNT; ++j)
	//		{
	//			if (m_BulletObj[j])
	//			{
	//				if (m_PlayerObj[i]->checkCrush(m_BulletObj[j]))
	//				{
	//					m_PlayerObj[i]->DecreaseHP(m_BulletObj[j]->GetLife());

	//					delete m_BulletObj[j];
	//					m_BulletObj[j] = NULL;
	//				}
	//			}

	//			//if (m_ArrowObj[j])
	//			//{
	//			//	if (m_PlayerObj[i]->checkCrush(m_ArrowObj[j]))
	//			//	{
	//			//		m_PlayerObj[i]->DecreaseHP(m_ArrowObj[j]->GetLife());

	//			//		delete m_ArrowObj[j];
	//			//		m_ArrowObj[j] = NULL;
	//			//	}
	//			//}
	//		}

	//		if (m_BuildingObj)
	//		{
	//			if (m_PlayerObj[i]->checkCrush(m_BuildingObj))
	//			{
	//				m_BuildingObj->DecreaseHP(m_PlayerObj[i]->GetLife());
	//				m_PlayerObj[i]->DecreaseHP(m_BuildingObj->GetLife());
	//			}
	//		}

	//		if (m_PlayerObj[i]->GetLife() <= 0.f)
	//		{
	//			delete m_PlayerObj[i];
	//			m_PlayerObj[i] = NULL;
	//		}
	//	}
	//}

	//for (int j = 0; j < MAX_BUL_ARR_COUNT; ++j)
	//{
	//	if (m_ArrowObj[j] && m_BuildingObj)
	//	{
	//		if (m_ArrowObj[j]->checkCrush(m_BuildingObj))
	//		{
	//			m_BuildingObj->DecreaseHP(m_ArrowObj[j]->GetLife());

	//			delete m_ArrowObj[j];
	//			m_ArrowObj[j] = NULL;
	//		}
	//	}
	//}

	//if (m_BuildingObj)
	//{
	//	if (m_BuildingObj->GetLife() <= 0.f)
	//	{
	//		delete m_BuildingObj;
	//		m_BuildingObj = NULL;
	//	}
	//}
}