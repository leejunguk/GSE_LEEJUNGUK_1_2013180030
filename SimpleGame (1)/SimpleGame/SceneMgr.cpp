#include "stdafx.h"
#include "SceneMgr.h"



SceneMgr::SceneMgr()
{
	m_objectCnt = 0;
	m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	
}


SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}


void SceneMgr::Update(float xvector, float yvector, DWORD time)
{
	for (int i = 0; i< m_objectCnt; ++i)
	{
		m_objectList[i]->PositionUpdate(xvector, yvector, time);
		//cout << "d" << endl; 
	}
}
bool SceneMgr::CollisionCheck(Object &a, Object &b)
{
	float AlowerXbound = 0.0f;
	float AlowerYbound = 0.0f;
	float AHighXbound = 0.0f;
	float AHighYbound = 0.0f;

	float BlowerXbound = 0.0f;
	float BlowerYbound = 0.0f;
	float BHighXbound = 0.0f;
	float BHighYbound = 0.0f;

	
	AHighXbound = a.GetPositionX() + a.GetSize() / 2;
	AHighYbound = a.GetPositionY() + a.GetSize() / 2;

	AlowerXbound = a.GetPositionX() - a.GetSize() / 2;
	AlowerYbound = a.GetPositionY() - a.GetSize() / 2;

	BHighXbound = b.GetPositionX() + b.GetSize() / 2;
	BHighYbound = b.GetPositionY() + b.GetSize() / 2;

	BlowerXbound = b.GetPositionX() - b.GetSize() / 2;
	BlowerYbound = b.GetPositionY() - b.GetSize() / 2;
	
	if (AHighXbound > AlowerXbound)
	{
		return true;
	}
	if (AHighYbound > AlowerYbound)
	{
		return true;
	}
	if (AlowerYbound < AHighYbound)
	{
		return true;
	}
	if (AlowerXbound < AHighXbound)
	{
		return true;
	}
}
void SceneMgr::Render()
{
	
	for (int i = 0; i < m_objectCnt; ++i)
	{
		m_Renderer->DrawSolidRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(), 
			m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
			m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA());
	}
}