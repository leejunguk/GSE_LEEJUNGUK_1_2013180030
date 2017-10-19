#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_objcctCnt = 0;
}


SceneMgr::~SceneMgr()
{
}
void SceneMgr::Update(float xvector, float yvector, float time)
{
	for (int i = 0; m_objcctCnt; ++i)
	{
		m_objectList[i]->PositionUpdate(xvector, yvector, time);
	}
}
void SceneMgr::CollisionCheck()
{
	float lowerXbound = 0.0f;
	float lowerYbound = 0.0f;
	float HighXbound = 0.0f;
	float HighYbound = 0.0f;
	for (int i = 0; m_objcctCnt; ++i)
	{
		HighXbound = m_objectList[i]->GetPositionX() + m_objectList[i]->GetSize() / 2;
		HighYbound = m_objectList[i]->GetPositionY() + m_objectList[i]->GetSize() / 2;

		lowerXbound = m_objectList[i]->GetPositionX() - m_objectList[i]->GetSize() / 2;
		lowerYbound = m_objectList[i]->GetPositionY() - m_objectList[i]->GetSize() / 2;
	}


}