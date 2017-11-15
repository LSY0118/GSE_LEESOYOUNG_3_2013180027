#pragma once

#include "Dependencies\glew.h"

#define MAX_BUL_ARR_COUNT 100
#define MAX_PLAYER_COUNT 10

enum OBJECT_TYPE {OBJECT_BUILDING, OBJECT_CHARACTER, OBJECT_BULLET, OBJECT_ARROW};

class GameObject;
class Renderer;

class SceneMgr
{
public:
	SceneMgr();
	virtual ~SceneMgr();

	void CreateObject(float x, float y);
	void Update(float frameTime);
	void Render();
	
	void CrushCheck();

private:
	Renderer* m_Renderer;
	GameObject* m_BuildingObj;
	GameObject* m_PlayerObj[MAX_PLAYER_COUNT];
	GameObject* m_ArrowObj[MAX_BUL_ARR_COUNT];
	GameObject* m_BulletObj[MAX_BUL_ARR_COUNT];

	GLuint m_BuildingTexID;
	void Initialize();

	float m_createBulletTime;
};

