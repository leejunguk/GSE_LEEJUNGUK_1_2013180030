#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_objcctCnt = 0;
	Renderer *g_Renderer = NULL;
	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}


SceneMgr::~SceneMgr()
{
	delete g_Renderer;
}


void SceneMgr::Update(float xvector, float yvector, float time)
{
	for (int i = 0; m_objcctCnt; ++i)
	{
		m_objectList[i]->PositionUpdate(xvector, yvector, time);
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
void SceneMgr::Render(int index)
{
	
	g_Renderer->DrawSolidRect(m_objectList[index]->GetPositionX(), m_objectList[index]->GetPositionY(), m_objectList[index]->GetPositionZ()
			, m_objectList[index]->GetSize(), m_objectList[index]->GetR(), m_objectList[index]->GetG(), m_objectList[index]->GetB(), m_objectList[index]->GetA());
	
}