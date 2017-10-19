#pragma once
#include "Object.h"
class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();
public:
	Object* m_objectList[MAX_OBJECTS_COUNT];
	int		m_objcctCnt;
public:
	void Update(float xvector, float yvector, float time);
	void CollisionCheck();
};

