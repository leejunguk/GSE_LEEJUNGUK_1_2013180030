#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_Life = 100.f;
	m_LifeTime = 100000.f;
	m_objectTimer = 0.00000f;
	m_bulletLastTime = 0.f;
	m_ArrowLastTime = 0.f;
	m_ChracterLastTime = 0.f;
	m_AnimationFrame = 0;
	m_BulletAnimationTime = 0.f;
	m_CommandAnimationTime = 0.0f;

	


	

}
Object::Object(float x, float y,int objecttype)
{
	m_bulletLastTime = 0.f;
	m_ArrowLastTime = 0.f;
	m_objectTimer = 0.00000f;
	m_ChracterLastTime = 0.f;
	m_AnimationFrame = 0;
	m_BulletAnimationTime = 0.f; 
	m_CommandAnimationTime = 0.0f;
	if (objecttype == OBJECT_BULDING)
	{
		m_type = OBJECT_BULDING;
		m_x = 0, m_y = 0;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1,1,1,1);
		m_LifeTime = 100000.f;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_SUBBUILDING)
	{
		m_type = OBJECT_SUBBUILDING;
		m_x = x, m_y = y;
		m_Life = 400.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 1, 1);
		m_LifeTime = 100000.f;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_EFFECT)
	{
		m_type = OBJECT_EFFECT;
		m_x = x, m_y = y;
		m_Life = 100.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 1;
		m_a = 1;
		SetRGBA(1, 1, 1, 1);
		m_LifeTime = 0.015f;  //EffectTime
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_SCOURGEEFFECT)
	{
		m_type = OBJECT_SCOURGEEFFECT;
		m_x = x, m_y = y;
		m_Life = 100.f;
		m_Speed = 0.f;
		m_size = 50.f;
		m_r = 1;
		m_g = 1;
		m_b = 1;
		m_a = 1;
		SetRGBA(1, 1, 1, 1);
		m_LifeTime = 0.010f;  //EffectTime
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_MARINEEFFECT)
	{
		m_type = OBJECT_MARINEEFFECT;
		m_x = x, m_y = y;
		m_Life = 100.f;
		m_Speed = 0.f;
		m_size = 20.f;
		m_r = 1;
		m_g = 1;
		m_b = 1;
		m_a = 1;
		SetRGBA(1, 1, 1, 1);
		m_LifeTime = 0.010f;  //EffectTime
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER)
	{
		m_type = OBJECT_CHARACTER;
		
		m_Life = 100.f;
		m_Speed = 300.f;
		m_size = 100.f;
		m_r = 1.f;
		m_g = 1.f;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_BULLET)
	{
		m_type = OBJECT_BULLET;
	
		m_Life = 15.f;
		m_Speed = 600.f;
		m_size = 4.f;
		m_r = 1.f;
		m_g = 0;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_BULLET;
		return;
	}
	else if (objecttype == OBJECT_ARROW)
	{
		m_type = OBJECT_ARROW;

		m_Life = 10.f;
		m_Speed = 100.f;
		m_size = 4.f;
		m_r = 0;
		m_g = 1.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_ARROW;
		return;
	}
	
	
	

}

Object::Object(float x, float y, int objecttype,int TeamNumber)
{
	m_objectTimer = 0.00000f;
	m_chracterTimer = 0.000000f;
	m_myFriend = TeamNumber;
	m_bulletLastTime = 0.f;
	m_ArrowLastTime = 0.f;
	m_ChracterLastTime = 0.f;
	m_AnimationFrame = 0;
	m_BulletAnimationTime = 0.f;
	m_CommandAnimationTime = 0.0f;
	if (objecttype == OBJECT_BULDING && TeamNumber == ATEAM)
	{
		m_type = OBJECT_BULDING;
		m_x = x, m_y = y;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 0, 1);
		m_LifeTime = 100000.f;
		m_TeamNumber = ATEAM;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_BULDING && TeamNumber == BTEAM)
	{
		m_type = OBJECT_BULDING;
		m_x = x, m_y = y;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 0, 1);
		m_LifeTime = 100000.f;
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_SUBBUILDING&& TeamNumber == BTEAM)
	{
		m_type = OBJECT_SUBBUILDING;
		m_x = x, m_y = y;
		m_Life = 400.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 1, 1);
		m_LifeTime = 100000.f;
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_SUBBUILDING&& TeamNumber == ATEAM)
	{
		m_type = OBJECT_SUBBUILDING;
		m_x = x, m_y = y;
		m_Life = 400.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 1, 1);
		m_LifeTime = 100000.f;
		m_TeamNumber = ATEAM;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER && TeamNumber == ATEAM)
	{
		m_type = OBJECT_CHARACTER;

		m_Life = 100.f;
		m_Speed = 300.f;
		m_size = 100.f;
		m_r = 1.f;
		m_g = 0.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = ATEAM;
		m_Birth = true;

		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER && TeamNumber == BTEAM)
	{
		m_type = OBJECT_CHARACTER;

		m_Life = 100.f;
		m_Speed = 300.f;
		m_size = 100.f;
		m_r = 0.f;
		m_g = 0.f;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_CHARACTER;
		
		return;
	}
	else if (objecttype == OBJECT_MARINE && TeamNumber == BTEAM)
	{
		m_type = OBJECT_MARINE;

		m_Life = 40.f;
		m_Speed = 500.f;
		m_size = 30.f;
		m_r = 1.f;
		m_g = 0.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 0.f;
		m_Vy = 1.f;
		m_BulletSound = true;
		m_TeamNumber = BTEAM;
		m_Birth = true;
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_BULLET && TeamNumber == ATEAM)
	{
		m_type = OBJECT_BULLET;

		m_Life = 15.f;
		m_Speed = 600.f;
		m_size = 4.f;
		m_r = 1.f;
		m_g = 0;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_BULLET;
		m_TeamNumber = ATEAM;
		return;
	}
	else if (objecttype == OBJECT_BULLET && TeamNumber == BTEAM)
	{
		m_type = OBJECT_BULLET;

		m_Life = 15.f;
		m_Speed = 600.f;
		m_size = 4.f;
		m_r = 0.f;
		m_g = 0;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_BULLET;
		return;
	}
	else if (objecttype == OBJECT_ARROW&& TeamNumber == ATEAM)
	{
		m_type = OBJECT_ARROW;

		m_Life = 10.f;
		m_Speed = 100.f;
		m_size = 4.f;
		m_r = 0.5f;
		m_g = 0.2f;
		m_b = 0.7;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = ATEAM;
		m_RenderLevel = RenderLevel_ARROW;
		return;
	}
	else if (objecttype == OBJECT_ARROW&& TeamNumber == BTEAM)
	{
		m_type = OBJECT_ARROW;

		m_Life = 10.f;
		m_Speed = 100.f;
		m_size = 4.f;
		m_r = 1.0f;
		m_g = 1.0f;
		m_b = 0.0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_ARROW;
		return;
	}
	else if (objecttype == OBJECT_SCOURGE && TeamNumber == ATEAM)
	{
		m_type = OBJECT_SCOURGE;

		m_Life = 50.f;
		m_Speed = 700.f;
		m_size = 50.f;
		m_r = 1.f;
		m_g = 0.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = ATEAM;
		m_Birth = true;

		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}


}



