#pragma once

#define MAX_OBJECTS_COUNT 10

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

private:
	Renderer* m_Renderer;
	GameObject* m_objects[MAX_OBJECTS_COUNT];

	void Initialize();
};

