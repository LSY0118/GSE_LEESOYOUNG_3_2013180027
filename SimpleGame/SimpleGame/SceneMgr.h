#pragma once

#include "Dependencies\glew.h"

#define RANDNUM 10-5

#define MAX_ARR_COUNT 100
#define MAX_BUILD_COUNT 3

enum OBJECT_TYPE {OBJECT_TEAM_RED, OBJECT_TEAM_BLUE, OBJECT_BUILDING, OBJECT_CHAR, OBJECT_BULLET, OBJECT_ARROW};

#define DEPTH_BACKGROUND 0.9
#define DEPTH_BUILDING 0.1
#define DEPTH_CHAR 0.2
#define DEPTH_ARR_BUL 0.3

#define BUILDING_GAUGE 100.f
#define CHAR_GAUGE 30.f
#define TOTAL_ANI 3

class GameObject;
class Renderer;
class Sound;

class SceneMgr
{
public:
	SceneMgr();
	virtual ~SceneMgr();

	void CreateBullet();
	void CreateRedChar();
	void CreateBlueChar(float x, float y);
	void CreateArrow();
	void Update(float elapsedTime);
	void Render();
	
	void CrushCheck();

private:
	Renderer* m_Renderer;
	Sound* m_Sound;
	GameObject* m_RedBuilding[MAX_BUILD_COUNT];
	GameObject* m_BlueBuilding[MAX_BUILD_COUNT];
	GameObject* m_RedObj[MAX_ARR_COUNT];
	GameObject* m_BlueObj[MAX_ARR_COUNT];

	GLuint m_RedTexID;
	GLuint m_BlueTexID;
	GLuint m_BackTexID;
	GLuint m_RedCharTexID;
	GLuint m_BlueCharTexID;
	GLuint m_RedBulletTexID; 
	GLuint m_BlueBulletTexID;

	void Initialize();

	float m_createBulletTime;
	float m_createCharRedTime;
	float m_createCharBlueTime;
	float m_createArrowTime;

	bool BlueCharCoolDown;
};

