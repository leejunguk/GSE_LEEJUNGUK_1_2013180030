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
	
private:
	int		m_objectCnt;
	Renderer *m_Renderer;
public:
	void Update(float xvector, float yvector, DWORD time);
	void Render();
	bool CollisionCheck(Object &a, Object &b);
public:
	inline void SetObjCnt(int cnt) { m_objectCnt = cnt; };
	inline int GetObjCnt() { return m_objectCnt; };
};

