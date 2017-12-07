#include "stdafx.h"
#include "SceneMgr.h"



SceneMgr::SceneMgr()
{
	m_objectCnt = 0;
	m_Renderer = new Renderer(SIZEWINDOWWIDTH, SIZEWINDOWHEIGHT);
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
	CollisionCheckList();
	float timer = 0.0f;
	timer += float(time);
	int tmpFriendNum = 0;
	
	

	for (int i = 0; i< m_objectCnt; ++i)
	{
		//포지션 업데이트 루프 
		if (m_objectList[i] != NULL)
		{
			

			if (m_objectList[i]->GetLife() < 0.0001f || m_objectList[i]->GetLifeTime() <0.0001f)
			{

				delete m_objectList[i];
				m_objectList[i] = NULL;
			}
			else if ((SIZEWINDOWWIDTH/2) <m_objectList[i]->GetPositionX() || m_objectList[i]->GetPositionX()<-(SIZEWINDOWWIDTH / 2) ||
				(SIZEWINDOWHEIGHT / 2) <m_objectList[i]->GetPositionY() || m_objectList[i]->GetPositionY() <-(SIZEWINDOWHEIGHT / 2)
				) //여기 범위 윈도우 범위로 바꾸기 
			{
				if (m_objectList[i]->GetObjectType() == OBJECT_BULLET || m_objectList[i]->GetObjectType() == OBJECT_ARROW)
				{
					//범위 밖에 나가면 총알 없애기 
					delete m_objectList[i];
					m_objectList[i] = NULL;
				}
				else
					m_objectList[i]->PositionUpdate(xvector, yvector, time);
				
			}
			else
			{
				//DWORD CurrentTime1 = timeGetTime();
				//에로우 
				if (m_objectList[i]->GetArrowTime() >0.03f && m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
				{
					AddObjectList(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(), OBJECT_ARROW, m_objectList[i]->GetMyTEAM()); //\dhfb
					SetObjCnt(GetObjCnt() + 1);
					m_objectList[i]->SetMyLastArrowTime(0.f);
					m_objectList[i]->SetMyFriend(i);
				}
				//빌딩총알 
				if (m_objectList[i]->GetBulletTime() >0.02f && m_objectList[i]->GetObjectType() == OBJECT_BULDING)
				{
					AddObjectList(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(), OBJECT_BULLET, m_objectList[i]->GetMyTEAM()); //\dhfb
					SetObjCnt(GetObjCnt() + 1);
					m_objectList[i]->SetMyLastBulletTime(0.f);
					m_objectList[i]->SetMyFriend(i);
				}
				if (m_objectList[i]->GetCharacterTime() > 0.02f  && m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[i]->GetMyTEAM() == ATEAM)
				{
					AddObjectList(m_objectList[i]->GetPositionX() + ((float)std::rand() / (float)RAND_MAX), m_objectList[i]->GetPositionY(), OBJECT_CHARACTER, m_objectList[i]->GetMyTEAM()); //\dhfb
					SetObjCnt(GetObjCnt() + 1);
					m_objectList[i]->SetChracterTime(0.f);
					m_objectList[i]->SetMyFriend(i);
				}

				m_objectList[i]->PositionUpdate(xvector, yvector, time);

			}
		
			
		}
	}

	

}
bool SceneMgr::CollisionCheck(Object *a, Object *b)
{
	float AlowerXbound = 0.0f;
	float AlowerYbound = 0.0f;
	float AHighXbound = 0.0f;
	float AHighYbound = 0.0f;

	float BlowerXbound = 0.0f;
	float BlowerYbound = 0.0f;
	float BHighXbound = 0.0f;
	float BHighYbound = 0.0f;

	
	AHighXbound = a->GetPositionX() + a->GetSize() / 2.f;
	AHighYbound = a->GetPositionY() + a->GetSize() / 2.f;

	AlowerXbound = a->GetPositionX() - a->GetSize() / 2.f;
	AlowerYbound = a->GetPositionY() - a->GetSize() / 2.f;

	BHighXbound = b->GetPositionX() + b->GetSize() / 2.f;
	BHighYbound = b->GetPositionY() + b->GetSize() / 2.f;

	BlowerXbound = b->GetPositionX() - b->GetSize() / 2.f;
	BlowerYbound = b->GetPositionY() - b->GetSize() / 2.f;
	
	if (AHighXbound < BlowerXbound)
	{
		return false;
	}
	if (AHighYbound < BlowerYbound)
	{
		return false;
	}
	if (AlowerYbound > BHighYbound)
	{
		return false;
	}
	if (AlowerXbound > BHighXbound)
	{
		return false;
	}
	return true;
}
void SceneMgr::Render()
{
	float testinglevel = 0.0f;
	static float animationFrame = 0;

	//if (16 < animationFrame)
		//animationFrame = 0;
	
	
	m_Renderer->DrawTexturedRect(0, 0, 0, 800, 0.5, 0.5, 0.5, 1, m_BakcGround, RenderLevel_BACKGROUND);

	for (int i = 0; i < m_objectCnt; ++i)
	{
		if (m_objectList[i] != NULL)
		{
			if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[i]->GetMyTEAM() == ATEAM)
			{
				
				m_Renderer->DrawTexturedRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(),m_texCharacter, m_objectList[i]->m_RenderLevel);

				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY()+30,
					m_objectList[i]->GetPositionZ(), 50,10, 1,
					0, 0, m_objectList[i]->GetA(),m_objectList[i]->GetLife()/ MaxLife_BUILDING,RenderLevel_GOD);

			}
			else if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[i]->GetMyTEAM() == BTEAM)
			{

				m_Renderer->DrawTexturedRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_airCharacter, m_objectList[i]->m_RenderLevel);
				//블루게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 30,
					m_objectList[i]->GetPositionZ(), 50, 10, 0,
					0, 1, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_BUILDING, RenderLevel_GOD);
			}
			else if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER&& m_objectList[i]->GetMyTEAM() == ATEAM)
			{

				/*m_Renderer->DrawSolidRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_objectList[i]->m_RenderLevel);*/

				//에니메이션 추가
				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(),m_CharaterAnimation, m_objectList[i]->m_AnimationFrame,0,16,1, m_objectList[i]->m_RenderLevel);

				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 20,
					m_objectList[i]->GetPositionZ(), 50, 10, 1,
					0, 0, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_CHARACTER, RenderLevel_GOD);
			}
			else if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER&& m_objectList[i]->GetMyTEAM() == BTEAM)
			{

				m_Renderer->DrawSolidRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_objectList[i]->m_RenderLevel);
				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 20,
					m_objectList[i]->GetPositionZ(), 50, 10, 0,
					0, 1, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_CHARACTER, RenderLevel_GOD);

				
			}
		
			else
			{
				if (m_objectList[i]->GetObjectType() == OBJECT_BULLET) //////////////////////paticle
				{
					m_Renderer->DrawParticle(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
						m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
						m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), -m_objectList[i]->m_Vx, -m_objectList[i]->m_Vy, m_Paticle, m_objectList[i]->m_BulletAnimationTime);

				}

				m_Renderer->DrawSolidRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_objectList[i]->m_RenderLevel);
				
			}
		}
	}

	m_Renderer->DrawText(-30, 0, GLUT_BITMAP_TIMES_ROMAN_24, 0.9f, 0.9f, 0.9f, "Stage 1");

}
void SceneMgr::CollisionCheckList()
{
	int collisionCount = 0;
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_objectList[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (i == j)
					continue;

				if (m_objectList[j] != NULL)
				{
					
					if (CollisionCheck(m_objectList[i],m_objectList[j]))
					{
						collisionCount++;
						
						//캐릭터와 불릿
						if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER && m_objectList[j]->GetObjectType() == OBJECT_BULLET)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{
								
							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
							}
						}
						//불릿과 빌딩
						if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[j]->GetObjectType() == OBJECT_BULLET)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
								
							}
						}


						//에로우와 캐릭터
						if(m_objectList[i]->GetObjectType() == OBJECT_CHARACTER && m_objectList[j]->GetObjectType() == OBJECT_ARROW )
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{
								
							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
							}

						}
						//에로우와 빌딩   나중에 요거 조건 묶어서 함수로 빼고 싶다 ..;;;
						if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[j]->GetObjectType() == OBJECT_ARROW)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{
								//cout << "";
							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
							}

						}

						//빌딩과캐릭터
						if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[j]->GetObjectType() == OBJECT_CHARACTER)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
							}
						}

					}
					else
					{
						////m_objectList[i]->SetRGBA(1,1,1,1);
						//if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
						//	m_objectList[i]->SetRGBA(1, 1, 1, 1);
						//if (m_objectList[i]->GetObjectType() == OBJECT_BULDING)
						//	m_objectList[i]->SetRGBA(1, 1, 0, 1);
					}
					
					
				}
			}
			
		}
	}


}
int	SceneMgr::AddObjectList(float x, float y,int objecttype)
{
	//Find empty slot
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objectList[i] == NULL)
		{

			m_objectList[i] = new Object(x, y,objecttype);
			/*DWORD CreateObjectTime = timeGetTime();
			m_objectList[i]->SetTimer(CreateObjectTime);*/
			return i;
		}
	}

	//slots are full
	std::cout << "slots are full \n";
	return -1;
}
int	SceneMgr::AddObjectList(float x, float y, int objecttype,int friendnumber)
{
	//Find empty slot
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objectList[i] == NULL)
		{

			m_objectList[i] = new Object(x, y, objecttype, friendnumber);
			//DWORD CreateObjectTime = timeGetTime();
			//m_objectList[i]->SetTimer(CreateObjectTime);
			return i;
		}
	}

	//slots are full
	std::cout << "slots are full \n";
	return -1;
}
void SceneMgr::DeleteObject(int index)
{
	if (m_objectList[index] != NULL)
	{
		delete m_objectList[index];
		m_objectList[index] = NULL;
	}
}
void SceneMgr::DeleteOlderObject()
{
	for (int i = 0; i < m_objectCnt; ++i)
	{
		if (m_objectList[i] != NULL)
		{
			DeleteObject(rand() % m_objectCnt);
		}
	}
}