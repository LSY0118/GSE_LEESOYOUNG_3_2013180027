#pragma once

#define MAX_OBJECTS_COUNT 2

class GameObject;
class Renderer;

class SceneMgr
{
public:
	SceneMgr();
	virtual ~SceneMgr();

	void Update();
	void Render();

private:
	Renderer* m_Renderer;
	GameObject* m_objects[MAX_OBJECTS_COUNT];

	void Initialize();
};