Object::~Object()
{

	//if (m_Life < 0)
	//	delete this;
}
void Object::PositionUpdate(float xvector, float yvector, DWORD time)
{
	float elapsetime = (float)time * 0.00001f;
	static int framecnt = 0; 

	m_bulletLastTime += elapsetime;
	m_ArrowLastTime += elapsetime;
	m_ChracterLastTime += elapsetime;
	m_AnimationTime += elapsetime;

	m_BulletAnimationTime += elapsetime *30.f;

	m_CommandAnimationTime += elapsetime *500.0f;

	m_MutallsikAnimationTime += elapsetime *500.f;

	m_LifeTime -= elapsetime;
	
	/*if (100.f < m_BulletAnimationTime)
		m_BulletAnimationTime = 0;*/



	if (m_type == OBJECT_MARINE && m_State == AI_ATTACK)
	{
		////마린공격할때 소리내기 
		//if (m_objectList[i]->m_State == AI_ATTACK&& m_objectList[i]->GetObjectType() == OBJECT_MARINE && m_objectList[i]->m_BulletSound == true)
		//{
		//	m_effectSound->PlaySound(Sound_MainreFire, false, 0.1f);
		//	m_objectList[i]->m_BulletSound = false;
		//	Sound_MainreFire = m_effectSound->CreateSound("./Dependencies/SoundSamples/MarineFire.mp3");
		//}
		m_x = m_x;
		m_y = m_y;

	}
	else
	{
		m_x = m_x + m_Vx *(xvector * elapsetime) * m_Speed;
		m_y = m_y + m_Vy *(yvector * elapsetime) * m_Speed;
	}

	if (16 < m_AnimationFrame)
		m_AnimationFrame = 1;
	if (0.0015f < m_AnimationTime)
	{
		m_AnimationFrame++;
		m_AnimationTime = 0.f;
	}
	//framecnt++;

	//m_size = 20 * sin(m_x);
	//m_size = 20;

	

	if ( m_x > SIZEWINDOWWIDTH /2)
	{
		m_Vx = -m_Vx;
		
	}
	if (m_x < -(SIZEWINDOWWIDTH / 2))
	{
		m_Vx = -m_Vx;
		
	}
	if (m_y > SIZEWINDOWHEIGHT/2)
	{
		m_Vy = -m_Vy;
		
	}
	if (m_y < -(SIZEWINDOWHEIGHT / 2))
	{
		m_Vy = -m_Vy;
		
	}
	//// Marine만해당 
	if (m_type == OBJECT_MARINE)
	{
		/*if (m_y > 50 && m_y <100  && 40< m_x  && m_x<180)
		{
			m_Vx = -1.2f*m_Vx;
			m_Vy = 0;

		}
		if (m_y > 50 && m_y <100 && -40> m_x  && m_x>-180)
		{
			m_Vx = -m_Vx;

		}*/
		if (m_y > -100 && -40> m_x  && m_x>-105)
		{
			m_Vx = 1;

		}
		else if (m_y > -100 && -105> m_x  && m_x>-180)
		{
			m_Vx = -1;

		}
		else if (m_y > -100 && 40< m_x  && m_x<105)
		{
			m_Vx = -1;

		}
		else if (m_y > -100 && 105< m_x  && m_x<180)
		{
			m_Vx = 1;

		}
		else
		{
			m_Vx = 0;
		}
	}
	
}