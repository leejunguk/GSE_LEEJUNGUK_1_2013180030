#include "stdafx.h"
#include "SceneMgr.h"
#include "Sound.h"


SceneMgr::SceneMgr()
{
	m_objectCnt = 0;
	m_Renderer = new Renderer(SIZEWINDOWWIDTH, SIZEWINDOWHEIGHT);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	m_texCharacter = m_Renderer->CreatePngTexture("Texture/OverMind.png");
	m_airCharacter = m_Renderer->CreatePngTexture("Texture/Command7.png");
	m_BakcGround = m_Renderer->CreatePngTexture("Texture/backgroundbackuplast.png");
	m_CharaterAnimation = m_Renderer->CreatePngTexture("Texture/MutaliskDown3.png");
	m_Paticle = m_Renderer->CreatePngTexture("Texture/Particle.png");
	m_snow = m_Renderer->CreatePngTexture("Texture/snow.png");
	m_Spire = m_Renderer->CreatePngTexture("Texture/Spire.png");
	m_Barrack = m_Renderer->CreatePngTexture("Texture/Barrack.png");
	m_Marine = m_Renderer->CreatePngTexture("Texture/MarineSprite1.png");
	m_MutalDeathEffect = m_Renderer->CreatePngTexture("Texture/MutalDeathEffect.png");
	m_LifleEffect = m_Renderer->CreatePngTexture("Texture/LifleEffect4.png");
	m_MutalBullet = m_Renderer->CreatePngTexture("Texture/MutalBullet.png");
	m_Scourge = m_Renderer->CreatePngTexture("Texture/Scourge2.png");
	m_ScourgeEffect = m_Renderer->CreatePngTexture("Texture/ScourgeEffect3.png");
	m_MarineEffect = m_Renderer->CreatePngTexture("Texture/MarineDeathSprite.png");
	m_MainImage = m_Renderer->CreatePngTexture("Texture/StarCraftMain.png");
	m_GameOver = m_Renderer->CreatePngTexture("Texture/Gameover.png");
	m_Climate = new Object;
	float m_ClimateAnimationTime = 0;

	m_Command = new Object;
	float m_CommandAnimationTime = 0;
	
	m_Scenesound = new Sound();
	Sound_MutalDeath = m_Scenesound->CreateSound("./Dependencies/SoundSamples/MutalDeath.mp3");

	//사운드 생성 
	m_effectSound = new Sound();
	Sound_MarineBirth = m_effectSound->CreateSound("./Dependencies/SoundSamples/MarineReady.mp3");
	Sound_MutalBirth = m_effectSound->CreateSound("./Dependencies/SoundSamples/MutalReady.mp3");
	Sound_MainreFire = m_effectSound->CreateSound("./Dependencies/SoundSamples/MarineFire.mp3");
	Sound_MarineDeath = m_effectSound->CreateSound("./Dependencies/SoundSamples/MarineDeath.mp3");
	Sound_ScourgeBirth = m_effectSound->CreateSound("./Dependencies/SoundSamples/ScourgeReady.mp3");
	Sound_ScourgeDeath = m_effectSound->CreateSound("./Dependencies/SoundSamples/ScourgeDeath.mp3");
	//Sound_MarineDeath = 
	isGameEnd = false;
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
	
	
	m_Climate->PositionUpdate(1,1,time);
	m_Command->PositionUpdate(1, 1, time);
	

	for (int i = 0; i< m_objectCnt; ++i)
	{
		//포지션 업데이트 루프 
		if (m_objectList[i] != NULL)
		{
			//마린공격할때 소리내기 
			if (m_objectList[i]->m_State == AI_DAMAGED_GUN && m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
			{
				m_effectSound->PlaySound(Sound_MainreFire, false, 0.02f);
				//m_objectList[i]->m_Birth = false;
			}
			
		
			if (m_objectList[i]->GetLife() < 0.0001f || m_objectList[i]->GetLifeTime() <0.0001f)
			{
				if (m_objectList[i]->GetObjectType() == OBJECT_BULDING)
				{
					isGameEnd = true;
					//m_effectSound->PlaySound(Sound_MainreFire, false, 0.02f);
					//m_objectList[i]->m_Birth = false;
				}

				//뮤탈 죽을때 소리내기 && 이펙트위치정보 받아오기  
				if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
				{
					m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
					AddObjectList(m_objectList[i]->GetPositionX(),m_objectList[i]->GetPositionY(),OBJECT_EFFECT); //죽을 위치 받아서 이펙트
				}
				// 스컬지 소리내기 && 이펙트위치정보 받아오기  
				if (m_objectList[i]->GetObjectType() == OBJECT_SCOURGE)
				{
					m_effectSound->PlaySound(Sound_ScourgeDeath, false, 0.1f);
					AddObjectList(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(), OBJECT_SCOURGEEFFECT); //죽을 위치 받아서 이펙트
				}
				// 마린 소리내기 && 이펙트위치정보 받아오기  
				if (m_objectList[i]->GetObjectType() == OBJECT_MARINE)
				{
					m_effectSound->PlaySound(Sound_MarineDeath, false, 0.1f);
					AddObjectList(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(), OBJECT_MARINEEFFECT); //죽을 위치 받아서 이펙트
				}
				delete m_objectList[i];
				m_objectList[i] = NULL;
			}
			//마린태어날때 소리내기 
			else if (m_objectList[i]->m_Birth == true && m_objectList[i]->GetObjectType() == OBJECT_MARINE)
			{
				m_effectSound->PlaySound(Sound_MarineBirth, false, 0.1f);
				m_objectList[i]->m_Birth = false;
			}
			else if (m_objectList[i]->m_Birth == true && m_objectList[i]->GetObjectType() == OBJECT_SCOURGE)
			{
				m_effectSound->PlaySound(Sound_ScourgeBirth, false, 0.1f);
				m_objectList[i]->m_Birth = false;
			}
			//뮤탈태어날때 소리내기 
			else if (m_objectList[i]->m_Birth == true && m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
			{
				m_effectSound->PlaySound(Sound_MutalBirth, false, 0.1f);
				m_objectList[i]->m_Birth = false;
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
				if (m_objectList[i]->GetArrowTime() >0.01f && m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
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
				//기존에 원래 ATeam만 나왔는데 두팀다 나오게 변경 예정 
				if (m_objectList[i]->GetCharacterTime() > 0.03f  && m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[i]->GetMyTEAM() == ATEAM)
				{
					AddObjectList(m_objectList[i]->GetPositionX() + ((float)std::rand() / (float)RAND_MAX), m_objectList[i]->GetPositionY(), OBJECT_CHARACTER, m_objectList[i]->GetMyTEAM()); //\dhfb
					SetObjCnt(GetObjCnt() + 1);
					m_objectList[i]->SetChracterTime(0.f);
					m_objectList[i]->SetMyFriend(i);
				}
				//기존에 원래 ATeam만 나왔는데 두팀다 나오게 변경 예정  // 스콜지 추가 
				if (m_objectList[i]->GetCharacterTime() > 0.03f  && m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[i]->GetMyTEAM() == ATEAM)
				{
					AddObjectList(m_objectList[i]->GetPositionX() + ((float)std::rand() / (float)RAND_MAX), m_objectList[i]->GetPositionY(), OBJECT_SCOURGE, m_objectList[i]->GetMyTEAM()); //\dhfb
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
bool SceneMgr::AttackBoundaryCheck(Object *a, Object *b)
{
	float AlowerXbound = 0.0f;
	float AlowerYbound = 0.0f;
	float AHighXbound = 0.0f;
	float AHighYbound = 0.0f;

	float BlowerXbound = 0.0f;
	float BlowerYbound = 0.0f;
	float BHighXbound = 0.0f;
	float BHighYbound = 0.0f;


	AHighXbound = a->GetPositionX() + a->GetSize() * 2.f;
	AHighYbound = a->GetPositionY() + a->GetSize() * 2.f;

	AlowerXbound = a->GetPositionX() - a->GetSize() * 2.f;
	AlowerYbound = a->GetPositionY() - a->GetSize() * 2.f;

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
	
	static int framecnt = 0;
	


	m_Renderer->DrawTexturedRect(0, 0, 0, 800, 0.8, 0.8, 0.8, 1, m_BakcGround, RenderLevel_BACKGROUND);
	m_Renderer->DrawTexturedRect(0,-300,0,200,1.0,1.0,1.0,1,m_MainImage,RenderLevel_GOD);
	//float elapsetime = (float)frametime * 0.00001f;

	if (isGameEnd == true)
	{
		m_Renderer->DrawTexturedRect(0, 0, 0, 800, 0.8, 0.8, 0.8, 1, m_GameOver, RenderLevel_GOD);
	}

	//m_ClimateAnimationTime += elapsetime *100.f;
	m_Renderer->DrawParticleClimate(1, 1, 0, 1, 1, 1, 1, 0.9, 0.1, -0.1, m_snow, m_Climate->m_BulletAnimationTime, RenderLevel_SKY);

	for (int i = 0; i < m_objectCnt; ++i)
	{
		if (m_objectList[i] != NULL)
		{
			//총알맞는거 그리기 
			if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER && m_objectList[i]->m_State == AI_DAMAGED_GUN)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), 50.f, m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_LifleEffect, m_objectList[i]->m_MutallsikAnimationTime, 0, 8, 1, RenderLevel_SKY);

			}
			//총알맞는거 그리기 
			if (m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[i]->m_State == AI_DAMAGED_GUN)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), 50.f, m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_LifleEffect, m_objectList[i]->m_MutallsikAnimationTime, 0, 8, 1, RenderLevel_SKY);

			}
			//총알맞는거 그리기 
			if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[i]->m_State == AI_DAMAGED_GUN)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), 50.f, m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_LifleEffect, m_objectList[i]->m_MutallsikAnimationTime, 0, 8, 1, RenderLevel_SKY);

			}
			//총알맞는거 그리기 
			if (m_objectList[i]->GetObjectType() == OBJECT_SCOURGE && m_objectList[i]->m_State == AI_DAMAGED_GUN)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), 50.f, m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_LifleEffect, m_objectList[i]->m_MutallsikAnimationTime, 0, 8, 1, RenderLevel_SKY);

			}

			if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[i]->GetMyTEAM() == ATEAM)
			{
				
				m_Renderer->DrawTexturedRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(),m_texCharacter, m_objectList[i]->m_RenderLevel);

				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY()+30,
					m_objectList[i]->GetPositionZ(), 50,10, 1,
					0, 0, m_objectList[i]->GetA(),m_objectList[i]->GetLife()/ MaxLife_BUILDING,RenderLevel_GOD);

			}/////////////////////////////////////ATeam SUBBUILNG
			else if (m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[i]->GetMyTEAM() == ATEAM)
			{

				m_Renderer->DrawTexturedRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_Spire, m_objectList[i]->m_RenderLevel);

				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 30,
					m_objectList[i]->GetPositionZ(), 50, 10, 1,
					0, 0, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_SUBBUILDING, RenderLevel_GOD);

			}
			else if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[i]->GetMyTEAM() == BTEAM)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_airCharacter, m_Command->m_CommandAnimationTime,0,2,1, m_objectList[i]->m_RenderLevel);
				//블루게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 30,
					m_objectList[i]->GetPositionZ(), 50, 10, 0,
					0, 1, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_BUILDING, RenderLevel_GOD);
			}//BTEAM SUBBUILDING
			else if (m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[i]->GetMyTEAM() == BTEAM)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_Barrack, m_Command->m_CommandAnimationTime, 0, 3, 1, m_objectList[i]->m_RenderLevel);
				//블루게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 30,
					m_objectList[i]->GetPositionZ(), 50, 10, 0,
					0, 1, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_SUBBUILDING, RenderLevel_GOD);
			}
			//이펙트 그리기 
			else if (m_objectList[i]->GetObjectType() == OBJECT_EFFECT )
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_MutalDeathEffect, m_objectList[i]->m_MutallsikAnimationTime, 0, 8, 1, m_objectList[i]->m_RenderLevel);
				
			}

			//스콜지 이펙트 그리기 
			else if (m_objectList[i]->GetObjectType() == OBJECT_SCOURGEEFFECT)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_ScourgeEffect, m_objectList[i]->m_MutallsikAnimationTime, 0, 5, 1, m_objectList[i]->m_RenderLevel);

			}
			//스콜지 이펙트 그리기 
			else if (m_objectList[i]->GetObjectType() == OBJECT_MARINEEFFECT)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_MarineEffect, m_objectList[i]->m_MutallsikAnimationTime, 0, 8, 1, m_objectList[i]->m_RenderLevel);

			}
		
			else if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER&& m_objectList[i]->GetMyTEAM() == ATEAM)
			{

				/*m_Renderer->DrawSolidRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_objectList[i]->m_RenderLevel);*/

				//에니메이션 추가
				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(),m_CharaterAnimation,0, m_objectList[i]->m_MutallsikAnimationTime,1,5, m_objectList[i]->m_RenderLevel);

				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 20,
					m_objectList[i]->GetPositionZ(), 50, 10, 1,
					0, 0, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_CHARACTER, RenderLevel_GOD);
			}
			// 스콜지 추가 
			else if (m_objectList[i]->GetObjectType() == OBJECT_SCOURGE&& m_objectList[i]->GetMyTEAM() == ATEAM)
			{

				/*m_Renderer->DrawSolidRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
				m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
				m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_objectList[i]->m_RenderLevel);*/

				//에니메이션 추가
				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_Scourge, 0, m_objectList[i]->m_MutallsikAnimationTime, 1, 5, m_objectList[i]->m_RenderLevel);

				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 20,
					m_objectList[i]->GetPositionZ(), 50, 10, 1,
					0, 0, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_Scourege, RenderLevel_GOD);
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
			else if (m_objectList[i]->GetObjectType() == OBJECT_MARINE&& m_objectList[i]->GetMyTEAM() == BTEAM)
			{

				m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(),m_Marine,1, m_objectList[i]->m_MutallsikAnimationTime,17,13 ,m_objectList[i]->m_RenderLevel);
				//레드게이지
				m_Renderer->DrawSolidRectGauge(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY() + 20,
					m_objectList[i]->GetPositionZ(), 50, 10, 0,
					0, 1, m_objectList[i]->GetA(), m_objectList[i]->GetLife() / MaxLife_MARINE, RenderLevel_GOD);


			}

		
			else
			{
				if (m_objectList[i]->GetObjectType() == OBJECT_BULLET) //////////////////////paticle
				{
					m_Renderer->DrawParticle(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
						m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize() *2.0f, m_objectList[i]->GetR(),
						m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), -0.1f*m_objectList[i]->m_Vx, -0.1f*m_objectList[i]->m_Vy, m_Paticle, m_objectList[i]->m_BulletAnimationTime,RenderLevel_PARTICLE);

				}
					//에니메이션 추가
					m_Renderer->DrawTexturedRectSeq(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
						m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
						m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_MutalBullet, m_objectList[i]->m_MutallsikAnimationTime,0, 1, 10, m_objectList[i]->m_RenderLevel);
				
			}
		}
	}
	
	m_Renderer->DrawText(-20, 70, GLUT_BITMAP_TIMES_ROMAN_24, ((float)std::rand() / ((float)RAND_MAX/2)), ((float)std::rand() / ((float)RAND_MAX / 2)), ((float)std::rand() / ((float)RAND_MAX / 2)), "Stage 1");

}
void SceneMgr::CollisionCheckList()
{
	static bool isShaking = false;
	int collisionCount = 0;

	m_Renderer->SetSceneTransform(0.0f, 0.f, 1, 1);
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
						//불릿과 서브빌딩
						if (m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[j]->GetObjectType() == OBJECT_BULLET)
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
						//에로우와 서브빌딩   나중에 요거 조건 묶어서 함수로 빼고 싶다 ..;;;
						if (m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[j]->GetObjectType() == OBJECT_ARROW)
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
						//서브빌딩과캐릭터
						if (m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[j]->GetObjectType() == OBJECT_CHARACTER)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
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
								//if (isShaking == false)
								//{
								//	//m_Renderer->SetSceneTransform(-50.0f, 0.f, 1, 1);
								//}
								//m_Renderer->SetSceneTransform(50.0f, 0.f, 1, 1);
							}
							
							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}

						//서브빌딩과스콜지
						if (m_objectList[i]->GetObjectType() == OBJECT_SUBBUILDING && m_objectList[j]->GetObjectType() == OBJECT_SCOURGE)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
								m_Renderer->SetSceneTransform((rand() / (float)RAND_MAX - 0.5), 0.f, 1, 1);
								
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}
						//빌딩과스콜지
						if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[j]->GetObjectType() == OBJECT_SCOURGE)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
								m_Renderer->SetSceneTransform((rand() / (float)RAND_MAX - 0.5), 0.f, 1, 1);
								
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}
						//마린과스콜지
						if (m_objectList[i]->GetObjectType() == OBJECT_MARINE && m_objectList[j]->GetObjectType() == OBJECT_SCOURGE)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(0.0f);
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}
					}
					if (!AttackBoundaryCheck(m_objectList[i], m_objectList[j])) //어택 범위 마린 기준 오브젝투 //캐릭터
					{
						m_objectList[i]->m_State = AI_WALK;
						//m_objectList[j]->m_State = AI_WALK;	

					}
					else
					{
						if (m_objectList[i]->GetObjectType() == OBJECT_MARINE && m_objectList[j]->GetObjectType() == OBJECT_CHARACTER)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								//m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(m_objectList[j]->GetLife() - 0.1f); //뮤탈 체깎이는거 
								m_objectList[i]->m_State = AI_ATTACK;
								m_objectList[i]->m_BulletSound = true;
								m_objectList[j]->m_State = AI_DAMAGED_GUN;
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}
						//// 건물이랑 마린
						if (m_objectList[i]->GetObjectType() == OBJECT_MARINE && m_objectList[j]->GetObjectType() == OBJECT_BULDING)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								//m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(m_objectList[j]->GetLife() - 0.05f); //건물 체깎이는거 
								m_objectList[i]->m_State = AI_ATTACK;
								m_objectList[i]->m_BulletSound = true;
								m_objectList[j]->m_State = AI_DAMAGED_GUN;
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}
						//// 서브건물이랑 마린
						if (m_objectList[i]->GetObjectType() == OBJECT_MARINE && m_objectList[j]->GetObjectType() == OBJECT_SUBBUILDING)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								//m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(m_objectList[j]->GetLife() - 0.05f); //건물 체깎이는거 
								m_objectList[i]->m_State = AI_ATTACK;
								m_objectList[i]->m_BulletSound = true;
								m_objectList[j]->m_State = AI_DAMAGED_GUN;
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}
						//마린과 스콜지 
						if (m_objectList[i]->GetObjectType() == OBJECT_MARINE && m_objectList[j]->GetObjectType() == OBJECT_SCOURGE)
						{
							if (m_objectList[j]->GetMyTEAM() == m_objectList[i]->GetMyTEAM())
							{

							}
							else
							{
								//m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
								m_objectList[j]->SetLife(m_objectList[j]->GetLife() - 0.4f); //스콜지 체깎이는거 
								m_objectList[i]->m_State = AI_ATTACK;
								m_objectList[i]->m_BulletSound = true;
								m_objectList[j]->m_State = AI_DAMAGED_GUN;
							}

							//m_Scenesound->PlaySound(Sound_MutalDeath, false, 0.1f);
						}
					}
					
					
				}
			}
			
		}
	}


	//// 한번더 ..... 
	//for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	//{
	//	//collisionCount = 0;
	//	if (m_objectList[i] != NULL)
	//	{
	//		for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
	//		{
	//			if (i == j)
	//				continue;

	//			if (m_objectList[j] != NULL)
	//			{
	//				if (m_objectList[i]->GetObjectType() == OBJECT_MARINE && m_objectList[i]->m_State == AI_ATTACK && m_objectList[j]->GetObjectType() == OBJECT_CHARACTER)
	//				{
	//					if (!AttackBoundaryCheck(m_objectList[i], m_objectList[j]))
	//					{
	//						m_objectList[i]->m_State = AI_WALK;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	
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