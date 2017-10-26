#pragma once
#include "Object.h"
#include "Renderer.h"
class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();
public:
	Object* m_objectList[MAX_OBJECTS_COUNT];
	int		m_objcctCnt;
	Renderer *g_Renderer;
public:
	void Update(float xvector, float yvector, float time);
	void Render(int index);
	bool CollisionCheck(Object &a, Object &b );
};

